//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2012, Shane Liesegang
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
#include "../UI/UserInterface.h"

#include "../UI/GwenRenderer.h"

#include "Gwen/Gwen.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/Controls/Canvas.h"
#include "Gwen/Controls/Button.h"

#include "../Infrastructure/Log.h"


class EventHandler : public Gwen::Event::Handler
{
public:
	void OnPress(Gwen::Controls::Base* control)
	{
		sysLog.Printf("Button pressed!");
	}
};

EventHandler handler;


namespace 
{
	Gwen::Controls::Canvas* AngelCanvas;
	Gwen::Skin::Base* AngelSkin;
}

UserInterface* UserInterface::s_UserInterface = NULL;

UserInterface& UserInterface::GetInstance()
{
	if (s_UserInterface == NULL)
	{
		s_UserInterface = new UserInterface();
	}
	return *s_UserInterface;
}

UserInterface::UserInterface()
{
	glfwGetMousePos(&_mousePosition.X, &_mousePosition.Y);
	_renderer = new GwenRenderer();
	
	AngelSkin = new Gwen::Skin::TexturedBase(_renderer);
    ((Gwen::Skin::TexturedBase*)AngelSkin)->Init("Resources/Images/DefaultSkin.png");
	AngelSkin->SetDefaultFont(Gwen::Utility::StringToUnicode("Resources/Fonts/Inconsolata.otf"), 20.0f);
	
	AngelCanvas = new Gwen::Controls::Canvas(AngelSkin);
	AngelCanvas->SetSize(1024, 768); // should be size of window (update when change)
    
	Gwen::Controls::Button* button = new Gwen::Controls::Button(AngelCanvas);
    button->SetSize(160, 40);
	button->SetText("Angelic Button");
	button->SetPos(1024 / 2 - (button->GetSize().x / 2), 768 / 2 - (button->GetSize().y / 2));
	button->onPress.Add(&handler, &EventHandler::OnPress);
}

UserInterface::~UserInterface()
{
    
}

void UserInterface::Shutdown()
{
    delete AngelCanvas;
	delete AngelSkin;
	
	delete _renderer;
}

void UserInterface::Render()
{
	AngelCanvas->DoThink();
	AngelCanvas->RenderCanvas();
}

void UserInterface::MouseMotionEvent(Vec2i screenCoordinates)
{
	int deltaX = _mousePosition.X - screenCoordinates.X;
	int deltaY = _mousePosition.Y - screenCoordinates.Y;
    _mousePosition.X = screenCoordinates.X;
    _mousePosition.Y = screenCoordinates.Y;
	AngelCanvas->InputMouseMoved(screenCoordinates.X, screenCoordinates.Y, deltaX, deltaY);
}

void UserInterface::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
	AngelCanvas->InputMouseButton(button, true);
}

void UserInterface::MouseUpEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
	AngelCanvas->InputMouseButton(button, false);
}

void UserInterface::MouseWheelEvent(int position)
{
	AngelCanvas->InputMouseWheel(position);
}

void UserInterface::HandleKey(int key, bool down)
{
    AngelCanvas->InputKey(key, down);
}

void UserInterface::HandleCharacter(wchar_t chr)
{
    AngelCanvas->InputCharacter(chr);
}


