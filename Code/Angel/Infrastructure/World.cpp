//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2009, Shane J. M. Liesegang
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

#include "../Infrastructure/World.h"

#include "../Infrastructure/Camera.h"
#include "../Infrastructure/Console.h"
#include "../AI/SpatialGraph.h"
#include "../Input/Input.h"
#include "../Input/MouseInput.h"
#include "../Input/Controller.h"
#include "../Input/InputManager.h"
#include "../Physics/PhysicsActor.h"
#include "../Physics/PhysicsDebugDraw.h"
#include "../Messaging/Switchboard.h"
#include "../Scripting/PythonModule.h"
#include "../Infrastructure/SoundDevice.h"

#include <algorithm>

World* World::s_World = NULL;

World::World()
{
	_simulateOn = true;
	_initialized = false;
	_started = false;
	_physicsRemainderDT = 0.0f;
	_physicsSetUp = false;
	_running = false;

	_blockersOn = false;
	_blockerRestitution = 0.0f;
	_blockers[0] = _blockers[1] = _blockers[2] = _blockers[3] = NULL;
	_physicsDebugDraw = NULL;
	_gameManager = NULL;
	_elementsLocked = false;
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

int windowClosed(void)
{
	theWorld.StopGame();

	return GL_TRUE; //returning GL_FALSE will stop the window from closing
}

bool World::Initialize(unsigned int windowWidth, unsigned int windowHeight, String windowName, bool antiAliasing)
{
	if (_initialized)
	{
		return false;
	}

	//standard initialization
	_running = true;
	glfwInit();
	if (antiAliasing)
	{
		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); //4x looks pretty good
	}
	glfwOpenWindow(windowWidth, windowHeight, 8, 8, 8, 8, 8, 1, GLFW_WINDOW);
	glfwSetWindowPos(50, 50);
	
	glfwSetWindowTitle(windowName.c_str());

	glfwSwapInterval(1); //better visual quality, set to zero for max drawing performance
	glfwSetWindowSizeCallback(Camera::ResizeCallback);
	glfwSetKeyCallback(keyboardInput);
	glfwSetCharCallback(charInput);
	glfwDisable(GLFW_KEY_REPEAT);
	glfwSetMousePosCallback(MouseMotion);
	glfwSetMouseButtonCallback(MouseButton);
	glfwSetWindowCloseCallback(windowClosed);

	_prevTime = glfwGetTime();

	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT, GL_FILL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearStencil(0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	theCamera.ResizeCallback(windowWidth, windowHeight);
	theControllerManager.Setup();

	#if defined(__APPLE__)
		// Set up paths correctly in the .app bundle
		// TODO: Centralize a declaration/initialization of paths
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
		char path[PATH_MAX];
		if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
		{
			sysLog.Log("Problem setting up working directory!");
		}
		CFRelease(resourcesURL);
		chdir(path);
		chdir("..");
	#endif
	
	//Subscribe to camera changes
	theSwitchboard.SubscribeTo(this, "CameraChange");
	
	//initialize singletons
	theInput;
	theSound;
	theSpatialGraph;
	
	RegisterConsole(new TestConsole());

	PythonScriptingModule::Initialize();
	
	return _initialized = true;
}

bool World::SetupPhysics(Vector2 gravity, Vector2 maxVertex, Vector2 minVertex)
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
	bool doSleep = true;
	_physicsWorld = new b2World(worldAABB, gravityVector, doSleep);

	_physicsWorld->SetContactListener(this);

	_physicsDebugDraw = new /*Physics*/DebugDraw();
	_physicsWorld->SetDebugDraw(_physicsDebugDraw);

	return _physicsSetUp = true;
}


void World::Destroy()
{
	theSound.Shutdown();
	theInput.Destroy();
	
	PythonScriptingModule::Finalize();

	delete _physicsDebugDraw;
	
	StringSet subs = theSwitchboard.GetSubscriptionsFor(this);
	StringSet::iterator it = subs.begin();
	while (it != subs.end())
	{
		theSwitchboard.UnsubscribeFrom(this, *it);
		++it;
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
		glfwSwapBuffers();
	}
}

void World::StopGame()
{
	_running = false;
	glfwTerminate();
}

void World::ScriptExec(String code)
{
	PythonScriptingModule::ExecuteInScript(code);
}

void World::LoadLevel(String levelName)
{
	ScriptExec("LoadLevel('" + levelName + "')");
}

float World::CalculateNewDT()
{
	_currTime = glfwGetTime();
	_dt = MathUtil::Clamp((_currTime - _prevTime), 0.0f, MAX_TIMESTEP);
	_prevTime = _currTime;
	return _dt;
}

void World::Simulate(bool simRunning)
{
	float frame_dt = CalculateNewDT();

	//system updates
	_console->Update( (float)frame_dt );
	theControllerManager.UpdateState();
	theCamera.Update(frame_dt);

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

		//Clear out the collision contact points
		_contactPointCount = 0;
		
		//rb - Flag that the _elements array is locked so we don't try to add any
		// new actors during the update.
		_elementsLocked = true;
			UpdateRenderables(frame_dt);
			CleanupRenderables();
		_elementsLocked = false; 

		// Now that we're done updating the list, allow any deferred Adds to be processed.
		ProcessDeferredAdds();
		ProcessDeferredLayerChanges();
		ProcessDeferredRemoves();

		RunPhysics(frame_dt);
		
		theSwitchboard.Update(frame_dt);
		//if there are any system updates that still need to be run, put them here
	}
}

