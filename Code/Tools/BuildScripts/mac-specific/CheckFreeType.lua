------------------------------------------------------------------------------
-- Copyright (C) 2008-2010, Shane J. M. Liesegang
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
mydir = mydir .. "/../"
package.path = mydir .. "?.lua;" .. package.path
package.path = package.path .. ";" .. mydir .. "lua-lib/penlight-0.8/lua/?/init.lua"
package.path = package.path .. ";" .. mydir .. "lua-lib/penlight-0.8/lua/?.lua"

require "angel_build"
require "lfs"
require "pl.path"

local env = os.environ()

local BASEDIR = fulljoin(env['PROJECT_DIR'], "Angel", "Libraries", "freetype-2.3.7")
local FILES = {'libfreetype.6.dylib', 'libfreetype.a'}
local BUILT_DIR = fulljoin(BASEDIR, "built")
local LIB_DIR = fulljoin(BUILT_DIR, "lib")

lfs.chdir(BASEDIR)

for _, filename in pairs(FILES) do
  local src = fulljoin(LIB_DIR, filename)
  if (not pl.path.exists(src)) then
    local conf_string = 'env CFLAGS='
    conf_string = conf_string .. '"-O -g -isysroot /Developer/SDKs/MacOSX10.6.sdk -arch i386" '
    conf_string = conf_string .. 'LDFLAGS='
    conf_string = conf_string .. '"-arch i386" '
    conf_string = conf_string .. './configure --prefix='
    conf_string = conf_string .. BUILT_DIR
    os.execute(conf_string)
    os.execute('make install 2> /dev/null')
    if (not pl.path.exists(src)) then
      io.stderr:write("ERROR: Building FreeType didn't produce " .. filename .. "\n")
      os.exit(1)
    end
  end
end
