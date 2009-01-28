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
	TextActor(String fontNickname="Console", String displayString="", TextAlignment align=TXT_Left, int lineSpacing=5);
	
	/**
	 * Override of the Actor::Render function to draw text
	 */
	virtual void Render();
	
	/**
	 * Get the name of the font currently being used for this Actor
	 * 
	 * @return the nickname of the current font, as set in RegisterFont
	 */
	const String GetFont();
	
	/**
	 * Change the font used in drawing this TextActor. 
	 * 
	 * @param newFont the nickname of the new font. This must be set up with RegisterFont
	 *  before being set here -- the TextActor will not draw at all if this is an invalid
	 *  nickname. 
	 */ 
	void SetFont(String newFont);
	
	/**
	 * Get the current string being drawn by this TextActor.
	 * 
	 * @return the display string
	 */
	const String GetDisplayString();
	
	/**
	 * Change the string to be drawn by this TextActor. Newlines can be delimited with
	 *  the plain newline character (\\n).
	 * 
	 * @param newString the string that should be drawn by this TextActor in the next
	 *  frame
	 */
	void SetDisplayString(String newString);
	
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
	virtual void SetPosition(Vector2 position);
	
	/**
	 * An implementation of the MessageListener interface, which listens for 
	 *  CameraChange messages and responds appropriately. 
	 * 
	 * @see MessageListener
	 * @param message The message getting delivered. 
	 */
	virtual void ReceiveMessage(Message* message);

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
};
