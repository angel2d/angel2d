%module(directors="1") angel
%{
#include "../../Actors/TextActor.h"
%}

class TextActor : public Actor
{
public:
	TextActor(String fontNickname="Console", String displayString="", TextAlignment align=TXT_Left, int lineSpacing=5);

	const String GetFont();
	void SetFont(String newFont);
	const String GetDisplayString();
	void SetDisplayString(String newString);

	const TextAlignment GetAlignment();
	void SetAlignment(TextAlignment newAlignment);

	const int GetLineSpacing();
	void SetLineSpacing(int newSpacing);
};


