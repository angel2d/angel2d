%module angel
%{
#include "../../Infrastructure/Camera.h"
%}

%nodefaultctor Camera;
class Camera : public Actor 
{
public:
	static Camera &GetInstance();
	static void ResizeCallback(int w, int h);
	
	void Reset();
	
	const int GetWindowHeight();
	const int GetWindowWidth();
	
	const double GetViewRadius();
	const Vector2 GetWorldMaxVertex();
	const Vector2 GetWorldMinVertex();

	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(Vector2 v2);
	virtual void SetPosition(Vector3 v3);
	virtual Vector2 GetPosition();
	virtual float GetZ();
	virtual void SetViewCenter(float x, float y, float z);
	virtual Vector3 GetViewCenter();
};
