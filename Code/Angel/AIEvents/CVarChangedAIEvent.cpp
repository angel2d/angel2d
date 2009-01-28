#include "../AIEvents/CVarChangedAIEvent.h"

#include "../AI/Brain.h"
#include "../Infrastructure/DeveloperConsole.h"


OnConsoleVariableChangedAIEvent* OnConsoleVariableChangedAIEvent::Initialize( const String& cVarId )
{
	_variable = theDevConsole.GetConsoleItemManager().GetCVar( cVarId );
	if( _variable )
		_lastValue = _variable->GetStringVal();

	return this;
}

void OnConsoleVariableChangedAIEvent::Update(float /*dt*/)
{
	if( _variable == NULL )
		return;

	if( _variable->GetStringVal() != _lastValue )
	{
		IssueCallback();
	}
}
