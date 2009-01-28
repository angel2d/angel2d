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
};
