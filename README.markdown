Angel 2D
========
Homepage:      http://angel2d.com
Documentation: http://docs.angel2d.com


Angel is a cross-platform 2D game prototyping framework based on OpenGL 
and C++. 

It provides a broad set of basic game functionality in a lightweight fashion, 
and is designed to make it easy to get your game ideas up and running as 
quickly as possible. 

### Angel's main priorities ###

* Provide all functionality in a quickly understandable way. 
    * We try to avoid overly complicated programming techniques, even if 
        that means sacrificing efficiency or, in some cases, functionality. 
    * As far down the stack as we can manage, the code is plainly written 
        and thoroughly commented. We expect people to modify the core engine 
        in the course of their work, so we've tried to make that a manageable 
        thing. 
* Provide as much functionality as possible. 
    * Angel was originally created (and is still used) as an engine for game 
        jams, and the last thing you want to be doing in a jam context is 
        debugging the pathfinding code you had to cobble together. 
    * If there's something big you feel is missing from Angel, please send 
        an email to the discussion group. We can't add every feature, 
        obviously, but we want to at least make sure there's nothing we're 
        forgetting. 
* Allow an experienced developer to dive deeper.
    * Given the first two points, we create a lot of wrappers around 
        third-party libraries, but we always make it simple to access the raw
        capabilities of those libraries. So if you know what you're doing, 
        you can be making direct OpenGL calls or poking the Box2D physics 
        simulation. 
    * In short, we strive to keep our code relatively shallow -- it's 
        always easy to find the code doing the actual work, so you're not 
        slogging through multiple levels of OO redirection.


Getting Started
---------------
In addition to the Angel library itself, we've included two sample projects 
that serve as useful starting points.

* IntroGame - a set of modular demos that show off specific bits of Angel
  functionality. Each demo also displays the relevant code or configuration 
  files, so if you see something you like, you know where to find it. 
* ClientGame - a good point for you start your own game. It already has all 
  its paths and includes set up properly, and a main function that initiates 
  Angel with nothing in the world but a simple grid to help you place objects.

We've taken pains to make Angel work as well as possible out of the box, but
there are some prerequisites for each platform, still. 

### Windows ###
* You'll need some version of Visual Studio 2008 or later. Angel works great
  with Visual Studio Express, so you don't even have to spend money here.
