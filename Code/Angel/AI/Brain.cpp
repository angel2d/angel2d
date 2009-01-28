#include "../AI/Brain.h"

#include "../AI/Sentient.h"
#include "../Infrastructure/TextRendering.h"
#include "../Infrastructure/DeveloperConsole.h"
#include "../Util/MathUtil.h"

AIBrain::AIBrain()
{
	_current = _brainStateTable.end();
}

AIBrain::~AIBrain()
{
	GotoNullState();
	//clean up states
	BrainStateTable::iterator itr = _brainStateTable.begin();
	for( ; itr != _brainStateTable.end(); itr++ )
	{
		AIBrainState* pState = (*itr).second;
		delete pState;
	}
}

void AIBrain::AddState( const String& id, AIBrainState* state )
{
	//remove existing state in this ID
	String useId = ToUpper(id);
	BrainStateTable::iterator itr = _brainStateTable.find( useId );
	if( itr != _brainStateTable.end() )
	{
		//delete second
		delete (*itr).second;
	}

	state->Initialize(this);

	_brainStateTable[useId] = state;
}

void AIBrain::Update(float dt)
{
	if( _brainStateTable.size() == 0 )
	{
		GetActor()->InitializeBrain();
		GetActor()->StartBrain();
	}
	if( _current == _brainStateTable.end() )
		return;

	(*_current).second->Update(dt);

}

void AIBrain::GotoState( const String& id )
{
	String useId = ToUpper(id);
	BrainStateTable::iterator itr = _brainStateTable.find( useId );
	if( itr != _brainStateTable.end() )
	{
		AIBrainState* pNextState = (*itr).second;
		AIBrainState* pLastState = NULL;
		if( _current != _brainStateTable.end() )
		{
			(*_current).second->EndState( pNextState );

			pLastState = (*_current).second;
		}

		_current = itr;
		(*_current).second->BeginState( pLastState );
	}
}

void AIBrain::Render()
{
	CONSOLE_DECLAREVAR( ai_drawbrain );
	if( ai_drawbrain->GetIntVal() == 0 )
		return;

	if( _current != _brainStateTable.end() )
	{
		Vector2 screenCenter = MathUtil::WorldToScreen( GetActor()->GetPosition().X, GetActor()->GetPosition().Y );
		//Print some vals
		glColor3f(0,0.f,1.f);
		DrawGameText( (*_current).first, "ConsoleSmall", (int)screenCenter.X, (int)screenCenter.Y );
	}

}

void AIBrain::GotoNullState()
{
	if( _current != _brainStateTable.end() )
		(*_current).second->EndState( NULL );

	_current = _brainStateTable.end();
}

void AIBrainState::Update(float dt)
{
	CustomUpdate(dt);
	for( unsigned int i = 0; i < _eventList.size(); i++ )
	{
		_eventList[i]->Update(dt);
	}
}


void AIBrainState::EndState( AIBrainState* nextState )
{
	CustomEndState( nextState );
	ClearEvents();
}

void AIBrainState::GotoState( const String& id )
{
	_brain->GotoState( id );
}

AIEvent* AIBrainState::RegisterEvent( AIEvent* newEvent )
{
	_eventList.push_back( newEvent );
	newEvent->SetBrain( _brain );
	return newEvent;
}

void AIBrainState::UnregisterEvent( AIEvent* oldEvent )
{
	for( EventList::iterator itr = _eventList.begin(); itr != _eventList.end(); itr++ )
	{
		if( (*itr) == oldEvent )
		{
			_eventList.erase( itr );
			StopEvent( oldEvent );
			return;
		}
	}
}

void AIBrainState::ClearEvents()
{
	//stop and delete events
	for( unsigned int i = 0; i < _eventList.size(); i++ )
	{
		StopEvent( _eventList[i]);
	}
	_eventList.clear();
}


void AIBrainState::StopEvent( AIEvent* pEvent )
{
	pEvent->Stop();
	delete pEvent;
}

