//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
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

#include "stdafx.h"
#include "../Infrastructure/World.h"

#include "../Infrastructure/Camera.h"
#include "../Infrastructure/Log.h"
#include "../AI/SpatialGraph.h"
#if !ANGEL_MOBILE
	#include "../Infrastructure/Console.h"
	#include "../Input/Input.h"
	#include "../Input/MouseInput.h"
	#include "../Input/Controller.h"
	#include "../Input/InputManager.h"
#else
	#include "../Infrastructure/TextRendering.h"
#endif
#include "../Infrastructure/Textures.h"
#include "../Actors/PhysicsActor.h"
#include "../Messaging/Switchboard.h"
#include "../Scripting/LuaModule.h"
#include "../Infrastructure/Preferences.h"
#include "../Infrastructure/SoundDevice.h"
#include "../UI/UserInterface.h"
#include "../Util/DrawUtil.h"

#if defined(WIN32) && defined(ANGEL_RELEASE)
	#include <comdef.h>
#endif
#include <algorithm>

World* World::s_World = NULL;

World::World()
{
	_simulateOn = true;
	_initialized = false;
	_started = false;
	_physicsRemainderDT = 0.0f;
	_physicsSetUp = false;
	_physicsRunning = false;
	_running = false;

	_blockersOn = false;
	_blockerRestitution = 0.0f;
	_blockers[0] = _blockers[1] = _blockers[2] = _blockers[3] = NULL;
	_gameManager = NULL;
	_elementsLocked = false;
	_highResScreen = false;
	
	_processingDeferredAdds = false;
}

World& World::GetInstance()
{
	if (s_World == NULL)
	{
		s_World = new World();
	}
	return *s_World;
}

void ReloadLevel( const String& levelName )
{
	theWorld.UnloadAll();
	theWorld.LoadLevel( levelName );
}


void UnloadAllStatic( const String& /*input*/ )
{
	theWorld.UnloadAll();
}

#if !ANGEL_MOBILE
	void windowClosed(GLFWwindow* window)
	{
		theWorld.StopGame();
	}
#endif

