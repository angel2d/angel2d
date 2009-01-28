#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/VecStructs.h"
#include "../Infrastructure/Vector2.h"

#if defined(WIN32)
	#include <XInput.h>
	#pragma comment(lib, "XInput.lib")
#elif defined(__APPLE__)
	#include <Carbon/Carbon.h>
	#include <IOKit/HID/IOHIDKeys.h>
	#include "HID_Utilities_External.h"
#endif

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

class Controller;

#define MAX_CONTROLLERS 2

class ControllerManager
{
public:
	static ControllerManager& GetInstance();
	ControllerManager::ControllerManager();
	
	Controller& GetController(int controllerIndex=0)
	{
		if ( (controllerIndex >= MAX_CONTROLLERS) || (controllerIndex < 0) )
		{
			std::cout << "ERROR: Bad controller index." << std::endl;
		}
		return *_controllers[controllerIndex];
	}
	
	void Setup();
	void UpdateState();
	
	~ControllerManager();
	
protected:
	static ControllerManager *s_ControllerManager;
	
private:
	Controller* _controllers[MAX_CONTROLLERS];
};

#define theControllerManager ControllerManager::GetInstance()
#define theController ControllerManager::GetInstance().GetController()

class Controller  
{
public:
	friend class ControllerManager;
	
	static Controller& GetInstance();
	
	void Setup();
	void UpdateState();
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
	
	void SetLeftVibrationRaw(unsigned int vibration); //lower frequencies, 0-65535
	void SetRightVibrationRaw(unsigned int vibration); //higher frequencies, 0-65535
	void SetLeftVibration(unsigned int vibration); //lower frequencies, 0-255
	void SetRightVibration(unsigned int vibration); //higher frequencies, 0255
	const unsigned int GetLeftVibration(); 
	const unsigned int GetRightVibration();
	
	const bool IsConnected() { return _connected; }
	
	int _controllerID;
	
protected:
	Controller();
	static Controller *s_Controller;
	
private:
	bool _connected;
	ControllerInput _currentControllerInput;
	
	unsigned int _currentLeftVibration;
	unsigned int _currentRightVibration;
	
#if defined(WIN32)
	DWORD _dwResult;
	XINPUT_STATE _currentControllerRawState;
#elif defined(__APPLE__)
	pRecDevice _device;
	hashmap_ns::hash_map<unsigned int, pRecElement> _elements;
	const long _getValueForCookie(unsigned int cookie)
	{
		return HIDGetElementValue(_device, _elements[cookie]);
	}
#endif
};
