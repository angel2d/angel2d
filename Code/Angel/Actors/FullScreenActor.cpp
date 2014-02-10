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
#include "../Actors/FullScreenActor.h"

#include "../Infrastructure/Camera.h"
#include "../Messaging/Switchboard.h"

FullScreenActor::FullScreenActor()
{
	_locked = false;
	theSwitchboard.SubscribeTo(this, "CameraChange");
	_resize();
}

void FullScreenActor::SetLock(bool locked)
{
	_locked = locked;
	if (!_locked)
	{
		_resize();
	}
}

const bool FullScreenActor::IsLocked()
{
	return _locked;
}

void FullScreenActor::ReceiveMessage(Message *message)
{
	if (!_locked && message->GetMessageName() == "CameraChange")
	{
		_resize();
	}
}

void FullScreenActor::_resize()
{
	Vector2 maxVert = theCamera.GetWorldMaxVertex();
	Vector2 minVert = theCamera.GetWorldMinVertex();
	Vector2 dimensions = maxVert - minVert;
	
	SetPosition(Vector2::Zero + theCamera.GetPosition());
	SetRotation(-theCamera.GetRotation());
	SetSize(dimensions.X, dimensions.Y);	
}