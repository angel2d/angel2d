%module angel
%{
#include "../../Infrastructure/TuningVariable.h"
%}

%nodefaultctor Tuning;
class Tuning
{
public:
	static Tuning& GetInstance();
	StringSet GetVariables();
	
	int GetInt(String name);
	float GetFloat(String name);
	String GetString(String name);
	Vector2 GetVector(String name);
	
	void SetInt(String name, int val);
	void SetFloat(String name, float val);
	void SetString(String name, String val);
	void SetVector(String name, Vector2 val);
	
	void AddToRuntimeTuningList(String varName);
	bool IsRuntimeTuned(String varName);
};
