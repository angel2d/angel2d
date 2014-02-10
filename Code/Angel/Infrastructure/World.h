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

#pragma once

#include "../Infrastructure/Renderable.h"
#include "../Infrastructure/RenderableIterator.h"
#include "../Infrastructure/GameManager.h"
#include "../Infrastructure/DebugDraw.h"
#include "../Messaging/Message.h"

#include <Box2D/Box2D.h>

//forward declarations
class Actor;
class PhysicsActor;
class Console;

#define MAX_TIMESTEP 1.0f
#define MAX_CONTACT_POINTS 2048

//singleton shortcut
#define theWorld World::GetInstance()

///The central class that manages all aspects of the simulation
/** 
 * The World is the class that keeps track of all Renderables, handles the
 *  Update/Render loop, processes events, etc. 
 * 
 * Like the Camera, it uses the singleton pattern; you can't actually declare 
 *  a new instance of a TagCollection. To access the World, use "theWorld" to 
 *  retrieve the singleton object. "theWorld" is defined in both C++ and 
 *  Lua. 
 * 
 * If you're not familiar with the singleton pattern, this paper is a good 
 *  starting point. (Don't be afraid that it's written by Microsoft.)
 * 
 * http://msdn.microsoft.com/en-us/library/ms954629.aspx
 */
class World : public b2ContactListener, public MessageListener
{
public:
	/**
	 * Used to access the singleton instance of this class. As a shortcut, 
	 *  you can just use "theWorld". 
	 * 
	 * @return The singleton
	 */
	static World& GetInstance();
	
	/**
	 * The initial call to get Angel up and running. Opens the window, sets
	 *  up our display, and begins the Update/Render loop. 
	 * 
	 * The values passed in here will be overridden by any values set in
	 *  the Preferences, with the WindowSettings table. (See the Preferences
	 *  documentation and the example preferences file in IntroGame for more
	 *  information.)
	 * 
	 * @param windowWidth The desired width (in pixels) of the window
	 * @param windowHeight The desired height (in pixels) of the window
	 * @param windowName The string that should appear in the window's title bar
	 * @param antiAliasing Whether or not the window should be initialized with
	 *   anti-aliasing
	 * @param fullScreen Whether the game should be started in fullscreen mode. 
	 *   Note that the resolution is determined from windowWidth and windowHeight,
	 *   and that Angel will attempt to change the system's video mode 
	 *   accordingly. We don't do any detection of what modes are valid, so
	 *   make sure you're feeding this a legitimate resolution.
	 * @param resizable Whether the user will be allowed to resize the game window
	 8   using the operating system's normal resize widgets.
	 * @return Returns true if initialization worked (i.e. if world was not
	 *   already initialized)
	 */
	bool Initialize(unsigned int windowWidth=1024, unsigned int windowHeight=768, String windowName="Angel Engine", bool antiAliasing=false, bool fullScreen=false, bool resizable=false);
	
	/**
	 * Queries the video drivers to get a list of supported video modes for
	 *  fullscreen gameplay. You'll likely want to get a list of valid modes to give
	 *  the player a choice of resolutions. (You can then save the selected mode
	 *  as part of the preferences.)
	 *
	 * @return A list of video modes bundled, each bundled as a Vec3ui. The X
	 *   value is the width; the Y value is the height, and the Z-value
	 *   represents the color depth. 
	 */
	std::vector<Vec3ui> GetVideoModes();

	/**
	 * Changes the dimension of the window while the game is running. Note that the
	 *  behavior is undefined if this method is called while in fullscreen mode.
	 * 
	 * @param windowWidth The new desired width
	 * @param windowHeight The new desired height
	 * @param windowName The new string to go in the window's title bar
	 */
	void AdjustWindow(int windowWidth, int windowHeight, const String& windowName);

	/**
	 * Moves the window around on screen, relative to the system origin. Note that
	 *  behavior is undefined if this method is called while in fullscreen mode.
	 * 
	 * @param xPosition The new x position offset from the system origin
	 * @param yPosition The new y position offset from the system origin
	 */
	void MoveWindow(int xPosition, int yPosition);
	
	#if !ANGEL_MOBILE
		/**
		 * Returns a handle for the main window. For most games, you'll only have one
		 *  window, so this seems a little redundant, but there are several GLFW
		 *  functions that need to operate on a specific window, so this gives you a
		 *  hook to that.
		 *
		 * @return a handle for the main game window
		 */
		GLFWwindow* GetMainWindow();
	#endif

