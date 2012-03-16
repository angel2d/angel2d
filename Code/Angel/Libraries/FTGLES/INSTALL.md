# Quick Install

Enter these commands at your terminal if you want to see the Demo projects in action:

	git clone git@github.com:cdave1/ftgles.git
	git clone git@github.com:cdave1/freetype2-ios.git
	cd freetype2-ios/
	bash install.sh
	cd ../ftgles
	ln -s ../freetype2-ios freetype2
	cd Xcode
	bash install.sh

At this point, it should be possible to compile and run the Xcode projects in your ftgles/Demos/iOS folder.


# Build the FTGLES Static Library

These instructions allow you to build FTGLES into a static library that you can use in another Xcode project.

### 1. Get Freetype2

FTGLES depends on the Freetype2 library.  You can either
 - [Download the Freetype2 source from here](http://www.freetype.org/download.html), preferably the latest version (2.4.4 was the latest at the time of writing).
 - Or, you can download an Xcode project specifically setup for Freetype2 on iOS.  [This project is available here](https://github.com/cdave1/freetype2-ios).

It's recommended that you put your Freetype2 files in a folder called "freetype2" in the root folder of this FTGLES repository.


### 2. Build a Freetype2 Static Library

The ftgles Xcode project must link to the Freetype2 static library, so you will need to compile freetype 2 into a static library for iOS.  The way of creating your Freetype2 static library depends on how you downloaded Freetype 2.  If you downloaded the source code from Freetype 2 home page, you can use cmake to generate your static file.  The [freetype-ios](https://github.com/cdave1/freetype2-ios) project mentioned above includes a script to generate a universal fat binary for the i386, armv6, and armv7 architectures.


### 3. Link the Freetype2 Static Library to the FTGLES Xcode Project

Once you have created the static library, copy it to the "path/to/ftgles/Xcode/" folder.  This is where the current ftgles.xcodeproj file expects to see this static library, but you can put it anywhere that is appropriate for you.  Ensure that the libFreetype.a binary is linked in your project's target's settings.

If you installed your Freetype2 library in a location other than that recommended in Step 1 above, then you'll need to change the current FTGLES project's "Header Search Paths" to point to the "include/" folder of your Freetype 2 library.

### 4. Build FTGLES

You can build directly from Xcode to create the static library.  Alternatively, there is a script in the Xcode folder of this project, "install.sh", that you can use to generate a universal fat binary for the i386, armv6, and armv7 architectures.


# Using the FTGLES Static Library in Other Xcode Projects

### 1. Link the FTGLES Static Library

Drag the libFTGLES.a to your open Xcode project.


### 2. FTGLES Header File Locations

From there, you will need to tell you target project where the both the FTGLES and Freetype 2 headers are located.  For this, you will need to add a recursive link to:
  * The "include/" path of the Freetype source code distribution you downloaded above.
  * The "ftgles/src" path of this library.

Add these paths to the "Header Search Paths" entry of your Xcode project so they relative to the target project's location on your file system.

You might find it useful to set up an Xcode config file for this.  The [FTGLES Demo projects](https://github.com/cdave1/ftgles/tree/master/Demos) all use such a config file.


### 3. Dependent Frameworks

Now you need to add some iPhone SDK frameworks to your project.  Find the following frameworks and add them to the project:
   - CoreGraphics.framework
   - QuartzCore.framework
   - OpenGLES.framework
   - UIKit.framework


### 4. #include "FTGL/ftgles.h"

Put "#include "FTGL/ftgles.h" anywhere you want to use FTGLES.  

You're done.


# Automake

The [ftgles](http://github.com/cdave1/ftgles/tree/master/ftgles/) folder contains a full automake system.  The conf files do NOT include the iPhone libraries, and thus you will get build errors if you just "./configure; make; make install".  Instead, use the very useful iphone-configure tool to include your preferred iPhone SDK files and set the target device.  iphone-configure is [currently available here](http://github.com/jlongster/configure-iphone).


# FTGLES as a dependent project in Xcode

You can ignore this section, unless you want to make changes to the FTGLES within Xcode.

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



# Credits

The Xcode installation notes were mostly based on the install notes for Facebook's [Three20 project](http://github.com/facebook/three20).