# FTGLES TUTORIAL

Tutorial is under construction.

## QUICK START

You may have seen this on the README page.  First, include the ftgles header in your code.
	
	#include "FTGL/ftgles.h"

Create a font from a truetype file or opentype font:
	
	FTFont *font = new FTTextureFont("/path/to/myfont.ttf");
	FTFont *font2 = new FTTextureFont("/path/to/myotherfont.otf");
	font->FaceSize(72);
	
To render the text within your render loop:

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	font->Render("Lorem ipsum dolor sit amet");


# Font Types

## Texture Fonts

Texture fonts are represented by an OpenGL texture.  This is the most efficient font class for OpenGL ES applications:

	FTFont *font = new FTTextureFont("/path/to/myfont.ttf");


## Outline Fonts

	FTOutlineFont *font = new FTOutlineFont("/path/to/myfont.ttf");

## Polygon Fonts

	FTFont *font = new FTOutlineFont("/path/to/myfont.ttf");


# Setting font sizes

Setting the font size by passing a pixel height:

	myfont->FaceSize(15.0f);

Note that this is a fixed pixel height.  On the iPhone 4's retina screen, a font with a size of 30 will appear to the half the size as it would on a non-retina screen.  You could fix this by using the scale factor:

	float scale = 1.0f;
	if([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) 
	{
		scale = [[UIScreen mainScreen] scale];
	}
	myfont->FaceSize(scale * 15.0f);


# Rendering

As mentioned earlier, when you use FTFont's Render() function, all text will be rendered in a straight line, without linebreaks, rendered at the origin along the positive x-axis:

	font->Render("Lorem ipsum dolor sit amet");

You'll need to use standard OpenGL transform functions to change where your font is rendered on screen.

As far as it is possible, FTGLES will attempt to restore pre-existing states before you rendered the font, but in particular, the following array pointers will be restored:

	GL_VERTEX_ARRAY_POINTER
	GL_TEXTURE_COORD_ARRAY_POINTER
	GL_COLOR_ARRAY_POINTER

## Vertex Buffer Objects

Neither font implementations use vertex buffer objects.  However, there is a [separate branch](https://github.com/cdave1/ftgles/tree/perf) of the project that does implement VBOs.


# Using Layouts to arrange text

You can use the Simple Layout to have greater control over how your text is rendered. 

	FTFont *font = new FTTextureFont("/path/to/myfont.ttf");
	myfont->FaceSize(15.0f);

	FTSimpleLayout layout;
	layout.SetLineLength(300.0f);
	layout.SetLineSpacing(1.25f);
	layout.SetAlignment(FTGL::ALIGN_CENTER);
	layout.SetFont(myfont);


And then, in your render loop:

	layout.Render("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");


# Demos

The [Hello World Demo](http://github.com/cdave1/ftgles/blob/master/Demos/iOS/HelloWorld/Classes/Delegate.mm) example class shows a minimal implementation of a render loop in Objective-C.

See the [Demos](http://github.com/cdave1/ftgles/tree/master/iPhone/) folder for several comprehensive sample iPhone apps.  The demo apps include a unicode demo, as well as a demonstration of how to use layouts to easily align and position your text.