%module angel
%{
#include "../../Input/Controller.h"
%}

struct ControllerInput
{
	int LeftThumbstickX;
	int LeftThumbstickY;
	int RightThumbstickX;
	int RightThumbstickY;
	int LeftTriggerValue;
	int RightTriggerValue;
	unsigned int Buttons;
};

%nodefaultctor ControllerManager;
class ControllerManager
{
public:
	static ControllerManager& GetInstance();
	
	Controller& GetController(int controllerIndex=0);
};

%nodefaultctor Controller;
class Controller  
{
public:
	const ControllerInput GetState();
	
	const Vector2 GetLeftThumbVec2();
	const Vector2 GetRightThumbVec2();
	const Vec2i GetLeftThumbstick();
	const Vec2i GetRightThumbstick();
	const int GetRightTrigger();
	const int GetLeftTrigger();
	const bool IsButtonDown(int buttonMask);
	const bool IsAButtonDown();
	const bool IsBButtonDown();
	const bool IsXButtonDown();
	const bool IsYButtonDown();
	const bool IsLeftThumbstickButtonDown();
	const bool IsRightThumbstickButtonDown();
	const bool IsStartButtonDown();
	const bool IsBackButtonDown();
	const bool IsLeftBumperDown();
	const bool IsRightBumperDown();
	const bool IsLeftTriggerPressed();
	const bool IsRightTriggerPressed();
	void SetLeftVibrationRaw(unsigned int vibration); 
	void SetRightVibrationRaw(unsigned int vibration); 
	void SetLeftVibration(unsigned int vibration); 
	void SetRightVibration(unsigned int vibration); 
	const unsigned int GetLeftVibration(); 
	const unsigned int GetRightVibration();

	const bool IsConnected() { return _connected; }
	const int GetControllerID() { return _controllerID; }
};