bool World::Initialize(unsigned int windowWidth, unsigned int windowHeight, String windowName, bool antiAliasing, bool fullScreen, bool resizable)
{
	if (_initialized)
	{
		return false;
	}
	
	_running = true;

	// Windows DLL locations
	#if defined(WIN32) && defined(ANGEL_RELEASE)
		String bitsPath = "bits";
		char currentDir[MAX_PATH];
		_getcwd(currentDir, MAX_PATH);
		String currDir(currentDir);

		StringList libs;
		#if !ANGEL_DISABLE_DEVIL
			libs.push_back("DevIL.dll");
			libs.push_back("ILU.dll");
			libs.push_back("ILUT.dll");
		#endif
		#if ANGEL_DISABLE_FMOD
			libs.push_back("OpenAL32.dll");
		#else
			libs.push_back("fmodex.dll");
		#endif

		for	(int i=0; i < libs.size(); i++)
		{
			String libstring = currDir + "\\" + bitsPath + "\\" + libs[i];
			HMODULE work = LoadLibrary(libstring.c_str());
			if (work == 0)
			{
				DWORD err = GetLastError();
				_com_error error(err);
				LPCSTR errorText = error.ErrorMessage();
				sysLog.Printf("ERROR: Couldn't load DLL (%s); %s", libs[i].c_str(), errorText);
			}
		}

		// does bits directory exist?
		DWORD dwAttrib = GetFileAttributes(bitsPath.c_str());
		if (dwAttrib != INVALID_FILE_ATTRIBUTES && dwAttrib & FILE_ATTRIBUTE_DIRECTORY)
		{
			_chdir(bitsPath.c_str());
		}
	#endif
	
	// General windowing initialization
	#if !ANGEL_MOBILE
		glfwInit();
	#endif
	
	#if defined(__APPLE__)
		// Set up paths correctly in the .app bundle
		#if !ANGEL_MOBILE
			CFBundleRef mainBundle = CFBundleGetMainBundle();
			CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
			char path[PATH_MAX];
			if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
			{
				sysLog.Log("ERROR: Problem setting up working directory! Probably nothing will work!");
			}
			CFRelease(resourcesURL);
			chdir(path);
			chdir("..");
			#if defined(ANGEL_DEBUG)
				// set paths to the local resources rather than the copied ones
				String fileName = __FILE__;
				String dirPath = fileName.substr(0, fileName.size() - String("Angel/Infrastructure/World.cpp").size());
				CFURLRef exeURL = CFBundleCopyExecutableURL(mainBundle);
				char exePath[PATH_MAX];
				if (!CFURLGetFileSystemRepresentation(exeURL, TRUE, (UInt8 *)exePath, PATH_MAX))
				{
					sysLog.Log("ERROR: Problem setting up working directory! Probably nothing will work!");
				}
				CFRelease(exeURL);
				chdir(dirPath.c_str());
				StringList pathElements = SplitString(exePath, "/");
				String exeName = pathElements[pathElements.size()-1];
				chdir(exeName.c_str());
			#endif
		#else
			CFBundleRef mainBundle = CFBundleGetMainBundle();
			CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
			char path[PATH_MAX];
			if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
			{
				std::cout << "Problem setting up working directory! Probably nothing will work!" << std::endl;
			}
			CFRelease(resourcesURL);
			chdir(path);
			chdir("Angel"); // the iPhone doesn't like having a "Resources" directory in the root of the .app bundle
		#endif
	#endif
	
	//Start scripting
	LuaScriptingModule::Prep();

	//Reset values based on preferences
	antiAliasing = thePrefs.OverrideInt("WindowSettings", "antiAliasing", antiAliasing);
	fullScreen = thePrefs.OverrideInt("WindowSettings", "fullScreen", fullScreen);
	resizable = thePrefs.OverrideInt("WindowSettings", "resizable", resizable);
	windowHeight = thePrefs.OverrideInt("WindowSettings", "height", windowHeight);
	windowWidth = thePrefs.OverrideInt("WindowSettings", "width", windowWidth);
	windowName = thePrefs.OverrideString("WindowSettings", "name", windowName);
	
	//Windowing system setup
	#if !ANGEL_MOBILE
		if (antiAliasing)
		{
			glfwWindowHint(GLFW_SAMPLES, 4); //4x looks pretty good
			_antiAliased = true;
		}
		else
		{
			_antiAliased = false;
		}
		
		GLFWmonitor* openOn = NULL; // windowed
		if (fullScreen)
		{
			openOn = glfwGetPrimaryMonitor();
		}
		if (resizable)
		{
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		}
		else
		{
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		}
		
		_mainWindow = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), openOn, NULL);
		glfwMakeContextCurrent(_mainWindow);
	
		int fbw, fbh;
		glfwGetFramebufferSize(_mainWindow, &fbw, &fbh);
		if (fbw == windowWidth * 2)
		{
			SetHighResolutionScreen(true);
		}
	
		#if defined(WIN32)
			glfwSwapInterval(0); // because double-buffering and Windows don't get along apparently
		#else
			glfwSwapInterval(1);
		#endif
		glfwSetWindowSizeCallback(_mainWindow, Camera::ResizeCallback);
		glfwSetKeyCallback(_mainWindow, keyboardInput);
		glfwSetCharCallback(_mainWindow, charInput);
		glfwSetCursorPosCallback(_mainWindow, MouseMotion);
		glfwSetMouseButtonCallback(_mainWindow, MouseButton);
		glfwSetScrollCallback(_mainWindow, MouseWheel);
		glfwSetWindowCloseCallback(_mainWindow, windowClosed);
		_prevTime = glfwGetTime();
	
		Camera::ResizeCallback(_mainWindow, fbw, fbh);
	#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		_currTime = _startTime = tv.tv_sec + (double) tv.tv_usec / 1000000.0;
	#endif
	
	//OpenGL state setup
	#if !ANGEL_MOBILE
		glClearDepth(1.0f);
		glPolygonMode(GL_FRONT, GL_FILL);
	#else
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0f, -1.0f);
	#endif
	glShadeModel(GL_FLAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearStencil(0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Get textures going
	InitializeTextureLoading();
	
	//Subscribe to camera changes
	theSwitchboard.SubscribeTo(this, "CameraChange");
	
	//initialize singletons
	#if !ANGEL_MOBILE
		theInput;
		theControllerManager.Setup();
	#endif
	theSound;
	theSpatialGraph;

	#if !ANGEL_MOBILE
		RegisterConsole(new TestConsole());
	#else
		// register fonts, since we don't have the console doing it for us on the phone
		RegisterFont("Resources/Fonts/Inconsolata.otf", 24, "Console");
		RegisterFont("Resources/Fonts/Inconsolata.otf", 18, "ConsoleSmall");
	#endif
	
	LuaScriptingModule::Initialize();

	return _initialized = true;
}

#if !ANGEL_MOBILE
	GLFWwindow* World::GetMainWindow()
	{
		return _mainWindow;
	}
#endif

std::vector<Vec3ui> World::GetVideoModes()
{
	std::vector<Vec3ui> forReturn;
	#if !ANGEL_MOBILE
		int numModes = 0;
		const GLFWvidmode* vidModes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &numModes);

		for (int i=0; i < numModes; i++)
		{
			Vec3ui avm;
			avm.X = vidModes[i].width;
			avm.Y = vidModes[i].height;
			avm.Z = vidModes[i].redBits + vidModes[i].greenBits + vidModes[i].blueBits;
			forReturn.push_back(avm);
		}
	#else
		//TODO: return the device's native resolution?
	#endif

	return forReturn;
}

