#pragma once

#include "../Actors/Actor.h"

#include "Box2D.h"
struct b2ShapeDef;


class PhysicsActor : public Actor
{
public:
	PhysicsActor();
	virtual ~PhysicsActor();

	enum eShapeType
	{
		SHAPETYPE_BOX,
		SHAPETYPE_CIRCLE,
	};
	
	void SetDensity(float density);
	void SetFriction(float friction);
	void SetRestitution(float restitution);
	void SetShapeType(eShapeType shapeType);
	void SetIsSensor(bool isSensor);
	void SetGroupIndex(int groupIndex);
	void SetCollisionFlags(int collisionFlags);
	void SetFixedRotation(bool fixedRotation);

	virtual void InitPhysics();
	virtual void CustomInitPhysics() {}

	// point parameters in Apply* functions are locations in actor space 
	// (if you want world space, convert yourself or use GetBody() and the underlying Box2D API)
	void ApplyForce(const Vector2& force, const Vector2& point);
	void ApplyLocalForce(const Vector2& force, const Vector2& point);	// apply a local space force on the object
	void ApplyTorque(float torque);
	void ApplyImpulse(const Vector2& impulse, const Vector2& point);

	// note, wake the body before applying velocities or it will continue sleeping (if it was)
	b2Body *GetBody() { return _physBody; }

	// these are dangerous things to do, so have been disabled.
	// implement if you know exactly what you want physics to do in these cases.
	void SetSize(float x, float y = -1.f);
	void SetDrawSize(float x, float y = -1.f);
	void SetPosition(float x, float y);
	void SetPosition(Vector2 pos);
	void SetRotation(float rotation);
	
	void MoveTo(Vector2 newPosition, float duration, String onCompletionMessage="") {}
	void RotateTo(float newRotation, float duration, String onCompletionMessage="") {}
	void ChangeSizeTo(Vector2 newSize, float duration, String onCompletionMessage="") {}
	void ChangeSizeTo(float newSize, float duration, String onCompletionMessage="") {}
	
	virtual bool HandlesCollisionEvents() {return false;}

protected:
	virtual void InitShape(b2ShapeDef* /*shapeDef*/ ) {}
	b2Body *_physBody;
	
	float _density;
	float _friction;
	float _restitution;
	eShapeType _shapeType;
	bool _isSensor;
	int _groupIndex;
	int _collisionFlags;
	bool _fixedRotation;

private:
	friend class World;

	void _syncPosRot(float x, float y, float rotation);
};

