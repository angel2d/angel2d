//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
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

#pragma once

#if ANGEL_MOBILE
    #include "../Input/MultiTouch.h"
#else
    #include "../Input/MouseInput.h"
#endif

#include "../Util/StringUtil.h"

class GwenRenderer;

//singleton shortcut
#define theUI UserInterface::GetInstance()

typedef void* AngelUIHandle;


#if ANGEL_MOBILE
    class UserInterface : public TouchListener
#else
    class UserInterface : public MouseListener
#endif
{
public:
	/**
	 * Used to access the singleton instance of this class. As a shortcut,
	 *  you can just use "theUI".
	 *
	 * @return The singleton
	 */
	static UserInterface& GetInstance();
	
	/**
	 * For internal engine use only; does the actual UI drawing.
	 */
	void Render();
	
    #if ANGEL_MOBILE
        virtual void TouchMotionEvent(Touch* movedTouch);
        virtual void TouchEndEvent(Touch* endedTouch);
        virtual void TouchStartEvent(Touch* startedTouch);
    #else
        // Mouse listener implementation functions
        virtual void MouseMotionEvent(Vec2i screenCoordinates);
        virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
        virtual void MouseUpEvent(Vec2i screenCoordinates, MouseButtonInput button);
        virtual void MouseWheelEvent(const Vector2& position);
    
        /**
         * For internal engine use only; handles keyboard input.
         */
        void HandleKey(int key, bool down);
    
        /**
         * For internal engine use only; handles keyboard input.
         */
        void HandleCharacter(wchar_t chr);
    #endif // ANGEL_MOBILE
	
	/**
	 * For internal engine use only; shuts down the UI layer cleanly when the world is destroyed.
	 */
	void Shutdown();
	
	/**
	 * Adds a UI button to the world with formatting and a callback function.
	 *
	 * @param label The text that will appear on the button
	 * @param position Where the button will appear on screen (in pixel units)
	 * @param callback The function to be called when the button is pressed. Must return
	 *   void and not take any parameters.
	 * @param center Whether the button should be centered on the given position. If false,
	 *   the position will be its top left. 
	 * @param font The font to use for the button's text. If left as an empty string (the
	 *   default), it will use the UI layer's default font, which is the same as the Angel
	 *   console.
	 * @param padding How much space (in pixels) to leave between the text and the edge of the button.
	 * @return A UI handle that can be passed to RemoveUIElement
	 */
	AngelUIHandle AddButton(const String& label, Vec2i position, void (*callback)(), bool center = false, const String& font="", Vec2i padding=Vec2i(10, 10));

	/**
	 * Pops a choice box consisting of several buttons and reports to the callback when
	 *   one is clicked. When a button is clicked, the choice box will automatically remove
	 *   itself, so the AngelUIHandle returned from this function only has to be tracked if
	 *   you want to remove the box manually for some reason.
	 * 
	 * @param choiceLabel The label at the top of the box, describing the choice the player is making
	 * @param labels A list of Strings that will be used for the buttons in the choice
	 * @param callback The function to be called when any of the buttons are pressed. Must return
	 *   void and take a single integer as a parameter. When the function is called, the integer will
	 *   be the index of the button that was pressed (from zero, so it will match the index in the 
	 *   labels list).
	 * @param font The font to use for the buttons' text. If left as an empty string (the
	 *   default), it will use the UI layer's default font, which is the same as the Angel
	 *   console.
	 * @param padding How much space (in pixels) to leave between the text and the edge of the button.
	 *   Also how much space will be left between buttons. 
	 * @return A UI handle that can be passed to RemoveUIElement.
	 */
	AngelUIHandle ShowChoiceBox(const String& choiceLabel, const StringList& labels, void (*callback)(int), const String& font="", Vec2i padding=Vec2i(10, 10), bool modal=true);

	/**
	 * Removes a UI element that was added through one of the UI functions described 
	 *   elsewhere in this file. Requires the opaque handle that was returned when the
	 *   element was created.
	 *
	 * @param element The handle for the UI element to remove. 
	 */
	void RemoveUIElement(AngelUIHandle element);
	
	
protected:
	UserInterface();
	~UserInterface();
	
	static UserInterface* s_UserInterface;

private:
	GwenRenderer* _renderer;

	Vec2i _mousePosition;
	
	std::set<AngelUIHandle> _elements;
	std::vector<AngelUIHandle> _deferredRemoves;
	
	bool _locked;
};
