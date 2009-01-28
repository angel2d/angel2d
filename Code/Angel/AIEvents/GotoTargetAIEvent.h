#pragma once

#include "../AIEvents/GotoAIEvent.h"
#include "../Util/StringUtil.h"

class GotoTargetAIEvent : public GotoAIEvent
{
public:

	virtual GotoTargetAIEvent* Initialize( const String& targetTag, float moveSpeed, float arrivalDist = 0.2f );
	virtual void Update(float dt);

protected:
	String			_targetTag;
};

DECLARE_AIEVENT_BASE( GotoTargetAIEvent )
