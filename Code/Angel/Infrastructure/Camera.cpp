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

#if !ANGEL_MOBILE
	void Camera::ResizeCallback(GLFWwindow* window, int w, int h)
	{
		theCamera.Resize(w, h);
	}
#endif

void Camera::Reset()
{
	_aperture = 90.0f;
	_camera3DPosition = Vector3(0.0f, 0.0f, 10.0f);
	_position = Vector2(0.0f, 0.0f);
	_view = Vector3(0.0f, 0.0f, -10.0f);
	_up = Vector3(0.0f, 1.0f, 0.0);
	_zNearClip = 0.001f;
	_zFarClip = 200.f;
	_locked = NULL;
}

void Camera::LockTo(Actor *locked, bool lockX, bool lockY, bool lockRotation)
{
	_locked = locked;
	_lockX = lockX;
	_lockY = lockY;
	_lockRotation = lockRotation;
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
	float aspect = (float)_windowWidth/(float)_windowHeight;
	gluPerspective(_aperture, aspect, _zNearClip, _zFarClip);
	glMatrixMode(GL_MODELVIEW);

	theSwitchboard.Broadcast(new Message("CameraChange"));
}

const int Camera::GetWindowHeight() const
{
	return _windowHeight;
}

const int Camera::GetWindowWidth() const
{
	return _windowWidth;
}

const double Camera::GetViewRadius() const
{
	double sideAngle = MathUtil::ToRadians(_aperture / 2.0);
	return tan(sideAngle) * fabs(_camera3DPosition.Z);
}

const Vector2 Camera::GetWorldMaxVertex() const
{
	return MathUtil::ScreenToWorld(GetWindowWidth(), 0);
}

const Vector2 Camera::GetWorldMinVertex() const
{
	return MathUtil::ScreenToWorld(0, GetWindowHeight());
}

void Camera::Update(float dt)
{
	Actor::Update(dt);
	
	if (_locked != NULL)
	{
		bool change = false;
		Vector2 pos = _locked->GetPosition();
		if (_lockX && !MathUtil::FuzzyEquals(_camera3DPosition.X, pos.X))
		{
			_camera3DPosition.X = pos.X;
			_position.X = pos.X;
			change = true;
		}
		if (_lockY && !MathUtil::FuzzyEquals(_camera3DPosition.Y, pos.Y))
		{
			_camera3DPosition.Y = pos.Y;
			_position.Y = pos.Y;
			change = true;
		}
		if (_lockRotation && !MathUtil::FuzzyEquals(_rotation, _locked->GetRotation()))
		{
			_rotation = _locked->GetRotation();
			change = true;
		}
		if (change)
		{
			theSwitchboard.Broadcast(new Message("CameraChange"));
		}
	}
    else
    {
        if (_3dPositionInterval.ShouldStep())
        {
            SetPosition(_3dPositionInterval.Step(dt));
            if (!_3dPositionInterval.ShouldStep())
            {
                if (_3dPositionIntervalMessage != "")
                {
                    theSwitchboard.Broadcast(new Message(_3dPositionIntervalMessage, this));
                }
            }
        }
    }
}

void Camera::Render()
{
	/*
		TODO Make this so it only updates if things have been dirtied. 
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
	gluLookAt(_camera3DPosition.X, _camera3DPosition.Y, _camera3DPosition.Z,
			_camera3DPosition.X + _view.X,
			_camera3DPosition.Y + _view.Y,
			_camera3DPosition.Z + _view.Z,
			_up.X, _up.Y, _up.Z
		);
}

void Camera::SetPosition(float x, float y, float z)
{
	_camera3DPosition = Vector3(x, y, z);
	_position = Vector2(_camera3DPosition.X, _camera3DPosition.Y);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

void Camera::SetPosition(float x, float y)
{
	_camera3DPosition = Vector3(x, y, _camera3DPosition.Z);
	_position = Vector2(_camera3DPosition.X, _camera3DPosition.Y);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

void Camera::SetPosition(const Vector2& v2)
{
	_camera3DPosition = Vector3(v2.X, v2.Y, _camera3DPosition.Z);
	_position = Vector2(_camera3DPosition.X, _camera3DPosition.Y);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

void Camera::SetPosition(const Vector3& v3)
{
	_camera3DPosition = v3;
	_position = Vector2(_camera3DPosition.X, _camera3DPosition.Y);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

void Camera::MoveTo(const Vector3& newPosition, float duration, bool smooth, String onCompletionMessage)
{
	_3dPositionInterval = Interval<Vector3>(_camera3DPosition, newPosition, duration, smooth);
	_3dPositionIntervalMessage = onCompletionMessage;
}

float Camera::GetZ() const
{
	return _camera3DPosition.Z;
}

void Camera::SetRotation(float newRotation)
{
	Actor::SetRotation(newRotation);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

float Camera::GetZForViewRadius(float radius)
{
	double sideAngle = MathUtil::ToRadians(_aperture / 2.0);
	return radius / tan(sideAngle);
}

float Camera::GetNearClipDist()
{
	return _zNearClip;
}

float Camera::GetFarClipDist()
{
	return _zFarClip;
}

void Camera::SetZByViewRadius(float newRadius)
{
	double sideAngle = MathUtil::ToRadians(_aperture / 2.0);
	_camera3DPosition.Z = newRadius / tan(sideAngle);
}

void Camera::SetNearClipDist(float dist)
{
	_zNearClip = dist;
	Resize(_windowWidth, _windowHeight);
}

void Camera::SetFarClipDist(float dist)
{
	_zFarClip = dist;
	Resize(_windowWidth, _windowHeight);
}

void Camera::SetViewCenter(float x, float y, float z)
{
	_view = Vector3(x, y, z);
	theSwitchboard.Broadcast(new Message("CameraChange"));
}

const Vector3& Camera::GetViewCenter() const
{
	return _view;
}

