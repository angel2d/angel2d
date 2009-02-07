%module angel
%{
#include "../../Infrastructure/World.h"
%}

%nodefaultctor World;
class World 
{
public:
	static World &GetInstance();
		
	void ResetWorld();
	
	void StopGame();
	
	float GetCurrentTimeSeconds();
	
	void SetBackgroundColor(Color bgColor);
	
	%apply SWIGTYPE *ANGEL_DISOWN {Actor *newElement};
	void Add(Actor *newElement, int layer = 0);
	void Add(Actor *newElement, String layer);
	%clear Actor *newElement;
	
	void Remove(Renderable *oldElement);
	void UpdateLayer(Renderable* element, int newLayer);
	void UpdateLayer(Renderable* element, String newLayer);
	void NameLayer(String name, int number);
	const int GetLayerByName(String name);
	
	bool SetupPhysics(Vector2 gravity = Vector2(0, -10), Vector2 maxVertex = Vector2(100.0f, 100.0f), Vector2 minVertex = Vector2(-100.0f, -100.0f));
	const bool IsPhysicsSetUp() { return _physicsSetUp; }
	
	void RegisterConsole(Console* console);
	Console* GetConsole();
};
