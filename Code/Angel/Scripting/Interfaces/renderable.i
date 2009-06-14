%module angel
%{
#include "../../Infrastructure/Renderable.h"
%}

%nodefaultctor Renderable;
class Renderable
{
public:
	void Destroy();
	bool IsDestroyed();
	int GetLayer();
	
	void Update(float dt);
	void Render();
};
