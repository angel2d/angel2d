#pragma once

#include "../Infrastructure/Renderable.h"
#include "../Infrastructure/RenderableIterator.h"
#include "../Infrastructure/GameManager.h"
#include "../Messaging/Message.h"

#include "Box2D.h"

//forward declarations
class Actor;
class PhysicsActor;
class /*Physics*/DebugDraw;
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
 *  Python. 
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
	 * @param windowWidth The desired width (in pixels) of the window
	 * @param windowHeight The desired height (in pixels) of the window
	 * @param windowName The string that should appear in the window's title bar
	 * @param antiAliasing Whether or not the window should be initialized with
	 *   anti-aliasing
	 * @return Returns true if initialization worked (i.e. if world was not
	 *   already initialized)
	 */
	bool Initialize(unsigned int windowWidth=1024, unsigned int windowHeight=768, String windowName="Angel Engine", bool antiAliasing=false);
	
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
	bool SetupPhysics(Vector2 gravity = Vector2(0, -10), Vector2 maxVertex = Vector2(100.0f, 100.0f), Vector2 minVertex = Vector2(-100.0f, -100.0f));
	
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
	 * Execute a string of Python code. 
	 * 
	 * @param code The string to execute
	 */
	void ScriptExec(String code);
	
	/**
	 * Loads a level from Config/Level/[levelName].ini. 
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
	void LoadLevel(String levelName);
	
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
	 * @return Whether the simulation was successfully stopped
	 */
	const bool StopSimulation();
	
	/**
	 * Toggles the simulation back on. 
	 * 
	 * @see World::StopSimulation
	 * @return Whether the simulation was successfully restarted
	 */
	const bool StartSimulation();
	
	/**
	 * Sets the world's background color. White by default. 
	 * 
	 * @param bgColor The new background color
	 */
	void SetBackgroundColor(Color bgColor);
	
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
	void Add(Renderable *newElement, String layer);
	
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
	void UpdateLayer(Renderable* element, String newLayerName);
	
	/**
	 * Lets you name layers for easier reference later. This name can be
	 *  used by the World::Add and World::UpdateLayer functions. 
	 * 
	 * @param name The string to assign as a layer name
	 * @param number The number to which this name should refer
	 */
	void NameLayer(String name, int number);
	
	/**
	 * Retrieve the layer number associated with a name. 
	 * 
	 * @param name The name to look up
	 * @return The layer number. Will return 0 if the name has not been
	 *   registered; note that 0 is still a valid layer. 
	 */
	const int GetLayerByName(String name);
	
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
	 * Implementation of the b2ContactListener::Add function. We use it to
	 *  manage collision notifications. 
	 */
	virtual void Add(const b2ContactPoint* point);
	/**
	 * Implementation of the b2ContactListener::Persist function. We use it to
	 *  manage collision notifications. 
	 */
	virtual void Persist(const b2ContactPoint* point);
	
	/**
	 * Implementation of the b2ContactListener::Remove function. We use it to
	 *  manage collision notifications. 
	 */
	virtual void Remove(const b2ContactPoint* point);
	
	/**
	 * Implementation of the b2ContactListener::Result function. We use it to
	 *  manage collision notifications. 
	 */
	virtual void Result(const b2ContactResult* point);
	
	/**
	 * When working with physics, oftentimes you want to keep objects from 
	 *  going beyond the edge of the visible screen. This function sets up 
	 *  objects to block the edges so they can't. 
	 * 
	 * @param turnOn If true, side blockers are enabled, if false, they're 
	 *   disabled
	 * @param resitution The restitution of the blockers (how bouncy they are)
	 */
	void SetSideBlockers(bool turnOn, float resitution=-1.0f);
	
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
	 * @param *m 
	 */
	virtual void ReceiveMessage(Message *m);
	
	/**
	 * The callback that the windowing toolkit (GLFW) will use to drive the
	 *  rendering loop. 
	 */
	static void DisplayCallback();
	
protected:
	World();
	static World* s_World;
	float CalculateNewDT();
	void UpdateRenderables(float frame_dt);
	void CleanupRenderables();
	void DrawRenderables();
	void Simulate(bool simRunning);
	void TickAndRender();
	void ProcessDeferredAdds();
	void ProcessDeferredLayerChanges();
	void ProcessDeferredRemoves();
	void RunPhysics(float frame_dt);

private:
	struct RenderableLayerPair
	{
		Renderable* _renderable;
		int			_layer;
	};
	bool _running;
	float _prevTime;
	float _currTime;
	float _dt;
	float _physicsRemainderDT;

	bool _simulateOn;
	bool _initialized;
	bool _started;


	RenderLayers _layers;

	std::vector<RenderableLayerPair> _deferredAdds;	
	std::vector<RenderableLayerPair> _deferredLayerChanges;
	std::vector<Renderable*> _deferredRemoves;
	std::map<String, int> _layerNames;

	bool _elementsLocked;

	b2World *_physicsWorld;
	bool _physicsSetUp;

	/*Physics*/DebugDraw *_physicsDebugDraw;

	void bufferContactPoint(const b2ContactPoint* cp);
	b2ContactPoint _contactPoints[MAX_CONTACT_POINTS];
	int _contactPointCount;
	std::map< PhysicsActor*, ActorSet > _currentTouches;

	bool _blockersOn;
	float _blockerRestitution;
	PhysicsActor* _blockers[4];

	GameManager* _gameManager;

	Console* _console;
};