	/**
	 * Intialize physics. If you're not using our built-in physics, you don't
	 *  have to call this function, but no PhysicsActors will do anything 
	 *  until you do. 
	 * 
	 * @param gravity The gravity vector that will be applied to all PhysicsActors
	 * @param maxVertex The maximum vertex at which PhysicsActors will simulate. 
	 *   Any PhysicsActors that go beyond this point will get "stuck" in the
	 *   bounding box. 
	 * @param minVertex The minimum vertex at which PhysicsActors will simulate. 
	 *   Any PhysicsActors that go beyond this point will get "stuck" in the
	 *   bounding box.
	 * @return True is successfully setup, false if physics were already initialized
	 */
	bool SetupPhysics(const Vector2& gravity = Vector2(0, -10), const Vector2& maxVertex = Vector2(100.0f, 100.0f), const Vector2& minVertex = Vector2(-100.0f, -100.0f));
	
	/**
	 * Called when the game shuts down, does all cleanup. 
	 */
	void Destroy();
	
	/**
	 * Removes all Actors from the world (pending a check to the 
	 *  GameManager::IsProtectedFromUnloadAll function) and resets the camera
	 *  to its default positioning. 
	 */
	void ResetWorld();
	
	/**
	 * Called once, after your world setup is done and you're ready to kick
	 *  things into motion. 
	 */
	void StartGame();
	
	/**
	 * Ends the game, has everything prepare for shutdown. Should only be
	 *  called once, when you're ready to finish. 
	 */
	void StopGame();
	
	/**
	 * Execute a string of Lua code. 
	 * 
	 * @param code The string to execute
	 */
	void ScriptExec(const String& code);
	
	/**
	 * Loads a level from Config/Level/[levelName].lua. 
	 * 
	 * Each section of a level file specifies an Actor to be added to the world. 
	 *  The name of the section will be the name of the Actor, and the values
	 *  in each section will be applied in addition to (or overriding) the 
	 *  ones specified in the archetype. Check the Actor::Create function for
	 *  more information on how archetypes are specified. 
	 * 
	 * @see Actor::Create
	 * @param levelName 
	 */
	void LoadLevel(const String& levelName);
	
	/**
	 * Get the amount of time that elapsed between the start of the last frame
	 *  and the start of the current frame. Useful for rate controlling any
	 *  changes on your actors. 
	 * 
	 * @return The amount of time elapsed in seconds
	 */
	const float GetDT();
	
	/**
	 * Toggles the simulation off. Several classes and objects will still
	 *  receive updates (GameManager, Console, Camera, etc.), but all standard
	 *  Actors will not receive Update calls until you call World::StartSimulation. 
	 * 
	 * @return Whether the simulation was successfully paused
	 */
	const bool PauseSimulation();
	
	/**
	 * Toggles the simulation back on. 
	 * 
	 * @see World::PauseSimulation
	 * @return Whether the simulation was successfully resumed
	 */
	const bool ResumeSimulation();
	
	/**
	 * Toggles the physics simulation off.
	 * 
	 * @return Whether the physics simulation was successfully paused
	 */
	const bool PausePhysics();
	
	/**
	 * Toggles the physics simulation back on. 
	 * 
	 * @see World::PausePhysics
	 * @return Whether the physics simulation was successfully resumed
	 */
	const bool ResumePhysics();

	/**
	 * Sets the world's background color. White by default. 
	 * 
	 * @param bgColor The new background color
	 */
	void SetBackgroundColor(const Color& bgColor);
	
	/**
	 * Add a Renderable to the World so it will start receiving Update and
	 *  Render calls every frame. 
	 * 
	 * @param *newElement The new object to insert into the world
	 * @param layer The layer at which to insert it
	 */
	void Add(Renderable *newElement, int layer = 0);
	
	/**
	 * Add a Renderable to the World with a named layer. 
	 * 
	 * @param *newElement The new object to insert into the world
	 * @param layer The name of the layer at which to insert it
	 */
	void Add(Renderable *newElement, const String& layer);
	
	/**
	 * Remove a Renderable from the World. Does not deallocate any memory; 
	 *  you're responsible for doing that yourself. 
	 * 
	 * @param *oldElement The element to remove
	 */
	void Remove(Renderable *oldElement);
	
