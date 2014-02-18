%module angel
%{
#include "../../Actors/PhysicsActor.h"
%}

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
	void SetFixedRotation(bool fixedRotation);
	
	virtual void InitPhysics();
	virtual void CustomInitPhysics();
	
	void ApplyForce(const Vector2& force, const Vector2& point);
	void ApplyLocalForce(const Vector2& force, const Vector2& point);
	void ApplyTorque(float torque);
	void ApplyLinearImpulse(const Vector2& impulse, const Vector2& point);
	void ApplyAngularImpulse(float impulse);
	
	virtual void SetSize(float x, float y = -1.f);
	virtual void SetSize(const Vector2& newSize);
	
	void SetDrawSize(float x, float y = -1.f);
	
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const Vector2& pos);

	virtual void SetRotation(float rotation);
	
	virtual void MoveTo(const Vector2& newPosition, float duration, bool smooth=false, String onCompletionMessage="");
	virtual void RotateTo(float newRotation, float duration, bool smooth=false, String onCompletionMessage="");
	virtual void ChangeSizeTo(const Vector2& newSize, float duration, bool smooth=false, String onCompletionMessage="");
	virtual void ChangeSizeTo(float newSize, float duration, bool smooth=false, String onCompletionMessage="");

	virtual const String GetClassName() const;
};

