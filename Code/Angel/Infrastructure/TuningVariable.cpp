//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
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
#include "../Infrastructure/TuningVariable.h"

Tuning* Tuning::s_Tuning = NULL;

Tuning& Tuning::GetInstance()
{
	if (s_Tuning == NULL)
	{
		s_Tuning = new Tuning();
	}
	return *s_Tuning;
}

Tuning::Tuning()
{
	//nothing to do here at the moment
}

StringSet Tuning::GetVariables()
{
	StringSet forReturn;
	LoadedVariableMap::iterator it = _tuningVariables.begin();
	while (it != _tuningVariables.end())
	{
		forReturn.insert(it->first);
		it++;
	}
	return forReturn;
}

int Tuning::GetInt(const String& name)
{
	LoadedVariableMap::iterator it = _tuningVariables.find(name);
	if (it == _tuningVariables.end())
	{
		return LoadedVariable()._int;
	}
	return it->second._int;
}

float Tuning::GetFloat(const String& name)
{
	LoadedVariableMap::iterator it = _tuningVariables.find(name);
	if (it == _tuningVariables.end())
	{
		return LoadedVariable()._float;
	}
	return it->second._float;
}

String Tuning::GetString(const String& name)
{
	LoadedVariableMap::iterator it = _tuningVariables.find(name);
	if (it == _tuningVariables.end())
	{
		return LoadedVariable()._string;
	}
	return it->second._string;
}

Vector2 Tuning::GetVector(const String& name)
{
	LoadedVariableMap::iterator it = _tuningVariables.find(name);
	if (it == _tuningVariables.end())
	{
		return LoadedVariable()._vector;
	}
	return it->second._vector;
}

void Tuning::SetInt(const String& name, int val)
{
	_tuningVariables[name] = LoadedVariable(val);
}

void Tuning::SetFloat(const String& name, float val)
{
	_tuningVariables[name] = LoadedVariable(val);
}

void Tuning::SetString(const String& name, const String& val)
{
	_tuningVariables[name] = LoadedVariable(val);
}

void Tuning::SetVector(const String& name, const Vector2& val)
{
	_tuningVariables[name] = LoadedVariable(val);
}

void Tuning::AddToRuntimeTuningList(const String& varName)
{
	_runTimeTunedList.insert(varName);
}

bool Tuning::IsRuntimeTuned(const String& varName)
{
	return (_runTimeTunedList.count(varName) > 0);
}
