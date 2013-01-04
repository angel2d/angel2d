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

#pragma once

#include "../Util/StringUtil.h"
#include "../Util/MathUtil.h"

///An internal structure used by the preferences and tuning system
struct LoadedVariable
{
	int _int;
	float _float;
	String _string;
	Vector2 _vector;
	int _setAs; // 0 - int; 1 - float; 2 - string; 3 - vector
	
	LoadedVariable()
	{
		_int = 0;
		_float = 0.0f;
		_string = "";
		_vector = Vector2::Zero;
		_setAs = 0;
	}
	LoadedVariable(int val)
	{
		_int = val;
		_float = (float)val;
		_string = IntToString(val);
		_vector = Vector2::Zero;
		_setAs = 0;
	}
	LoadedVariable(float val)
	{
		_int = MathUtil::RoundToInt(val);
		_float = val;
		_string = FloatToString(val);
		_vector = Vector2::Zero;
		_setAs = 1;
	}
	LoadedVariable(String val)
	{
		_int = StringToInt(val); 
		_float = StringToFloat(val);
		_string = val;
		_vector = Vector2::Zero;
		_setAs = 2;
	}
	LoadedVariable(Vector2 val)
	{
		_int = 0;
		_float = 0.0f;
		_string = "{" + FloatToString(val.X) + ", " + FloatToString(val.Y) + "}";
		_vector = val;
		_setAs = 3;
	}
};

typedef hashmap_ns::hash_map<String, LoadedVariable>    LoadedVariableMap;