void World::AdjustWindow(int windowWidth, int windowHeight, const String& windowName)
{
	#if !ANGEL_MOBILE
		glfwSetWindowTitle(_mainWindow, windowName.c_str());

		int width, height;
		glfwGetWindowSize(_mainWindow, &width, &height);
		if ( (width != windowWidth) || (height != windowHeight) )
		{
			glfwSetWindowSize(_mainWindow, windowWidth, windowHeight);
		}
	#endif
}

void World::MoveWindow(int xPosition, int yPosition)
{
	#if !ANGEL_MOBILE
		glfwSetWindowPos(_mainWindow, xPosition, yPosition);
	#endif
}


bool World::SetupPhysics(const Vector2& gravity, const Vector2& maxVertex, const Vector2& minVertex)
{
	if (_physicsSetUp)
	{
		return false;
	}

	//setup physics
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(minVertex.X, minVertex.Y);
	worldAABB.upperBound.Set(maxVertex.X, maxVertex.Y);
	b2Vec2 gravityVector(gravity.X, gravity.Y);
	_physicsWorld = new b2World(gravityVector);

	_physicsWorld->SetContactListener(this);
	
	return _physicsSetUp = _physicsRunning = true;
}


void World::Destroy()
{
	#if !ANGEL_MOBILE
		theInput.Destroy();
	#endif
	theSound.Shutdown();
	
	FinalizeTextureLoading();
	LuaScriptingModule::Finalize();
    
    theUI.Shutdown();

	if (_gameManager != NULL)
	{
		delete _gameManager;
	}
}

void World::StartGame()
{
	if (_started)
	{
		return;
	}
	_started = true;

	theSwitchboard.Broadcast(new Message("GameStart"));

	//enter main loop
	while(_running)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		TickAndRender();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		#if !ANGEL_MOBILE
			glfwSwapBuffers(_mainWindow);
			glfwPollEvents();
		#endif
	}
	
	#if !ANGEL_MOBILE
		glfwDestroyWindow(_mainWindow);
		glfwTerminate();
	#endif
}

void World::StopGame()
{
	_running = false;
}

void World::ScriptExec(const String& code)
{
	LuaScriptingModule::ExecuteInScript(code);
}

void World::LoadLevel(const String& levelName)
{
	lua_State* L = LuaScriptingModule::GetLuaState();
	lua_getglobal(L, "LoadLevel");
	lua_pushstring(L, levelName.c_str());
	if (lua_pcall(L, 1, 0, 0 ))
	{
		const char* errs = lua_tostring(L, -1);
		sysLog.Printf("ERROR: %s\n", errs);
		// error, will be in the stack trace
		lua_gc(L, LUA_GCCOLLECT, 0); // garbage collect on error
	}
}

float World::CalculateNewDT()
{
	#if ANGEL_MOBILE
		// SJML - We're now using the iOS GLKit to handle the timing of the update
		//   functions, so there's no need to compare against time of day anymore.
		//   This code is being left here (commented) in case we decide to someday
		//   port to other mobile platforms, stop using GLKit, etc. 
		// struct timeval tv;
		// gettimeofday(&tv, NULL);
		// _currTime = tv.tv_sec + (double) tv.tv_usec / 1000000.0 - _startTime;
		return _systemEstimatedDT;
	#else
		_currTime = glfwGetTime();
	#endif
	_dt = MathUtil::Clamp((_currTime - _prevTime), 0.0f, MAX_TIMESTEP);
	_prevTime = _currTime;
	return _dt;		
}

