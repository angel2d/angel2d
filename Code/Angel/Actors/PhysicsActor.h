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

#include "../Actors/Actor.h"

#include <Box2D/Box2D.h>
struct b2ShapeDef;

///An Actor that interacts with other Actors using our built-in physics system
/** 
 * Angel incorporates Box2D (http://www.box2d.org) to handle our physics 
 *  simulation. This Actor is a loose wrapping around Box2D so that you don't
 *  need to worry about the underlying library if you're just doing simple
 *  physics. 
 */
class PhysicsActor : public Actor
{
public:
	/**
	 * Sets up a new PhysicsActor with some reasonable default physical 
	 *  properties. Box-shaped; Density = 1.0; Friction = 0.3; Restitution = 
	 *  0.0. 
	 * 
	 * Note that the PhysicsActor won't actually start doing anything until
	 *  you call PhysicsActor::InitPhysics().
	 */
	PhysicsActor();
	
	/**
	 * The destructor removes the PhysicsActor from the internal simulation. 
	 *  It's \b very important to call the destructor when your remove a 
	 *  PhysicsActor from your World, because otherwise the physics engine
	 *  will think it's still around and you'll get some \i strange results. 
	 */
	virtual ~PhysicsActor();
	
	///The two physics shapes we currently support. If you want anything else,
	/// you're going to be delving into the Box2D library itself. 
	enum eShapeType
	{
		SHAPETYPE_BOX,
		SHAPETYPE_CIRCLE,
	};
	
	/**
	 * Set the density to be used by the physics simulation. Box2D assumes
	 *  that the units are kg/m^2. If you set density to 0.0, the PhysicsActor
	 *  is static and will never move in the world. (Other objects will still
	 *  collide with it.)
	 * 
	 * Note that after you call PhysicsActor::InitPhysics, the density is
	 *  locked and this function will do nothing but spew a warning. 
	 * 
	 * @param density Desired density 
	 */
	void SetDensity(float density);
	
	/**
	 * Set the friction to be used by the physics simulation. 0.0 indicates 
	 *  no friction, while 1.0 indicates very high friction. 
	 * 
	 * Note that after you call PhysicsActor::InitPhysics, the friction is
	 *  locked and this function will do nothing but spew a warning.
	 * 
	 * @param density Desired friction 
	 */
	void SetFriction(float friction);
	
	/**
	 * Set the restitution (bounciness) to be used by the physics simulation. 
	 *  0.0 indicates no bounce at all, while 1.0 is a superball. 
	 * 
	 * Note that after you call PhysicsActor::InitPhysics, the restitution is
	 *  locked and this function will do nothing but spew a warning.
	 * 
	 * @param density Desired restitution 
	 */
	void SetRestitution(float restitution);
	
	/**
	 * Set the shape you want to use for this object. 
	 * 
	 * Note that after you call PhysicsActor::InitPhysics, the restitution is
	 *  locked and this function will do nothing but spew a warning.
	 * 
	 * @param shapeType Either SHAPETYPE_BOX or SHAPETYPE_CIRCLE.
	 */
	void SetShapeType(eShapeType shapeType);
	
	/**
	 * If you set an object up as a sensor, it will cause collision messages
	 *  to be sent, but not actually physically react to the collision. 
	 *  Useful for detecting when objects have entered certain regions. 
	 * 
	 * Note that after you call PhysicsActor::InitPhysics, the restitution is
	 *  locked and this function will do nothing but spew a warning.
	 * 
	 * @param isSensor True if the object should be a sensor, false if not. 
	 *   PhysicsActors are assumed to \b not be sensors unless otherwise
	 *   specified. 
	 */
	void SetIsSensor(bool isSensor);
	
	/**
	 * Set a group index if you want to have objects only collide with certain
	 *  other groups of objects. Positive numbers mean that objects always
	 *  collide, negative numbers mean they never will. 
	 * 
	 * See the Box2D documentation for more information on collision groups
	 * 
	 * Note that after you call PhysicsActor::InitPhysics, the group index is
	 *  locked and this function will do nothing but spew a warning.
	 * 
	 * @param groupIndex The new group index for this PhysicsActor
	 */
	void SetGroupIndex(int groupIndex);
	
	/**
	 * If true, this PhysicsActor will not rotate (useful for characters).
	 * 
	 * Note that after you call PhysicsActor::InitPhysics, the this value is
	 *  locked and the function will do nothing but spew a warning.
	 * 
	 * @param fixedRotation 
	 */
	void SetFixedRotation(bool fixedRotation);
	
	/**
	 * Start simulating this PhysicsActor in the world. 
	 */
	virtual void InitPhysics();
	
	/**
	 * If you want to have your own setup in a derived class, you can 
	 *  implement this function there. It's called at the end of the base
	 *  class's PhysicsActor::InitPhysics.
	 */
	virtual void CustomInitPhysics() {}

	/**
	 * Apply a force to an object. The standard units are Newtons (kg * 
	 *  m/s^2). The point parameter is a location in actor space; if you want
	 *  world space, you can either convert it yourself or use GetBody() to
	 *  manipulate the underlying Box2D API. 
	 * 
	 * ApplyForce should be called every timestep if you want the force to 
	 *  be continuously applied. 
	 * 
	 * @param force The force to apply (direction and magnitude are 
	 *   significant) in Newtons
	 * @param point The point in actor space to which the force should be
	 *   applied
	 */
	void ApplyForce(const Vector2& force, const Vector2& point);
	
