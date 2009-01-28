#pragma once

#include "../Util/StringUtil.h"
#include "../AI/Brain.h"

class ConsoleVariable;

class OnConsoleVariableChangedAIEvent : public AIEvent
{
public:
	virtual OnConsoleVariableChangedAIEvent* Initialize( const String& cVarId );
	virtual void Update(float dt);
private:
	ConsoleVariable*	_variable;
	String					_lastValue;
};

DECLARE_AIEVENT_BASE( OnConsoleVariableChangedAIEvent )

