//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../Input/Controller.h"

#include "../Input/InputManager.h"
#include "../Util/MathUtil.h"



 // Here are the definitions from XInput.h
#ifndef XINPUT_GAMEPAD_DPAD_UP
	#define XINPUT_GAMEPAD_DPAD_UP          0x00000001
	#define XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
	#define XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
	#define XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
	#define XINPUT_GAMEPAD_START            0x00000010
	#define XINPUT_GAMEPAD_BACK             0x00000020
	#define XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
	#define XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
	#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
	#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
	#define XINPUT_GAMEPAD_A                0x1000
	#define XINPUT_GAMEPAD_B                0x2000
	#define XINPUT_GAMEPAD_X                0x4000
	#define XINPUT_GAMEPAD_Y                0x8000
	#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD	30
	#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE	7849
	#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#endif


/*
 // The definitions sussed out from the Apple HID Utilities 
 Generic Desktop X - Left X			- 0x1b
 Generic Dekstop Y - Left Y			- 0x1c
 Generic Desktop Rx - Right X		- 0x1d
 Generic Desktop Ry - Right Y		- 0x1e
 Button #0x000C - Dpad Up			- 0x0a
 Button #0x000D - Dpad Down			- 0x0b
 Button #0x000E - Dpad Left			- 0x0c
 Button #0x000F - Dpad Right		- 0x0d
 Button #0x0009 - Start				- 0x0e
 Button #0x000A - Back				- 0x0f
 Button #0x0007 - L3				- 0x10
 Button #0x0008 - R3				- 0x11
 Button #0x0005 - Left Bumper		- 0x12
 Button #0x0006 - Right Bumper		- 0x13
 Button #0x000B - Xbox Button		- 0x14
 Button #0x0001 - A Button			- 0x15
 Button #0x0002 - B Button			- 0x16
 Button #0x0003 - X Button			- 0x17
 Button #0x0004 - Y Button			- 0x18
 Generic Desktop Z - Left Trigger	- 0x19
 Generic Desktop Rz - Right Trigger - 0x1a
*/


ControllerManager* ControllerManager::s_ControllerManager = NULL;

ControllerManager& ControllerManager::GetInstance()
{
	if (s_ControllerManager == NULL)
	{
		s_ControllerManager = new ControllerManager();
	}
	return *s_ControllerManager;
}

ControllerManager::ControllerManager()
{	
	_controllers[0] = new Controller();
	_controllers[0]->_controllerID = 0;
	
	_controllers[1] = new Controller();
	_controllers[1]->_controllerID = 1;
}

ControllerManager::~ControllerManager()
{
	#if defined(__APPLE__)
		HIDReleaseAllDeviceQueues();
		HIDReleaseDeviceList();
	#endif
}

void ControllerManager::Setup()
{
	_controllers[0]->Setup();
	_controllers[1]->Setup();
}

void ControllerManager::UpdateState()
{	
	_controllers[0]->UpdateState();
	_controllers[1]->UpdateState();
}

Controller* Controller::s_Controller = NULL;

Controller::Controller()
{
	_connected = false;
	_currentLeftVibration = 0;
	_currentRightVibration = 0;
	
	#if defined(__APPLE__)
		_device = NULL;
	#endif
}

