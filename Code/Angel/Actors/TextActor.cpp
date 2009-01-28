#include "../Actors/TextActor.h"

#include "../Infrastructure/TextRendering.h"
#include "../Util/StringUtil.h"
#include "../Util/MathUtil.h"
#include "../Messaging/Switchboard.h"


TextActor::TextActor(String fontNickname, String displayString, TextAlignment align, int lineSpacing)
{
	SetColor(0,0,0); //default text is black
	_fontNickname = fontNickname;
	_alignment = align;
	_lineSpacing = lineSpacing;
	_screenPosition = Vector2::Zero;

	SetDisplayString(displayString);
	
	theSwitchboard.SubscribeTo(this, "CameraChange");
}

void TextActor::Render()
{
	glColor4f(_color.R, _color.G, _color.B, _color.A);
	for(unsigned int i=0; i < _displayStrings.size(); i++)
	{
		DrawGameText(_displayStrings[i]._string, _fontNickname, (int)_displayStrings[i]._position.X, (int)_displayStrings[i]._position.Y);
	}
}

const String TextActor::GetFont()
{
	return _fontNickname;
}

void TextActor::SetFont(String newFont)
{
	_fontNickname = newFont;
	CalculatePosition();
}

const String TextActor::GetDisplayString()
{
	return _rawString;
}

void TextActor::SetDisplayString(String newString)
{
	_rawString = newString;
	_displayStrings.clear();
	StringList strings = SplitString(_rawString, "\n", false);
	StringList::iterator it = strings.begin();
	while(it!= strings.end())
	{
		TextNugget nugget;
		nugget._string = *it;
		_displayStrings.push_back(nugget);
		it++;
	}

	CalculatePosition();
}

const TextAlignment TextActor::GetAlignment()
{
	return _alignment;
}

void TextActor::SetAlignment(TextAlignment newAlignment)
{
	_alignment = newAlignment;
	CalculatePosition();
}

const int TextActor::GetLineSpacing()
{
	return _lineSpacing;
}

void TextActor::SetLineSpacing(int newSpacing)
{
	_lineSpacing = newSpacing;
	CalculatePosition();
}

void TextActor::SetPosition(float x, float y)
{
	Actor::SetPosition(x, y);
	CalculatePosition();
}

void TextActor::SetPosition(Vector2 position)
{
	Actor::SetPosition(position);
	CalculatePosition();
}

void TextActor::ReceiveMessage(Message* m)
{
	if (m->GetMessageType() == "CameraChange")
	{
		CalculatePosition();
	}
}

void TextActor::CalculatePosition()
{
	Vector2 largest = Vector2::Zero;
	std::vector<TextNugget>::iterator it = _displayStrings.begin();
	while(it != _displayStrings.end())
	{
		(*it)._extents = GetTextExtents((*it)._string, _fontNickname);
		if ((*it)._extents.X > largest.X)
		{
			largest.X = (*it)._extents.X;
		}
		if ((*it)._extents.Y > largest.Y)
		{
			largest.Y = (*it)._extents.Y;
		}

		it++;
	}

	float currentY = MathUtil::WorldToScreen(GetPosition()).Y;
	it = _displayStrings.begin();
	while(it != _displayStrings.end())
	{
		Vector2 size;
		switch(_alignment)
		{
		case TXT_Left:
			(*it)._position = Vector2(MathUtil::WorldToScreen(GetPosition()).X, currentY);
			break;
		case TXT_Center:
			(*it)._position = 
				Vector2(MathUtil::WorldToScreen(GetPosition()).X, currentY) + 
				Vector2(-(*it)._extents.X * 0.5f, 0.0f);
			break;
		case TXT_Right:
			(*it)._position = 
				Vector2(MathUtil::WorldToScreen(GetPosition()).X, currentY) + 
				Vector2(-(*it)._extents.X, 0.0f);
			break;
		}
		
		currentY += largest.Y + _lineSpacing;
		it++;
	}
}