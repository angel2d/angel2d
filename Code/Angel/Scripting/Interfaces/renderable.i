%module angel
%{
#include "../../Infrastructure/Renderable.h"
%}

%nodefaultctor Renderable;
class Renderable
{
public:
	virtual ~Renderable();

	void Destroy();
	bool IsDestroyed();
	int GetLayer();
};
