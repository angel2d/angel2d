# FTGLES 0.1

FTGLES is a C++ library for rendering fonts on mobile operating systems with OpenGL ES 1.1.  It is a port of [FTGL](http://homepages.paradise.net.nz/henryj/code/#FTGL).  It currently targets the iPhone and iPad, with plans to port to Android in the very near future.  iOS 4 is currently supported.

From the FTGL notes:

"Unlike other OpenGL font libraries FTGL uses standard font file formats so doesn't need a preprocessing step to convert the high quality font data into a lesser quality, proprietary format."

"FTGL uses the [Freetype](http://www.freetype.org) font library to open and 'decode' the fonts. It then takes that output and stores it in a format most efficient for OpenGL rendering."


## INSTALL

See [INSTALL NOTES](http://github.com/cdave1/ftgles/blob/master/INSTALL.md) for instructions on how to add FTGLES to your Xcode project or build using automake.


## USAGE

Include the library in your code:
	
	#include "FTGL/ftgles.h"

Create a font from a truetype file or opentype font:
	
	FTFont *font = new FTTextureFont("/path/to/myfont.ttf");
	FTFont *font2 = new FTTextureFont("/path/to/myotherfont.otf");
	font->FaceSize(72);
	
To render the text within your render loop (fonts are rendered at the origin along the positive x-axis):

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Black text
	font->Render("Lorem ipsum dolor sit amet");

The [Hello World Demo](http://github.com/cdave1/ftgles/blob/master/Demos/iOS/HelloWorld/Classes/HelloWorldDemo.cpp) example class shows a minimal implementation of a render loop.

See the [Demos](http://github.com/cdave1/ftgles/tree/master/iPhone/) folder for several comprehensive sample iPhone apps.  The demo apps include a unicode demo, as well as a demonstration of how to use layouts to easily align and position your text.


## Differences between FTGL and FTGLES

FTGLES 0.1 supports the following font types from the original FTGL library:

 - FTBufferFont
 - FTGLOutlineFont
 - FTGLPolygonFont
 - FTGLTextureFont

Extrusion and pixmap rendering from the original FTGL library are currently not supported.  Bitmap font support is currently in progress.

Open GL ES 2 support is coming soon.