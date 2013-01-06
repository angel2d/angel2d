------------------------------------------------------------------------------
-- Copyright (C) 2008-2013, Shane Liesegang
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
require "io"

if (package.path == nil) then
  package.path = ""
end
local mydir = debug.getinfo(1,"S").source:match[[^@?(.*[\/])[^\/]-$]]
if (mydir == nil) then
  mydir = "."
end
package.path = mydir .. "?.lua;" .. package.path
package.path = package.path .. ";" .. mydir .. "lua-lib/penlight-1.0.2/lua/?/init.lua"
package.path = package.path .. ";" .. mydir .. "lua-lib/penlight-1.0.2/lua/?.lua"
package.path = package.path .. ";" .. mydir .. "lua-lib/penlight-1.0.2/lua/pl/?.lua"

require "pl"

-- whether this file is hidden and should thus be ignored
--  (mostly used for skipping .svn directories)
function _isdotfile(filePath)
  if (path.basename(filePath):sub(1,1) == ".") then
    return true
  else
    return false
  end
end

-- because the penlight copy function doesn't preserve case on windows. :-(
function copyfile(from, to)
  if (path.is_windows) then
    os.execute(string.format('copy /Y "%s" "%s" > nul', from, to))
  else
    dir.copyfile(from, to, true)
  end
end

-- this and makedirs blatantly copied from penlight, but without
--  normalizing the case on Windows, because that is dumb
local dirpat
if path.is_windows then
    dirpat = '(.+)\\[^\\]+$'
else
    dirpat = '(.+)/[^/]+$'
end

-- makes a path recursively
--  (there was some good reason at some point to re-implement this here instead
--  of using the penlight version)
function makedirs(p)
  -- windows root drive case
  if(p:find('^%a:$')) then
    return true
  end

  if not path.isdir(p) then
    local subp = p:match(dirpat)
    if not (makedirs(subp)) then
      io.stderr:write("ERROR: Cannot create " .. subp .. "\n")
      os.exit(1)
    end
    return lfs.mkdir(p)
  else
    return true
  end
end

-- recursively copy a directory and its files from src to dst
function recursive_copy(src, dst)
  if (_isdotfile(src)) then
    -- print("Skipping " .. path.basename(src))
    return
  end
  
  if (not path.exists(src)) then
    return
  end

  if (not path.exists(dst)) then
    makedirs(dst)
  end
  
  local names = dir.getfiles(src, "")
  for _, name in pairs(names) do
    if (not _isdotfile(name)) then
      name = path.basename(name)
      local srcname = fulljoin(src, name)
      local dstname = fulljoin(dst, name)
      copyfile(srcname, dstname)
    end
  end
  
  local dirs = dir.getdirectories(src, "")
  for _, dirname in pairs(dirs) do
    dirname = path.basename(dirname)
    local srcname = fulljoin(src, dirname)
    local dstname = fulljoin(dst, dirname)
    recursive_copy(srcname, dstname)
  end
end