* You'll also need to install the DirectX SDK, or resign yourself to not being
  able to use a 360 controller. You can get the SDK from [Microsoft's web
  site](http://msdn.microsoft.com/en-us/directx/default.aspx).
* When you build your game in Release mode, a "Published" directory is created
  alongside the .vcproj file. This contains all the libraries, resources, 
  documentation, etc., and is appropriate for zipping up for distribution. 

### Mac ###
* You'll need the OS X Development Tools, available either from the Extra 
  Installs disc that came with your computer (prior to Lion) or free from 
  the Mac App Store. After you install Xcode, go to the Downloads section of 
  the Xcode preferences and install the command line tools. 
* You need to either have [MacPorts](http://www.macports.org/) or 
  [Homebrew](http://mxcl.github.com/homebrew/) installed. Hopefully if you're
  a developer you've already got one of these systems that you like. Either
  one is easy to install.
* Once you've done both of the above, you have a choice. Do ONE of:
    * Run the included script that will prep your system. Open the terminal, 
      navigate to the `Code/Angel` directory, and run `sudo ./nix-prereqs.sh`
    * Do what that script is doing, manually:
        * Install SWIG. 
            * MacPorts: `sudo port install swig-lua`
            * Homebrew: `brew install swig`
        * Install the kernel extension that exposes the 360 controller as a
          HID Input device. This extension is in Tools directory. 
* When you build your game for Archiving (or with any scheme with a Release
  configuration) it will create a "Published" directory alongside the 
  project file. This contains the app itself, along with the documentation,
  ready for zipping and distribution. 

### iOS ###
* Follow the same setup instructions for the Mac build. There's a separate
  Xcode project file for the iOS build. 
* There are some differences in building a project for iOS:
    * We only support loading PNG files as textures on iOS, so make sure to
      convert all your resources beforehand.
    * Because of the way iOS apps are structured, the `main()` function is 
      taken over by the base engine. So take any setup that you used to do 
      in main() and move it to the `iPhoneMain.cpp` file. 
    * You can't set the resolution of the game -- it will always be the 
      native resolution of the device. Note this may cause some differences
      between high resolution screens and traditional ones, so take this 
      into account when doing any calculations about pixel distances.

### Linux ###
* Angel's tested on the latest releases of Ubuntu and Fedora. It should work
  on other recent distributions as well so long as all the dependencies are
  installed. 
* If you're on one of those supported distributions, navigate to `Code/Angel` 
  and run `sudo ./nix-prereqs.sh` to install all the prerequisites. 
* To compile, cd into either the ClientGame or IntroGame directory and simply
  run `make`. This will also build Angel and all its associated libraries if
  necessary. 
* FMOD (the default sound library used by Angel) sometimes has difficulties 
  with autodetecting your audio subsystem.  Because of this, by default we
  configure FMOD to use ALSA.  If you do not wish to use ALSA, you can
  override the audio subsystem selection using an environment variable:
  FMOD_OUTPUTTYPE. The possible override choices are: AUTODETECT,
  ALSA, OSS, ESD, and NOSOUND. For example, to set the environment variable
  (if using the bash shell), use the following command:
      `export FMOD_OUTPUTTYPE="OSS"`
* On certain processors, Angel applications may crash with "Illegal 
  instruction" errors. This is likely due to the fact that the DevIL 
  library in most distributions is compiled to use SSE1, SSE2, and SSE3 
  instructions. Some processors do not support these instructions and the 
  program will crash. If you see this error, the recommended work-around is 
  to download and compile your own version of 
  [DevIL](http://openil.sourceforge.net). To disable all SSE instructions, 
  add "--disable-asm" when using the configure script.
* On Fedora systems, Angel and SELinux do not get along. Be prepared to 
  create exceptions for your Angel programs or disable SELinux altogether.


FAQ
---
* Why is it called "Angel"?
    * Because the original team was working at Electronic Arts in Los 
      Angeles. It's a whole *city* of angels.

* Why did you set up {X} that way? Don't you know it's faster if you...
    * Take a look at the top of this document and the goals we laid out there.
      Angel is designed to be easy to use and modify, not hyper-efficient.

* You said the code was supposed to be easy to read, but some parts are 
  really ugly. What gives?
    * Some of it gets a little sloppy. Cleanup is always ongoing. Also, some 
      of the ease of use comes from deep magic. 

* Why make your own engine instead of using {MyFavoriteEngine3D}?
    * We initially explored lots of options, but couldn't find anything 
      lightweight enough, focused on 2D, and in C++. As a bonus, it's kind of
      fun to make an engine. 

* Was Angel made from scratch?
    * Yes, but it was based on experiences using the Experimental Gameplay 
      Project engine (which evolved into the 2D Boy engine), Unreal, Panda 3D,
      and some other engines. If you're familiar with any of these, you'll 
      recognize some concepts and techniques. 

* Why C++? {C#/Erlang/D/Haskell} is the wave of the future!
    * We wanted a language that would match up well with the experience of
      most of the people at our studio at the time. When you only have a 
      weekend to make a game, you don't want to have the language reference
      open in another window. Since then, that decision has proven to give
      us a lot of flexibility in porting to new platforms, and has kept the
      engine alive as other platforms have fallen away. ( :( RIP XNA)

* What libraries are used in Angel?
    * OpenGL for rendering
    * FMOD **or** OpenAL/Vorbis for audio
    * Box2D for physics
    * FreeType2 and FTGL for text rendering
    * DevIL **or** libpng for image loading
    * GLFW for windowing and input
    * Lua for scripting
    * SWIG to bind the engine to Lua
    * Doxygen for HTML and PDF documentation

