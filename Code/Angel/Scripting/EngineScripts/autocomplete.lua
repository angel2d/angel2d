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

local tabSplits = "[%.%:]"

function getAutoCompletions(inc)
  local forReturn = {}
  
  local return_prefix = ""
  local remainder = inc
  local searchTab = _G
  local break_ind = remainder:find(tabSplits)
  while (break_ind ~= nil) do
    return_prefix = return_prefix .. remainder:sub(1, break_ind)
    local prefix = remainder:sub(1, break_ind-1)
    remainder = remainder:sub(break_ind+1, -1)
    local prefTab = searchTab[prefix]
    if (prefTab ~= nil) then
      if     (type(prefTab) == "table") then
        searchTab = prefTab
      elseif (type(prefTab) == "userdata") then
        -- check if we have a .fn table
        local m = getmetatable(prefTab)
        if (m == nil) then
          searchTab = nil
          break
        end
        if (type(m[".fn"]) == "table") then
          searchTab = m[".fn"]
        end
      else
        searchTab = nil
        break
      end
    else
      searchTab = nil
      break
    end
    break_ind = remainder:find(tabSplits)
  end
  
  if (searchTab ~= nil) then
    for name, val in pairs(searchTab) do
      if (name:sub(1, #remainder) == remainder) then
        if (type(val) == "function") then
          name = name .. "("
        end
        table.insert(forReturn, return_prefix .. tostring(name))
      end
    end
  end

  return forReturn
end

function printAutoCompletions(inc)
  ac = getAutoCompletions(inc)
  if (type(ac) == "table") then
    table.foreach(ac, print)
  end
end
