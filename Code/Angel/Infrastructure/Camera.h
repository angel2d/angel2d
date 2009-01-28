#pragma once

#include "../Actors/Actor.h"
#include "../Infrastructure/Vector3.h"

#define theCamera Camera::GetInstance()

//Camera is an actor so we can add weight and movement to it as easily as
//  we do with actors
class Camera : public Actor 
{
public:
	static Camera &GetInstance();
	static void ResizeCallback(int w, int h);

	void Destroy();

	void Render();

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

protected:
	Camera();
	static Camera *s_Camera;

	void Resize(int w, int h);

private:
	int _windowWidth;
	int _windowHeight;
	double _aperture;
	Vector3 _position;
	Vector3 _view;
	Vector3 _up;
};