void Controller::Setup()
{
	#if defined(WIN32)
		ZeroMemory( &_currentControllerRawState, sizeof(XINPUT_STATE));
		
		_dwResult = XInputGetState(_controllerID, &_currentControllerRawState);
		
		if (_dwResult == ERROR_SUCCESS)
		{
			sysLog.Printf("Controller %d connected!", _controllerID+1);
			_connected = true;
		}
		else
		{
			sysLog.Printf("Controller %d not present...", _controllerID+1);
			ZeroMemory( &_currentControllerRawState, sizeof(XINPUT_STATE));
			_currentControllerInput.LeftThumbstickX = 
			_currentControllerInput.LeftThumbstickY =
			_currentControllerInput.RightThumbstickX =
			_currentControllerInput.RightThumbstickY = 
			_currentControllerInput.LeftTriggerValue = 
			_currentControllerInput.RightTriggerValue = 
			_currentControllerInput.Buttons = 0;
			_connected = false;
		}
	
	#elif defined(__APPLE__)
		unsigned long usagePage = 0;
		unsigned long usage = 0;
		if (!HIDHaveDeviceList())
		{	
			HIDBuildDeviceList(usagePage, usage);
		}
		
		_device = HIDGetFirstDevice();
		while (_device != NULL)
		{
			//is this device already taken by another controller? 
			bool breakIt = false;
			for (int i=0; i < MAX_CONTROLLERS; i++)
			{
				Controller* check = &theControllerManager.GetController(i);
				if ((check != this) && (check->_device == _device))
				{
					_device = HIDGetNextDevice(_device);
					if (_device == NULL)
					{
						breakIt = true;
					}
				}
			}
			if (breakIt)
			{
				break;
			}
			
			std::string manufacturer = _device->manufacturer;
			std::string product = _device->product;
			if (manufacturer.length() > 0)
				manufacturer = manufacturer.substr(1, manufacturer.length()-1).c_str(); //trimming off the initial copyright symbol so matching won't be dumb
			if (
				((manufacturer == "Microsoft Corporation") && (product == "Controller"))
				|| ((manufacturer == "icrosoft") && (product == "Wireless 360 Controller"))
				)
			{
				sysLog.Printf("Controller %d connected!", _controllerID+1);
				_connected = true;
				break;
			}
			
			_device = HIDGetNextDevice(_device);
		}
		if (_device == NULL)
		{
			sysLog.Printf("Controller %d not present...", _controllerID+1);
			_connected = false;
		}
		else
		{
			pRecElement current_element = HIDGetFirstDeviceElement(_device, kHIDElementTypeIO);
			while (current_element != NULL)
			{
				_elements[(unsigned int)current_element->cookie] = current_element;
				current_element = HIDGetNextDeviceElement(current_element, kHIDElementTypeIO);
			}
		}
	#elif defined(__linux__)
		_currentControllerInput.LeftThumbstickX = 
		_currentControllerInput.LeftThumbstickY =
		_currentControllerInput.RightThumbstickX =
		_currentControllerInput.RightThumbstickY = 
		_currentControllerInput.LeftTriggerValue = 
		_currentControllerInput.RightTriggerValue = 
		_currentControllerInput.Buttons = 0;
		char* devicePath;
		if (_controllerID == 0)
			devicePath = LINUX_CONTROLLER_1_PATH;
		else
			devicePath = LINUX_CONTROLLER_2_PATH;

		_deviceFD = open(devicePath, O_RDONLY | O_NONBLOCK);
		if (_deviceFD < 0)
		{
			sysLog.Printf("Controller %d not present...", _controllerID+1);
			_connected = false;
		}
		else
		{
			sysLog.Printf("Controller %d connected!", _controllerID+1);
			_connected = true;
		}

		// Discover the force feedback device.
		bool foundFirstController = false;
		_ffFD = -1;
		for (int i = 0; i < MAX_LINUX_EVENT_INTERFACES; i++)
		{
			std::stringstream ss;
			ss << i;
			String eventDev = LINUX_EVENT_INTERFACE + ss.str();
			int fd = open(eventDev.c_str(), O_RDWR);
			if (fd >= 0)
		 	{
				char name[256] = "Unknown";
				ioctl(fd, EVIOCGNAME(sizeof(name)), name);
				if (strcmp(name, "Microsoft X-Box 360 pad") == 0)
				{
					if (_controllerID == 0)
					{
						_ffFD = fd;
						break;
					}
					else
					{
						if (foundFirstController)
						{
							_ffFD = fd;
							break;
						}
						else
						{
							foundFirstController = true;
							close(fd);
						}
					}
				}
				else
				{
					close(fd);
				}
			}
		}
		if (_ffFD < 0)
		{
			sysLog.Printf("Error opening Force Feedback device for controller %d!", _controllerID+1);
		}
		else
		{
			_ffEffect.type = FF_RUMBLE;
			_ffEffect.id = -1;
			_ffEffect.u.rumble.strong_magnitude = 0;
			_ffEffect.u.rumble.weak_magnitude = 0;
			_ffEffect.replay.length = 0x7fff;
			_ffEffect.replay.delay = 0;
			_ffPlay.type = EV_FF;
			_ffPlay.value = 1;
		}
	#endif
}

