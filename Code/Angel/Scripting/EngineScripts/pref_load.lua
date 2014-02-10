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

require "lfs"
require "util"

-- Load a file, and insert its values into the Angel preferences
function LoadAndInsertFile(prefPath)
  local loadedPrefs = {}

  local attributes, err = lfs.attributes(prefPath)
  if (attributes ~= nil) then
    loadFileIn(prefPath, loadedPrefs)

    for category, var_list in pairs(loadedPrefs) do
      for variable, value in pairs(var_list) do
        if     (type(value) == "number") then
          if (math.floor(value) == value) then
            angel.Preferences_GetInstance():SetInt(category, variable, value)
          else
            angel.Preferences_GetInstance():SetFloat(category, variable, value)
          end
        elseif (type(value) == "boolean") then
          if (value) then
            angel.Preferences_GetInstance():SetInt(category, variable, 1)
          else
            angel.Preferences_GetInstance():SetInt(category, variable, 0)
          end
        else
          angel.Preferences_GetInstance():SetString(category, variable, value)
        end
      end
    end
  end
end

function LoadPreferences()
  -- Load base preferences file
  LoadAndInsertFile(angel.Preferences_GetInstance():GetDefaultPath())

  -- Load user overrides
  LoadAndInsertFile(angel.Preferences_GetInstance():GetUserPrefsPath())
end

function errorHandler(err)
  print(err)
end

local status, err = xpcall(LoadPreferences, errorHandler)
