------------------------------------------------------------------------------
-- Copyright (C) 2008-2014, Shane Liesegang
-- All rights reserved.
-- 
-- Redistribution and use in source and binary forms, with or without 
-- modification, are permitted provided that the following conditions are met:
-- 
--     * Redistributions of source code must retain the above copyright 
--       notice, this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright 
--       notice, this list of conditions and the following disclaimer in the 
--       documentation and/or other materials provided with the distribution.
--     * Neither the name of the copyright holder nor the names of any 
--       contributors may be used to endorse or promote products derived from 
--       this software without specific prior written permission.
-- 
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
-- AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
-- IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
-- ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
-- LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
-- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
-- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
-- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
-- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
-- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
-- POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------

require "lfs"
require "util"

TUNING_FILE_PATH = "Config/tuning.lua"

local angelActorDefs = {}
setmetatable(angelActorDefs, {__index = _G})

local angelLevelDefs = {}

local configUpdateTime = nil


-- Load tuning variable definitions from Config/tuning.lua.
function LoadTuningVariables()
  local loadedTuning = {}
  
  loadFileIn(TUNING_FILE_PATH, loadedTuning)

  for var_name, data in pairs(loadedTuning) do
    -- Don't load this from the file if we've been tuning it from the console.
    if not (theTuning:IsRuntimeTuned(var_name)) then
      if (data.type == "float") then
        theTuning:SetFloat(var_name, data.value)
      elseif (data.type == "int") then
        theTuning:SetInt(var_name, data.value)
      elseif (data.type == "string") then
        theTuning:SetString(var_name, data.value)
      elseif (data.type == "vector") then
        theTuning:SetVector(var_name, data.value)
      else
        print("WARNING: " .. var_name .. " of unknown variable type.")
      end
    end
  end
end

-- Saves the current tuning variables back to the tuning.lua file, appending
--  any new ones that have been declared.
function SaveTuningVariables()
  local truth = {"true", "1", "one", "yes", "on", "t"}
  local tabDataPat = "(VARNAME[%s*]=[%s*]%{)(.*)(%})"  -- finds tables of given names
  local valDataPat = "(value[%s*]=[%s*])([^%s,]*)([,%s]*)" -- gets the data from those tables
  local vecPat     = "^%{%s*[%d%.]+%s*,%s*[%d%.]+%s*%}$" -- tells if a string is expressing a Vector2
  
  -- load the file's data again, for comparison
  local fileTuning = {}
  
  loadFileIn(TUNING_FILE_PATH, fileTuning)
  local f = assert(io.open(TUNING_FILE_PATH, "r"))
  local fileString = f:read("*all")
  f:close()
  
  for _, v in pairs(theTuning:GetVariables()) do
    if (fileTuning[v] ~= nil) then
      -- already in the config file; find and change
      local readonly = false
      
      -- first check to see if we're readonly
      if (fileTuning[v].readonly ~= nil) then
        if (type(fileTuning[v].readonly) == "boolean") then
          readonly = fileTuning[v].readonly
        else
          for _, truthtest in pairs(truth) do
            if (truthtest == fileTuning[v].readonly) then
              readonly = true
            end
          end
          if (fileTuning[v].readonly == 1) then
            readonly = true
          end
        end
      end
      
      -- skip this variable if it's readonly
      if (readonly ~= true) then
        -- extract existing data
        local mtabdata = tabDataPat:gsub("VARNAME", v)
        local prefix, data, postfix = fileString:match(mtabdata)
        
        local newVal = nil
        if     (fileTuning[v].type == "vector") then
          newVal = theTuning:GetVector(v)
        elseif (fileTuning[v].type == "float") then
          newVal = theTuning:GetFloat(v)
        elseif (fileTuning[v].type == "int") then
          newVal = theTuning:GetInt(v)
        elseif (fileTuning[v].type == "string") then
          newVal = theTuning:GetString(v)
        end
        
        -- we've got a new value, and the variable is not readonly
        if (newVal ~= nil) then
          local before, val, after = data:match(valDataPat)
          local inString = before .. val .. after
          local outString = before
          if     (fileTuning[v].type == "vector") then
            outString = outString .. tostring(newVal)
          elseif (fileTuning[v].type == "float") then
            outString = outString .. string.format("%f", newVal)
          elseif (fileTuning[v].type == "int") then
            outString = outString .. string.format("%i", newVal)
          elseif (fileTuning[v].type == "string") then
            outString = outString .. tostring(newVal)
          end
          outString = outString .. after
          local oldValData = prefix .. data .. postfix
          local newValData = prefix .. data:gsub(inString, outString) .. postfix
          local _begin, _end = fileString:find(oldValData, 1, true)
          fileString = fileString:sub(1, _begin-1) .. newValData .. fileString:sub(_end+1, -1)
        else
          -- wtf, it's not any kind of acceptable tuning variable
        end
      end
    else
      -- not in the config file; add to the end
      local valString = theTuning:GetString(v)
      local valType = nil
      -- see if we can make a vector from it
      if (valString:match(vecPat) ~= nil) then
        valType = "vector"
      end
      -- or coerce it into a number
      if (tonumber(valString) ~= nil) then
        valType = "float"
        -- do we care about seeing if it should be an int? I'm going to go ahead and say no...
      end
      -- oh well, it's just a string then
      if (valType == nil) then
        valType = "string"
        valString = '"' .. valString .. '"'
      end
      local outString = string.format("\n\n%s = {\n  type = \"%s\", \n  value = %s, \n}\n", v, valType, valString)
      fileString = fileString .. outString
    end
  end
  
  -- write out the changes
  f = assert(io.open(TUNING_FILE_PATH, "w"))
  f:write(fileString)
  f:close()
