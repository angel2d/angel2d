#pragma once

#include "../Infrastructure/Renderable.h"
#include "../Infrastructure/RenderableIterator.h"
#include "../Infrastructure/GameManager.h"
#include "../Physics/PhysicsUtil.h"
#include "../Messaging/Message.h"
#include "../Infrastructure/Console.h"

#include "Box2D.h"

//forward declaration
class Actor;
class PhysicsActor;
class /*Physics*/DebugDraw;

#define MAX_TIMESTEP 1.0f
#define MAX_CONTACT_POINTS 2048

#define theWorld World::GetInstance()

class World : public b2ContactListener, public MessageListener
{
public:
	static World& GetInstance();
	
	bool Initialize(unsigned int windowWidth=1024, unsigned int windowHeight=768, String windowName="Angel Engine", bool antiAliasing=false);
	bool SetupPhysics(Vector2 gravity = Vector2(0, -10), Vector2 maxVertex = Vector2(100.0f, 100.0f), Vector2 minVertex = Vector2(-100.0f, -100.0f));
	void Destroy();
	void ResetWorld();
	void StartGame();
	void StopGame();

	void ScriptExec(String code);
	void LoadLevel(String levelName);

	void UpdateRenderables(float frame_dt);
	void CleanupRenderables();
	void DrawRenderables();

	const float GetDT();
	const bool StopSimulation();
	const bool StartSimulation();
	
	void SetBackgroundColor(Color bgColor);

	static void DisplayCallback();
	static void IdleCallback();

	void Add(Renderable *newElement, int layer = 0);
	void Add(Renderable *newElement, String layer);
	void Remove(Renderable *oldElement);
	void UpdateLayer(Renderable* element, int newLayer);
	void UpdateLayer(Renderable* element, String newLayerName);
	void NameLayer(String name, int number);
	const int GetLayerByName(String name);

	// physics
	b2World &GetPhysicsWorld();
	const bool IsPhysicsSetUp() { return _physicsSetUp; }

	RenderLayers& GetLayers() { return _layers; }

	void WakeAllPhysics();
	void AddCollisionListener(CollisionListener* listener);
	void RemoveCollisionListener(CollisionListener* listener);

	//Contact listener implementations
	virtual void Add(const b2ContactPoint* point);
	virtual void Persist(const b2ContactPoint* point);
	virtual void Remove(const b2ContactPoint* point);
	virtual void Result(const b2ContactResult* point);

	void SetSideBlockers(bool turnOn, float resitution=-1.0f);

	float GetCurrentTimeSeconds() { return ( float(_currTime) ); }
	float GetTimeSinceSeconds( float lastTime ) {return GetCurrentTimeSeconds() - lastTime;}

	void SetGameManager(GameManager* gameManager);
	GameManager* GetGameManager() { return _gameManager; }

	RenderableIterator GetFirstRenderable()
	{
		RenderableIterator iter;
		return iter.begin(); 
	}
	RenderableIterator GetLastRenderable()
	{
		RenderableIterator iter;
		return iter.end();
	}

	void UnloadAll();
	
	virtual void ReceiveMessage(Message *m);

	void RegisterConsole(Console* console);
	Console* GetConsole();

protected:
	World();
	static World* s_World;
	float CalculateNewDT();
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
	std::set<CollisionListener*> _collisionListeners;

	bool _blockersOn;
	float _blockerRestitution;
	PhysicsActor* _blockers[4];

	GameManager* _gameManager;

	Console* _console;
};