void World::Simulate(bool simRunning)
{
	float frame_dt = CalculateNewDT();

	//system updates
	#if !ANGEL_MOBILE
		theControllerManager.UpdateState();
		_console->Update( (float)frame_dt );
	#endif

	// Must be called once per frame.
	theSound.Update();

	//make sure the game manager gets updates first, if we have one
	if (_gameManager)
	{
		_gameManager->Update(frame_dt);
	}

	if (simRunning)
	{
		// Deliver any messages that have been queued from the last frame. 
		theSwitchboard.SendAllMessages();

		RunPhysics(frame_dt);
		
		//Flag that the _elements array is locked so we don't try to add any
		// new actors during the update.
		_elementsLocked = true;
			UpdateRenderables(frame_dt);
			CleanupRenderables();
		_elementsLocked = false; 

		// Now that we're done updating the list, allow any deferred Adds to be processed.
		ProcessDeferredAdds();
		ProcessDeferredLayerChanges();
		ProcessDeferredRemoves();
		
		theSwitchboard.Update(frame_dt);

		UpdateDebugItems(frame_dt);
		//if there are any system updates that still need to be run, put them here
	}
	
	//making this the last update so we can accurately lock on position for rendering
	theCamera.Update(frame_dt);
}

void World::RunPhysics(float frame_dt)
{
	if (!_physicsSetUp || !_physicsRunning) 
		return;

	_currentTouches.clear();
	
	// fixed time step
	const float physicsDT = 1.0f/60.f;
	
	float total_step = _physicsRemainderDT + frame_dt;
	while (total_step >= physicsDT)
	{
		// more iterations -> more stability, more cpu
		// tune to your liking...
		GetPhysicsWorld().Step(physicsDT, /*velocity iterations*/ 10, /* position iterations */ 10);
		total_step -= physicsDT;
	}
	_physicsRemainderDT = total_step;

	// update PhysicsActors
	for (b2Body* b = GetPhysicsWorld().GetBodyList(); b; b = b->GetNext())
	{
		b2Vec2 vec = b->GetPosition();
		PhysicsActor *physActor = reinterpret_cast<PhysicsActor*>(b->GetUserData());
		if (physActor != NULL)
		{
			physActor->_syncPosRot(vec.x, vec.y, MathUtil::ToDegrees(b->GetAngle()));
		}
	}
}

