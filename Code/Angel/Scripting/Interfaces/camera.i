%module angel
%{
#include "../../Infrastructure/Camera.h"
%}

%nodefaultctor Camera;
class Camera : public Actor 
{
public:
	static Camera &GetInstance();
	
	void Reset();

	void LockTo(Actor* locked, bool lockX=true, bool lockY=true, bool lockRotation=false);
	Actor* GetLockedActor();
	
	const int GetWindowHeight();
	const int GetWindowWidth();
	
	const double GetViewRadius();
	const Vector2 GetWorldMaxVertex();
	const Vector2 GetWorldMinVertex();

	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const Vector3& v3);
	virtual void SetPosition(const Vector2& v2);

	virtual void SetRotation(float rotation);

	virtual void MoveTo(const Vector3& newPosition, float duration, bool smooth=false, String onCompletionMessage="");

	float GetZ();
	float GetZForViewRadius(float radius);
	float GetNearClipDist();
	float GetFarClipDist();

	virtual void SetZByViewRadius(float newRadius);
	virtual void SetNearClipDist(float dist);
	virtual void SetFarClipDist(float dist);
	
	virtual void SetViewCenter(float x, float y, float z);
	const Vector3& GetViewCenter();

	virtual const String GetClassName() const;
};
