#include "../Infrastructure/TextRendering.h"

#include "../Infrastructure/Camera.h"
#include "../Infrastructure/VecStructs.h"

#include "FTFont.h"
#include "FTGLTextureFont.h"


std::map<String, FTFont*> _fontCache;

const bool RegisterFont(String filename, int pointSize, String nickname)
{
	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if(it != _fontCache.end())
	{
		UnRegisterFont(nickname);
	}

	FTFont *font = new FTGLTextureFont(filename.c_str());
	if(font->Error())
	{
		std::cout << "Failed to open font " << filename << std::endl;
		return false;
	}
	if(!font->FaceSize(pointSize))
	{
		std::cout << "Failed to set size." << std::endl;
		return false;
	}
	font->CharMap(FT_ENCODING_NONE);
	font->UseDisplayList(true);

	_fontCache[nickname] = font;
	return true;
}

const bool UnRegisterFont(String nickname)
{
	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if (it == _fontCache.end())
	{
		return false;
	}
	delete it->second;
	it->second = NULL; //redundant with next line, but to keep good habits...
	_fontCache.erase(it);
	return true;
}

Vector2 DrawGameText(String text, String nickname, int pixelX, int pixelY, float angle)
{
	Vector2 forReturn;

	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if (it == _fontCache.end())
	{
		return forReturn;
	}

	Vec2i winDimensions;
	winDimensions.X = theCamera.GetWindowWidth();
	winDimensions.Y = theCamera.GetWindowHeight();
	pixelY = winDimensions.Y - pixelY;

	//set up projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, winDimensions.X, 0, winDimensions.Y);

	//set up modelview
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef((GLfloat)pixelX, (GLfloat)pixelY, 0);
	glRotatef(angle, 0, 0, 1);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	it->second->Render(text.c_str());
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	float llx, lly, llz, urx, ury, urz;
	it->second->BBox(text.c_str(), llx, lly, llz, urx, ury, urz);
	forReturn.X = urx - llx;
	forReturn.Y = ury - lly;	
	return forReturn;
}

Vector2 GetTextExtents(String text, String nickname)
{
	Vector2 forReturn;

	std::map<String,FTFont*>::iterator it = _fontCache.find(nickname);
	if (it == _fontCache.end())
	{
		return forReturn;
	}

	float llx, lly, llz, urx, ury, urz;
	it->second->BBox(text.c_str(), llx, lly, llz, urx, ury, urz);
	forReturn.X = urx - llx;
	forReturn.Y = ury - lly;	
	return forReturn;
}