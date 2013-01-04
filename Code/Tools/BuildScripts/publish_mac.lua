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
    -g,--gamename (default ClientGame.app)  Name of the final game
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

local output_d = path.join(args.output_directory, config.game_info.name)

if (not path.exists(output_d)) then
  dir.makepath(output_d)
end

local files_base = {"GameInfo.txt", "Attributions.txt"}
for _, file_base in pairs(files_base) do
  dir.copyfile(fulljoin(args.input_directory, "Documentation", file_base), path.join(output_d, file_base), true)
end

local app_path = path.join(output_d, config.game_info.name .. ".app")
if path.exists(app_path) then
  dir.rmtree(app_path)
end

recursive_copy(fulljoin(os.getenv('BUILT_PRODUCTS_DIR'), args.gamename), app_path)
-- recursive_copy(fulljoin(output_d, "..", "..", "Release", args.gamename), app_path)

conf_path = fulljoin(args.input_directory, "..", "Angel", "AngelConfig.h")
t = io.open(conf_path, "r")
tr = t:read("*all")
t:close()

disable_fmod = tonumber(tr:match("\n%s*#define%s+ANGEL_DISABLE_FMOD%s+([0-9]+)"))
disable_devil = tonumber(tr:match("\n%s*#define%s+ANGEL_DISABLE_DEVIL%s+([0-9]+)"))

if (disable_fmod == 1) then
  local lib = fulljoin(app_path, "Contents", "Frameworks", "libfmodex.dylib")
  os.remove(lib)
end
if (disable_devil == 1) then
  local libs = {"libIL.dylib", "libILU.dylib", "libILUT.dylib", "libjasper.dylib", "libjpeg.dylib", "liblcms.dylib", "libmng.dylib", "libtiff.dylib"}
  for _, lib in pairs(libs) do
    local libpath = fulljoin(app_path, "Contents", "Frameworks", lib)
    os.remove(libpath)
  end
end

exename = os.getenv('EXECUTABLE_NAME')
exepath = fulljoin(app_path, "Contents", "MacOS", exename)
renamed = fulljoin(app_path, "Contents", "MacOS", config.game_info.name)
dir.movefile(exepath, renamed)

plist_path = fulljoin(app_path, "Contents", "Info.plist")
plist = io.open(plist_path, "r")
plist_text = plist:read("*all")
plist:close()
plist = io.open(plist_path, "w")
find = "<key>CFBundleExecutable</key>\n\t<string>" .. exename .. "</string>"
replace = "<key>CFBundleExecutable</key>\n\t<string>" .. config.game_info.name .. "</string>"
plist_text = plist_text:gsub(find, replace)
plist:write(plist_text)
plist:close()

att_path = fulljoin(args.input_directory, "..", "Tools", "BuildScripts", "Attributions")
correct_attributions(path.join(output_d, "Attributions.txt"), att_path, disable_devil, disable_fmod)
