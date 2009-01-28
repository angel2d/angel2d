#pragma once

class Renderable
{
	friend class World;

public:
	Renderable() : _deleteMe(false) {}
	virtual ~Renderable() {}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	void Destroy() 
	{
		if( IsDestroyed() )
			return;
		PreDestroy(); 
		_deleteMe = true;
	}
	bool IsDestroyed() {return _deleteMe;}
	int GetLayer() {return _layer;}
protected:
	virtual void PreDestroy() {}

protected:
	bool _deleteMe;
	int _layer;
};
