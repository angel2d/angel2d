#include "../AIEvents/NamedEventAIEvent.h"

NamedEventAIEvent* NamedEventAIEvent::Initialize( const String& eventId, StringList* eventIdList )
{
	_eventId = eventId;
	_eventIdList = eventIdList;

	return this;
}

void NamedEventAIEvent::Update(float /*dt*/)
{
	for( unsigned int i = 0; i < _eventIdList->size(); i++ )
	{
		if( _eventId == (*_eventIdList)[i] )
		{
			IssueCallback();
			return;
		}
	}
}
