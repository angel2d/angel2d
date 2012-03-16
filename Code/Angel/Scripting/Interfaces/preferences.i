%module angel
%{
#include "../../Infrastructure/Preferences.h"
%}

%nodefaultctor Preferences;
class Preferences
{
public:
	static Preferences& GetInstance();

	void SavePreferences();
	
	int GetInt(String category, String name);
	float GetFloat(String category, String name);
	String GetString(String category, String name);
	
	void SetInt(String category, String name, int val);
	void SetFloat(String category, String name, float val);
	void SetString(String category, String name, String val);

	const String GetDefaultPath();
	const String GetUserPrefsPath();
};
