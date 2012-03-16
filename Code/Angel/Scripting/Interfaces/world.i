%module angel
%{
#include "../../Infrastructure/World.h"
%}

%nodefaultctor World;
class World 
{
public:
	static World &GetInstance();
	
	std::vector<Vec3ui> GetVideoModes();

	void AdjustWindow(int windowWidth, int windowHeight, const String& windowName);
	void MoveWindow(int xPosition, int yPosition);

	void ResetWorld();
	
	void StopGame();
	
	float GetCurrentTimeSeconds();
	
	void SetBackgroundColor(Color bgColor);
	
	%apply SWIGTYPE *DISOWN {Actor *newElement};
	void Add(Actor *newElement, int layer = 0);
	void Add(Actor *newElement, String layer);
	%clear Actor *newElement;
	
	void Remove(Renderable *oldElement);
	void UpdateLayer(Renderable* element, int newLayer);
	void UpdateLayer(Renderable* element, String newLayer);
	void NameLayer(String name, int number);
	const int GetLayerByName(String name);
	
	void DrawDebugLine( Vector2 a, Vector2 b, float time = 5.f, Color color = Color(1.f, 0.f, 0.f) );
	void PurgeDebugDrawing();
	const bool IsSimulationOn();
	
	bool SetupPhysics(Vector2 gravity = Vector2(0, -10), Vector2 maxVertex = Vector2(100.0f, 100.0f), Vector2 minVertex = Vector2(-100.0f, -100.0f));
	const bool IsPhysicsSetUp() { return _physicsSetUp; }
	
	void RegisterConsole(Console* console);
	Console* GetConsole();
};
