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

require "util"

-- Singleton shortcuts
theWorld = World_GetInstance()
theTagList = TagCollection_GetInstance()
theSwitchboard = Switchboard_GetInstance()
theCamera = Camera_GetInstance()
theSound = SoundDevice_GetInstance()
theTuning = Tuning_GetInstance()
thePrefs = Preferences_GetInstance()
if (ANGEL_MOBILE == false) then
  theControllerManager = ControllerManager_GetInstance()
  sysLog = CompoundLog_GetSystemLog()
end

-- Input accessors
if (ANGEL_MOBILE == false) then
  theController = theControllerManager:GetController()
  controllerOne = theController
  controllerTwo = theControllerManager:GetController(1)
end

-- Convenience functions
function reset()
	theWorld:ResetWorld()
end

function tune(varName, newVal)
  if (type(newVal) == "table") then
    theTuning:SetVector(varName, newVal)
  elseif (type(newVal) == "number") then
    theTuning:SetFloat(varName, newVal)
  else
    theTuning:SetString(varName, tostring(newVal))
  end
  
  theTuning:AddToRuntimeTuningList(varName)
end

-- COLOR_MAP and paint form a convenience function for setting a color and tag
--  at the same time. More importantly, it's a good goldspike to ensure that
--  the scripting <-> engine glue is functioning. (Note that it passes a 
--  a table instead of a Color object, stress testing the input typemaps.)
COLOR_MAP = {
  white     = {1.0, 1.0, 1.0},
  black     = {0.0, 0.0, 0.0},
  red       = {1.0, 0.0, 0.0},
  green     = {0.0, 1.0, 0.0},
  blue      = {0.0, 0.0, 1.0},
  yellow    = {1.0, 1.0, 0.0},
  magenta   = {1.0, 0.0, 1.0},
  cyan      = {0.0, 1.0, 1.0},
  purple    = {0.5, 0.0, 1.0},
  orange    = {1.0, 0.5, 0.0},
}

function paint(a, colorName)
  colTable = COLOR_MAP[colorName]
  
  if (colTable == nil) then
    print("No color " .. colorName .. " defined.")
    return
  end
  
  for name, val in pairs(COLOR_MAP) do
    a:Untag(name)
  end
  a:SetColor(colTable)
  a:Tag(colorName)
end

addClassMethod("Actor", "Paint", paint)