void World::RunPhysics(float frame_dt)
{
	if (!_physicsSetUp) 
		return;

	_currentTouches.clear();
	
	// fixed time step
	const float physicsDT = 1.0f/60.f;
	
	float total_step = _physicsRemainderDT + frame_dt;
	while (total_step >= physicsDT)
	{
		// more iterations -> more stability, more cpu
		// tune to your liking...
		GetPhysicsWorld().Step(physicsDT, /*iterations*/ 10);
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

void World::bufferContactPoint(const b2ContactPoint* point)
{
	if (_contactPointCount == MAX_CONTACT_POINTS)
	{
		return;
	}

	b2ContactPoint* cp = _contactPoints + _contactPointCount;
	cp->shape1 = point->shape1;
	cp->shape2 = point->shape2;
	cp->position = point->position;
	cp->velocity = point->velocity;
	cp->normal = point->normal;
	cp->separation = point->separation;
	cp->friction = point->friction;
	cp->restitution = point->restitution;
	cp->id = point->id;
	
	PhysicsActor* pa1 = (PhysicsActor*)cp->shape1->GetBody()->GetUserData();
	PhysicsActor* pa2 = (PhysicsActor*)cp->shape2->GetBody()->GetUserData();
	if (theSwitchboard.GetSubscribersTo("CollisionWith" + pa1->GetName()).size() > 0)
	{
		if (_currentTouches[pa1].find(pa2) != _currentTouches[pa1].end())
		{
			TypedMessage<b2ContactPoint*>* coll = new TypedMessage<b2ContactPoint*>("CollisionWith" + pa1->GetName(), cp, pa2);
			theSwitchboard.Broadcast(coll);
		}
		_currentTouches[pa1].insert(pa2);
	}
	if (theSwitchboard.GetSubscribersTo("CollisionWith" + pa2->GetName()).size() > 0)
	{
		if (_currentTouches[pa2].find(pa1) != _currentTouches[pa2].end())
		{
			TypedMessage<b2ContactPoint*>* coll = new TypedMessage<b2ContactPoint*>("CollisionWith" + pa2->GetName(), cp, pa1);
			theSwitchboard.Broadcast(coll);
		}
		_currentTouches[pa2].insert(pa1);
	}

	_contactPointCount++;
}

void World::Add(const b2ContactPoint* point)
{
	//Persist is the only consistent message we care about at the moment
	bufferContactPoint(point);
}

void World::Persist(const b2ContactPoint* point)
{
	bufferContactPoint(point);
}

void World::Remove(const b2ContactPoint* /*point*/)
{
	//Persist is the only consistent message we care about at the moment
}

void World::Result(const b2ContactResult* /*result*/)
{
	//Result?
}

void World::TickAndRender()
{
	Simulate(_simulateOn);

	// Setup the camera matrix.
	theCamera.Render();

	DrawRenderables();

	// Give the GameManager a chance to draw something.
	if (_gameManager)
		_gameManager->Render();

	//Render debug information
	theSpatialGraph.Render();

	//Draw developer console
	_console->Render();
}

void World::CleanupRenderables()
{
	RenderableIterator it = theWorld.GetFirstRenderable();
	while (it != theWorld.GetLastRenderable())
	{
		if ((*it)->IsDestroyed())
		{
			//delete *it; 
			it = it.erase(it);
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

void World::DisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	theWorld.TickAndRender();

	glPopMatrix();
	glfwSwapBuffers();
}

const float World::GetDT()
{
	return _dt;
}

const bool World::StartSimulation()
{
	return _simulateOn = true;
}

const bool World::StopSimulation()
{
	return _simulateOn = false;
}

void World::ResetWorld()
{
	theCamera.Reset();
	UnloadAll();
}

void World::SetBackgroundColor(Color bgColor)
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

void World::Add(Renderable *newElement, String layer)
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
		return;

	RenderableLayerPair layerChange;
	layerChange._layer = newLayer;
	layerChange._renderable = element;
	_deferredLayerChanges.push_back( layerChange );
}

void World::UpdateLayer(Renderable* element, String newLayerName)
{
	UpdateLayer(element, GetLayerByName(newLayerName));
}

void World::NameLayer(String name, int number)
{
	_layerNames[name] = number;
}

const int World::GetLayerByName(String name)
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

void World::WakeAllPhysics()
{
	for (b2Body* b = GetPhysicsWorld().GetBodyList(); b; b = b->GetNext())
	{
		b->WakeUp();
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
	std::vector<RenderableLayerPair>::iterator it = _deferredAdds.begin();
	while(it != _deferredAdds.end())
	{
		Add( (*it)._renderable, (*it)._layer );
		++it;
	}

	_deferredAdds.clear();
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
}

void World::RegisterConsole(Console* console)
{
	_console = console;
}

Console* World::GetConsole()
{
	return _console;
}