void Controller::UpdateState()
{
	if(!_connected)
	{
		return;
	}
	#if defined(WIN32)
		_dwResult = XInputGetState(_controllerID, &_currentControllerRawState);
		
		// We either don't have a controller or the Input has failed.  Keep clearing the input
		// data so we don't get garbage input.
		if (_dwResult != ERROR_SUCCESS)
		{
			if (_connected)
			{
				sysLog.Printf("Uh oh, we lost controller %d...", _controllerID+1);
			}
			
			_connected = false;
			ZeroMemory( &_currentControllerRawState, sizeof(XINPUT_STATE));
			_currentControllerInput.LeftThumbstickX = 
			_currentControllerInput.LeftThumbstickY =
			_currentControllerInput.RightThumbstickX =
			_currentControllerInput.RightThumbstickY = 
			_currentControllerInput.LeftTriggerValue = 
			_currentControllerInput.RightTriggerValue = 
			_currentControllerInput.Buttons = 0;
			return;
		}
		
		_connected = true;
		
		_currentControllerInput.Buttons = _currentControllerRawState.Gamepad.wButtons;
		//TODO: dpad
		_currentControllerInput.LeftTriggerValue = (int)_currentControllerRawState.Gamepad.bLeftTrigger;
		_currentControllerInput.RightTriggerValue = (int)_currentControllerRawState.Gamepad.bRightTrigger;
		_currentControllerInput.LeftThumbstickX = _currentControllerRawState.Gamepad.sThumbLX;
		_currentControllerInput.LeftThumbstickY = _currentControllerRawState.Gamepad.sThumbLY;
		_currentControllerInput.RightThumbstickX = _currentControllerRawState.Gamepad.sThumbRX;
		_currentControllerInput.RightThumbstickY = _currentControllerRawState.Gamepad.sThumbRY;
		
	#elif defined(__APPLE__)
		_currentControllerInput.LeftThumbstickX = _getValueForCookie(0x1b);
		_currentControllerInput.LeftThumbstickY = -_getValueForCookie(0x1c);
		_currentControllerInput.RightThumbstickX = _getValueForCookie(0x1d);
		_currentControllerInput.RightThumbstickY = -_getValueForCookie(0x1e);
		_currentControllerInput.LeftTriggerValue = _getValueForCookie(0x19);
		_currentControllerInput.RightTriggerValue = _getValueForCookie(0x1a);
		
		_currentControllerInput.Buttons = 0;
		if (_getValueForCookie(0x0a))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_DPAD_UP;
		if (_getValueForCookie(0x0b))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_DPAD_DOWN;
		if (_getValueForCookie(0x0c))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_DPAD_LEFT;
		if (_getValueForCookie(0x0d))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_DPAD_RIGHT;
		if (_getValueForCookie(0x0e))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_START;
		if (_getValueForCookie(0x0f))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_BACK;
		if (_getValueForCookie(0x10))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_LEFT_THUMB;
		if (_getValueForCookie(0x11))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_RIGHT_THUMB;
		if (_getValueForCookie(0x12))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_LEFT_SHOULDER;
		if (_getValueForCookie(0x13))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
		if (_getValueForCookie(0x15))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_A;
		if (_getValueForCookie(0x16))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_B;
		if (_getValueForCookie(0x17))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_X;
		if (_getValueForCookie(0x18))
			_currentControllerInput.Buttons |= XINPUT_GAMEPAD_Y;

	#elif defined(__linux__)
		struct js_event js;
		while (read(_deviceFD, &js, sizeof(struct js_event)) == sizeof(struct js_event))
		{
			switch (js.type)
			{
				case JS_EVENT_BUTTON:
					unsigned int currButton;
					switch (js.number)
					{
						case 0:
							currButton = XINPUT_GAMEPAD_A;
							break;
						case 1:
							currButton = XINPUT_GAMEPAD_B;
							break;
						case 2:
							currButton = XINPUT_GAMEPAD_X;
							break;
						case 3:
							currButton = XINPUT_GAMEPAD_Y;
							break;
						case 4:
							currButton = XINPUT_GAMEPAD_LEFT_SHOULDER;
							break;
						case 5:
							currButton = XINPUT_GAMEPAD_RIGHT_SHOULDER;
							break;
						case 6:
							currButton = XINPUT_GAMEPAD_BACK;
							break;
						case 7:
							currButton = XINPUT_GAMEPAD_START;
							break;
						case 8:
							// Big 'X' button - not used.
							continue;
						case 9:
							currButton = XINPUT_GAMEPAD_LEFT_THUMB;
							break;
						case 10:
							currButton = XINPUT_GAMEPAD_RIGHT_THUMB;
							break;
						// Note: for certain XBox 360 Controllers (e.g. wireless models) the
						// Linux kernel driver maps the DPAD as buttons (vice axes, as handled
						// below).  We attempt to support both mappings here.
						case 11:
							currButton = XINPUT_GAMEPAD_DPAD_LEFT;
							break;
						case 12:
							currButton = XINPUT_GAMEPAD_DPAD_RIGHT;
							break;
						case 13:
							currButton = XINPUT_GAMEPAD_DPAD_UP;
							break;
						case 14:
							currButton = XINPUT_GAMEPAD_DPAD_DOWN;
							break;
						default:
							sysLog.Printf("Error! Unknown button press event received!\n");
							continue;
					}
					if (js.value) // button pressed
						_currentControllerInput.Buttons |= currButton;
					else // button released
						_currentControllerInput.Buttons &= ~currButton;
					break;
					case JS_EVENT_AXIS:
					switch (js.number)
					{
						case 0:
							_currentControllerInput.LeftThumbstickX = js.value;
							break;
						case 1:
							_currentControllerInput.LeftThumbstickY = -js.value;
							break;
						case 2:
							_currentControllerInput.LeftTriggerValue = js.value;
							break;
						case 3:
							_currentControllerInput.RightThumbstickX = js.value;
							break;
						case 4:
							_currentControllerInput.RightThumbstickY = -js.value;
							break;
						case 5:
							_currentControllerInput.RightTriggerValue = js.value;
							break;
						case 6:
							if (js.value == 0)
								_currentControllerInput.Buttons &= ~(XINPUT_GAMEPAD_DPAD_LEFT | XINPUT_GAMEPAD_DPAD_RIGHT);
							else if (js.value < 0)
								_currentControllerInput.Buttons |= XINPUT_GAMEPAD_DPAD_LEFT;
							else
								_currentControllerInput.Buttons |= XINPUT_GAMEPAD_DPAD_RIGHT;
							break;
						case 7:
							if (js.value == 0)
								_currentControllerInput.Buttons &= ~(XINPUT_GAMEPAD_DPAD_UP | XINPUT_GAMEPAD_DPAD_DOWN);
							else if (js.value < 0)
								_currentControllerInput.Buttons |= XINPUT_GAMEPAD_DPAD_UP;
							else
								_currentControllerInput.Buttons |= XINPUT_GAMEPAD_DPAD_DOWN;
							break;
						default:
							sysLog.Printf("Error! Unknown axis event received!\n");
							break;
					}
					break;
					default:
					break;
			}
		}
	#endif
	
	//Using the built-in deadzone -- comment out if you don't like it
	if (_currentControllerInput.LeftThumbstickX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		_currentControllerInput.LeftThumbstickX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		_currentControllerInput.LeftThumbstickY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		_currentControllerInput.LeftThumbstickY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		_currentControllerInput.LeftThumbstickX = 0;
		_currentControllerInput.LeftThumbstickY = 0;
	}
	if (_currentControllerInput.RightThumbstickX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		_currentControllerInput.RightThumbstickX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		_currentControllerInput.RightThumbstickY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		_currentControllerInput.RightThumbstickY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		_currentControllerInput.RightThumbstickX = 0;
		_currentControllerInput.RightThumbstickY = 0;
	}
	
	theInput.HandleControl( *this );
}

