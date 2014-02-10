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

#pragma once

#include "../Actors/Actor.h"
#include "../Messaging/Message.h"
#include "../Infrastructure/SoundDevice.h"

///A class to oversee the high-level aspects of your game
/** 
 * Oftentimes you want to have a central class that handles game-flow. Things 
 *  like keeping score, managing the creation of new Actors, etc. You could
 *  do this with a centralized Actor that doesn't get drawn, but there's a lot
 *  of functionality (baggage) on the Actor class that you wouldn't be using 
 *  in that case. 
 * 
 * The GameManager class is a Renderable, so it will get all the Render and
 *  Update calls that an Actor would receive. You register it with your World 
 *  (via the \c theWorld.SetGameManager function) and can then retrieve it 
 *  from anywhere in your game. 
 */
class GameManager : public Renderable, public MessageListener
{
public:
	/**
	 * The default constructor is empty; we expect you to subclass to do 
	 *  anything meaningful. 
	 */
	GameManager(){}
	
	/**
	 * The destructor makes sure that the GameManager unsubscribes from all
	 *   Message notifications. 
	 */
	~GameManager();

	/**
	 * Override of the Renderable::Render function. Doesn't do anything in 
	 *  this base class. 
	 */
	virtual void Render();
	
	/**
	 * Override of the Renderable::Update function. Also doesn't do anything 
	 *  in the base class, but in the future it might, so make sure you call 
	 *  this in any override implementations. 
	 * 
	 * @param dt The amount of time elapsed since the start of the last frame. 
	 */
	virtual void Update(float dt);
	
	/**
	 * In your GameManager, you can define a custom function to determine whether
	 *  specific Renderables should be protected from the World::UnloadAll 
	 *  function. This function will get called for each Renderable during
	 *  an UnloadAll attempt. 
	 * 
	 * @param renderable The Renderable to test
	 * @return Whether it should be protected (returning false means it will
	 *   be removed from the world)
	 */
	virtual bool IsProtectedFromUnloadAll( Renderable* renderable ) {return false;} 
	
	/**
	 * Override of the MessageListener::ReceiveMessage function. Does nothing
	 *  in this base class. 
	 * 
	 * @param message The received message. 
	 */
	virtual void ReceiveMessage(Message* message) {}
	
	/**
	 * The sound system needs a callback that gets triggered when any sound
	 *  ends. Since the GameManager is a logical place to have sound control
	 *  functionality, it has this function for you to implement. 
	 * 
	 * @param sound The handle to the sound that has just completed. 
	 */
	virtual void SoundEnded(AngelSoundHandle sound){}
};
