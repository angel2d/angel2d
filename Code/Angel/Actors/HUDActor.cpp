#include "../Actors/HUDActor.h"

#include "../Infrastructure/VecStructs.h"
#include "../Infrastructure/Camera.h"
#include "../Util/MathUtil.h"

void HUDActor::Render()
{
	Vec2i winDimensions;
	winDimensions.X = theCamera.GetWindowWidth();
	winDimensions.Y = theCamera.GetWindowHeight();
	float pixelY = winDimensions.Y - _position.Y;
	
	//set up projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, winDimensions.X, 0, winDimensions.Y);
	
	//set up modelview
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(_position.X, pixelY, 0);
	glRotatef(_rotation, 0, 0, 1);
	glScalef(_size.X, _size.Y, 1.0f);
	glColor4f(_color.R, _color.G, _color.B, _color.A);
	
	int textureReference = _spriteTextureReferences[_spriteCurrentFrame];
	if (textureReference >= 0)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureReference);
	}
	
	switch( _drawShape )
	{
		default:
		case ADS_Square:
			glBegin(GL_QUADS);
			//glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(UV_rightup.X, UV_rightup.Y); glVertex2f( 0.5f,  0.5f);
			glTexCoord2f(UV_leftlow.X, UV_rightup.Y); glVertex2f(-0.5f,  0.5f);
			glTexCoord2f(UV_leftlow.X, UV_leftlow.Y); glVertex2f(-0.5f, -0.5f);
			glTexCoord2f(UV_rightup.X, UV_leftlow.Y); glVertex2f( 0.5f, -0.5f);
			glEnd();
			break;
			
		case ADS_Circle:
			const int NUM_SECTIONS = 32;
			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(0, 0);
			for (float i = 0; i <= NUM_SECTIONS; i++)
				glVertex2f(0.5f*cos((float) MathUtil::TwoPi * i / NUM_SECTIONS), 0.5f*sin((float) MathUtil::TwoPi * i / NUM_SECTIONS));
            glEnd();
			break;
	}
	
	if (textureReference >= 0)
	{
		glDisable(GL_TEXTURE_2D);
	}
	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