const ControllerInput Controller::GetState()
{
	return _currentControllerInput;
}

const Vector2 Controller::GetLeftThumbVec2()
{
	Vector2 forReturn;
	forReturn.X = float(_currentControllerInput.LeftThumbstickX) / 32768.0f;
	forReturn.Y = float(_currentControllerInput.LeftThumbstickY) / 32768.0f;
	return forReturn;
}

const Vector2 Controller::GetRightThumbVec2()
{
	Vector2 forReturn;
	forReturn.X = float(_currentControllerInput.RightThumbstickX) / 32768.0f;
	forReturn.Y = float(_currentControllerInput.RightThumbstickY) / 32768.0f;
	return forReturn;
}

const Vec2i Controller::GetLeftThumbstick()
{
	Vec2i forReturn;
	forReturn.X = _currentControllerInput.LeftThumbstickX;
	forReturn.Y = _currentControllerInput.LeftThumbstickY;
	return forReturn;
}
const Vec2i Controller::GetRightThumbstick()
{
	Vec2i forReturn;
	forReturn.X = _currentControllerInput.RightThumbstickX;
	forReturn.Y = _currentControllerInput.RightThumbstickY;
	return forReturn;
}

const int Controller::GetRightTrigger()
{
	return _currentControllerInput.RightTriggerValue;
}

