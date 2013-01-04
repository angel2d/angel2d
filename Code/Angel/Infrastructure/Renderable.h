//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
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

///Our base simulation element that gets inserted to the World
/** 
 * This is the base class from which most of the simulation elements in Angel
 *  derive. When you insert a Renderable into the World, it will receive 
 *  Update and Render calls once per frame. 
 */
class Renderable
{
	friend class World;

public:
	/**
	 * The base constructor just sets a flag on the Renderable to not 
	 *  delete it, since that would be kind of a buzzkill out of the gate. 
	 * 
	 * @param _deleteMe 
	 */
	Renderable() : _deleteMe(false) {}
	
	/**
	 * Abstract base class needs a virtual destructor. 
	 */
	virtual ~Renderable() {}
	
	/**
	 * This function gets called once per frame. Any game logic for an Actor
	 *  should be done in this function, since it provides you with a dt for
	 *  controlling rate of movement, animation, etc. 
	 * 
	 * @param dt The amount of time (in seconds) that has elapsed since the 
	 *  last frame. 
	 */
	virtual void Update(float dt) {}
	
	/**
	 * This function also gets called once per frame, \b after the 
	 *  Renderable::Update call. Anything you do in this function should be
	 *  strictly related to drawing something on the screen. Moving it, 
	 *  changing its appearance/properties/etc. should happen in Update. 
	 */
	virtual void Render() {}
	
	/**
	 * A safe way to kill off a Renderable -- it will be removed from the 
	 *  world and deleted from memory at the end of the current Update loop. 
	 * 
	 * The protected Renderable::PreDestroy function is guaranteed to be 
	 *  called exactly once by this function, even if you call it many times. 
	 */
	void Destroy() 
	{
		if( IsDestroyed() )
			return;
		PreDestroy(); 
		_deleteMe = true;
	}
	
	/**
	 * Used by the World to see if a Renderable is flagged to be deleted. 
	 * 
	 * @return True if the Renderable should be removed and deleted. 
	 */
	bool IsDestroyed() {return _deleteMe;}
	
	/**
	 * The layer to which this Renderable has been assigned in the world. 
	 *  returns garbage if it hasn't been added to the World yet. (Negative 
	 *  layers are valid.)
	 * 
	 * @return The world layer for this Renderable
	 */
	int GetLayer() {return _layer;}
protected:
	/**
	 * Will get called before this Renderable is destroyed (if you do it via 
	 *  the Destroy function, obviously). Override this function in a subclass
	 *  to do any cleanup work that is appropriate to your element. 
	 */
	virtual void PreDestroy() {}

protected:
	bool _deleteMe;
	int _layer;
};
