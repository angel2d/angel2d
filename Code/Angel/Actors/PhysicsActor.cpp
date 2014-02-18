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
#include "../Actors/PhysicsActor.h"

#include "../Infrastructure/World.h"
#include "../Infrastructure/Log.h"
#include "../Util/MathUtil.h"

#include <Box2D/Box2D.h>


#define POST_PHYSICS_INIT_WARNING "WARNING: %s had no effect; don't change an actor after its physics have been initialized."
#define PRE_PHYSICS_INIT_WARNING "WARNING: %s had no effect; this actor's physics were not initialized."

PhysicsActor::PhysicsActor(void) :	
_physBody(NULL),
_density(1.f),
_friction(0.3f),
_restitution(0.0f),
_shapeType(SHAPETYPE_BOX),
_isSensor(false),
_groupIndex(0), 
_fixedRotation(false)
{
}

PhysicsActor::~PhysicsActor()
{
	if( _physBody != NULL )
	{
		_physBody->SetUserData(NULL);
		theWorld.GetPhysicsWorld().DestroyBody(_physBody);
	}
}

void PhysicsActor::SetDensity(float density)
{
	if (_physBody == NULL)
		_density = density;
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetDensity()");
}

void PhysicsActor::SetFriction(float friction)
{
	if (_physBody == NULL)
		_friction = friction;
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetFriction()");	
}

void PhysicsActor::SetRestitution(float restitution)
{
	if (_physBody == NULL)
		_restitution = restitution;
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetRestitution()");
}

void PhysicsActor::SetShapeType(eShapeType shapeType)
{
	if (_physBody == NULL)
		_shapeType = shapeType;
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetShapeType()");
}

void PhysicsActor::SetIsSensor(bool isSensor)
{
	if (_physBody == NULL)
		_isSensor = isSensor;
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetIsSensor()");
}

void PhysicsActor::SetGroupIndex(int groupIndex)
{
	if (_physBody == NULL)
		_groupIndex = groupIndex;
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetGroupIndex()");
}

void PhysicsActor::SetFixedRotation(bool fixedRotation)
{
	if (_physBody == NULL)
		_fixedRotation = fixedRotation;
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetFixedRotation()");
}


void PhysicsActor::InitPhysics()
{
	if (!theWorld.IsPhysicsSetUp())
	{
		sysLog.Log("ERROR: World physics must be initialized before Actor's.");
		return;
	}
	
	b2CircleShape circle;
	b2PolygonShape box;
	b2Shape* shape = NULL;
	if (_shapeType == SHAPETYPE_BOX)
	{
		// The extents is just a vector of the box's half widths. 
		// Box2D is tuned for meters, kilograms, and seconds. (Unless you've changed its units. [You probably shouldn't.])
		box.SetAsBox(0.5f*_size.X, 0.5f*_size.Y);
		shape = &box;
	}
	else if (_shapeType == SHAPETYPE_CIRCLE)
	{
		circle.m_radius = 0.5f*_size.X;
		shape = &circle;
	}
	else
	{
		sysLog.Log("ERROR: Invalid shape type given.");
		return;
	}
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.density = _density;
	fixtureDef.friction = _friction;
	fixtureDef.restitution = _restitution;
	
	fixtureDef.filter.groupIndex = _groupIndex;
	fixtureDef.isSensor = _isSensor;
	
	InitShape( shape );
	
	b2BodyDef bd;
	bd.userData = this;
	bd.position.Set(_position.X, _position.Y);
	bd.angle = MathUtil::ToRadians(_rotation);
	bd.fixedRotation = _fixedRotation;
	if (MathUtil::FuzzyEquals(_density, 0.0f))
	{
		bd.type = b2_staticBody;
	}
	else 
	{
		bd.type = b2_dynamicBody;
	}
	
	_physBody = theWorld.GetPhysicsWorld().CreateBody(&bd);
	_physBody->CreateFixture(&fixtureDef);
	_physBody->SetUserData(this);
	CustomInitPhysics();
}

void PhysicsActor::ApplyForce(const Vector2& force, const Vector2& point)
{
	if (_physBody != NULL)
		_physBody->ApplyForce(b2Vec2(force.X, force.Y), b2Vec2(point.X + _position.X, point.Y + _position.Y));
	else
		sysLog.Printf(PRE_PHYSICS_INIT_WARNING, "ApplyForce()");
}

void PhysicsActor::ApplyLocalForce(const Vector2& force, const Vector2& point)
{
	if (_physBody != NULL)
		_physBody->ApplyForce(_physBody->GetWorldVector(b2Vec2(force.X, force.Y)), b2Vec2(point.X + _position.X, point.Y + _position.Y));
	else
		sysLog.Printf(PRE_PHYSICS_INIT_WARNING, "ApplyLocalForce()");
}

void PhysicsActor::ApplyTorque(float torque)
{
	if (_physBody != NULL)
		_physBody->ApplyTorque(torque);
	else
		sysLog.Printf(PRE_PHYSICS_INIT_WARNING, "ApplyTorque()");
}

void PhysicsActor::ApplyLinearImpulse(const Vector2& impulse, const Vector2& point)
{
	if (_physBody != NULL)
		_physBody->ApplyLinearImpulse(b2Vec2(impulse.X, impulse.Y), b2Vec2(point.X + _position.X, point.Y + _position.Y));
	else
		sysLog.Printf(PRE_PHYSICS_INIT_WARNING, "ApplyLinearImpulse()");	
}

void PhysicsActor::ApplyAngularImpulse(float impulse)
{
	if (_physBody != NULL)
		_physBody->ApplyAngularImpulse(impulse);
	else
		sysLog.Printf(PRE_PHYSICS_INIT_WARNING, "ApplyAngularImpulse()");
}

void PhysicsActor::SetSize(float x, float y)
{
	if (_physBody == NULL)
		Actor::SetSize(x, y);
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetSize()");
}

void PhysicsActor::SetSize(const Vector2& newSize)
{
	if (_physBody == NULL)
		Actor::SetSize(newSize);
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetSize()");
}

void PhysicsActor::SetDrawSize(float x, float y)
{
	Actor::SetSize(x,y);
}

void PhysicsActor::SetPosition(float x, float y)
{
	if (_physBody == NULL)
		Actor::SetPosition(x, y);
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetPosition()");
}

void PhysicsActor::SetPosition(const Vector2& pos)
{
	if (_physBody == NULL)
		Actor::SetPosition(pos);
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetPosition()");
}

void PhysicsActor::SetRotation(float rotation)
{
	if (_physBody == NULL)
		Actor::SetRotation(rotation);
	else
		sysLog.Printf(POST_PHYSICS_INIT_WARNING, "SetRotation()");
}

void PhysicsActor::_syncPosRot(float x, float y, float rotation)
{
	_position.X = x;
	_position.Y = y;
	_rotation = rotation;
	while (_rotation > 180.f)
		_rotation -= 360.f;
	while (_rotation < -180.f)
		_rotation += 360.f;
}