end

-- Load actor definitions from Config/ActorDef/*.lua.
-- 
-- Instantiate an Actor from a definition with Actor.Create(<name>)
-- 
-- If called a second time, it will reload the file, so the definitions
-- will be updated, but any existing Actors that were created from them
-- remain the same. 
function ReloadActorDefs()
  cd = "Config/ActorDef/"
  for f in lfs.dir(cd) do
    if (not f:starts(".") and f:ends(".lua")) then
      loadFileIn(cd .. f, angelActorDefs)
    end
  end
end

-- Apply a configuration value to an Actor.
-- 
-- We check for different forms the name might take:
--   If the config file listed "display_name", we would try to call
--   SetDisplayName, DisplayName, and display_name. Once one is found, 
--   we stop trying. An error prints if no suitable match is found. 
function _ApplyToActor(actor, config, value)
  -- generate potential names
  local pieces = config:split("_")
  for i, piece in ipairs(pieces) do
    pieces[i] = piece:gsub("^%l", string.upper)
  end
  local camel_case_name = table.concat(pieces)
  local name_checks = {config, camel_case_name, "Set"..camel_case_name}
  
  -- see if any of those are in the actor's table
  local fname = nil
  for _, name in ipairs(name_checks) do
    if ("function" == type(actor[name])) then
      fname = name
      break
    end
  end
  
  -- call the function if we can
  if (nil == fname) then
    print( string.format("WARNING: No method or attribute found for %s, %s, or %s", table.unpack(name_checks)) )
  else
    actor[fname](actor, value)
  end
end

-- Instantiate an Actor from a previously loaded definition file.
--   
--   Returns the Actor -- it still has to be added to the World to 
--   receive Update and Render calls.
function Actor_Create(actor_type)
  local desc = angelActorDefs[actor_type]
  if (desc == nil) then
    print("ERROR: Actor definition " .. actor_type .. " not loaded.")
    return nil
  end
  local class_name = desc.class
  if (class_name == nil) then
    class_name = "Actor"
  end
  if (type(_G[class_name][".constructor"]) ~= "function") then
    print("ERROR: No class called " .. class_name .. " is available.")
    return nil
  end
  local a = _G[class_name]()
  
  for config, value in pairs(desc) do
    if (config ~= "class") then
      _ApplyToActor(a, config, value)
    end
  end
  
  return a
end

-- Instantiate an Actor and pass it back to the engine for use. 
--  
--  This is used internally by the engine so it can directly get
--  at Actors that it instantiates with Create calls. (Otherwise
--  we would have to jump through some hoops to find them in
--  memory.) You probably shouldn't call this directly.
--  NB: This function also disowns the Actor so Lua won't 
--  garbage-collect it. 
function Actor_CreateAndRegister(actor_type)
  a = Actor_Create(actor_type)
  Actor_SetScriptCreatedActor(a)
end

-- Instantiate and add all Actors described in a previously loaded
--   Level definition file.
--   
--   Call theWorld:ResetWorld() to remove all existing Actors beforehand
--   if you want to start over.
function LoadLevel(levelName)
  local levelDef = angelLevelDefs[levelName]
  if (levelDef == nil) then
    print("Level definition " .. levelName .. " not loaded.")
    return
  end
  
  for name, desc in pairs(levelDef) do
    local a = nil

    if (desc["def"] ~= nil and desc["class"] ~= nil) then
      print("Actor " .. name .. " has both class and definition attributes. Invalid.")
      return
    end

    if (desc["def"] ~= nil) then
      a = Actor_Create(desc["def"])
    elseif (desc["class"]~= nil and type(_G[desc["class"]][".constructor"]) == "function") then
      a = _G[desc["class"]]()
    else
      print("Actor " .. name .. " has no definition specified.")
    end

    if (a ~= nil) then
      a:SetName(name)
      local layer = tonumber(desc["layer"])
      if (layer == nil) then
        layer = 0
      end
      for config, value in pairs(desc) do
        if (config ~= "def" and config ~= "class") then
          _ApplyToActor(a, config, value)
        end
      end
      theWorld:Add(a, layer)
      local mt = getmetatable(a)
      if (type(mt[".fn"]["InitPhysics"]) == "function") then
        a:InitPhysics()
      end
    end
  end
end

-- Loads all levels in the Config/Level directory into the working
--   definitions list.
-- 
--   Can be called again to reload all the level definitions.
function ReloadLevelDefs()
  ld = "Config/Level/"
  for f in lfs.dir(ld) do
    if (not f:starts(".") and f:ends(".lua")) then
      levelName = f:sub(1, f:find(".lua")-1)
      angelLevelDefs[levelName] = {}
      setmetatable(angelLevelDefs[levelName], {__index = _G})
      loadFileIn(ld .. f, angelLevelDefs[levelName])
    end
  end
end


