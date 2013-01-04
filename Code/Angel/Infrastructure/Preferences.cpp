//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../Infrastructure/Preferences.h"

#include "../Infrastructure/Log.h"
#include "../Util/FileUtil.h"

#if defined(WIN32)
	#pragma warning(disable:4503)
#endif

Preferences* Preferences::s_Preferences = NULL;

Preferences& Preferences::GetInstance()
{
	if (s_Preferences == NULL)
	{
		s_Preferences = new Preferences();
	}
	return *s_Preferences;
}

Preferences::Preferences()
{
	//nothing to do here at the moment
}

void Preferences::SavePreferences()
{
	StringList written;
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.begin();
	while (it != _preferenceVariables.end())
	{
		written.push_back(it->first + " = {");
		LoadedVariableMap::iterator lvmIt = it->second.begin();
		while (lvmIt != it->second.end())
		{
			if (lvmIt->second._setAs == 2)
			{
				written.push_back("\t" + lvmIt->first + " = \"" + lvmIt->second._string + "\",");
			}
			else
			{
				written.push_back("\t" + lvmIt->first + " = " + lvmIt->second._string + ",");
			}
			lvmIt++;
		}
		written.push_back("}\n");
		it++;
	}
	WriteLinesToFile(GetUserPrefsPath(), written);
}

const String Preferences::GetDefaultPath()
{
	return "Config/defaults.lua";
}

const String Preferences::GetUserPrefsPath()
{
	MakeDirectories(GetStorageDirectory());
	return GetStorageDirectory() + "user_prefs.lua";
}

int Preferences::GetInt(const String& category, const String& name) 
{
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		return LoadedVariable()._int;
	}
	LoadedVariableMap::iterator lvmIt = it->second.find(name);
	if (lvmIt == it->second.end())
	{
		return LoadedVariable()._int;
	}

	return lvmIt->second._int;
}

float Preferences::GetFloat(const String& category, const String& name) 
{
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		return LoadedVariable()._float;
	}
	LoadedVariableMap::iterator lvmIt = it->second.find(name);
	if (lvmIt == it->second.end())
	{
		return LoadedVariable()._float;
	}

	return lvmIt->second._float;
}

String Preferences::GetString(const String& category, const String& name) 
{
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		return LoadedVariable()._string;
	}
	LoadedVariableMap::iterator lvmIt = it->second.find(name);
	if (lvmIt == it->second.end())
	{
		return LoadedVariable()._string;
	}

	return lvmIt->second._string;
}

LoadedVariableMap Preferences::GetTable(const String& category)
{
	LoadedVariableMap forReturn;

	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		return forReturn;
	}

	LoadedVariableMap::iterator lvmIt = it->second.begin();
	while (lvmIt != it->second.end())
	{
		forReturn[lvmIt->first] = LoadedVariable(lvmIt->second._string);
		lvmIt++;
	}

	return forReturn;
}

void Preferences::SetInt(const String& category, const String& name, int val) 
{
	if (category == "" || name == "")
	{
		sysLog.Log("ERROR: Null strings passed for category or name in preference setting.");
	}
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		_preferenceVariables[category] = LoadedVariableMap();
	}
	_preferenceVariables[category][name] = LoadedVariable(val);
}

void Preferences::SetFloat(const String& category, const String& name, float val) 
{
	if (category == "" || name == "")
	{
		sysLog.Log("ERROR: Null strings passed for category or name in preference setting.");
	}
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		_preferenceVariables[category] = LoadedVariableMap();
	}
	_preferenceVariables[category][name] = LoadedVariable(val);
}

void Preferences::SetString(const String& category, const String& name, const String& val) 
{
	if (category == "" || name == "")
	{
		sysLog.Log("ERROR: Null strings passed for category or name in preference setting.");
	}
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		_preferenceVariables[category] = LoadedVariableMap();
	}
	_preferenceVariables[category][name] = LoadedVariable(val);
}

int Preferences::OverrideInt(const String& category, const String& name, int val)
{
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		return val;
	}
	LoadedVariableMap::iterator lvmIt = it->second.find(name);
	if (lvmIt == it->second.end())
	{
		return val;
	}

	return lvmIt->second._int;
}

float Preferences::OverrideFloat(const String& category, const String& name, float val)
{
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		return val;
	}
	LoadedVariableMap::iterator lvmIt = it->second.find(name);
	if (lvmIt == it->second.end())
	{
		return val;
	}

	return lvmIt->second._float;
}

String Preferences::OverrideString(const String& category, const String& name, String val)
{
	hashmap_ns::hash_map<String, LoadedVariableMap>::iterator it = _preferenceVariables.find(category);
	if (it == _preferenceVariables.end())
	{
		return val;
	}
	LoadedVariableMap::iterator lvmIt = it->second.find(name);
	if (lvmIt == it->second.end())
	{
		return val;
	}

	return lvmIt->second._string;
}

