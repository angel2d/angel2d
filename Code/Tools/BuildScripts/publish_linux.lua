------------------------------------------------------------------------------
-- Copyright (C) 2008-2011, Shane Liesegang
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
package.path = package.path .. ";" .. mydir .. "lua-lib/penlight-0.8/lua/?/init.lua"
package.path = package.path .. ";" .. mydir .. "lua-lib/penlight-0.8/lua/?.lua"

require "angel_build"
require "lfs"
require "pl.path"
require "pl.lapp"

local args = pl.lapp [[
  Packages a game for easy distribution. 
    -i,--input_directory (string)  Project directory
    -e,--executable_name (string)  Name of executable to grab
    -g,--gamename (default ClientGame)  Name of the final game
  ]]

TOOLS_PATH = fulljoin(args.input_directory, "..", "Tools", "LinuxBuildTools")
APPIMAGE_PATH = fulljoin(TOOLS_PATH, "AppImageKit-8")
APPIMAGE_EXE = fulljoin(APPIMAGE_PATH, "AppImageAssistant.appdir", "package")

if (pl.path.exists(fulljoin(APPIMAGE_PATH, "AppImageAssistant")) ~= true) then
  lfs.chdir(APPIMAGE_PATH)
  os.execute("make")
end

lfs.chdir(args.input_directory)

local config = {}
local libs_gotten = {}

function in_list(needle, haystack)
  for _, v in ipairs(haystack) do
    if (needle == v) then
      return true
    end
  end
  return false
end

if (pl.path.exists("build.lua")) then
  loadFileIn("build.lua", config)
end
if (pl.path.exists("platforms/linux/libs.lua")) then
  loadFileIn("platforms/linux/libs.lua", config)
end

if (config.game_info == nil) then
  config.game_info = {}
end
if (config.game_info.name == nil) then
  config.game_info.name = pl.path.splitext(args.gamename)
end
if (config.libs == nil) then
  config.libs = {}
end

local output_d = pl.path.join(args.input_directory, config.game_info.name .. ".appdir")

if (not pl.path.exists(output_d)) then
  pl.dir.makepath(output_d)
end

os.chdir(output_d)

local dtop_file = io.open(config.game_info.name .. ".desktop", "w")
dtop_file:write(string.format("[Desktop Entry]\nName=%s\nExec=%s\nIcon=%s\nTerminal=false\nType=Application\n", config.game_info.name, args.executable_name, config.game_info.name))
dtop_file:close()

copyfile(fulljoin(APPIMAGE_PATH, "AppRun"), "AppRun")

pl.dir.makepath("usr/lib")
pl.dir.makepath("usr/bin")

copyfile(pl.path.join(args.input_directory, args.executable_name), "usr/bin/")
copyfile(pl.path.join(args.input_directory, "platforms/linux/angel.png"), config.game_info.name .. ".png")

local directories = {"Resources", "Config"}
for _, directory in pairs(directories) do
  recursive_copy(pl.path.join(args.input_directory, directory), fulljoin(output_d, "usr", directory))
end

local ldd_outpath = fulljoin(args.input_directory, "..", "Tools", "BuildScripts", "build_cache", "ldd_out.txt")
os.execute("ldd " .. fulljoin(args.input_directory, args.executable_name) .. " > " .. ldd_outpath)

local ldd_file = io.open(ldd_outpath, "r")
local ldd_data = ldd_file:read("*all")
ldd_file:close()

local ldd_lines = ldd_data:split("\n")
for _, lib_line in pairs(ldd_lines) do
  local lib_data = lib_line:split(" ")
  if (in_list(lib_data[1]:trim(), config.libs)) then
    copyfile(lib_data[3], "usr/lib/")
  end
end

os.execute("sed -i -e 's|../Angel/Libraries/FMOD/lib/libfmodex.so|././././././././././././lib/libfmodex.so|g' usr/bin/" .. args.executable_name)
copyfile("../../Angel/Libraries/FMOD/lib/libfmodex.so", "usr/lib/libfmodex.so")

os.chdir("..")

local pubdir = fulljoin(args.input_directory, "Published")
pl.dir.makepath(pubdir)

os.execute(APPIMAGE_EXE .. " " .. output_d:gsub(" ", "\\ ") ..  " " .. pubdir .. "/" .. config.game_info.name:gsub(" ", "\\ "))

local files_base = {"GameInfo.txt", "Attributions.txt"}
for _, base in pairs(files_base) do
  copyfile("Documentation/"..base, pubdir)
end

att_path = fulljoin(args.input_directory, "..", "Tools", "BuildScripts", "Attributions")
correct_attributions(pl.path.join(pubdir, "Attributions.txt"), att_path, 0, 0)