void World::SendCollisionNotifications(b2Contact* contact, bool beginning)
{
	String messageStart;
	if (beginning)
	{
		messageStart = "CollisionStartWith";
	}
	else
	{
		messageStart = "CollisionEndWith";
	}
	
	PhysicsActor* pa1 = (PhysicsActor*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysicsActor* pa2 = (PhysicsActor*)contact->GetFixtureB()->GetBody()->GetUserData();
	
	if (pa1 != NULL)
	{
		String pa1Message = messageStart + pa1->GetName();
		if (theSwitchboard.GetSubscribersTo(pa1Message).size() > 0)
		{
			if (_currentTouches[pa1].find(pa2) == _currentTouches[pa1].end())
			{
				TypedMessage<b2Contact*>* coll = new TypedMessage<b2Contact*>(pa1Message, contact, pa2);
				theSwitchboard.Broadcast(coll);
			}
			_currentTouches[pa1].insert(pa2);
		}
	}
	
	if (pa2 != NULL)
	{
		String pa2Message = messageStart + pa2->GetName();
		if (theSwitchboard.GetSubscribersTo(pa2Message).size() > 0)
		{
			if (_currentTouches[pa2].find(pa1) == _currentTouches[pa2].end())
			{
				TypedMessage<b2Contact*>* coll = new TypedMessage<b2Contact*>(pa2Message, contact, pa1);
				theSwitchboard.Broadcast(coll);
			}
			_currentTouches[pa2].insert(pa1);
		}
	}
}

void World::BeginContact(b2Contact* contact)
{
	SendCollisionNotifications(contact, true);
}

void World::EndContact(b2Contact* contact)
{
	SendCollisionNotifications(contact, false);
}

void World::TickAndRender()
{
	Tick();
	Render();
}

void World::Tick()
{
	Simulate(_simulateOn);
}

void World::Render()
{
	// Setup the camera matrix.
	theCamera.Render();

	DrawRenderables();

	// Give the GameManager a chance to draw something.
	if (_gameManager)
		_gameManager->Render();

	//Render debug information
	theSpatialGraph.Render();

	theUI.Render();

	DrawDebugItems();

	#if !ANGEL_MOBILE
		//Draw developer console
		_console->Render();
	#endif

	HandleGLErrors();
}

void World::CleanupRenderables()
{
	RenderableIterator it = theWorld.GetFirstRenderable();
	while (it != theWorld.GetLastRenderable())
	{
		if ((*it)->IsDestroyed())
		{
			Renderable* deadManWalking = *it;
			it = it.erase(it);
			delete deadManWalking;
		}
		else
		{
			++it;
		}
	}
}

void World::UpdateRenderables(float frame_dt)
{
	RenderableIterator it = theWorld.GetFirstRenderable();
	while (it != theWorld.GetLastRenderable())
	{
		(*it)->Update(frame_dt);
		++it;
	}
}

void World::DrawRenderables()
{
	RenderableIterator it = theWorld.GetFirstRenderable();
	while (it != theWorld.GetLastRenderable())
	{
		(*it)->Render();
		++it;
	}
}

const float World::GetDT()
{
	return _dt;
}

const bool World::ResumeSimulation()
{
	return _simulateOn = true;
}

const bool World::PauseSimulation()
{
	_simulateOn = false;
	return true;
}

const bool World::IsSimulationOn()
{
	return _simulateOn;
}

const bool World::PausePhysics()
{
	if (!_physicsSetUp)
	{
		sysLog.Log("WARNING: Attempted to pause physics, but physics haven't been set up yet.");
		return false;
	}
	_physicsRunning = false;
	return true;
}

const bool World::ResumePhysics()
{
	if (!_physicsSetUp)
	{
		sysLog.Log("WARNING: Attempted to resume physics, but physics haven't been set up yet.");
		return false;
	}
	_physicsRunning = true;
	return false;
}

void World::ResetWorld()
{
	theCamera.Reset();
	UnloadAll();
}

void World::SetBackgroundColor(const Color& bgColor)
{
	glClearColor(bgColor.R, bgColor.G, bgColor.B, 1.0f);
}

void World::Add(Renderable *newElement, int layer)
{
	if (newElement == NULL)
	{
		sysLog.Log("WARNING: Can't add a null element to the World.");
		return;
	}
	
	//Check to see if it's an Actor; give it a name if it doesn't have one
	Actor *a = dynamic_cast<Actor*> (newElement);
	if (a != NULL && !_processingDeferredAdds)
	{
		// Ensures that the actor has a unique, non-empty name. 
		a->SetName(a->GetName());
	}
	
	// If we're not locked, add directly to _elements.
	if (!_elementsLocked)
	{
		newElement->_layer = layer;
		_layers[layer].push_back(newElement);
	}
	// If we're locked, add to _deferredAdds and we'll add the new
	// Renderable after we're done updating all the _elements.
	else
	{
		RenderableLayerPair addMe;
		addMe._layer = layer;
		addMe._renderable = newElement;
		_deferredAdds.push_back( addMe );
	}
}

void World::Add(Renderable *newElement, const String& layer)
{
	Add(newElement, GetLayerByName(layer));
}

void World::Remove(Renderable *oldElement)
{
	if (oldElement == NULL)
	{
		return;
	}

	if (_elementsLocked)
	{
		_deferredRemoves.push_back(oldElement);
		return;
	}

	// First, make sure that it isn't deferred in the _deferredAdds list.
	std::vector<RenderableLayerPair>::iterator it = _deferredAdds.begin();
	while (it != _deferredAdds.end())
	{
		if ((*it)._renderable == oldElement)
		{
			_deferredAdds.erase(it);
			return;
		}
		++it;
	}

	// If we didn't find it in the deferred list, find/remove it from the layers.
	bool found = false;
	// Find the layer that matches the elements layer.
	RenderLayers::iterator layer = _layers.find(oldElement->_layer);
	// Found the layer (list of renderables).
	if ( layer != _layers.end() )
	{
		// Now that we have the list of elements for this layer, let's remove the requested element.
		//rb - TODO - Cache off vector.
		std::vector<Renderable*>::iterator element = (*layer).second.begin();
		for ( ; element != (*layer).second.end(); ++element )
		{
			// Found it.
			if ( (*element) == oldElement )
			{
				// Remove the element.
				element = (*layer).second.erase(element);
				found = true;
				// Nothing else to do.
				break;
			}
		}
		if (!found)
		{
			//log or error handle
		}
	}
}

void World::UpdateLayer(Renderable* element, int newLayer)
{
	if (element->_layer == newLayer)
	{
		return;
	}

    RenderableLayerPair layerChange;
    layerChange._layer = newLayer;
    layerChange._renderable = element;
    _deferredLayerChanges.push_back( layerChange );
}

void World::UpdateLayer(Renderable* element, const String& newLayerName)
{
	UpdateLayer(element, GetLayerByName(newLayerName));
}

void World::NameLayer(const String& name, int number)
{
	_layerNames[name] = number;
}

const int World::GetLayerByName(const String& name)
{
	std::map<String,int>::iterator it = _layerNames.find(name);
	if (it != _layerNames.end())
	{
		return it->second;
	}
	else
	{
		return 0;
	}
}

void World::DrawDebugLine(const Vector2& a, const Vector2& b, float time, const Color& color)
{
	DebugLine* line = new DebugLine();
	line->_points[0] = a.X;
	line->_points[1] = a.Y;
	line->_points[2] = b.X;
	line->_points[3] = a.Y;
	line->_color = color;
	line->_timeRemaining = time;
	line->_bPermanent = (time < 0);
	_debugDrawItems.push_back(line);
}

void World::WakeAllPhysics()
{
	for (b2Body* b = GetPhysicsWorld().GetBodyList(); b; b = b->GetNext())
	{
		b->SetAwake(true);
	}
}

b2World& World::GetPhysicsWorld()
{
	return *_physicsWorld;
}

void World::SetSideBlockers(bool turnOn, float restitution)
{
	if (!MathUtil::FuzzyEquals(restitution, -1.0f))
	{
		_blockerRestitution = restitution;
	}

	if (_blockers[0] != NULL)
	{
		theWorld.Remove(_blockers[0]);
		theWorld.Remove(_blockers[1]);
		theWorld.Remove(_blockers[2]);
		theWorld.Remove(_blockers[3]);
		delete _blockers[0];
		delete _blockers[1];
		delete _blockers[2];
		delete _blockers[3];
		_blockers[0] = NULL;
		_blockers[1] = NULL;
		_blockers[2] = NULL;
		_blockers[3] = NULL;
	}

	if (!turnOn)
	{
		_blockersOn = false;
		return;
	}

	_blockersOn = true;

	Vector2 botLeft = theCamera.GetWorldMinVertex();
	Vector2 topRight = theCamera.GetWorldMaxVertex();
	float worldHeight = topRight.Y - botLeft.Y;
	float worldWidth = topRight.X - botLeft.X;

	float thickness = 5.0f; //just so it's thick enough to avoid tunnelling
	Vector2 screenOrigin(((topRight.X - botLeft.X) * 0.5f) + botLeft.X,
						 ((topRight.Y - botLeft.Y) * 0.5f) + botLeft.Y);
	
	//right blocker
	_blockers[0] = new PhysicsActor();
	_blockers[0]->SetPosition(topRight.X + (thickness * 0.5f), screenOrigin.Y);
	_blockers[0]->SetColor(1, .5, .5);
	_blockers[0]->SetSize(thickness, worldHeight + 1.0f);
	_blockers[0]->SetDensity(0.0f);
	_blockers[0]->SetFriction(0.1f);
	_blockers[0]->SetRestitution(_blockerRestitution);
	_blockers[0]->InitPhysics();

	//left blocker
	_blockers[1] = new PhysicsActor();
	_blockers[1]->SetPosition(botLeft.X - (thickness * 0.5f), screenOrigin.Y);
	_blockers[1]->SetColor(1, .5, .5);
	_blockers[1]->SetSize(thickness, worldHeight + 1.0f);
	_blockers[1]->SetDensity(0.0f);
	_blockers[1]->SetFriction(0.1f);
	_blockers[1]->SetRestitution(_blockerRestitution);
	_blockers[1]->InitPhysics();
	
	//top blocker
	_blockers[2] = new PhysicsActor();
	_blockers[2]->SetPosition(screenOrigin.X, topRight.Y + (thickness * 0.5f));
	_blockers[2]->SetColor(1.0f, .5f, .5f);
	_blockers[2]->SetSize(worldWidth + 1.0f, thickness);
	_blockers[2]->SetDensity(0.0f);
	_blockers[2]->SetFriction(0.1f);
	_blockers[2]->SetRestitution(_blockerRestitution);
	_blockers[2]->InitPhysics();
	
	//bottom blocker
	_blockers[3] = new PhysicsActor();
	_blockers[3]->SetPosition(screenOrigin.X, botLeft.Y - (thickness * 0.5f));
	_blockers[3]->SetColor(1.0f, .5f, .5f);
	_blockers[3]->SetSize(worldWidth + 1.0f, thickness);
	_blockers[3]->SetDensity(0.0f);
	_blockers[3]->SetFriction(0.1f);
	_blockers[3]->SetRestitution(_blockerRestitution);
	_blockers[3]->InitPhysics();
	
	// We don't want these removed when we call ReloadLevel.
	for (int i=0; i<4; ++i)
	{
		_blockers[i]->Tag("NoDelete");
	}
	
	theWorld.Add(_blockers[0]);
	theWorld.Add(_blockers[1]);
	theWorld.Add(_blockers[2]);
	theWorld.Add(_blockers[3]);
}

void World::ReceiveMessage(Message* m)
{
	if (m->GetMessageName() == "CameraChange")
	{
		if (_blockersOn)
		{
			SetSideBlockers(true);
		}
	}
}

void World::ProcessDeferredAdds()
{
	_processingDeferredAdds = true;
	std::vector<RenderableLayerPair>::iterator it = _deferredAdds.begin();
	while(it != _deferredAdds.end())
	{
		Add( (*it)._renderable, (*it)._layer );
		++it;
	}

	_deferredAdds.clear();
	_processingDeferredAdds = false;
}

void World::ProcessDeferredLayerChanges()
{
	//TODO: use appropriate layer
	std::vector<RenderableLayerPair>::iterator it = _deferredLayerChanges.begin();
	while(it != _deferredLayerChanges.end())
	{
		Remove((*it)._renderable);
		Add( (*it)._renderable, (*it)._layer );
		++it;
	}
	_deferredLayerChanges.clear();
}

void World::ProcessDeferredRemoves()
{
	RenderList::iterator it = _deferredRemoves.begin();
	while(it != _deferredRemoves.end())
	{
		Remove(*it);
		++it;
	}
	_deferredRemoves.clear();
}

void World::UpdateDebugItems(float frame_dt)
{
	DebugDrawIterator itdd = _debugDrawItems.begin();
	while (itdd != _debugDrawItems.end())
	{
		if ( !(*itdd)->_bPermanent )
		{
			(*itdd)->_timeRemaining -= _dt;
			if ((*itdd)->_timeRemaining <= 0.f)
			{
				DebugDrawBase* pDD = (*itdd);
				_debugDrawItems.erase(itdd);
				delete pDD;
			}
			else
			{
				itdd++;
			}
		}
	}
}

void World::PurgeDebugDrawing()
{
	DebugDrawIterator itdd = _debugDrawItems.begin();
	while (itdd != _debugDrawItems.end())
	{
		DebugDrawBase* pDD = (*itdd);
		_debugDrawItems.erase(itdd);
		delete pDD;
	}
}

void World::DrawDebugItems()
{
	DebugDrawIterator itdd = _debugDrawItems.begin();
	while (itdd != _debugDrawItems.end())
	{
		(*itdd)->SetupDraw();
		(*itdd)->Draw();
		itdd++;
	}
}

// This should only be done once. (at least for now)
void World::SetGameManager(GameManager* gameManager)
{
	if ( (_gameManager != NULL) || (gameManager == NULL) )
	{
		sysLog.Log("ERROR: Can only have one game manager!");
		return;
	}

	_gameManager = gameManager;
}

void World::UnloadAll()
{
	RenderableIterator it = theWorld.GetFirstRenderable();
	while (it != GetLastRenderable())
	{
		Renderable* renderable = (*it);
		if( _gameManager != NULL && _gameManager->IsProtectedFromUnloadAll(renderable))
		{
			// Let the persistent actors know that we're unloading the level.
			Actor* actor = dynamic_cast<Actor*>(renderable);
			if (actor)
				actor->LevelUnloaded();
			++it;
			continue;
		}

		it = it.erase( it );
		renderable->Destroy();
		delete renderable;
	}

	PurgeDebugDrawing();
}

void World::RegisterConsole(Console* console)
{
	_console = console;
}

Console* World::GetConsole()
{
	return _console;
}
