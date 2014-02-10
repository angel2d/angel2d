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
#include "../AIEvents/TraversalAIEvent.h"

#include "../AI/Traversal.h"


TraversalAIEvent* TraversalAIEvent::Initialize( Traversal* traversal, Vector2& startPos, int numIterationsPerFrame, int maxResults, int maxIterations )
{
	_numIterationsPerFrame = numIterationsPerFrame;
	_traversal = traversal;

	_traversal->StartTraversal( startPos, maxResults, maxIterations );

	return this;
}

void TraversalAIEvent::Update(float /*dt*/)
{
	if( _numIterationsPerFrame < 0 )
	{
		_traversal->ExecuteFullTraversal();
		IssueCallback();
		return;
	}

	for( int i = 0; i < _numIterationsPerFrame; i++ )
	{
		//callback when we're done
		if( !_traversal->DoNextTraversal() )
		{
			IssueCallback();
			return;
		}
	}
}

void TraversalAIEvent::Stop()
{
	delete _traversal;
}

std::vector<Vector2>& TraversalAIEvent::GetResults()
{
	return _traversal->GetResults();
}