	/**
	 * Applies a force relative to the Actor. The standard units are Newtons
	 *  (kg * m/s^2). The point parameter is a location in actor space; if 
	 *  you want world space, you can either convert it yourself or use 
	 *  GetBody() to manipulate the underlying Box2D API.
	 * 
	 * ApplyLocalForce should be called every timestep if you want the force 
	 *  to be continuously applied.
	 * 
	 * @param force The force to apply (direction and magnitude are 
	 *   significant) in Newtons
	 * @param point The point in actor space to which the force should be
	 *   applied
	 */
	void ApplyLocalForce(const Vector2& force, const Vector2& point); 
	
	/**
	 * Apply torque to affect angular velocity without affecting linear
	 *  velocity. The standard units are Newton-meters. 
	 * 
	 * @param torque Amount of torque to apply around the Z-axis. 
	 */
	void ApplyTorque(float torque);
	
	/**
	 * Similar to ApplyForce, but will immediately affect a PhysicsActor's 
	 *  velocity, as opposed to forces which need to be applied every frame. 
	 *  The result is that ApplyImpulse will appear to have roughly 30x the 
	 *  affect of ApplyForce. 
	 * 
	 * For more information: 
	 *  http://www.box2d.org/forum/viewtopic.php?f=3&t=260
	 * 
	 * The point parameter is a location in actor space; if you want world 
	 *  space, you can either convert it yourself or use GetBody() to 
	 *  manipulate the underlying Box2D API.
	 * 
	 * @param impulse The strength of the impulse to apply. 
	 * @param point 
	 */
	void ApplyLinearImpulse(const Vector2& impulse, const Vector2& point);
	
	/**
	 * Similar to ApplyLinearImpulse, but affects the angular rather than 
	 *  linear velocity. 
	 * 
	 * @param impulse The strength of the impulse to apply.
	 */
	void ApplyAngularImpulse(float impulse);
	
	/**
	 * Get the Box2D representation of this PhysicsActor. If you're going to
	 *  be directly manipulating the Box2D API, this will be useful to you. 
	 * 
	 * @return The Box2D data about the actor
	 */
	b2Body *GetBody() { return _physBody; }

	/**
	 * Resets the internal pointer to the Box2D physics body to NULL. Call
	 *  this if you're manually destroying the body for some reason and 
	 *  need to make sure the PhysicsActor doesn't keep trying to track
	 *  it. 
	 */
	void ResetBody() { _physBody = NULL; }
	
	/**
	 * An override of the Actor::SetSize function that disables itself after
	 *  #InitPhysics has been called.
	 */
	void SetSize(float x, float y = -1.f);
	
	/**
	 * Sometimes you want the visible size of an Actor to be larger or smaller
	 *  than its collision geometry in the world. This function lets you alter
	 *  the former without affecting the latter. 
	 * 
	 * @param x Horizontal draw size in OpenGL units -- negative numbers 
	 *   treated as zero
	 * @param y Vertical draw size in OpenGL units -- if less than or equal to 
	 *   zero, assumed to be equal to x
	 */
	void SetDrawSize(float x, float y = -1.f);
	
	/**
	 * An override of the Actor::SetPosition function that disables itself 
	 *  after #InitPhysics has been called.
	 */
	void SetPosition(float x, float y);
	
	/**
	 * An override of the Actor::SetPosition function that disables itself 
	 *  after #InitPhysics has been called.
	 */
	void SetPosition(const Vector2& pos);
	
	/**
	 * An override of the Actor::SetRotation function that disables itself 
	 *  after #InitPhysics has been called.
	 */
	void SetRotation(float rotation);
	
	/**
	 * An override of the Actor::MoveTo function that doesn't allow the 
	 *  interval to be applied to PhysicsActors. 
	 */
	void MoveTo(const Vector2& newPosition, float duration, String onCompletionMessage="") {}
	
	/**
	 * An override of the Actor::RotateTo function that doesn't allow the 
	 *  interval to be applied to PhysicsActors.
	 */
	void RotateTo(float newRotation, float duration, String onCompletionMessage="") {}
	
	/**
	 * An override of the Actor::ChangeSizeTo function that doesn't allow the 
	 *  interval to be applied to PhysicsActors.
	 */
	void ChangeSizeTo(const Vector2& newSize, float duration, String onCompletionMessage="") {}
	
	/**
	 * An override of the Actor::ChangeSizeTo function that doesn't allow the 
	 *  interval to be applied to PhysicsActors.
	 */
	void ChangeSizeTo(float newSize, float duration, String onCompletionMessage="") {}
	
	/**
	 * Used by the SetName function to create a basename for this class. 
	 *  Overridden from Actor::GetClassName.
	 * 
	 * @return The string "PhysicsActor"
	 */
	virtual const String GetClassName() const { return "PhysicsActor"; }

protected:
	virtual void InitShape(b2Shape* /*shapeDef*/ ) {}
	b2Body *_physBody;
	
	float _density;
	float _friction;
	float _restitution;
	eShapeType _shapeType;
	bool _isSensor;
	int _groupIndex;
	bool _fixedRotation;

private:
	friend class World;

	void _syncPosRot(float x, float y, float rotation);
};

