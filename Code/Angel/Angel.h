//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

/**
 * @mainpage The Angel Engine 
 * @section ReadMe
 * Make sure to first read the overview information at 
 *  http://angel2d.com -- it contains a good rundown of what Angel is and, 
 *  more importantly, what it is not. Calibrating your expectations can save a 
 *  lot of heartache later. :-)
 * 
 * @section intro Introduction
 * This documentation is meant as an introduction to Angel, but also serves
 *  as a small intro into basic game architecture. If you're a beginner, don't
 *  be off-put by the advanced stuff. If you're experienced, don't be 
 *  patronized by the beginner stuff. This documentation is probably best 
 *  skimmed or searched for data rather than read straight through, but hey,
 *  it's a free country. 
 * 
 * This file really only documents the engine itself -- for information on 
 *  how to get started building, the history of Angel, support, etc., please
 *  visit the <a href="http://angel-engine.googlecode.com">website</a>. Note
 *  that this documentation is focused on the desktop builds of Angel. The
 *  differences that exist in the iOS build are documented in \ref ios 
 *  "their own section." 
 * 
 * Whether you're a beginner or advanced, please drop a line if you think 
 *  something in here is wrong or could be explained better. Always looking
 *  to improve. 
 * 
 * @section code_tour A Brief Tour of the Code
 * The root directory has just one other directory: \c Code. You may ask why
 *  we bother having this single-nested hierarchy. The idea is that when 
 *  you're working on a game, you may wish to have your raw assets in version 
 *  control as well, instead of just the final exported files you place in
 *  your game's \c Resources directory. So at this root level you can add 
 *  another directory called \c Assets to keep track of those, if you wish. 
 * 
 * If you open the Code directory, you should see the following files and 
 *  subdirectories [not an exhaustive list, these are just the ones that are
 *  interesting or may warrant explanation]: 
 *  - \b GameJam.sln: The Visual Studio 2008 solution file (Windows)
 *  - \b GameJam-Mac.xcodeproj: The Xcode 3 build and project information (Mac 
 *       OS X)
 *  - \b GameJam-iOS.xcodeproj: The Xcode 3 build and project information (iOS)
 *  - \b README.Linux: Information about how to get Angel up and running on
 *       Linux, along with data about what should and shouldn't work at 
 *       present.
 *  - \b Angel: where the core prototyping framework gets built. Doesn't do 
 *       anything by itself, but requires client code to load it up and get 
 *       things going. 
 *    - \e Angel.h: the master header file that includes all other header 
 *      files you should need for your game. The included starter projects 
 *      have this set up as part of their pre-compiled header. 
 *    - \e AngelConfig.h: A set of global defines that are used to disable
 *      large scale libraries like FMOD and DevIL. 
 *    - \e Libraries: all the third-party libraries that Angel works to do its 
 *      magic. \n
 *      They all include their distributed documentation and appropriate 
 *      website links.
 *      - Box2D: Physics \n
 *        (http://box2d.org)
 *      - DevIL: Image loading \n
 *        (http://openil.sourceforge.net)
 *      - FMOD: Sound \n
 *        (http://www.fmod.org)
 *      - FreeType: Font rasterization \n
 *        (http://www.freetype.org)
 *      - FTGL: Makes it easy to use FreeType in OpenGL \n
 *        (http://homepages.paradise.net.nz/henryj/code/#FTGL)
 *      - GLFW: A cross-platform framework to handle basic windowing and input 
 *        events \n
 *        (http://www.glfw.org/)
 *      - gwen: A simple GUI toolkit designed for game engines \n
 *        (http://gwen.googlecode.com)
 *      - HID Utilities: USB Controller support for Mac OS X \n
 *        (http://developer.apple.com/samplecode/HID_Utilities_Source/index.html)
 *      - LibOgg and LibVorbis: Open source alternative to FMOD \n
 *        (http://www.vorbis.com)
 *      - LibPNG: Library for loading PNG files (when DevIL is disabled) \n
 *        (http://www.libpng.org/pub/png/libpng.html)
 *      - Lua: Scripting \n
 *        (http://www.lua.org)
 *  - \b Tools: a collection of scripts and tools that are used as part of the 
 *       build process or may be useful to developers.
 *    - \e BuildScripts: the Lua files which get called during the build 
 *      process
 *      - \c angel_build.lua: utility functions and classes for the 
 *        build/publish
 *      - \c publish.lua: On Windows, this gets called whenever you make a 
 *        release build. \n
 *        It produces a new directory called \c Published within your project 
 *        directory -- the \c Published directory should contain everything 
 *        your game needs to run on any (Windows) system and is suitable for 
 *        zipping up and sharing. 
 *      - \c publish_mac.lua: The publish script for the Mac build. It produces
 *        a new directory in your \build directory. The application there is
 *        renamed to what you've defined in \c build.lua.
 *      - \c swig_wrap.lua: part of the build process to determine if the SWIG 
 *        scripting bridge needs to be regenerated. It can be time consuming 
 *        to regenerate and recompile, so it's worth checking first. (See 
 *        SWIG, below.)
 *    - \e Mac360: The binary and source versions of a Mac OS X kernel 
 *      extension that makes it possible for Angel to interface with the Xbox 
 *      360 controller. You may have trouble compiling if this isn't 
 *      installed. (A pain, but thems the breaks.)
 *    - \e swigwin: The Windows distribution of SWIG -- a tool for generating 
 *      script interfaces to C and C++ code. The \c swig_wrap.lua build script 
 *      calls this executable (on Windows) and processes \c 
 *      Angel/Scripting/Interfaces/angel.i to generate all the script hooks 
 *      into the engine. For the most part, this should just work, but please 
 *      see the SWIG documentation if you're curious as to how. (Warning: 
 *      SWIG can be a deep rabbit hole, so don't go diving into it unless you 
 *      already know what what you're doing or are not using Angel in a 
 *      GameJam context.)
 *  - \b IntroGame: A modular example project that shows off a lot of the 
 *      features of Angel using thoroughly commented code. We recommend you 
 *      start here and explore the indicated files when you see a feature you 
 *      like. Its directory structure is very similar to that of ClientGame, 
 *      described in detail, below. 
 *  - \b ClientGame: Where you should build your actual game. 
 *    - \e GameInfo.txt: a ReadMe file that will be included in your final \c 
 *      Published directory by the publish build script (see above). Make sure 
 *      to edit this file appropriately, or you'll have the sample text as the 
 *      first thing people see about your game! (Because everybody reads the 
 *      ReadMe, of course...)
 *    - \e Attributions.txt: Angel uses a lot of open source components, and 
 *      the license requirements typically require a shoutout at some point in 
 *      your documentation. This file will also get included in your \c 
 *      Published directory, and already contains the acknowledgements for all 
 *      of Angel's components. Make sure, if you bring in any additional open 
 *      source components, that you add the appropriate license information.
 *      This is also a good place to throw in asset acknowledgements if you 
 *      didn't create them yourself -- though make sure you're ok 
 *      copyright-wise! 
 *    - \e build.lua: a set of values used by the build and publish scripts to 
 *      customize your game. At the moment, it only contains a value for 
 *      giving your game a name -- we strongly recommend naming your game here 
 *      as opposed to renaming the project itself so merging will be easier 
 *      later. 
 *    - \e Config: configuration files for your game -- this entire directory 
 *      gets copied to your distribution, so don't leave anything in here you 
 *      don't want to become public somehow. 
 *      - \c input_bindings.ini: maps keyboard and controller button presses 
 *        to Messages that will be sent in the game (see the \ref messaging 
 *        "Messages" section)
 *      - \c ActorDef: definition files for your actor archetypes (see the 
 *        \ref actor_defs "Archetypes" section)
 *      - \c Level: definitions files for your levels (see the \ref levels
 *        "Levels" section)
 *    - \e Logs: Where any logs you generate in your game will be stored for 
 *      later viewing. (Assuming you use the Angel built-in logging. Obviously 
 *      you could write your own files wherever the heck you want.) Gets 
 *      copied to the Published directory.
 *    - \e Resources: All non-code bits of your game should go in here. This 
 *      will also be copied to the Published directory. 
 *      - \c Fonts: hopefully this is self-explanatory
 *      - \c Images: hopefully this is self-explanatory
 *      - \c Sounds: hopefully this is self-explanatory
 *      - \c Scripts: Any Lua that you want to use in your game should get 
 *        put in here. The included \c client_start.lua gets imported directly 
 *        into the console namespace, so any functions you define here will be 
 *        available in the console. If you want to do any game setup from Lua,
 *        \c client_start.lua is where it should go. As you build you'll 
 *        notice other files get copied to this directory -- the scripts that 
 *        help make Angel run. These files will be frequently updated from the 
 *        \c Angel/Scripts/EngineScripts directory every time you build, so 
 *        making changes to them here will leave you disappointed when they 
 *        get overwritten. 
 * 
 * @section world The World
 * Angel's entire simulation is based around the World class. It represents, 
 *  unsurprisingly, the world of your game. Nothing will take place in your
 *  game without adding things to the world. 
 * 
 * Like many other classes in Angel, World uses the singleton pattern. What
 *  this means is that there can only ever be one instance of this class in
 *  the program -- if you think about it, this makes a lot of sense. So you'll
 *  never actually create the world directly. Instead, you call the static
 *  function World::GetInstance(), which returns a reference to the single
 *  world that has been created for your game. (Instead of using 
 *  World::GetInstance, you'll find that we use a defined shortcut called 
 *  theWorld. Since getting the world instance is such a common operation, 
 *  this shortcut is handy.) For more information on the singleton pattern, 
 *  this paper from Microsoft is a good starting point: 
 * 
 * http://msdn.microsoft.com/en-us/library/ms954629.aspx
 * 
 * To do the initial setup of the world, we call the World::Initialize 
 *  function. 
 * 
 * \code
 * theWorld.Initialize(1024, 768, "My Game", false);
 * \endcode
 * 
 * This call opens a window to view the world -- it's 1024x768 with "My Game"
 *  in the title bar and anti-aliasing disabled. Obviously you can swap out
 *  your own values and change the properties of the window. 
 * 
 * After you call World::Initialize, you'll want to do all your setup (adding
 *  Actors to the world), but nothing will actually happen until you call
 *  World::StartGame(). This actually begins the game loop, and the function
 *  will never return until you close down the application by calling 
 *  World::StopGame(). 
 * 
 * The game loop is an important concept. There are two parts to it (if you
 *  look at the World::TickAndRender function you'll see there's actually
 *  a bit more, but conceptually, two parts): Update and Render. Every 
 *  object that you add to the world implements these two functions and will
 *  have them called once every time we go through the game loop. The Update
 *  parts just deal with game logic -- handling collisions, answering 
 *  messages, updating positions, changing colors, incrementing scores, etc. 
 *  The Render parts are strictly for drawing the individual element to the 
 *  screen. We separate the two because what happens in the Update part of the
 *  loop can affect how things should be drawn in the Render part. 
 * 
 * You can also pause and unpause your game by calling World::StopSimulation
 *  or World::StartSimulation. While the sim is paused, certain things will 
 *  still go on (like sound and input), but normal objects won't get their
 *  update calls. (Note that they'll still be drawn!)
 * 
 * The world has a good deal of other functionality, but it's mostly related
 *  to other parts of the game and so it'll be covered in other sections. 
 * 
 * @subsection logging Logging
 * Logging is one of those things (like a lot of Angel's functionality) that
 *  isn't really hard to get working, but is kind of annoying and not the 
 *  fun part of game development. So we provide some simple classes to make
 *  logging easier, and if you need something more advanced, you can always
 *  just hack it in yourself. :-) 
 * 
 * There are a few types of logs. All of them are derived classes of 
 *  DeveloperLog, and implement DeveloperLog::Log and DeveloperLog::Printf. 
 *  When you call DeveloperLog::Log, you just pass it a string and it gets
 *  written in the log of your choice. When you call DeveloperLog::Printf, 
 *  you can pass it a format string and list of parameters, just like you 
 *  would do with the <a href="
 *  http://www.cplusplus.com/reference/clibrary/cstdio/printf.html">normal \c 
 *  printf function</a>. For all cases where you write to a log, the system 
 *  will automatically put a newline character at the end. 
 * 
 * The first type of log we care about is a SystemLog. This log just spews
 *  right to the OS's console. You may ask why not use the normal \c std::cout
 *  or \c printf functions -- by using a SystemLog, you integrate with the 
 *  Angel logging system, which lets you easily mirror output to a file, for
 *  instance. Also, when debugging in Visual Studio, the SystemLog prints 
 *  to the Output pane instead of the system console, which makes it a lot
 *  easier to review messages. 
 * 
 * Then there's a ConsoleLog, which writes its output to the in-game Console
 *  (invoked with '~'; see below). This can be handy for getting debug values 
 *  without having to even leave your game. 
 * 
 * We also have FileLog, which writes its output to a file of your choosing. 
 *  The class provides a static function FileLog::MakeLogFileName, which 
 *  accepts a string and returns another string representing the file path
 *  where that log should reside. On Windows, this is in the Logs directory
 *  right next to your executable. On the Mac, though, the logs will go in
 *  \c ~/Library/Application \c Support/Angel \c Games/Logs, in order to be a 
 *  good OS X citizen. 
 * 
 * Finally, we have a CompoundLog, which lets you combine several different
 *  logs together and write to them all at once. The best use case for this
 *  is the static "sysLog," which Angel uses internally to write all its 
 *  messages and errors. By default, it just contains a SystemLog, but you 
 *  can add a FileLog to it if you want to record the Angel messages in a 
 *  more persistent fashion. 
 * 
 * That's pretty much it for logging -- the system is simple, but really 
 *  flexible. You could create a separate log for warnings or errors, put 
 *  some into one file, some into another, some only to the console, etc. 
 * 
 * \code
 * sysLog.Log("This message will go to the system console.");
 * ConsoleLog *c = new ConsoleLog();
 * c->Printf("This will print pi to the in-game console: %1.4f. ", MathUtil::Pi);
 * FileLog *f = new FileLog(FileLog::MakeLogFileName("warn_log"));
 * f->Log("This will write to a file in the Logs directory called \"warn_log.log\".");
 * sysLog.AddLog(f); 
 * sysLog.Log("This will log to both the system console and the log file we created.");
 * \endcode
 * 
 * @subsection preferences Preferences
 * Angel contains a simple mechanism for storing persistent values so your 
 *  players can store data across sessions. It's only good for simple sets
 *  of values (floats, ints, strings), but you can do quite a bit with just
 *  those.
 * 
 * To set a preference, we call the appropriate function for the desired type.
 * 
 * \code
 * thePrefs.SetInt("GameStartupSettings", "NumberOfEnemies", 15);
 * thePrefs.SetFloat("GameStartupSettings", "JumpHeight", 3.14159);
 * thePrefs.SetString("GameStartupSettings", "HeroName", "SuperDude");
 * \endcode
 *
 * Note that just setting the preference does not make it persist. If you want 
 *  to hang on to the current values of the preference system, call 
 *  \c thePrefs.SavePreferences() at some point. This will write out a file
 *  that the game will look for at next startup. 
 * 
 * There's a file in the Config directory of your game called \c defaults.ini.
 *  Any values you put in here will automatically be loaded into the 
 *  Preferences structure, where tables will become categories. The values will
 *  be overridden if you have called \c thePrefs.SavePreferences() to store
 *  them off. 
 * 
 * @subsection text Text Rendering
 * There are two steps you have to take before drawing text to the screen. 
 *  First off, you have to register the font with our text system. You can
 *  do this by calling RegisterFont:
 * 
 * \code
 * RegisterFont("Resources/Fonts/Helvetica.ttf", 12, "Helvetica12");
 * \endcode
 * 
 * This example will register the font file at the path we referenced (in our
 *  \c Resources/Fonts directory), at a size of 12 points, with the nickname
 *  "Helvetica12" that we will use to reference this font when we actually
 *  want to draw text. 
 * 
 * By default Angel includes a mono-spaced font called <a href=
 *  "http://www.levien.com/type/myfonts/inconsolata.html">Inconsolata</a>, 
 *  which it registers at 24 points as "Console" and 18 points as 
 *  "ConsoleSmall". You can use this for your own text if you like, or use
 *  any font which is readable by FreeType. Be careful when distributing your
 *  game, though, since most fonts are not free to distribute. Here are some
 *  resources for fonts which may be distributed (but check their licenses):
 *    - OFL Licensed Fonts: 
 *      http://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&item_id=OFL_fonts
 *    - Bitstream Vera Fonts:
 *      http://www.gnome.org/fonts/
 *    - Open Font Library:
 *      http://openfontlibrary.org/
 *    - Google Web Fonts:
 *      http://www.google.com/webfonts
 * 
 * When you actually want to render some text on the screen, you simply call:
 * 
 * \code
 * DrawGameText("Draw Me", "Helvetica12", 50, 50, 45.0f);
 * \endcode
 * 
 * This will render the text "Draw Me", in the font referenced by 
 *  "Helvetica12", starting at 50 pixels from the top of the window and 50
 *  pixels from the left of the window. It will be rendered at a 45 degree
 *  angle. Text will also accept any color values that you set using a 
 *  glColor* call, including transparency. 
 * 
 * Of particular note is that the text rendering system operates using pixel
 *  coordinates -- this is different from the rest of Angel, which uses the
 *  coordinates of the world for placing items. 
 * 
 * Most of the time, though, you won't need to manipulate the text system
 *  directly. It's typically easier to use a TextActor, which we'll cover
 *  in a bit. 
 * 
 * @section actors Actors
 * Actors are the central unit of simulation in Angel. Anything you want to
 *  place in the world -- your hero character, enemies, the ground, the walls,
 *  a spaceship -- is likely going to be an Actor. 
 * 
 * @subsection appearance Appearance
 * The base Actor provides all the functionality you need to draw something
 *  on the screen. It has a position, a size, a color, a texture (or series
 *  of textures), and a shape. 
 * 
 * \code
 * Actor *a = new Actor();
 * a->SetPosition(-3.0f, 4.0f);
 * a->SetColor(1.0f, 0.0f, 0.0f);
 * a->SetDrawShape(ADS_Circle);
 * a->SetSize(3.0f);
 * \endcode
 * 
 * This code will create an Actor who lives at (-3, 4) on the XY coordinate
 *  plane, is pure red, and drawn as a circle with a radius of 3. 
 * 
 * \b NB: The Actor won't show up in your world until you add it. Don't forget
 *  to call:
 * 
 * \code
 * theWorld.Add(a);
 * \endcode
 * 
 * This inserts your Actor into the world so it will start receiving Update
 *  and Render calls when the game loop runs. You can also pass a second 
 *  parameter to the World::Add function that indicates the layer you want
 *  to put this Actor on. This only affects the order in which an Actor is
 *  rendered -- Actors on lower layers will always appear behind Actors on 
 *  higher ones. Within a layer, Actors are drawn in the order they were 
 *  added. The layer numbers are arbitrary, so use whatever system makes 
 *  sense to you. 
 * 
 * You can also assign a texture to an Actor. If we wanted the previous actor 
 *  to have a texture, we would have called: 
 * 
 * \code
 * a->SetDrawShape(ADS_Square);
 * a->SetSprite("Resources/Images/superdude.png");
 * \endcode
 * 
 * Images can be in any format supported by <a href="
 *  http://openil.sourceforge.net/features.html">DevIL</a>, and any
 *  transparency on the image will show up in Angel. (Note that if you disable
 *  DevIL in AngelConfig.h, only PNG images will be supported.)
 * 
 * You can also assign multiple sprites to an Actor, either for use in an
 *  animation or for switching between various visual states. To load up a
 *  series of images, call: 
 * 
 * \code
 * a->LoadSpriteFrames("Resources/Images/superdude_001.png");
 * \endcode
 * 
 * This will load up the \c superdude_001.png file, and all other files that
 *  start with "superdude_" and end in a number. Internally we're limited to
 *  64 frames, but if you need to get more, simply change the 
 *  MAX_SPRITE_FRAMES value in Actor.h. 
 * 
 * Once you've loaded up your sprites, you can swap between them manually:
 * 
 * \code
 * a->SetSpriteFrame(7);
 * \endcode
 * 
 * Or play a series of them:
 *
 * \code
 * a->PlaySpriteAnimation(0.1f, SAT_OneShot, 0, 10, "JumpingAnim"); 
 * \endcode
 * 
 * That call will play frames 0-10, waiting 0.1 seconds between each frame,
 *  and ending when it finishes (other options are SAT_PingPong and SAT_Loop).
 *  The final parameter, "JumpingAnim," is an optional name assigned to this
 *  animation. When it finishes, the animation system will call 
 *  Actor::AnimCallback on this Actor, passing in that name. If you want to
 *  receive notifications about animations finishing, you can implement this
 *  in a subclass. 
 * 
 * @subsection names_tags Names and Tags
 * Once you've added a bunch of Actors to your world, it can become difficult
 *  to manage them. So we've added the ability to add metadata to Actors to
 *  make it easier to work with individuals and groups. 
 * 
 * The first bit of metadata is the Actor's name. Every Actor in the world
 *  has a name that is guaranteed to be unique. By default this name is simply
 *  "Actor" with numbers appended to make it unique, but you can assign 
 *  whatever names you want to your actors. 
 * 
 * \code
 * a->SetName("hank"); 
 * b->SetName("hank");
 * theWorld.Add(a);
 * theWorld.Add(b);
 * \endcode
 *
 * Actor names are always upper-cased, so after this code runs, \c a will 
 *  have the name "Hank." Since Actor names are also guaranteed unique, \c b
 *  will have the name "Hank1." (The Actor::SetName function returns the
 *  \b actual name that was assigned to the Actor, so you know what it is.)
 * 
 * \b NB: Names are only guaranteed unique when the Actor has been added to
 *  the World. Until then, if you haven't assigned a name, the Actor::GetName
 *  function will return an empty string. 
 * 
 * Later, if you want to access one of these objects, you can call:
 * 
 * \code
 * Actor *retrieved = Actor::GetNamed("Hank");
 * \endcode
 * 
 * The Actor::GetNamed function will return \c NULL if there's no Actor with
 *  the given name, so be sure to check your pointers before dereferencing. 
 * 
 * Oftentimes, though, you want to keep track of a group of Actors with 
 *  similar properties. That's where tags come in. You can throw a set of 
 *  freeform string data on an Actor and retrieve groups that match specific
 *  sets. For example: 
 * 
 * \code
 * //a, b, and c are Actors
 * a->Tag("blue, person");
 * b->Tag("blue, person, tall");
 * c->Tag("green, person");
 * 
 * ActorSet people = theTagList.GetObjectsTagged("person");
 * ActorSet bluePeople = theTagList.GetObjectsTagged("person, blue");
 * ActorSet tallPeople = theTagList.GetObjectsTagged("tall, person");
 * \endcode
 * 
 * After calling this, \c people will be an ActorSet containing \c a, \c b, 
 *  and \c c. \c bluePeople will just contain \c a and \c b, while \c 
 *  tallPeople will only contain \c b. If you decide that \c c is now 
 *  sub-human, you can call:
 * 
 * \code
 * c->Untag("person");
 * \endcode
 * 
 * Tags and names give you a lot of flexibility in how you manage groups of
 *  Actors. Depending on your specific need, it can be a lot easier to just
 *  use tags and names instead of managing your own pointers and groups of
 *  Actors. 
 * 
 * @subsection intervals Intervals
 * Usually, when you change an Actor's property, it immediately takes effect. 
 *  Setting a new position teleports the Actor there, changing a size happens
 *  immediately, etc. A lot of times, though, you want an Actor to visibly
 *  transition to a new state. You could set up a timer and do all your
 *  updates in the Actor::Update function to accomplish this, but if your 
 *  transition is straightforward, we've provided some utility functions to
 *  make it simpler. 
 * 
 * \code
 * a->MoveTo(Vector2(-5.0f, 0.0f), 3.0f, true, "MovementFinished");
 * a->RotateTo(0.0f, 3.0f, true);
 * a->ChangeColorTo(Color(0.0f, 0.0f, 1.0f), 3.0f, true);
 * a->ChangeSizeTo(3.0f, 3.0f, true);
 * \endcode
 * 
 * The Actor \c a will now begin moving from its current position to (-5, 0),
 *  while rotating to 0 degrees, turning blue, and changing its size to 3. 
 *  All of this will happen over the course of the 3 seconds (the second 
 *  parameter of each interval function is the duration).
 * 
 * The third parameter indicates whether the Actor should move linearly or 
 *  use the MathUtil::SmoothStep function. If the Actor is transitioning 
 *  smoothly, you'll see it ease out of the old state and into the new state;
 *  otherwise it will follow a straight trajectory. (See MathUtil::SmoothStep
 *  for more information.)
 * 
 * The final optional parameter to an interval function is a Message name that
 *  will get broadcast when the transition is done. Because all the changes in 
 *  our example will all finish at the same time, we only send one Message. 
 *  More on messaging in a bit; for now just know that it's a way for your 
 *  Actors to get notifications of specific events. 
 * 
 * @subsection derived_actors Subclasses
 * The base Actor class contains a lot of functionality, but oftentimes you
 *  want to do more or different things with it. We expect that most 
 *  developers will subclass Actor to add their own functionality to it. We
 *  also provide some useful subclasses, described below. 
 * 
 * @subsection camera Camera
 * A fairly unique subclass of Actor, the Camera is what controls how you
 *  view the world. By default, it's set up at (0, 0, 10), and looks at the
 *  origin. Note that the Camera is the only Actor in Angel which accepts 
 *  three-dimensional coordinates. You can zoom in and out by changing its
 *  Z value. Like the world, it uses the singleton pattern; its instance is
 *  accessed via \c theCamera. See the Camera class documentation for more 
 *  information. 
 * 
 * @subsection grid_actors GridActors
 * By default, a GridActor is the first thing you see when you start up 
 *  Angel. Not too surprisingly, it draws a grid of lines to the screen. Our
 *  default grid matches the OpenGL coordinate system, so it's useful for 
 *  placing objects in your world or setting up your camera positioning. You 
 *  can change the color of the lines, spacing, draw extents, etc. of the 
 *  grid. See the GridActor class documentation for more information. 
 * 
 * @subsection fullscreen_actors FullScreenActors
 * A FullScreenActor is useful for splash screens or backdrops. No matter 
 *  where you move the Camera, this Actor is guaranteed to take up the entire
 *  window. If there's a texture assigned, it will be stretched to fit the 
 *  current window parameters. See the FullScreenActor class documentation for
 *  more information. 
 * 
 * @subsection hud_actors HUDActors
 * HUD Actors are used when you want to create some element of user interface
 *  that should appear on the screen at the same position regardless of 
 *  Camera movements. Essentially, all the HUDActor's functions regarding
 *  things like size and position operate in pixel units and screenspace. 
 *  Otherwise, they are normal Actors, and you can do animations, transitions,
 *  etc. with them. See the HUDActor class documentation for more information.
 * 
 * @subsection particles_actors ParticleActors
 * A game isn't a game until it has particle systems! If you're unfamiliar 
 *  with what particles are in the context of a game, <a href="
 *  http://www.double.co.nz/dust/col0798.pdf">this article by Jeff Lander</a>
 *  is a good introduction. Don't worry about the implementation, though, 
 *  since we've done that for you. :-) 
 * 
 * The ParticleActor has a lot of properties to affect its appearance, but
 *  don't be scared. The important functions to look at are things like 
 *  ParticleActor::SetParticleLifetime, which says how long each individual
 *  particle can stay on the screen, ParticleActor::SetEndColor, which sets
 *  the color that the particle will transition to over its lifetime (use one
 *  with an alpha of 0 to have the particles fade out). 
 * 
 * You can set textures and animations on particles like you would with any
 *  other Actor -- animated particles are good for making things like smoke
 *  and fire. 
 * 
 * See the ParticleActor class documentation for more information. 
 * 
 * @subsection text_actors TextActors
 * The raw text rendering system described earlier is pretty limited. You 
 *  have to draw the text every frame, it doesn't handle newlines, it works
 *  in screen coordinates, you can't align the text, etc. The TextActor class
 *  mitigates these pains by bundling up a bunch of convenient text 
 *  functionality into an Actor which draws itself at a position in the World
 *  (as opposed to on the screen). 
 * 
 * \code
 * TextActor *t = new TextActor("Console", "Here I am \nRock you like a hurricane", TXT_Center);
 * theWorld.Add(t);
 * \endcode
 * 
 * This code will create a TextActor that is center-aligned, uses the default
 *  console font, and prints the lyrics to a totally sweet rock song. The
 *  newline character gets interpreted properly, so the second line of the
 *  song will be below the first one. 
 * 
 * See the TextActor class documentation for more information. 
 * 
 * @section messages Messaging
 * Angel supports sending messages through a centralized Switchboard class. 
 *  Any class which implements the MessageListener interface can send or 
 *  subscribe to Messages. 
 * 
 * Each Message has a name that it's given, which should tell what event it's
 *  signaling or what type of Message it is. MessageListeners who wish to 
 *  subscribe to that Message pass it to the Switchboard to receive newly
 *  broadcast Messages every frame.
 * 
 * \code
 * theSwitchboard.SubscribeTo(a, "MeteorHit");
 * theSwitchboard.UnsubscribeFrom(a, "GameStarted");
 * theSwitchboard.Broadcast(new Message("ReadyToGo"));
 * TypedMessage<Vector2> loc = new TypedMessage("StartingSpot", a->GetPosition(), a);
 * theSwitchboard.Broadcast(loc);
 * \endcode
 * 
 * This code does a few things. First of all, it subscribes \c a to any 
 *  Messages named "MeteorHit." So when someone broadcasts a MeteorHit 
 *  message, the MessageListener::ReceiveMessage function will be called on \c 
 *  a. Then it unsubscribes \c a from the "GameStarted" Message, so it won't 
 *  receive notifications anymore. Finally, it creates a new TypedMessage that
 *  carries a bit of position data, and broadcasts it to anyone who cares
 *  about Messages with the name "StartingSpot." (TypedMessages are a 
 *  templated class, so you can put anything you need to broadcast into them.)
 * 
 * \b NB: When you pass a Message pointer to the Switchboard::Broadcast 
 *  function, that's it, you're done with it. The Switchboard will delete the
 *  memory once it's delivered the Message to all subscribers, so don't expect
 *  to do anything with it afterwards. It's not a good idea to hang on to 
 *  Message pointers for this reason. 
 * 
 * Controller and keyboard input is performed using Messages -- by making 
 *  changes to the \c input_bindings.ini file in your \Config directory, you
 *  designate what Messages get sent when keys or buttons are pressed. (See 
 *  the \c input_bindings.ini file included with IntroGame for an example.)
 * 
 * By using Messages to signal game events, you make it easier to extend your
 *  game -- anybody can listen for any message, so you don't have to keep 
 *  making changes to the class sending the signals to have new objects
 *  respond to it. You can also kind of "sketch out" your game flow in Message
 *  form before implementing game logic, or experiment with an individual 
 *  Actor by sending it the Messages it will receive when it's a part of the
 *  full game. 
 * 
 * @section physics Physics
 * Angel supports simple rigid body physics by incorporating the <a href="
 *  http://www.box2d.org/">Box2D</a> library. Box2D has \b a \b lot of 
 *  functionality, so check out the documentation available on their website
 *  and wiki for details. 
 * 
 * If all you want to do is play with some simple physics, though, we've 
 *  wrapped up a lot of Box2D into a very \e angelic interface. :-) 
 * 
 * The first thing you need to do if you want to use physics is call 
 *  World::SetupPhysics. By default, this function sets up physics with
 *  a standard gravity pointing down the Y axis and extending from (-100, 
 *  -100) to (100, 100). (Outside of that region, physics don't exist. It is
 *  the netherrealm.) You can override these defaults if you want a different
 *  (or no) gravity, or a differently sized simulation space. 
 * 
 * Afterwords, you can create a PhysicsActor and put them in the world. 
 * 
 * \code
 * p1 = new PhysicsActor();
 * p1->SetDensity(0.8f);
 * p1->SetFriction(0.5f);
 * p1->SetRestitution(0.7f);
 * p1->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
 * p1->InitPhysics();
 * \endcode
 * 
 * This creates a new PhysicsActor, sets up its physical properties, and
 *  kicks it into motion. If you're not familiar with the physics terms, see 
 *  the individual function documentation for information on the effects they
 *  have on your object. Note that the PhysicsActor will not start being 
 *  physically simulated until you call PhysicsActor::InitPhysics. That 
 *  function also locks in the physical properties you set, and they can no 
 *  longer be changed. (Also things like position and rotation, since you've 
 *  now turned those over to Sir Isaac Newton.)
 * 
 * @subsection side_blockers Side-Blockers
 * Oftentimes you want to keep your PhysicsActors from flying off the edge of
 *  the screen. We've added a function to the World that makes it easy to set
 *  up blockers at the edge of the screen. 
 * 
 * \code
 * theWorld.SetSideBlockers(true, 0.7f);
 * \endcode
 * 
 * That code will turn the blockers on and make them fairly bouncy 
 *  (restitution = 0.7). You can turn them off or change their bounciness at
 *  any time. Note that the side blockers move when the Camera moves, but
 *  otherwise are static in the world. 
 * 
 * @section input Input
 * A game isn't much without being able to accept input from the player. We've
 *  provided three different ways to get that input, which should cover a 
 *  pretty good variety of use cases. 
 * 
 * @subsection mouse Mouse
 * There are two things that you care about with regard to the mouse: when 
 *  the player moves it, and when they click it. To get information on either
 *  of these events, have a class implement the MouseListener interface. 
 *  Any instance of MouseListener will get MouseListener::MouseMotionEvent, 
 *  MouseListener::MouseDownEvent, and MouseListener::MouseUpEvent called when
 *  these happenings take place. All three functions pass in the current 
 *  mouse coordinates (in screen space), and the button functions pass in an
 *  enum to tell you which button was affected (if you care about left-click 
 *  vs. right-click, for instance). 
 * 
 * It's a pretty bare-bones mouse notification system, but it should be enough
 *  to build whatever mouse input functionality you need. 
 * 
 * @subsection keyboard Keyboard
 * The keyboard contains many more buttons than the mouse (at least on most
 *  machines). Keyboard input is handled through the Messaging system and 
 *  the \c input_bindings.ini file located in the Config directory. Using that
 *  \c .ini file, you can map keypresses to Messages that will be sent at the
 *  appropriate time. For instance:
 * 
 * \code
 * SPACE= Jump
 * G= ToggleGrid
 * A= +SomeonePressedA
 * A= -SomeoneReleasedA
 * \endcode
 * 
 * Maps the space bar to a "Jump" Message and the \e G button to a 
 *  "ToggleGrid" Message. The \e A button mappings here are a bit more
 *  interesting. By prepending a Message with \e +, you indicate that Message
 *  should only be sent when the key is pressed down. If you prepend it with 
 *  a \e - (minus sign), the Message will be sent when the key is released. 
 *  If you have no symbol in front of a Message, the assumption is that you
 *  want it sent when the key is pressed. 
 * 
 * Once you have your input bindings set up, you just need to set up objects
 *  in your world to listen for those Messages and respond appropriately. 
 * 
 * For a more immediate check without having to set up Messages and bindings,
 *  you can call InputManager::IsKeyDown, passing it either a plain \c char or
 *  any of the defined values from \c GL/glfw.h. 
 * 
 * \code
 * bool d = theInput.IsKeyDown('d'); // Will return true if the D button is pressed
 * \endcode
 * 
 * @subsection controller Controller
 * Angel supports getting input from an Xbox 360 controller connected over 
 *  USB. On Windows, developers will need the DirectX SDK and players will 
 *  need the DirectX runtime. Both are freely available from Microsoft. On 
 *  the Mac, developers and players both need to install a kernel extension
 *  that exposes the controller as a HID device. It's available in our Tools
 *  directory, or from 
 *  http://tattiebogle.net/index.php/ProjectRoot/Xbox360Controller/OsxDriver 
 * 
 * To get input from the controller, you have a few options. For button 
 *  presses, you can use the input_bindings.ini file to map things like
 *  \c P1BUTTON_A for the \e A button on controller one. You can also 
 *  directly query the controller during gameplay, which gives you access to
 *  the analog sticks and triggers. You can also use the vibration function
 *  of the controller (currently only on Windows). 
 * 
 * See the Controller class documentation for more information. 
 *
 * @subsection multitouch MultiTouch
 * When building for iOS devices, Angel will wrap the unique hardware input
 *  for these devices into a more angelic, C++ interface so you don't have
 *  to learn Objective-C and/or scatter your code with strange references to
 *  a foreign SDK. 
 * 
 * You can have any of your classes inherit from TouchListener to get
 *  notifications when each touch starts, moves, or ends. (The interface is
 *  very similar to the MouseListener setup.)
 * 
 * In addition, you can query to get a list of all touches the devices is 
 *  currently registering with the static function TouchListener::GetTouchList,
 *  which returns a list of pointers to Touch structures.
 * 
 * Finally, there's the Accelerometer class, which just provides access to 
 *  the current tilt data as a Vector3. Note that it does some simple 
 *  buffering and smoothing of the values to prevent jitter -- if you want to
 *  tweak the lag/smoothness tradeoff, edit the value for 
 *  ANGEL_ACCEL_BUFFER_SIZE, found in AngelAppDelegate.m
 *
 * @subsection mobilesimulator MobileSimulator
 * Angel builds and runs on iOS devices and the simulators that Apple provides
 *  with their SDK. Maybe not everyone on your team has a Mac, though, or 
 *  you just want to play with an idea and don't want to bother setting up the
 *  extra machine. The MobileSimulator class will help you out here. When you
 *  add one of these objects for the world, it \e pretends to be the hardware
 *  of an iPhone, iPod Touch, or iPad. Mouse clicks are treated as touches, 
 *  holding down the Ctrl key will let you play with multi-touch gestures, 
 *  and the Xbox 360 controller's thumbsticks are read as the accelerometer
 *  input. 
 * 
 * The important thing here is that this simulator fills all the same data
 *  structures that the real hardware would, so as long as your code is 
 *  working through the provided TouchListener and Accelerometer interfaces,
 *  it will work the same as it would on the device itself. 
 * 
 * Obviously you would eventually want to build with the real Apple SDK, but
 *  this can get you a lot of the way there. Also, since the iOS build doesn't
 *  support the Console, using the MobileSimulator can be useful to let you
 *  run the same code, but have more control over your world while you're 
 *  prototyping. 
 * 
 * @section sound Sound
 * The sound system in Angel is a wrapper around <a href="
 *  http://www.fmod.org">FMOD</a>. It can play most sound formats, including 
 *  WAV, MP3, and Ogg Vorbis. We recommend Ogg for your sound distribution
 *  needs because of the following properties: 
 *   - It's free to distribute Ogg files, unlike MP3s, which require a 
 *     license. (We're just talking about the file formats themselves here; 
 *     copyrighted content is still legally thorny to distribute.)
 *   - They have good compression to save you space (unlike WAVs)
 *   - They have more precise timing than MP3s, which can be important if 
 *     you're trying to sync up events in your game with a music track. 
 * 
 * If you don't currently have a sound program capable of dealing with Ogg, 
 *  there's <a href="http://audacity.sourceforge.net/">Audacity</a>, which is 
 *  free, and <a href="http://reaper.fm/">Reaper</a>, which has a free trial 
 *  period.
 * 
 * There are two steps to playing sound in your game. 
 * 
 * \code
 * SAMPLE_HANDLE mySound = theSound.LoadSample("Resources/Sounds/bonk.ogg", false);
 * SOUND_HANDLE soundPlaying = theSound.PlaySample(mySound);
 * \endcode
 * 
 * The first call loads up a sound from disk and prepares it for playback. It
 *  returns a sound handle that you'll want to hold on to so you can use it
 *  for triggering the sound later. The \c bool parameter says whether or not
 *  the sound should stream or get loaded all at once (longer sounds should 
 *  be streamed). 
 * 
 * After a sound has been loaded, you play it with the second call, passing
 *  the handle you got from the first. There are additional parameters you can 
 *  set when calling SoundDevice::PlaySample, to set the volume, the stereo 
 *  positioning, and whether it should loop. This function returns a 
 *  SOUND_HANDLE that you can use to manipulate the sound \b during its 
 *  playback.
 * 
 * See the SoundDevice class documentation for more information. 
 * 
 * FMOD is the default sound system for Angel, but it is \b not free to
 *  distribute if you are charging for your game. 
 *  Their <a href="http://www.fmod.org/index.php/sales">rates</a> are very
 *  reasonable, but if you would prefer a free alternative, you can disable
 *  FMOD in AngelConfig.h. This will cause Angel to fall back to OpenAL 
 *  support only. 
 * 
 * \b NB: OpenAL, as implemented in Angel, does not produce sound at the same
 *  quality level as FMOD. In particular, you're likely to hear skips/pops at
 *  the boundaries of looping audio. In addition, we only support Ogg Vorbis
 *  playback if you've chosen to use OpenAL. Them's the breaks. 
 * 
 * @section ai AI
 * @subsection pathfinding Pathfinding
 * One of the trickier problems of low-level AI is getting characters to move
 *  around the environment without running into things. Real games use big
 *  expensive solutions like <a href="http://en.wikipedia.org/wiki/Kynapse">
 *  Kynapse</a>, because generating pathfinding data in 3D is hard. Luckily, 
 *  we're only 2D, so we whipped up a path generation system just for Angel. 
 *  The paths it produces aren't the prettiest, but it sure beats authoring
 *  by hand (and then having to change it if you change the layout of your
 *  space).
 * 
 * The path generation tool will generate paths around PhysicsActors located
 *  in the world. The best idea is probably to add your static geometry (the 
 *  things you want to path around), generate your pathfinding data, then add
 *  all your other PhysicsActors. 
 * 
 * Here's how you actually generate path data:
 * 
 * \code
 * BoundingBox bounds(Vector2(-20, -20), Vector2(20, 20));
 * theSpatialGraph.CreateGraph(0.75f, bounds);
 * \endcode
 * 
 * First we create a bounding box to let the spatial graph know what area it
 *  needs to explore (the smaller the area, the quicker the paths will 
 *  generate). The second function takes a radius and the bounding box we 
 *  made. The radius is how wide the Actor who will be trying to pathfind is. 
 *  This way the generator knows how small a space is too small for it to fit.
 * 
 * Once you've generated the graph, you're ready to get path information from
 *  it. 
 * 
 * \code
 * Vector2 start(0, 0);
 * Vector2 end(5, 5);
 * VectorList path;
 * theSpatialGraph.GetPath(start, end, path);
 * \endcode
 * 
 * SpatialGraph::GetPath will fill up the \c path parameter with a list of
 *  points which make up the most efficient path from \c start to \c end. If 
 *  there is no path available, \c path will be empty. 
 * 
 * Once you have this data, your actors can do with it whatever they want. 
 *  See the IntroGame's Pathfinding screen for an example of how to build an
 *  Actor that follows a path to a given point. 
 * 
 * (Note that even in a large space, generating the spatial graph is fairly 
 *  quick. While you definitely shouldn't call it every frame, calling it when
 *  something major has changed in your world is not inappropriate.)
 * 
 * @subsection other_ai Other AI
 * The good news is that there are other AI functions in Angel, like a 
 *  simple state machine that can let you give different goals to an Actor
 *  and have him switch between them (including automatically traversing a 
 *  path). 
 * 
 * The bad news is that it was written by someone who's no longer affiliated
 *  with Angel, and the code is mysterious. Some day it will be investigated, 
 *  grokked, and documented. But not today. (If somebody would like to take up 
 *  this task, we wouldn't stop them.)
 * 
 * @section archs_and_levels Archetypes and Level Files
 * @subsection actor_defs Archetypes
 * When you want to iterate on an Actor's properties (getting it to be just
 *  the right size or starting position), it can be very annoying to have to
 *  keep recompiling your whole game just to check on it. We've provided a 
 *  way to make actor definitions data-driven so you can just work with a 
 *  set of text files. 
 * 
 * In the \c Config directory of your game, you'll find another directory 
 *  called \c ActorDef. Any \c .lua file you throw in here will be assumed to
 *  be describing a set of Actor archetypes. The format is fairly 
 *  straightforward. 
 * 
 * \code
 * simple_actor = {
 *   color = {1, 0, 1},
 *   position = {-3, -2},
 *   alpha = 0.5,
 *   size = 5,
 *   tag = "simple, small, purple",
 *   name = "SimpleActor"
 * }
 * \endcode
 * 
 * If you're familiar with Lua, you may notice that this is a straight-up 
 *  table declaration. The name of the table represents the name of the 
 *  archetype -- what you'll use to actually instantiate it. 
 * 
 * The properties that follow will directly affect the Actor after it's been
 *  created. Any Actor function that takes the form "SetX" can be used here
 *  as simply "x," and other functions can simply be lowercased to be invoked 
 *  (see how Actor::Tag became simply "tag"). Vectors and colors are enclosed 
 *  in braces. The properties in an Actor defintion file will only work for 
 *  functions that take one parameter -- if you try and call something with 
 *  multiple parameters, you'll get scripting errors. 
 * 
 * Once we've defined \c simple_actor in our file, we can create one in
 *  code very simply. 
 *
 * \code
 * Actor *a = Actor::Create("simple_actor");
 * \endcode
 * 
 * Note that the Actor::Create function doesn't add the Actor to the World, so
 *  you'll still want to call World::Add. 
 * 
 * @subsection levels Level Files
 * Once we've made our actor definitions, we may want to iterate on their 
 *  placement in the world. To do that, we create another \c .lua file in 
 *  \c Config/Level. 
 * 
 * \code
 * LeftActor = {
 *   type = "simple_actor",
 *   size = 3,
 *   position = {-5, 0},
 *   tag = "spawned"
 * }
 * 
 * RightActor = {
 *   type = "simple_actor",
 *   size = 5,
 *   position = {5, 0},
 *   color = {1, 0, 0},
 *   alpha = 0.8,
 *   tag = "spawned"
 * } 
 * \endcode
 * 
 * Each section in a level file describes an Actor to be placed in the world. 
 *  The first property in a section is \c type, which indicates which 
 *  archetype to use for this Actor. All the properties after that will be
 *  called on the newly created Actor, \b potentially \b overriding properties
 *  set in the archetype. 
 * 
 * To load a level in code:
 * 
 * \code
 * theWorld.LoadLevel("my_level");
 * \endcode
 *
 * This example will process \c Config/Level/my_level.lua, create all the 
 *  Actors from designated archetypes, apply the additional properties, and 
 *  add them to the world. 
 * 
 * @section lua Lua
 * Angel includes Lua scripting, for those who prefer to work in something
 *  other than C++. Internal functions are exposed to the scripting layer  
 *  using <a href="http://www.swig.org/">SWIG</a>. Within Angal, Lua is 
 *  intended less as a full runtime (though you can receive messages, create 
 *  Actors, and call almost all engine functions from Lua), but more as a 
 *  configuration language for use in ActorDefs and Level files.
 * 
 * In the \c Resources/Scripts directory, you'll find a file called \c 
 *  client_start.lua. This will get executed at startup, so any Lua setup
 *  you want to do can go in here. 
 * 
 * Most internal functionality is exposed in Lua. So, for example, you 
 *  could have this in your \c client_start.lua.
 * 
 * \code
 * a = Actor_Create("simple_actor")
 * theWorld:Add(a)
 * \endcode
 * 
 * Yeah, it's not too exciting, but you don't have to recompile the engine 
 *  when you change it! 
 * 
 * If you're not familiar with Lua, Roberto Ierusalimschy's <i><a 
 *  href="http://www.lua.org/pil/contents.html">Programming in Lua</a></i> is 
 *  a good start. (The online edition is for version 5.0, whereas we ship 
 *  with 5.2. Most functionality is the same, but there are some differences, 
 *  so if you want to dive further into Lua, be sure to track down a print 
 *  copy.)
 * 
 * @subsection console In-Game Console
 * When you press the "~" button, the in-game console appears. This is, for
 *  most intents and purposes, a functional Lua console. From here you 
 *  can manipulate your world, create new Actors, modify existing ones, etc. 
 * 
 * It even has auto-complete. Pretty snazzy. 
 * 
 * @section tuning Tuning
 * Very frequently while developing a game, you'll want the ability to change
 *  values at runtime and watch their results. We provide a few methods of 
 *  doing this; hopefully one of them is a good fit to your workflow. 
 * 
 * If you look in your \c Config directory, you'll see a file called 
 *  \c tuning.lua. You can declare variables in here that will be available 
 *  for easy tuning when the game runs. 
 * 
 * As an example, if you wanted to tune how high a character jumped, you 
 *  could put this in your tuning file: 
 * 
 * \code
 * JumpHeight = {
 *   type = "float",
 *   value = 10.0
 * }
 * \endcode
 * 
 * Then, in your C++ code, in the function that handles jumping, you get 
 *  access to it like so: 
 * 
 * \code
 * float jumpHeight = theTuning.GetFloat("JumpHeight");
 * \endcode
 * 
 * Lua usage would looks nearly identical:
 * 
 * \code
 * jumpHeight = theTuning:GetFloat("JumpHeight")
 * \endcode
 * 
 * Now this doesn't seem like much of a win, since you could have just 
 *  \c #defined it at the top of your source file. But, if you edit this 
 *  \c tuning.lua file while the game is running, Angel will detect the 
 *  changes and alter the variable's value. 
 * 
 * If you prefer to stay in one program while tuning, we also provide some
 *  easy console handles for playing with variables. Pull up the console with
 *  (~), and run: 
 * 
 * \code
 * tune("JumpHeight", 3)
 * \endcode
 * 
 * And you'll see the effects immediately in-game. 
 * 
 * Once you have the values where you want them, you can call 
 *  \c SaveTuningVariables() from the console and the values you've set will
 *  be written back out into the file so you don't have to try and remember
 *  them. 
 * 
 * @section ios Working on iOS
 * There are a few differences to be aware of when building a game for iOS, or
 *  when porting an existing game to the platform. 
 * 
 *  - iOS apps are structured a little differently than traditional desktop
 *    programs. In particular, the \c main() function is used to set up the
 *    OpenGL context and input hooks, so the spot to do any game initialization
 *    is now in \c iPhoneMain.cpp. 
 *  - You can't set the name of your came in the \c build.lua file anymore, 
 *    because Xcode needs to know the final program name so it can do 
 *    code signing. To set your game's name, open the target properties for
 *    ClientGame and set the "Product Name" value to whatever you want.
 *  - If you are disabling FMOD, in addition to setting the value in 
 *    AngelConfig.h, you \b also need to remove the "Other Linker Flags" 
 *    values in the Target properties. Otherwise the app will try to link
 *    against FMOD anyway, and then segfault when you try to load audio. 
 *  - In the \c ClientGame/ios folder, in addition to the \c iPhoneMain.* 
 *    and \c .plist files, you'll also find a series of images. 
 *    - The ones named as \c Icon*.png will, not surprisingly, get used as 
 *      icons in various places in iOS. Don't change the names, dimensions, or
 *      format of any of these images, but put your own content into each image
 *      file. The Xcode target has already been set up to pull these images in
 *      as part of the packaging process. 
 *    - The ones called \c Default*.png will be used as splash screens on 
 *      various devices while the game is loading. Same principles apply -- 
 *      keep the names, dimensions, and PNG format, but put whatever you want 
 *      into the files. 
 *    - Finally, there's the \c iTunesArtwork file. Though it doesn't have a
 *      file extension, it's a PNG file at 512x512 pixels. It's for that 
 *      glorious day in the far-flung future when your game is making a 
 *      hojillion dollars on the App Store. This is the image that will be 
 *      displayed on the store page. 
 * 
 * See the \ref multitouch "MultiTouch" section for information on how to 
 *  access the hardware input of iOS devices. 
 * 
 * @section util Niceties and Handy Doodads
 * Finally, we provide a number of utility classes and functions to handle 
 *  common game tasks. In particular, the MathUtil class contains declarations
 *  of constants and wrappers for common (annoying) math that game developers
 *  find useful. The StringUtil.h file contains a number of simple functions 
 *  for processing strings. Check them out before re-inventing the wheel. 
 * 
 * @subsection publish Publish Script
 * Modern software distribution can be a pain, especially ensuring that what
 *  runs on the developer's machine will run on the player's. Making sure 
 *  all the resources are included, the right libraries, etc. We've taken some
 *  steps to make this easier on you in the form of the publish scripts. 
 * 
 * On Windows, the publish script runs whenever you build your program in 
 *  Release mode. (If you find this to be a buzzkill, you can disable it by 
 *  going to Project -> Properties -> Configuration Properties -> Build Events 
 *  -> Post-Build Event and editing the command line there. Make sure you're 
 *  editing the Release configuration.) After the script runs you'll find a \c 
 *  Published directory sitting in your \c Release directory. It should 
 *  contain everything you need to run your game. Let us know if you find 
 *  that something is missing from the \c Published directory so the publish 
 *  script can be updated. 
 * 
 * On the Mac, the publish script also runs when you build in Release, which
 *  you can disable by commenting out the appropriate lines in the "Run 
 *  Script" phase of your game's target. It produces a \c Published directory 
 *  in your \c build directory that should also contain everything you need
 *  to distribute your game. 
 * 
 * Both publish scripts also put the \c Attributions.txt and \c GameInfo.txt 
 *  alongside the executable for your game. The attributions file is important
 *  for licensing purposes (Angel uses \b a \b lot of open source libraries), 
 *  and the GameInfo file is good for giving your players whatever additional
 *  information you want them to have about your game. 
 * 
 * @section final Final Thoughts
 * This was an overview of what Angel can do, but there's a lot more to be 
 *  found by exploring the classes and their interactions. The full API 
 *  documentation is also here, so poke around if you're curious as to exactly
 *  what a certain function or class does. 
 * 
 * Or, try it out in your game and see what it does. :-) 
 * 
 * Good luck! 
 * 
 * @section bugs Bug Reports and Feedback
 * Please use the angel-engine Google Group to discuss any problems, thoughts,
 *  ideas for new features, bugs, complaints about the documentation, etc. 
 * 
 * http://groups.google.com/group/angel-engine
 * 
 * We'd especially like to see any games you make with Angel! For serious. 
 * 
 * 
 */