const int Controller::GetLeftTrigger()
{
	return _currentControllerInput.LeftTriggerValue;
}

const bool Controller::IsButtonDown(int buttonMask)
{
	return ((_currentControllerInput.Buttons & buttonMask) != 0);
}

const bool Controller::IsAButtonDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_A)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsBButtonDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_B)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsXButtonDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_X)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsYButtonDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_Y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsLeftThumbstickButtonDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_LEFT_THUMB)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsRightThumbstickButtonDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_RIGHT_THUMB)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsStartButtonDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_START)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsBackButtonDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_BACK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsLeftBumperDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsRightBumperDown()
{
	if(_currentControllerInput.Buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsLeftTriggerPressed()
{
	if (_currentControllerInput.LeftTriggerValue > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Controller::IsRightTriggerPressed()
{
	if (_currentControllerInput.RightTriggerValue > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return true;
	}
	else
	{
		return false;
	}
}


const unsigned int Controller::GetLeftVibration()
{
	return _currentLeftVibration;
}

const unsigned int Controller::GetRightVibration()
{
	return _currentRightVibration;
}

void Controller::SetLeftVibrationRaw(unsigned int newVibration)
{
#if defined(WIN32)
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = _currentLeftVibration = newVibration;
	vibration.wRightMotorSpeed = _currentRightVibration;
	XInputSetState(0, &vibration);
#elif defined(__APPLE__)
	newVibration = 0;
#elif defined(__linux__)
	_ffEffect.u.rumble.strong_magnitude = _currentLeftVibration = newVibration;
	_ffEffect.u.rumble.weak_magnitude = _currentRightVibration;
	if (ioctl(_ffFD, EVIOCSFF, &_ffEffect) == -1)
	{
		sysLog.Printf("Error writing force feedback effect!");
		return;
	}
	_ffPlay.code = _ffEffect.id;
	if (write(_ffFD, &_ffPlay, sizeof(_ffPlay)) == -1)
	{
		sysLog.Printf("Error playing force feedback effect!");
	}
#endif
}

void Controller::SetRightVibrationRaw(unsigned int newVibration)
{
#if defined(WIN32)
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = _currentLeftVibration;
	vibration.wRightMotorSpeed = _currentRightVibration = newVibration;
	XInputSetState(0, &vibration);
#elif defined(__APPLE__)
	newVibration = 0;
#elif defined(__linux__)
	_ffEffect.u.rumble.strong_magnitude = _currentLeftVibration;
	_ffEffect.u.rumble.weak_magnitude = _currentRightVibration = newVibration;
	if (ioctl(_ffFD, EVIOCSFF, &_ffEffect) == -1)
	{
		sysLog.Printf("Error writing force feedback effect!");
		return;
	}
	_ffPlay.code = _ffEffect.id;
	if (write(_ffFD, &_ffPlay, sizeof(_ffPlay)) == -1)
	{
		sysLog.Printf("Error playing force feedback effect!");
	}
#endif
}

void Controller::SetLeftVibration(unsigned int newVibration)
{
	newVibration = MathUtil::Clamp(newVibration, 0, 255);
	if (newVibration == 255)
	{
		SetLeftVibrationRaw(65535);
	}
	else
	{
		SetLeftVibrationRaw(newVibration << 8);
	}
}

void Controller::SetRightVibration(unsigned int newVibration)
{
	newVibration = MathUtil::Clamp(newVibration, 0, 255);
	if (newVibration == 255)
	{
		SetRightVibrationRaw(65535);
	}
	else
	{
		SetRightVibrationRaw(newVibration << 8);
	}
}
