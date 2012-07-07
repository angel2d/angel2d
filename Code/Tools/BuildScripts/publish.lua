------------------------------------------------------------------------------
-- Copyright (C) 2008-2012, Shane Liesegang
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

require "angel_build"
require "lfs"
require "pl"

local args = lapp [[
  Packages a game for easy distribution. 
    -i,--input_directory (string)  Project directory
    -o,--output_directory  (string)  Where the packaged game should go
    -v,--vcpath (string)  Where Visual Studio is installed
    -g,--gamename (default ClientGame.exe)  Name of the final game
  ]]

lfs.chdir(args.input_directory)

local config = {}

if (path.exists("build.lua")) then
  loadFileIn("build.lua", config)
end

if (config.game_info == nil) then
  config.game_info = {}
end
if (config.game_info.name == nil) then
  config.game_info.name = path.splitext(args.gamename)
end

local bits_path = path.join(args.output_directory, "bits")
if (not path.exists(bits_path)) then
  makedirs(bits_path)
end

conf_path = fulljoin(args.input_directory, "..", "Angel", "AngelConfig.h")
t = io.open(conf_path, "r")
tr = t:read("*all")
t:close()

disable_fmod = tonumber(tr:match("\n%s*#define%s+ANGEL_DISABLE_FMOD%s+([0-9]+)"))
disable_devil = tonumber(tr:match("\n%s*#define%s+ANGEL_DISABLE_DEVIL%s+([0-9]+)"))

local files_ex = {}
local files_base = {"GameInfo.txt", "Attributions.txt"}
local directories = {"Resources", "Config", "Logs"}

if (disable_fmod == 1) then
  table.insert(files_ex, "OpenAL32.dll")
else
  table.insert(files_ex, "fmodex.dll")
end

if (disable_devil ~= 1) then
  table.insert(files_ex, "DevIL.dll")
  table.insert(files_ex, "ILU.dll")
  table.insert(files_ex, "ILUT.dll")
end

for _, file_ex in pairs(files_ex) do
  copyfile(path.join(args.input_directory, file_ex), path.join(bits_path, file_ex))
end
for _, file_base in pairs(files_base) do
  copyfile(fulljoin(args.input_directory, "Documentation", file_base), path.join(args.output_directory, file_base))
end
for _, directory in pairs(directories) do
  recursive_copy(path.join(args.input_directory, directory), path.join(bits_path, directory))
end

att_path = fulljoin(args.input_directory, "..", "Tools", "BuildScripts", "Attributions")
correct_attributions(path.join(args.output_directory, "Attributions.txt"), att_path, disable_devil, disable_fmod)

copyfile(fulljoin(args.input_directory, "Release", args.gamename), path.join(bits_path, config.game_info.name .. ".exe"))


local kicker_exe = fulljoin(args.output_directory, config.game_info.name .. ".exe")
local kicker_dir = fulljoin(args.input_directory, "..", "Angel", "Win", "WindowsAngelKicker")
local kicker_source_fname = "WindowsAngelKicker.cpp"
local kicker_config = "Release" 
local kicker_built = fulljoin(kicker_dir, kicker_config, "WindowsAngelKicker.exe")

local rebuild_needed = false
if (path.exists(kicker_exe) ~= true) then
  rebuild_needed = true
end

local kicker_files = {"angel.ico", "angel_small.ico"}
for _, kicker_file in pairs(kicker_files) do
  local src = fulljoin(args.input_directory, "platforms", "win", kicker_file)
  local dst = fulljoin(kicker_dir, kicker_file)
    
  if ( (path.exists(dst) ~= true) or (lfs.attributes(dst, "modification") < lfs.attributes(src, "modification") ) ) then
    rebuild_needed = true
    copyfile(src, dst)
  end
end

lfs.chdir(kicker_dir)

local build_file = fulljoin(args.input_directory, "build.lua")

if (path.exists(kicker_source_fname) ~= true) then
  rebuild_needed = true
  copyfile("WindowsAngelKicker.cpp.orig", kicker_source_fname)
end

if ((path.exists(build_file) ~= true) or (lfs.attributes(kicker_source_fname, "modification") < lfs.attributes(build_file, "modification"))) then
  rebuild_needed = true
  local kicker_file = io.open(kicker_source_fname, "r")
  local kicker_source = kicker_file:read("*all")
  kicker_file:close()
  
  local newstring = string.format("\n#define ANGEL_EXE_NAME \"%s.exe\"", config.game_info.name)
  kicker_source = kicker_source:gsub("\n#define%s+ANGEL_EXE_NAME%s+[^\n]+", newstring)
  kicker_file = io.open(kicker_source_fname, "w")
  kicker_file:write(kicker_source)
  kicker_file:close()
end

if (rebuild_needed) then
  print("Rebuilding kicker...")
  local exec_string = string.format("echo off & \"%sbin\\vcvars32.bat\" > nul & msbuild WindowsAngelKicker.sln /p:Configuration=%s /nologo /noconsolelogger /v:quiet > nul", args.vcpath, kicker_config)
  
  os.execute(exec_string)
end

copyfile(kicker_built, kicker_exe)

