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
#include "Gwen/Skins/Simple.h"
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

GwenRenderer* UserInterface::_renderer = NULL;
bool UserInterface::isInitialized = false;

namespace 
{
	Gwen::Controls::Canvas* AngelCanvas;
	Gwen::Skin::Simple* AngelSkin;
}

void UserInterface::Initialize()
{
	UserInterface::_renderer = new GwenRenderer();
	
	AngelSkin = new Gwen::Skin::Simple();
	AngelSkin->SetRender(_renderer);
	AngelSkin->SetDefaultFont(Gwen::Utility::StringToUnicode("Resources/Fonts/Inconsolata.otf"));
	
	AngelCanvas = new Gwen::Controls::Canvas(AngelSkin);
	AngelCanvas->SetSize(1024, 768); // should be size of window (update when change)
	
	Gwen::Controls::Button* button = new Gwen::Controls::Button(AngelCanvas);
//    button->SetBounds(1024 / 2, 768 / 2, 20, 10);
	button->SetText("Angelic Button");
	button->SetPos(1024 / 2 - (button->GetSize().x / 2), 768 / 2 - (button->GetSize().y / 2));
	button->onPress.Add(&handler, &EventHandler::OnPress);

	isInitialized = true;
}

void UserInterface::Finalize()
{
	delete AngelCanvas;
	delete AngelSkin;
	
	delete _renderer;
	isInitialized = false;
}

void UserInterface::Render()
{
	if (!isInitialized)
	{
		return;
	}

	AngelCanvas->DoThink();
	AngelCanvas->RenderCanvas();
}

void UserInterface::HandleMouseMoved(int x, int y, int deltaX, int deltaY)
{
	AngelCanvas->InputMouseMoved(x, y, deltaX, deltaY);
}

void UserInterface::HandleMouseButton(int button, bool down)
{
    AngelCanvas->InputMouseButton(button, down);
}

void UserInterface::HandleMouseWheel(int val)
{
    AngelCanvas->InputMouseWheel(val);
}

void UserInterface::HandleKey(int key, bool down)
{
    AngelCanvas->InputKey(key, down);
}

void UserInterface::HandleCharacter(wchar_t chr)
{
    AngelCanvas->InputCharacter(chr);
}


