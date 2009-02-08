#pragma once

/**
 * @mainpage The Angel Engine 
 * @section ReadMe
 * Make sure to first read the overview information at 
 *  http://code.google.com/p/angel-engine/ -- it contains a good rundown of 
 *  what Angel is and, more importantly, what it is not. Calibrating your 
 *  expectations can save a lot of heartache later. :-)
 * 
 * @section intro Introduction
 * As will be apparent after the first section, this documentation is 
 *  incomplete. Efforts are ongoing. 
 * 
 * @section code_tour A Brief Tour of the Code
 * If you open the Code directory, you should see the following files and 
 *  subdirectories [not an exhaustive list, these are just the ones that are
 *  interesting or may warrant explanation]: 
 *  - \b GameJam.sln: The Visual Studio 2005 solution file (Windows)
 *  - \b GameJam.xcodeproj: The Xcode 3 build and projet information (Mac OS 
 *       X)
 *  - \b Angel: where the core prototyping framework gets built. Doesn't do 
 *       anything by itself, but requires client code to load it up and get 
 *       things going. 
 *    - \e Angel.h: the master header file that includes all other header 
 *      files you should need for your game. The included starter projects 
 *      have this set up as part of their pre-compiled header. 
 *    - \e Libraries: all the third-party libraries that Angel works to do its 
 *      magic. \n
 *      They all include their distributed documentation and appropriate 
 *      website links.
 *      - Box2D: Physics \n
 *        (http://www.box2d.com)
 *      - FMOD: Sound \n
 *        (http://www.fmod.org)
 *      - FreeImage: Image loading \n
 *        (http://freeimage.sourceforge.net)
 *      - FreeType: Font rasterization \n
 *        (http://www.freetype.org)
 *      - FTGL: Makes it easy to use FreeType in OpenGL \n
 *        (http://homepages.paradise.net.nz/henryj/code/#FTGL)
 *      - GLFW: A cross-platform framework to handle basic windowing and input 
 *        events \n
 *        (http://glfw.sourceforge.net/)
 *      - HID Utilities: USB Controller support for Mac OS X \n
 *        (http://developer.apple.com/samplecode/HID_Utilities_Source/index.html)
 *  - \b Tools: a collection of scripts and tools that are used as part of the 
 *       build process or may be useful to developers.
 *    - \e BuildScripts: the Python files which get called during the build 
 *      process
 *      - \c angel_build.py: utility functions and classes for the 
 *        build/publish
 *      - \c publish.py: On Windows, this gets called whenever you make a 
 *        release build. \n
 *        It produces a new directory called \c Published within your project 
 *        directory -- the \c Published directory should contain everything 
 *        your game needs to run on any system and is suitable for zipping up 
 *        and sharing. 
 *      - \c swig_wrap.py: part of the build process to determine if the SWIG 
 *        scripting bridge needs to be regenerated. It can be time consuming 
 *        to regenerate and recompile, so it's worth checking first. (See 
 *        SWIG, below.)
 *    - \e Mac360: The binary and source versions of a Mac OS X kernel 
 *      extension that makes it possible for Angel to interface with the Xbox 
 *      360 controller. You may have trouble compiling if this isn't 
 *      installed. (A pain, but thems the breaks.)
 *    - \e Python25: The official Python distribution for Windows. All our 
 *      build scripts run using this Python, and the publish script will 
 *      package up the appropriate modules from here, so if you ever need to  
 *      install more Python goodies for your game, make sure to do it in this 
 *      directory as opposed to whatever local installation you may have of 
 *      Python. (Note that at present, the Mac version just uses the OS X 
 *      built-in Python, and doesn't package up modules for distribution.)
 *    - \e swigwin: The Windows distribution of SWIG -- a tool for generating 
 *      script interfaces to C and C++ code. The \c swig_wrap.py build script 
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
 *    - \e build.ini: a set of values used by the build and publish scripts to 
 *      customize your game. At the moment, it only contains a value for 
 *      giving your game a name -- we strongly recommend naming your game here 
 *      as opposed to renaming the project itself so merging will be easier 
 *      later. 
 *    - \e Config: configuration files for your game -- this entire directory 
 *      gets copied to your distribution, so don't leave anything in here you 
 *      don't want to become public somehow. 
 *      - \c input_bindings.ini: maps keyboard and controller button presses 
 *        to Messages that will be sent in the game (see below)
 *      - \c ActorDef: definition files for your actor archetypes (see below)
 *      - \c Level: defintions files for your levels (see below)
 *    - \e Logs: Where any logs you generate in your game will be stored for 
 *      later viewing. (Assuming you use the Angel built-in logging. Obviously 
 *      you could write your own files wherever the heck you want.) Gets 
 *      copied to the Published directory.
 *    - \e Resources: All non-code bits of your game should go in here. This 
 *      will also be copied to the Published directory. 
 *      - \c Fonts: hopefully this is self-explanatory
 *      - \c Images: hopefully this is self-explanatory
 *      - \c Sounds: hopefully this is self-explanatory
 *      - \c Scripts: Any Python that you want to use in your game should get 
 *        put in here. The included \c client_start.py gets imported directly 
 *        into the console namespace, so any functions you define here will be 
 *        available in the console. If you want to create your own classes or 
 *        do any game setup from Python, \c client_start.py is where it should 
 *        go. As you build you'll notice other files get copied to this 
 *        directory -- the scripts that help make Angel run. These files will 
 *        be frequently updated from the \c Angel/Scripts/EngineScripts 
 *        directory every time you build, so making changes to them here will 
 *        leave you disappointed when they get overwritten. 
 * 
 * @section world The World
 * @subsection logging Logging
 * @subsection text TextRendering
 * 
 * @section actors Actors
 * @subsection grid_actors GridActors
 * @subsection fullscreen_actors FullScreenActors
 * @subsection hud_actors HUDActors
 * @subsection particles_actors ParticleActors
 * @subsection text_actors TextActors
 * 
 * @section messages Messaging
 * @subsection input Handling Input
 * 
 * @section physics Physics
 * @subsection side_blockers Side-Blockers
 * 
 * @section sound Sound
 * 
 * @section util Niceties and Handy Doodads
 * 
 * @section ai AI
 * 
 * @section archs_and_levels Archetypes and Level Files
 * 
 * @section python Python
 * @subsection console In-Game Console
 * @subsection python_subclasses Python Sublasses
 * 
 * @section bugs Bug Reports
 * 
 * 
 */


