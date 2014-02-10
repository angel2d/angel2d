//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AI/Brain.h"

#include "../AI/Sentient.h"
#include "../Infrastructure/TextRendering.h"
#include "../Util/MathUtil.h"

AIBrain::AIBrain()
{
	_current = _brainStateTable.end();
	_drawMe = false;
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
	if( !_drawMe )
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

void AIBrain::EnableDrawing(bool enable)
{
	_drawMe = enable;
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
