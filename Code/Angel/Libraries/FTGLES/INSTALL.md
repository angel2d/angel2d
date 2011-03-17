# Installation Instructions

### Xcode

The FTGLES Xcode project is compiled as a static library, and the easiest way to add it to your project is to use Xcode's "dependent project" facilities.  Here is how:

1. Locate the "ftgles.xcodeproj" file under the folder "ftgles" inside the directory you "git cloned" or downloaded the project into.  Drag ftgles.xcodeproj and drop it onto the root of your Xcode project's "Groups and Files"  sidebar.  A dialog will appear -- make sure "Copy items" is unchecked and "Reference Type" is "Relative to Project" before clicking "Add".

2. Now you need to link the libFTGLES static library to your project.  Click the "ftgles.xcodeproj" item that has just been added to the sidebar.  Under the "Details" table, you will see a single item: libFTGLES.a.  Check the checkbox on the far right of libFTGLES.a. Alternatively, drag libFTGLES.a to your target's "Link Binary With Libraries" section.

3. Now you need to add libFTGLES as a dependency of your project, so Xcode compiles it whenever you compile your project.  Expand the "Targets" section of the sidebar and double-click your application's target.  Under the "General" tab you will see a "Direct Dependencies" section. Click the "+" button, select "libFTGLES", and click "Add Target".

4. Now you need to add some iPhone SDK frameworks to your project.  Right click on the "Frameworks" group in your project (or equivalent) and select Add > Existing Frameworks.  Then locate following frameworks and add them to the project:
   - CoreGraphics.framework
   - QuartzCore.framework
   - OpenGLES.framework
   - UIKit.framework

5. Finally, we need to tell your project where to find the FTGLES headers.  Open your "Project Settings" and go to the "Build" tab. Look for "Header Search Paths" and double-click it.  Add the relative path from your project's directory to the "src" directory in the FTGLES install directory. Also, add a recursive entry to the following entry:
   - YOUR_FTGLES_INSTALL_DIRECTORY/freetype-2.3.9/include

6. You're ready to go.  Just #include "FTGL/ftgles.h" anywhere you want to use FTGLES classes in your project.  See the BasicDemo for an example of how to set up and draw FTGLES fonts in OpenGL ES 1.1.


### Automake

The [ftgles](http://github.com/cdave1/ftgles/tree/master/ftgles/) folder contains a full automake system if you want to go that way.  The conf files do NOT include the iPhone libraries, and thus you will get build errors if you just "./configure; make; make install".  Instead, use the very useful iphone-configure tool to include your preferred iPhone SDK files and set the target device.  iphone-configure is [currently available here](http://github.com/jlongster/configure-iphone).


# Credits

The Xcode installation notes were mostly based on the install notes for Facebook's [Three20 project](http://github.com/facebook/three20).