#include "Actors/Actor.h"
#include "Actors/FullScreenActor.h"
#include "Actors/GridActor.h"
#include "Actors/HUDActor.h"
#include "Actors/ParticleActor.h"
#include "Actors/TextActor.h"

#include "AI/BoundingShapes.h"
#include "AI/Brain.h"
#include "AI/Pathfinder.h"
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
#include "Infrastructure/Renderable.h"
#include "Infrastructure/RenderableIterator.h"
#include "Infrastructure/SoundDevice.h"
#include "Infrastructure/TagCollection.h"
#include "Infrastructure/TextRendering.h"
#include "Infrastructure/Textures.h"
#include "Infrastructure/VecStructs.h"
#include "Infrastructure/Vector2.h"
#include "Infrastructure/Vector3.h"
#include "Infrastructure/World.h"

#include "Input/Input.h"
#include "Input/InputManager.h"
#include "Input/MouseInput.h"
#include "Input/Controller.h"

#include "Messaging/Message.h"
#include "Messaging/Switchboard.h"

#include "Physics/PhysicsActor.h"
#include "Physics/PhysicsDebugDraw.h"

#include "Util/DrawUtil.h"
#include "Util/FileUtil.h"
#include "Util/MathUtil.h"
#include "Util/StringUtil.h"