	/**
	 * Move a Renderable to a new layer
	 * 
	 * @param element The renderable to move
	 * @param newLayer Its new home
	 */
	void UpdateLayer(Renderable* element, int newLayer);
	
	/**
	 * Move a Renderable to a new layer by name
	 * 
	 * @param element The renderable to move
	 * @param newLayerName The name of its new home
	 */
	void UpdateLayer(Renderable* element, const String& newLayerName);
	
	/**
	 * Lets you name layers for easier reference later. This name can be
	 *  used by the World::Add and World::UpdateLayer functions. 
	 * 
	 * @param name The string to assign as a layer name
	 * @param number The number to which this name should refer
	 */
	void NameLayer(const String& name, int number);
	
	/**
	 * Retrieve the layer number associated with a name. 
	 * 
	 * @param name The name to look up
	 * @return The layer number. Will return 0 if the name has not been
	 *   registered; note that 0 is still a valid layer. 
	 */
	const int GetLayerByName(const String& name);
	
	/**
	 * Get the set of layers and their associated Renderables
	 * 
	 * @return The world's layers
	 */
	RenderLayers& GetLayers() { return _layers; }
	
	/**
	 * Register a new Console with the World. Only one Console can be
	 *  activated at at time. 
	 * 
	 * @param console The new Console that should accept input
	 */
	void RegisterConsole(Console* console);
	
	/**
	 * Get a pointer to the current registered console
	 * 
	 * @return The current console
	 */
	Console* GetConsole();
	
	/**
	 * Get a reference to the Box2D world that's handling all the Physics
	 * 
	 * @return 
	 */
	b2World &GetPhysicsWorld();
	
	/**
	 * Lets you know if physics have been appropriately initialized with the
	 *  World::SetupPhysics function. 
	 * 
	 * @return True if physics has been initialized
	 */
	const bool IsPhysicsSetUp() { return _physicsSetUp; }
	
	/**
	 * Wakes up all physics bodies in the world. See the Box2D documentation
	 *  for more information on what this means. 
	 */
	void WakeAllPhysics();
	
	/**
	 * Implementation of the b2ContactListener::BeginContact function. We 
	 *  use it to manage collision notifications. 
	 */
	virtual void BeginContact(b2Contact* contact);
	
	/**
	 * Implementation of the b2ContactListener::EndContact function. We 
	 *  use it to manage collision notifications. 
	 */
	virtual void EndContact(b2Contact* contact);
		
	/**
	 * When working with physics, oftentimes you want to keep objects from 
	 *  going beyond the edge of the visible screen. This function sets up 
	 *  objects to block the edges so they can't. 
	 * 
	 * @param turnOn If true, side blockers are enabled, if false, they're 
	 *   disabled
	 * @param restitution The restitution of the blockers (how bouncy they are)
	 */
	void SetSideBlockers(bool turnOn, float restitution=-1.0f);
	
	/**
	 * Find out how much time has elapsed since the game started
	 * 
	 * @return Total elapsed time in seconds
	 */
	float GetCurrentTimeSeconds() { return ( float(_currTime) ); }
	
	/**
	 * Find out how much time has elapsed since a specific timestamp. 
	 * 
	 * @param lastTime The time index you want to calculate the difference from
	 * @return How much time has elapsed since lastTime
	 */
	float GetTimeSinceSeconds( float lastTime ) {return GetCurrentTimeSeconds() - lastTime;}
	
	/**
	* Draw a line for a specified length of time.
	* 
	* @param a The starting point of the line
	* @param b The ending point of the line
	* @param time The length of time the line will be drawn (less than 0 will draw it permanently)
	* @param color The color of the line
	*/
	void DrawDebugLine( const Vector2& a, const Vector2& b, float time = 5.f, const Color& color = Color(1.f, 0.f, 0.f) );

	/**
	* Purge all debug drawing.
	* 
	*/
	void PurgeDebugDrawing();

	/**
	* Check whether the simulation is running.  See also StartSimulation() and StopSimulation().
	* 
	* @return Whether the simulation is running
	*/
	const bool IsSimulationOn();

	/**
	 * Set a GameManager object to be your high-level coordinator. 
	 * 
	 * @param gameManager The new manager
	 */
	void SetGameManager(GameManager* gameManager);
	
	/**
	 * Get the current registered manager
	 * 
	 * @return The GameManager currently overseeing the game
	 */
	GameManager* GetGameManager() { return _gameManager; }
	
