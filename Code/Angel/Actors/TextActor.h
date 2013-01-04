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

/** @file */
#pragma once

#include "../Actors/Actor.h"

/**
 * An enumeration for the alignment of text within a TextActor
 */
enum TextAlignment
{
	TXT_Left,
	TXT_Center,
	TXT_Right
};

/// An Actor for displaying text on the screen.
/**
 * A TextActor handles drawing text to the screen using world coordinates. The
 *  basis text rendering functions operate in screen-space, which can be annoying
 *  if you want to have debug data or labels for your Actors. 
 * 
 * In addition, a TextActor supports wraps up more functionality than the simple 
 *  text rendering, allowing varying alignments, newlines, etc. 
 */
class TextActor : public Actor
{
public:
	/**
	 * The constructor sets up all the textual information that this TextActor will
	 *  use to draw itself to the screen. 
	 * 
	 * @param fontNickname the name of the font to be used when drawing this TextActor. 
	 *  The name of the font is set with the RegisterFont function. By default it uses
	 *  the monospaced font used in the Console, at 24 points. 
	 * @param displayString the actual text to be displayed
	 * @param align the desired alignment of the text
	 * @param lineSpacing the amount of space (in pixels) between each line of text
	 */
	TextActor(const String& fontNickname="Console", const String& displayString="", TextAlignment align=TXT_Left, int lineSpacing=5);
	
	/**
	 * Override of the Renderable::Render function to draw text
	 */
	virtual void Render();
	
	/**
	 * Get the name of the font currently being used for this Actor
	 * 
	 * @return the nickname of the current font, as set in RegisterFont
	 */
	const String& GetFont() const;
	
	/**
	 * Change the font used in drawing this TextActor. 
	 * 
	 * @param newFont the nickname of the new font. This must be set up with RegisterFont
	 *  before being set here -- the TextActor will not draw at all if this is an invalid
	 *  nickname. 
	 */ 
	void SetFont(const String& newFont);
	
	/**
	 * Get the current string being drawn by this TextActor.
	 * 
	 * @return the display string
	 */
	const String& GetDisplayString() const;
	
	/**
	 * Change the string to be drawn by this TextActor. Newlines can be delimited with
	 *  the plain newline character (\\n).
	 * 
	 * @param newString the string that should be drawn by this TextActor in the next
	 *  frame
	 */
	void SetDisplayString(const String& newString);
	
	/**
	 * Get the current alignment being used by this TextActor
	 * 
	 * @return the text alignment (TXT_Left, TXT_Right, or TXT_Center) 
	 */
	const TextAlignment GetAlignment();
	
	/**
	 * Change the alignment of this TextActor. 
	 * 
	 * @param newAlignment the desigred alignment, as described by the enum 
	 */
	void SetAlignment(TextAlignment newAlignment);

	/**
	 * Get the amount of space between each line that this TextActor draws
	 * 
	 * @return the amount of space (in pixels) that goes between each line
	 */
	const int GetLineSpacing();
	
	/**
	 * Change the line spacing of this TextActor
	 * 
	 * @param newSpacing the desired amount of space (in pixels) between each line 
	 */
	void SetLineSpacing(int newSpacing);

	/**
	 * An override of the SetPosition function, since we need to update the screen
	 *  space drawing coordinates of our text drawing when the TextActor moves in 
	 *  the World.
	 * 
	 * @param x the X coordinate (in GL units) of the TextActor 
	 * @param y the Y coordinate (in GL units) of the TextActor 
	 */
	virtual void SetPosition(float x, float y);
	
	/**
	 * An override of the SetPosition function, since we need to update the screen
	 *  space drawing coordinates of our text drawing when the TextActor moves in 
	 *  the World.
	 * 
	 * @param position a Vector2 indicating the X and Y coordinates of the TextActor
	 * (in GL units) 
	 */
	virtual void SetPosition(const Vector2& position);
	
	/**
	 * An override of the SetRotation function, since we need to update the screen
	 *  space drawing coordinates of our text drawing when the TextActor moves in 
	 *  the World.
	 * 
	 * @param position a float indicating the new rotation counter-clockwise around
	 * the z-axis (in degrees)
	 */
	virtual void SetRotation(float newRotation);
	
	/**
	 * An implementation of the MessageListener interface, which listens for 
	 *  CameraChange messages and responds appropriately. 
	 * 
	 * @see MessageListener
	 * @param message The message getting delivered. 
	 */
	virtual void ReceiveMessage(Message* message);
	
	/**
	 * Since TextActors use their own methods of drawing, it can be difficult to 
	 *  determine what space they're covering. If you want to do any kind of logic
	 *  dealing with TextActor overlap, this is the way to get the BoundingBox
	 *  information. 
	 * 
	 * @return A BoundingBox describing the area covered by the TextActor in 
	 *   GL units (not pixels). 
	 */
	const BoundingBox& GetBoundingBox() const;
	
	/**
	 * Used by the SetName function to create a basename for this class. 
	 *  Overridden from Actor::GetClassName.
	 * 
	 * @return The string "TextActor"
	 */
	virtual const String GetClassName() const { return "TextActor"; }

private:
	struct TextNugget
	{
		String _string;
		Vector2 _extents;
		Vector2 _position;
	};

	void CalculatePosition();

	String _fontNickname;
	String _rawString;
	TextAlignment _alignment;

	std::vector<TextNugget> _displayStrings;

	int _lineSpacing;

	Vector2 _screenPosition;
	
	BoundingBox _extents;
};