-- split a string into a table along a single separator character
function string:split(sep)
  local sep, fields = sep or " ", {}
  local pattern = string.format("([^%s]+)", sep)
  self:gsub(pattern, function(c) fields[#fields+1] = c end)
  return fields
end

--trim leading and following whitespace from a string
function string:trim()
  return self:match("^%s*(.-)%s*$")
end

-- <sigh> the penlight library only joins paths one at a time. :-(
--  (this also corrects for its inability to deal with quoted paths)
function fulljoin(...)
  local arg = {...}
  local isQuoted = false
  -- check to see if any of the paths have quotes in them
  for i, v in ipairs(arg) do
    if (v:find('"')) then
      isQuoted = true
      arg[i] = v:gsub('"', '')
    end
  end

  local for_return = ""
  for i, v in ipairs(arg) do
    for_return = path.join(for_return, v)
  end

  if (isQuoted) then
    for_return = '"' .. for_return .. '"'
  end
  return for_return
end

-- load a file using the passed table as its environment
function loadFileIn(filename, environment)
  if (environment == nil) then
    print "ERROR: Cannot load into nil environment."
  end
  local f, err = loadfile(filename, "bt", environment)
  if (f == nil) then
    print(err)
    return
  end
  return f()
end

-- get the absolute path to the current file
function get_file_location()
  local file_location = debug.getinfo(2,'S').source
  if (file_location:sub(1,1) == "@") then
    file_location = file_location:sub(2, -1)
  end
  return (path.dirname(path.abspath(file_location)))
end

-- correct a given attributions file to claim the used libraries
function correct_attributions(filename, att_dir, disable_devil, disable_fmod)
  local function append_to(file_handle, newfile)
    local newfile_handle = assert(io.open(newfile, "r"))
    local newtext = newfile_handle:read("*all")
    newfile_handle:close()
    file_handle:write(newtext)
  end
  
  local lgpl = false
  
  local f = assert(io.open(filename, "a+"))
  append_to(f, fulljoin(att_dir, "base-angel.txt"))
  if (disable_devil ~= 1) then
    append_to(f, fulljoin(att_dir, "devil-libs.txt"))
    lgpl = true
  end
  if (disable_fmod == 1) then
    append_to(f, fulljoin(att_dir, "ogg-vorbis.txt"))
    if (path.is_windows) then
      append_to(f, fulljoin(att_dir, "openal-soft.txt"))
      lgpl = true
    end
  else
    append_to(f, fulljoin(att_dir, "fmod.txt"))
  end
  
  if (lgpl) then
    append_to(f, fulljoin(att_dir, "lgpl.txt"))
  end
  
  f:close()
end

-- make sure that the installed SWIG is up to date
function check_swig_version(path)
  local f = assert(io.popen(path.." -version", 'r'))
  local s = assert(f:read('*a'))
  f:close()

  version = s:match("\n%s*SWIG Version%s+([^%s]*)")
  vparts = version:split(".")

  -- check that we're at at least 2.0.6
  local old = false
  if (tonumber(vparts[1]) < 2) then
    old = true
  elseif ((tonumber(vparts[2]) < 1) and (tonumber(vparts[3]) < 6)) then
    old = true
  end

  if (old) then
    io.stderr:write("ERROR: swig version "..version.." is too old for Angel; update to at least 2.0.6.\n")
    os.exit(1)
  end
end

-- find a local install of SWIG
function get_swig_path()
  if (path.is_windows) then
    -- we're on windows; use the distributed swig
    return "..\\swigwin-2.0.6\\swig.exe"
  end
  
  local ports_path = "/opt/local/bin/swig"
  if (path.exists(ports_path)) then
    -- this mac user has wisely installed swig from macports
    check_swig_version(ports_path)
    return ports_path
  end

  local brew_path = "/usr/local/Cellar/swig"
  local brew_swig_path = "/usr/local/bin/swig"
  if (path.exists(brew_path)) then
    -- THIS mac user prefers brew to macports. we can support that!
    check_swig_version(brew_swig_path)
    return brew_swig_path
  end

  -- check for other installed swig
  local f = assert(io.popen("which swig", 'r'))
  local s = assert(f:read('*a'))
  f:close()
  if (s == "") then
    io.stderr:write("ERROR: swig not found.\n")
    os.exit(1)
  end
  local other_path = s:gsub("\n" , "")
  check_swig_version(other_path)
  return other_path
end

function find_in_table(haystack, needle)
  for _,v in pairs(haystack) do
    if v == needle then
      return true
    end
  end
  return false
end

-- generate typemap inheritance for SWIG factories
function generate_typemaps(interface_directory, additional_defines)
  local swig = get_swig_path()
  local junkfile = fulljoin(interface_directory, "..", "..", "..", "Tools", "BuildScripts", "build_cache", "swigout.txt")
  local inheritance_file = ""
  if (find_in_table(additional_defines, "INTROGAME")) then
    inheritance_file = fulljoin(interface_directory, "inheritance_intro.i")
  else
    inheritance_file = fulljoin(interface_directory, "inheritance.i")
  end
  if (not path.exists(inheritance_file:gsub('"', ''))) then
    -- need to make sure we have at least a blank file for swig to include 
    --  when it runs to get the type data
    local inheritance_handle = assert(io.open(inheritance_file:gsub('"', ''), "w"))
    inheritance_handle:close()
  end
  local swig_options = ""
  if (additional_defines ~= nil) then
    swig_options = swig_options .. " -D" .. table.concat(additional_defines, " -D")
  end
  swig_options = swig_options .. " -c++ -lua -Werror -debug-typedef -I" .. interface_directory .. " -o " .. junkfile .. " " .. fulljoin(interface_directory, "angel.i")
  
  local exe_string = swig .. swig_options
  local f = assert(io.popen(exe_string, 'r'))
  local s = assert(f:read('*a'))
  f:close()
  
  local separator = "-------------------------------------------------------------"
  local class_data = {}
  local immediate_class_data = {}
  local class_pattern = "Type scope '(%w+)'"
  local inh_patterh = "Inherits from '(%w+)'"
  local splits = s:split(separator)
  for _, v in pairs(splits) do
    local _, _, class = v:find(class_pattern)
    if (class ~= nil) then
      local lines = v:split("\n")
      if (#lines == 1) then
        -- no inheritance here
      else
        immediate_class_data[class] = {}
        for i=1,#lines do -- skip the first line
          local _, _, base = lines[i]:find(inh_patterh)
          if (base ~= nil) then
            if (class_data[base] == nil) then
              class_data[base] = {}
            end
            table.insert(class_data[base], class)
            table.insert(immediate_class_data[class], base)
          end
        end
      end
    end
  end

  local sortf = function(class1, class2)
    local parents1 = immediate_class_data[class1]
    local parents2 = immediate_class_data[class2]
    if (parents1 == nil and parents2 == nil) then
      return false
    end
    if (parents1 ~= nil) then
      for _, p in pairs(parents1) do
        if (p == class2) then
          -- the second class is a parent of the first
          return true
        end
      end
    end
    return false
  end

  local out_strings = {}
  for base, descendants in pairs(class_data) do
    table.sort(class_data[base], sortf)
    table.insert(out_strings, "%factory("..base.."*, "..table.concat(descendants, ", ")..");")
  end
  table.sort(out_strings)

  local out_string = "%include <factory.i>\n\n" .. table.concat(out_strings, "\n")
  
  local out_file = assert(io.open(inheritance_file:gsub('"', ''), "r"))
  local current_file = out_file:read("*a")
  out_file:close()
  if (current_file ~= out_string) then
    out_file = assert(io.open(inheritance_file:gsub('"', ''), "w"))
    out_file:write(out_string)
    out_file:close()
  end
end

