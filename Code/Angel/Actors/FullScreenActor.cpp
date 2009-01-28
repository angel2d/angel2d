#include "../Actors/FullScreenActor.h"

#include "../Infrastructure/Camera.h"
#include "../Messaging/Switchboard.h"

FullScreenActor::FullScreenActor()
{
	_locked = false;
	theSwitchboard.SubscribeTo(this, "CameraChange");
	_resize();
}

void FullScreenActor::SetLock(bool locked)
{
	_locked = locked;
	if (!_locked)
	{
		_resize();
	}
}

const bool FullScreenActor::IsLocked()
{
	return _locked;
}

void FullScreenActor::ReceiveMessage(Message *message)
{
	if (!_locked && message->GetMessageType() == "CameraChange")
	{
		_resize();
	}
}

void FullScreenActor::_resize()
{
	Vector2 maxVert = theCamera.GetWorldMaxVertex();
	Vector2 minVert = theCamera.GetWorldMinVertex();
	Vector2 dimensions = maxVert - minVert;
	
	SetPosition(Vector2::Zero + theCamera.GetPosition());
	SetSize(dimensions.X, dimensions.Y);	
}