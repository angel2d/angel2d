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

#define thePrefs Preferences::GetInstance()

///A centralized class that handles any persistent preferences
/**
 * We very often want to define persistent preferences for the user. They are
 *  stored out in .lua files, so they can be easily written or inspected by 
 *  hand if needed. 
 * 
 * When the game starts, the game will first load preferences from 
 *  \c Config/defaults.lua, then load saved preferences, overriding any default
 *  preferences. 
 * 
 * Preferences are organized into categories, represented as discrete tables in
 *  the .lua files. For example, if this was the preferences file:
 * 
 * \code
 * GameStart = {
 * 	enemies = 15,
 * 	heroName = "Superdude",
 * }
 * \endcode
 * 
 * Then we would retrieve the preference using "GameStart" as the category, and
 *  "enemies" or "heroName" as the value. Preferences can either be integers,
 *  floats, or Strings.
 */
class Preferences
{
public:
	/**
	 * Used to access the singleton instance of this class. As a shortcut, 
	 *  you can just use "thePrefs". 
	 * 
	 * @return The singleton
	 */
	static Preferences& GetInstance();

	/**
	 * Writes out all currently set preferences to a user-writable directory, 
	 *  which will override the defaults the next time the game launches.
	 */
	void SavePreferences();

	/**
	 * Retrieves a given preference in integer form.
	 * 
	 * @param category The category of the desired preference
	 * @param name The value of the desired preference
	 * @return The retrieved integer (0 if this preference has never been set)
	 */
	int GetInt(const String& category, const String& name);

	/**
	 * Retrieves a given preference in float form.
	 * 
	 * @param category The category of the desired preference
	 * @param name The value of the desired preference
	 * @return The retrieved float (0.0f if this preference has never been set)
	 */
	float GetFloat(const String& category, const String& name);

	/**
	 * Retrieves a given preference in String form.
	 * 
	 * @param category The category of the desired preference
	 * @param name The value of the desired preference
	 * @return The retrieved String (Empty string if this preference has never been set)
	 */
	String GetString(const String& category, const String& name);

	/**
	 * Gets all variables in a given category.
	 * 
	 * @param category The desired category
	 * @return All defined preferences for this category
	 */
	LoadedVariableMap GetTable(const String& category);

	/**
	 * Sets a preference as an integer. If it did not previously exist,
	 *  it will be created.
	 * 
	 * @param category The category of the preference to set
	 * @param name The value of the preference to set
	 * @param val The actual value we want to store
	 */
	void SetInt(const String& category, const String& name, int val);

	/**
	 * Sets a preference as a float. If it did not previously exist,
	 *  it will be created.
	 * 
	 * @param category The category of the preference to set
	 * @param name The value of the preference to set
	 * @param val The actual value we want to store
	 */
	void SetFloat(const String& category, const String& name, float val);

	/**
	 * Sets a preference as a String. If it did not previously exist,
	 *  it will be created.
	 * 
	 * @param category The category of the preference to set
	 * @param name The value of the preference to set
	 * @param val The actual value we want to store
	 */
	void SetString(const String& category, const String& name, const String& val);

	/**
	 * Takes a given integer, and returns either that integer or, if an
	 *  appropriate preference exists, will return it. Handy for 
	 *  allowing hardcoded values to be overridden by user-defined ones.
	 * 
	 * @param category The category of the preference to check
	 * @param name The value of the preference to check
	 * @param val The value to return if there is no such preference
	 * @return Either the given integer or the appropriate preference integer
	 */
	int OverrideInt(const String& category, const String& name, int val);

	/**
	 * Takes a given float, and returns either that float or, if an
	 *  appropriate preference exists, will return it. Handy for 
	 *  allowing hardcoded values to be overridden by user-defined ones.
	 * 
	 * @param category The category of the preference to check
	 * @param name The value of the preference to check
	 * @param val The value to return if there is no such preference
	 * @return Either the given float or the appropriate preference float
	 */
	float OverrideFloat(const String& category, const String& name, float val);

	/**
	 * Takes a given String, and returns either that String or, if an
	 *  appropriate preference exists, will return it. Handy for 
	 *  allowing hardcoded values to be overridden by user-defined ones.
	 * 
	 * @param category The category of the preference to check
	 * @param name The value of the preference to check
	 * @param val The value to return if there is no such preference
	 * @return Either the given String or the appropriate preference String
	 */
	String OverrideString(const String& category, const String& name, String val);
	

	/**
	 * Used by the scripting system when it attempts to load the preferences
	 *  files at game start. 
	 * 
	 * @return The absolute path to the \c Config/defaults.lua file
	 */
	const String GetDefaultPath();

	/**
	 * Used by the scripting system when it attempts to load the preferences
	 *  files at game start. 
	 * 
	 * @return The absolute path to the file which stores any preferences
	 *   that were saved with thePrefs.SavePreferences()
	 */
	const String GetUserPrefsPath();
	
private:
	Preferences();
	static Preferences* s_Preferences;
	
	hashmap_ns::hash_map<String,LoadedVariableMap> _preferenceVariables;
};
