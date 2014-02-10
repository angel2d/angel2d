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
#include "../Input/MouseInput.h"

#include "../Infrastructure/Common.h"

std::set<MouseListener*> _mouseSubscribers;
Vec2i _mouseLocation;

MouseListener::MouseListener()
{
	RegisterMouseSubscriber(this);
}

MouseListener::~MouseListener()
{
	DeregisterMouseSubscriber(this);
}


void MouseListener::MouseDownEvent(Vec2i /*screenCoordinates*/, MouseButtonInput /*button*/) {}
void MouseListener::MouseUpEvent(Vec2i /*screenCoordinates*/, MouseButtonInput /*button*/) {}
void MouseListener::MouseMotionEvent(Vec2i /*screenCoordinates*/) {}
void MouseListener::MouseWheelEvent(const Vector2& /*scrollOffset*/) {}

void RegisterMouseSubscriber(MouseListener* actor)
{
	_mouseSubscribers.insert(actor);
}

void DeregisterMouseSubscriber(MouseListener *actor)
{
	std::set<MouseListener*>::iterator it = _mouseSubscribers.find(actor);
	if (it != _mouseSubscribers.end())
	{
		_mouseSubscribers.erase(it);
	}
}

void MouseMotion(GLFWwindow* window, double x, double y)
{
	_mouseLocation.X = (int)x;
	_mouseLocation.Y = (int)y;
	std::set<MouseListener*>::iterator it = _mouseSubscribers.begin();
	while (it != _mouseSubscribers.end())
	{
		(*it)->MouseMotionEvent(Vec2i(x, y));
		it++;
	}
}

void MouseButton(GLFWwindow* window, int button, int state, int mods)
{
	MouseButtonInput mouseButton;
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		mouseButton = MOUSE_RIGHT;
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		mouseButton = MOUSE_MIDDLE;
	}
	else
	{
		mouseButton = MOUSE_LEFT;
	}

	std::set<MouseListener*>::iterator it = _mouseSubscribers.begin();
	while (it != _mouseSubscribers.end())
	{
		if (state == GLFW_PRESS)
		{
			(*it)->MouseDownEvent(_mouseLocation, mouseButton);
		}
		else
		{
			(*it)->MouseUpEvent(_mouseLocation, mouseButton);
		}
		it++;
	}
}

void MouseWheel(GLFWwindow* window, double x, double y)
{
	std::set<MouseListener*>::iterator it = _mouseSubscribers.begin();
	Vector2 offset(x, y);
	while (it != _mouseSubscribers.end())
	{
		(*it)->MouseWheelEvent(offset);
		it++;
	}
}
