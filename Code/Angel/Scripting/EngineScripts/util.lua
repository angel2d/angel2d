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

function string:split(sep)
  local sep, fields = sep or " ", {}
  local pattern = string.format("([^%s]+)", sep)
  self:gsub(pattern, function(c) fields[#fields+1] = c end)
  return fields
end

function string:starts(startString)
  return string.sub(self, 1, string.len(startString)) == startString
end

function string:ends(endString)
  return endString == '' or string.sub(self, -string.len(endString)) == endString
end

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

function addClassMethod(className, methodName, method)
  if ("function" ~= type(method)) then
    print ("WARNING: " .. method .. " is not a function.")
  end
  local reg = debug.getregistry()
  local classTable = reg["SWIG"][className]
  if (classTable == nil) then
    print("WARNING: No class called " .. className .. " to give " .. method .. ".")
    return
  end
  classTable[".fn"][tostring(methodName)] = method
end

