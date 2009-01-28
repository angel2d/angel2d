#pragma once

#include "../AI/Brain.h"

class TimerAIEvent : public AIEvent
{
public:

	virtual TimerAIEvent* Initialize( float duration );
	virtual void Update(float dt);

protected:
	float				_duration;
};

DECLARE_AIEVENT_BASE( TimerAIEvent )
