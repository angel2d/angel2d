#pragma once

#include "../AI/Brain.h"
#include "../Util/StringUtil.h"

class NamedEventAIEvent : public AIEvent
{
public:

	virtual NamedEventAIEvent* Initialize( const String& eventId, StringList* eventIdList );
	virtual void Update(float dt);

protected:
	String					_eventId;
	StringList*			_eventIdList;
};

DECLARE_AIEVENT_BASE( NamedEventAIEvent )