#pragma once

#include "AngelConfig.h"

#include "Actors/Actor.h"
#include "Actors/FullScreenActor.h"
#include "Actors/GridActor.h"
#include "Actors/HUDActor.h"
#include "Actors/ParticleActor.h"
#include "Actors/PhysicsActor.h"
#include "Actors/TextActor.h"

#include "AI/BoundingShapes.h"
#include "AI/Brain.h"
#include "AI/PathFinder.h"
#include "AI/Ray2.h"
#include "AI/Sentient.h"
#include "AI/SpatialGraph.h"
#include "AI/Traversal.h"

#include "AIEvents/GotoAIEvent.h"
#include "AIEvents/GotoTargetAIEvent.h"
#include "AIEvents/NamedEventAIEvent.h"
#include "AIEvents/TimerAIEvent.h"
#include "AIEvents/TraversalAIEvent.h"

#include "Infrastructure/Camera.h"
#include "Infrastructure/Color.h"
#include "Infrastructure/Common.h"
#include "Infrastructure/GameManager.h"
#include "Infrastructure/Interval.h"
#include "Infrastructure/Log.h"
#include "Infrastructure/Preferences.h"
#include "Infrastructure/Renderable.h"
#include "Infrastructure/RenderableIterator.h"
#include "Infrastructure/SoundDevice.h"
#include "Infrastructure/TagCollection.h"
#include "Infrastructure/TextRendering.h"
#include "Infrastructure/Textures.h"
#include "Infrastructure/TuningVariable.h"
#include "Infrastructure/VecStructs.h"
#include "Infrastructure/Vector2.h"
#include "Infrastructure/Vector3.h"
#include "Infrastructure/World.h"

#if !ANGEL_MOBILE
	#include "Input/Input.h"
	#include "Input/InputManager.h"
	#include "Input/MouseInput.h"
	#include "Input/Controller.h"
	#include "Input/MobileSimulator.h"
#endif
#include "Input/MultiTouch.h" 

#include "Messaging/Message.h"
#include "Messaging/Switchboard.h"

#include "UI/UserInterface.h"

#include "Util/DrawUtil.h"
#include "Util/FileUtil.h"
#include "Util/MathUtil.h"
#include "Util/StringUtil.h"
