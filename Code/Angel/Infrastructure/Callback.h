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

#pragma once 
#include <cstdio>

/// (Internal) A callback template to simplify storage/retrieval of method pointers
/** 
 * Storing pointers to member functions (as opposed to just loose functions)
 *  can be complicated and error-prone. This template class is designed to 
 *  make such things simpler. An example usage is in the SoundDevice class. 
 * 
 * Note that this template only lets you store callbacks that take a single
 *  parameter. 
 */
template <class ClassInstance, class ParamType>
class TGenericCallback
{
public:
	TGenericCallback()
	{
		_function = 0;
	}
	
	typedef void (ClassInstance::*FunctionPointer)(ParamType param);
	
	virtual void Execute(ParamType param) const
	{
		if (_function) 
			(_instance->*_function)(param);
		else 
			printf("WARNING: No callback function specified!");
	}
	
	void SetCallback(	ClassInstance* instance, 
						FunctionPointer function)
	{
		_instance = instance;
		_function = function;
	}
	
	const ClassInstance* GetInstance()
	{
		return _instance;
	}
	
	const FunctionPointer GetFunction()
	{
		return _function;
	}
	
private:
	ClassInstance*	_instance;
	FunctionPointer  _function;
};
