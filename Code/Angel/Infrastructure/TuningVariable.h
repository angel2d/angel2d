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

#include "../Infrastructure/LoadedVariable.h"
#include "../Util/StringUtil.h"
#include "../Util/MathUtil.h"

#define theTuning Tuning::GetInstance()

///The class which handles getting and setting tuning variables. 
/** 
 * This class is used to handle housekeeping of variables you'll want to 
 *  manually change at runtime to affect the way your game plays. A good 
 *  example is the height a character can jump -- you might declare this as
 *  a tuning variable in the \c Config/tuning.ini, change it from the console
 *  using the \c tune() function, and then call SaveTuningVariables() from
 *  the console to save the new value back into the file. 
 * 
 * Some people find it helpful to bind certain tuning functions to keypresses
 *  while they're tuning, so you could increase or decrease a certain tuning
 *  variable with the arrow keys, for instance. 
 * 
 * It's also possible to declare new tuning variables at runtime and do
 *  all sorts of crazy things. Go nuts! 
 */
class Tuning
{
public:
	/**
	 * Used to access the singleton instance of this class. As a shortcut, 
	 *  you can just use "theTuning". 
	 * 
	 * @return The singleton
	 */
	static Tuning& GetInstance();
	
	/** 
	 * Get a list of the currently declared tuning variables. This only 
	 *  gives you a set of variable names; you'll have to look up the 
	 *  values if you want them. 
	 * 
	 * @return The set of strings representing the variable names. 
	 */
	StringSet GetVariables();
	
	/**
	 * Get an integer representation of a tuning variable. The engine will do
	 *  its best to convert declared values into reasonable integer 
	 *  representations, and will return 0 if it can't or if the variable has
	 *  not been declared. 
	 * 
	 * @param name The name of the variable
	 * @return Its integer representation
	 */
	int GetInt(const String& name);
	
	/**
	 * Get a floating point representation of a tuning variable. The engine
	 *  will do its best to convert declared values into reasonable float 
	 *  representations, and will return 0.0f if it can't or if the variable
	 *  has not been declared. 
	 * 
	 * @param name The name of the variable
	 * @return Its floating point representation
	 */
	float GetFloat(const String& name);
	
	/**
	 * Get a string representation of a tuning variable. If the variable was
	 *  declared as another type, you'll still get a string representation of
	 *  the value. Returns an empty string if the variable has not been 
	 *  declared. 
	 * 
	 * @param name The name of the variable
	 * @return Its string representation
	 */
	String GetString(const String& name);
	
	/**
	 * Get a Vector2 representation of a tuning variable. This guy is pretty
	 *  much the odd man out in terms of conversions, since there's no obvious
	 *  default way to convert between the different types and a 2d vector. 
	 *  Returns a zero-length vector if you haven't actually set a vector to
	 *  this variable or if the variable has not been declared. 
	 * 
	 * @param name The name of the variable
	 * @return Its Vector2 representation
	 */
	Vector2 GetVector(const String& name);
	
	/**
	 * Change a tuning variable's value to a new integer. The Set* functions
	 *  are also how you declare new tuning variables.
	 * 
	 * @param name The name of the variable to change
	 * @param val The new integer value
	 */
	void SetInt(const String& name, int val);
	
	/**
	 * Change a tuning variable's value to a new float. The Set* functions
	 *  are also how you declare new tuning variables.
	 * 
	 * @param name The name of the variable to change. 
	 * @param val The new float value
	 */
	void SetFloat(const String& name, float val);
	
	/**
	 * Change a tuning variable's value to a new string. The Set* functions
	 *  are also how you declare new tuning variables.
	 * 
	 * @param name The name of the variable to change. 
	 * @param val The new string value
	 */
	void SetString(const String& name, const String& val);
	
	/**
	 * Change a tuning variable's value to a new vector. The Set* functions
	 *  are also how you declare new tuning variables.
	 * 
	 * @param name The name of the variable to change. 
	 * @param val The new vector value
	 */
	void SetVector(const String& name, const Vector2& val);
	
	/**
	 * For internal usage -- lets the engine keep track of what variables have
	 *  been tuned at runtime so they don't get stomped by the auto-reloading
	 *  of the \c tuning.ini file. 
	 * 
	 * @param varName The name of the variable to add to the list. 
	 */
	void AddToRuntimeTuningList(const String& varName);
	
	/**
	 * For internal usage -- lets the engine keep check if a variable has
	 *  been tuned at runtime so it doesn't get stomped when \c tuning.ini 
	 *  gets reloaded. 
	 * 
	 * @param varName The name of the variable to check
	 * @return Whether or not it's been tuned manually during this session
	 */
	bool IsRuntimeTuned(const String& varName);
	
private:
	Tuning();
	static Tuning* s_Tuning;
	
	LoadedVariableMap _tuningVariables;
	StringSet _runTimeTunedList;
};
