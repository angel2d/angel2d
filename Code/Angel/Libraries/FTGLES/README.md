# FTGLES 0.3

FTGLES is a C++ library for rendering fonts on mobile operating systems with OpenGL ES 1.1.  It is a port of [FTGL](http://homepages.paradise.net.nz/henryj/code/#FTGL).  It currently targets the iPhone and iPad, with plans to port to Android in the very near future.  iOS 4.2 is currently supported.

From the FTGL notes:

"Unlike other OpenGL font libraries FTGL uses standard font file formats so doesn't need a preprocessing step to convert the high quality font data into a lesser quality, proprietary format."

"FTGL uses the [Freetype](http://www.freetype.org) font library to open and 'decode' the fonts. It then takes that output and stores it in a format most efficient for OpenGL rendering."

OpenGL ES 2.0 support has not yet been added to the main branch.  Please see the [gles2 branch](https://github.com/cdave1/ftgles/tree/gles2) for an experimental version of FTGLES that supports OpenGL ES 2.0.


## QUICK INSTALL

	git clone git@github.com:cdave1/ftgles.git
	git clone git@github.com:cdave1/freetype2-ios.git
	cd freetype2-ios/
	bash install.sh
	cd ../ftgles
	ln -s ../freetype2-ios freetype2
	cd Xcode
	bash install.sh

At this point, it should be possible to compile and run the Xcode projects in your ftgles/Demos/iOS folder.


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

The [Hello World Demo](http://github.com/cdave1/ftgles/blob/master/Demos/iOS/HelloWorld/Classes/Delegate.mm) example class shows a minimal implementation of a render loop.

See the [Demos](http://github.com/cdave1/ftgles/tree/master/iPhone/) folder for several comprehensive sample iPhone apps.  The demo apps include a unicode demo, as well as a demonstration of how to use layouts to easily align and position your text.


## Differences between FTGL and FTGLES

FTGLES 0.1 supports the following font types from the original FTGL library:

 - FTBufferFont
 - FTGLOutlineFont
 - FTGLPolygonFont
 - FTGLTextureFont

Extrusion and pixmap rendering from the original FTGL library are currently not supported.  Bitmap font support is currently in progress.


## Performance Notes

If you need to render large amounts of text, Texture fonts are preferable, and also currently look much better than other font types.  Texture fonts allow you to render a full screen of text without any appreciable drop in frame rate.

For Polygon and Outline fonts, rendering speeds depend very much on the type face being rendered.  More complex glyphs will almost always contain more vertices, and thus FTGLES will need to draw more polygons or lines.  

While you may get acceptable results by switching to a simple typeface, it is generally recommended that you avoid excessive use of Polygon and Outline fonts in iOS applications.  Expect to see large drops in frame rate when drawing any more than 100-200 Polygon or Outline glyphs on screen.   

Performance of the SimpleLayout class was previously very slow, but was recently improved in a recent build.  

There is a [Performance test application](https://github.com/cdave1/ftgles/tree/master/Demos/iOS/PerformanceTest/) that will show the framerate of a screen full of text rendered using the SimpleLayout class, along with several font faces.


## Licenses

 - FTGLES License [here](http://github.com/cdave1/ftgles/blob/master/LICENSE.md)
 - Original FTGL License [here](https://github.com/cdave1/ftgles/blob/master/ftgles/COPYING)
 - Freetype 2 License [here](http://www.freetype.org/FTL.TXT)