	/**
	 * Get an iterator to start cycling through all the Renderables that 
	 *  have been added to the World. 
	 * 
	 * @return An iterator pointing to the first Renderable
	 */
	RenderableIterator GetFirstRenderable()
	{
		RenderableIterator iter;
		return iter.begin(); 
	}
	
	/**
	 * Get an iterator pointing to the last Renderable in the World.
	 * 
	 * @return An iterator at the end of the list
	 */
	RenderableIterator GetLastRenderable()
	{
		RenderableIterator iter;
		return iter.end();
	}
	
	/**
	 * Removes all Actors from the world (pending a check to the 
	 *  GameManager::IsProtectedFromUnloadAll function).
	 */
	void UnloadAll();
	
	/**
	 * Implementation of the MessageListener::ReceiveMessage function. Used
	 *  to get notifications of camera changes so the side blockers can be
	 *  updated if they're enabled. 
	 * 
	 * @param m The message being delivered. 
	 */
	virtual void ReceiveMessage(Message *m);
	
	/**
	 * Lets you know whether the current rendering device is high resolution
	 *  (like the iPhone 4's "Retina Display").
	 *
	 * @return Whether or not the screen is high resolution.
	 */
	const bool IsHighResScreen() { return _highResScreen; }
	
	/**
	 * INTERNAL: This function is called by the OS setup functions to let Angel
	 *  know about the screen resolution. If you call in manually, expect
	 *  weirdness. 
	 *
	 * @param highRes Whether or not we should be set up for high resolution rendering.
	 */
	void SetHighResolutionScreen(bool highRes) { _highResScreen = highRes; }

	/**
	 * Lets you know whether the current display is antialiased.
	 *
	 * @return Whether or not we're running with antialiasing (multisampling). 
	 */
	const bool IsAntiAliased() { return _antiAliased; }
	
	/**
	 * INTERNAL: This function is used by various OS systems to run the Angel
	 *  update loop. If you call it manually, expect weirdness. 
	 */
	void TickAndRender();

	/**
	 * INTERNAL: This function is used by various OS systems to run the Angel
	 *  update loop. If you call it manually, expect weirdness. 
	 */
	void Tick();

	/**
	 * INTERNAL: This function is used by various OS systems to run the Angel
	 *  update loop. If you call it manually, expect weirdness. 
	 */
	void Render();

	/**
	 * INTERNAL: This function is used by various OS systems to run the Angel
	 *  update loop. If you call it manually, expect weirdness. 
	 */	
	void SetDT(float dt)
	{
		#if ANGEL_MOBILE
			_systemEstimatedDT = dt;
		#endif
	}
	
protected:
	World();
	static World* s_World;
	float CalculateNewDT();
	void UpdateRenderables(float frame_dt);
	void CleanupRenderables();
	void DrawRenderables();
	void Simulate(bool simRunning);
	void ProcessDeferredAdds();
	void ProcessDeferredLayerChanges();
	void ProcessDeferredRemoves();
	void RunPhysics(float frame_dt);
	void UpdateDebugItems(float frame_dt);
	void DrawDebugItems();

private:
	struct RenderableLayerPair
	{
		Renderable* _renderable;
		int			_layer;
	};
	bool _running;
	#if ANGEL_MOBILE
		float _startTime;
		float _systemEstimatedDT;
	#else
		GLFWwindow* _mainWindow;
	#endif
	bool _highResScreen;
	bool _antiAliased;
	float _prevTime;
	float _currTime;
	float _dt;
	float _physicsRemainderDT;

	bool _simulateOn;
	bool _initialized;
	bool _started;


	RenderLayers _layers;

	bool _processingDeferredAdds;
	std::vector<RenderableLayerPair> _deferredAdds;	
	std::vector<RenderableLayerPair> _deferredLayerChanges;
	std::vector<Renderable*> _deferredRemoves;
	std::map<String, int> _layerNames;

	bool _elementsLocked;

	b2World *_physicsWorld;
	bool _physicsSetUp;
	bool _physicsRunning;
	
	void SendCollisionNotifications(b2Contact* cp, bool beginning);
	std::map< PhysicsActor*, ActorSet > _currentTouches;

	bool _blockersOn;
	float _blockerRestitution;
	PhysicsActor* _blockers[4];

	std::vector< DebugDrawBase* > _debugDrawItems;

	GameManager* _gameManager;

	Console* _console;
};
