#include "../AIEvents/TimerAIEvent.h"

TimerAIEvent* TimerAIEvent::Initialize( float duration )
{
	_duration = duration;
	return this;
}

void TimerAIEvent::Update(float dt)
{
	_duration -= dt;
	if( _duration < 0.0f )
	{
		IssueCallback();
	}
}
