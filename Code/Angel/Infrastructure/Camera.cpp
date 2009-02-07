#include "../Infrastructure/Camera.h"

#include "../Infrastructure/Common.h"
#include "../Infrastructure/World.h"
#include "../Util/MathUtil.h"
#include "../Messaging/Switchboard.h"

#include <math.h>

Camera *Camera::s_Camera = NULL;

Camera::Camera()
{
	Reset();
}

Camera &Camera::GetInstance()
{
	if (s_Camera == NULL)
	{
		s_Camera = new Camera();
	}
	return *s_Camera;
}

//destroy the singleton
void Camera::Destroy()
{
	delete s_Camera;
	s_Camera = NULL;
}

void Camera::ResizeCallback(int w, int h)
{
	theCamera.Resize(w, h);
}

void Camera::Reset()
{
	_aperture = 90.0f;
	_position = Vector3(0.0f, 0.0f, 10.0f);
	_view = Vector3(0.0f, 0.0f, -10.0f);
	_up = Vector3(0.0f, 1.0f, 0.0);
}

void Camera::Resize(int width, int height)
{
	if ( (_windowHeight != height) || (_windowWidth != width) ) 
	{
		_windowHeight = height;
		_windowWidth = width;

		glViewport(0, 0, _windowWidth, _windowHeight);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_aperture, (float)_windowWidth/(float)_windowHeight, 0.001f, 200.0f);
	glMatrixMode(GL_MODELVIEW);

	theSwitchboard.Broadcast(new Message("CameraChange"));
}

const int Camera::GetWindowHeight()
{
	return _windowHeight;
}

const int Camera::GetWindowWidth()
{
	return _windowWidth;
}

const double Camera::GetViewRadius() 
{
	double sideAngle = MathUtil::ToRadians(_aperture / 2.0);
	return tan(sideAngle) * abs(_position.Z);
}

const Vector2 Camera::GetWorldMaxVertex()
{
	return MathUtil::ScreenToWorld(GetWindowWidth(), 0);
}

const Vector2 Camera::GetWorldMinVertex()
{
	return MathUtil::ScreenToWorld(0, GetWindowHeight());
}

void Camera::Render()
{
	/*
		TODO Make this so it only updates if things have been dirtied. 
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(_position.X, _position.Y, _position.Z,
			_position.X + _view.X,
			_position.Y + _view.Y,
			_position.Z + _view.Z,
			_up.X, _up.Y, _up.Z
		);
}

void Camera::SetPosition(float x, float y, float z)
{
	_position = Vector3(x, y, z);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

void Camera::SetPosition(float x, float y)
{
	_position = Vector3(x, y, _position.Z);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

void Camera::SetPosition(Vector2 v2)
{
//	_position = Vector3(v2.X, v2.Y, 0);
	_position = Vector3(v2.X, v2.Y, _position.Z);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

void Camera::SetPosition(Vector3 v3)
{
	_position = v3;
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

Vector2 Camera::GetPosition()
{
	return Vector2(_position.X, _position.Y);
}

float Camera::GetZ()
{
	return _position.Z;
}

void Camera::SetViewCenter(float x, float y, float z)
{
	_view = Vector3(x, y, z);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

Vector3 Camera::GetViewCenter()
{
	return _view;
}

