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

-- set up paths
if (package.path == nil) then
  package.path = ""
end
package.path = package.path .. ";./Resources/Scripts/?.lua"

require "util"

function catchExit()
  print("Can't exit game from console.")
end

if (ANGEL_MOBILE == false) then
  function angelPrint(...)
    local arg = {...}
    local str
    str = ""
    for i=1, #arg do
      if (str ~= "") then
        str = str .. '\t'
      end
      str = str .. tostring(arg[i])
    end
    LuaWrite(str)
  end
end

function angelStart()
  -- merge everything into the global namespace
  for k, v in pairs(angel) do
    if (nil == _G[k]) then -- keep from overriding any built-ins
      _G[k] = v
    end
  end
  angel = nil
  
  -- override the built-in exit
  os.exit = catchExit
  
  -- override printing to go to in-game console
  if (ANGEL_MOBILE == false) then
    print = angelPrint
    io.write = angelPrint
  end
  
  -- stir up some syntactic sugar
  require("sugar")
  
  -- configuration loading
  require("conf_load")
  ReloadActorDefs()
  ReloadLevelDefs()
  
  -- autocompletion
  require("autocomplete")
  
  -- run the client code
  require("client_start")
end

function errorHandler(err)
  print(err)
end

local status, err = xpcall(angelStart, errorHandler)
