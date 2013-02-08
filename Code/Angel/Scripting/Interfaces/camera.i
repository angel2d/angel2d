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
	
	const int GetWindowHeight();
	const int GetWindowWidth();
	
	const double GetViewRadius();
	const Vector2 GetWorldMaxVertex();
	const Vector2 GetWorldMinVertex();

	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(Vector3 v3);
    void MoveTo(Vector3 newPosition, float duration, bool smooth=false, String onCompletionMessage="");
	virtual float GetZ();
	virtual float GetZForViewRadius(float radius);
	virtual float GetNearClipDist();
	virtual float GetFarClipDist();
	virtual void SetZByViewRadius(float newRadius);
	virtual void SetNearClipDist(float dist);
	virtual void SetFarClipDist(float dist);	
	virtual void SetViewCenter(float x, float y, float z);
	virtual Vector3 GetViewCenter();
};
