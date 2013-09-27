//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
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

#pragma once

#include "../Infrastructure/VecStructs.h"
#include "../Infrastructure/Vector2.h"
#include "../Infrastructure/Log.h"

#if defined(WIN32)
	#include <XInput.h>
	#pragma comment(lib, "XInput.lib")
	#include <assert.h>
#elif defined(__APPLE__)
	#include <Carbon/Carbon.h>
	#include <IOKit/HID/IOHIDKeys.h>
	#include "HID_Utilities_External.h"
#elif defined(__linux__)
	#include <fcntl.h>
	#include <linux/joystick.h>
	#include <string.h>
	#include <sstream>
	#include <unistd.h>
	#define LINUX_CONTROLLER_1_PATH "/dev/input/js0"
	#define LINUX_CONTROLLER_2_PATH "/dev/input/js1"
	#define LINUX_EVENT_INTERFACE "/dev/input/event"
	#define MAX_LINUX_EVENT_INTERFACES 32
#endif

///A struct that wraps all controller input values into one unit
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

//forward declaration for the manager class
class Controller;

//Limited to two because our wrapping is a little naive at the moment
#define MAX_CONTROLLERS 2

/// (Internal) Manages multiple controllers (currently up to 2)
/** 
 * This internal class represents the coordinator for gamepad controllers. You 
 *  should only have to deal with it if you're using it with multiple 
 *  controllers, and even then, it's best to access them with the 
 *  "controllerOne" and "controllerTwo" shortcuts. 
 * 
 * Like the World, it uses the singleton pattern; you can't actually declare 
 *  a new instance of a ControllerManager. To access controllers in your 
 *  world, use "theControllerManager" to retrieve the singleton object. 
 *  "theControllerManager" is defined in both C++ and Lua. 
 * 
 * If you're not familiar with the singleton pattern, this paper is a good 
 *  starting point. (Don't be afraid that it's written by Microsoft.)
 * 
 * http://msdn.microsoft.com/en-us/library/ms954629.aspx
 */
class ControllerManager
{
public:
	/**
	 * Used to access the singleton instance of this class. As a shortcut, 
	 *  you can just use "theControllerManager". 
	 * 
	 * @return The singleton
	 */
	static ControllerManager& GetInstance();
	
	/**
	 * Get a reference to one of the controllers. 
	 * 
	 * @param controllerIndex The index of the controller you want to 
	 *   retrieve. Since we only support 2 controllers, this needs to be 
	 *   either 0 or 1. 
	 * @return A Controller object
	 */
	Controller& GetController(int controllerIndex=0)
	{
		if ( (controllerIndex >= MAX_CONTROLLERS) || (controllerIndex < 0) )
		{
			sysLog.Log("ERROR: Bad controller index.");
			#if defined(ANGEL_DEBUG)
				assert(0);
			#endif
		}
		return *_controllers[controllerIndex];
	}
	
	/**
	 * Attempt to initialize both controllers. 
	 */
	void Setup();
	
	/**
	 * Called once per frame, reads all input data from the controller for
	 *  polling by the rest of the game. 
	 */
	void UpdateState();
	
	/**
	 * The destructor releases all the controller input handles. 
	 */
	~ControllerManager();
	
protected:
	static ControllerManager *s_ControllerManager;
	
private:
	ControllerManager();
	Controller* _controllers[MAX_CONTROLLERS];
};

//Accessor and Singleton shortcuts
#define theControllerManager ControllerManager::GetInstance()
#define theController ControllerManager::GetInstance().GetController()
#define controllerOne theController
#define controllerTwo ControllerManager::GetInstance().GetController(1)

///A class representing a gamepad controller
/** 
 * This class is your means of getting data from a controller. At the moment
 *  we only test and support the Xbox 360 controller over USB, but this 
 *  interface could be abstracted to support other controllers. 
 * 
 * On Windows you'll need DirectX installed to play a game made with Angel, 
 *  and the DirectX SDK to develop one. A pretty big download/install just
 *  to get access to a controller, but we figure most gamers/developers have
 *  already done so anyway. 
 * 
 * On the Mac both players and developers need to install a kernel extension 
 *  (sorry!) included in the Tools directory. We'd be more than happy to 
 *  remove this requirement, but unless someone who knows more about how to
 *  use IOKit and raw USB values wants to help, this is what we've got.
 */
class Controller  
{
public:
	friend class ControllerManager;
	
	/**
	 * Sets the controller up to read data every frame. If it's successful, 
	 *  the Controller::IsConnected function will return true. 
	 */
	void Setup();
	
	/**
	 * Called once per frame to read the data in from the controller. Called
	 *  automatically by the ControllerManager. 
	 */
	void UpdateState();
	
	/**
	 * Directly access all current input on the controller. 
	 * 
	 * @return The current input data from the buttons and thumbsticks of this
	 *   controller. 
	 */
	const ControllerInput GetState();
	
	/**
	 * Get the X and Y positions of the left thumbstick as a Vector2. 
	 * 
	 * @return The current direction of the left thumbstick, as a Vector2 with 
	 *   both dimensions ranging from -1.0 to 1.0. 
	 */
	const Vector2 GetLeftThumbVec2();
	
	/**
	 * Get the X and Y positions of the right thumbstick as a Vector2. 
	 * 
	 * @return The current direction of the right thumbstick, as a Vector2 
	 *   with both dimensions ranging from -1.0 to 1.0. 
	 */
	const Vector2 GetRightThumbVec2();
	
	/**
	 * Get the raw values of the left thumbstick as an integer vector. 
	 * 
	 * @return The current raw values of the left thumbstick, with both X and
	 *   Y ranging from -32768 to 32768. 
	 */
	const Vec2i GetLeftThumbstick();
	
	/**
	 * Get the raw values of the right thumbstick as an integer vector. 
	 * 
	 * @return The current raw values of the right thumbstick, with both X and
	 *   Y ranging from -32768 to 32768. 
	 */
	const Vec2i GetRightThumbstick();
	
	/**
	 * Get the current value of the right trigger.
	 * 
	 * @return How much the right analog trigger is pressed, ranging from 0 
	 *   (untouched) to 255 (all the way down).
	 */
	const int GetRightTrigger();
	
	/**
	 * Get the current value of the left trigger.
	 * 
	 * @return How much the left analog trigger is pressed, ranging from 0 
	 *   (untouched) to 255 (all the way down).
	 */
	const int GetLeftTrigger();
	
	/**
	 * Pass a button mask to find out if a combination of buttons is depressed
	 *  at the same time. Here are the mask values:
	 * 
	 * \code
	 * #define XINPUT_GAMEPAD_DPAD_UP          0x00000001
	 * #define XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
	 * #define XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
	 * #define XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
	 * #define XINPUT_GAMEPAD_START            0x00000010
	 * #define XINPUT_GAMEPAD_BACK             0x00000020
	 * #define XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
	 * #define XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
	 * #define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
	 * #define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
	 * #define XINPUT_GAMEPAD_A                0x1000
	 * #define XINPUT_GAMEPAD_B                0x2000
	 * #define XINPUT_GAMEPAD_X                0x4000
	 * #define XINPUT_GAMEPAD_Y                0x8000
	 * \endcode
	 * 
	 * @param buttonMask The values you care about, combined as a bitmask
	 * @return True if all the masked buttons are pressed, false if they're
	 *   not
	 */
	const bool IsButtonDown(int buttonMask);
	
	
	//Do these really need documentation comments? Sigh. I guess so. 
	
	/**
	 * Find out if the A button is currently pressed. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsAButtonDown();
	
	/**
	 * Find out if the B button is currently pressed. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsBButtonDown();
	
	/**
	 * Find out if the X button is currently pressed. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsXButtonDown();
	
	/**
	 * Find out if the Y button is currently pressed. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsYButtonDown();
	
	/**
	 * Find out if the left thumbstick is currently pressed down. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsLeftThumbstickButtonDown();
	
	/**
	 * Find out if the right thumbstick is currently pressed down. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsRightThumbstickButtonDown();
	
	/**
	 * Find out if the start button is currently pressed. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsStartButtonDown();
	
	/**
	 * Find out if the back button is currently pressed. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsBackButtonDown();
	
	/**
	 * Find out if the left shoulder button is currently pressed. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsLeftBumperDown();
	
	/**
	 * Find out if the right shoulder button is currently pressed. 
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsRightBumperDown();
	
	/**
	 * Find out if the left trigger is pressed down. Since it's an analog
	 *  trigger, there's a driver-defined threshold that this function will
	 *  use to determine when it can be considered "activated."
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsLeftTriggerPressed();
	
	/**
	 * Find out if the left trigger is pressed down. Since it's an analog
	 *  trigger, there's a driver-defined threshold that this function will
	 *  use to determine when it can be considered "activated."
	 * 
	 * @return True if it is, false if it's not. 
	 */
	const bool IsRightTriggerPressed();
	
	/**
	 * Set the rumble of the controller's lower frequencies. This sets the
	 *  raw driver value. 
	 * 
	 * Not available on Mac OS X. :-(
	 * 
	 * @param frequencies The desired intensity, ranging from 0 to 65535. 
	 */
	void SetLeftVibrationRaw(unsigned int vibration); 
	
	/**
	 * Set the rumble of the controller's higher frequencies. This sets the
	 *  raw driver value. 
	 * 
	 * Not available on Mac OS X. :-(
	 * 
	 * @param frequencies The desired intensity, ranging from 0 to 65535. 
	 */
	void SetRightVibrationRaw(unsigned int vibration); 
	
	/**
	 * Set the rumble of the controller's lower frequencies. This uses more
	 *  manageable numbers if you don't feel like dealing with INT_MAX. 
	 * 
	 * Not available on Mac OS X. :-(
	 * 
	 * @param frequencies The desired intensity, ranging from 0 to 255. 
	 */
	void SetLeftVibration(unsigned int vibration); 
	
	/**
	 * Set the rumble of the controller's higher frequencies. This uses more
	 *  manageable numbers if you don't feel like dealing with INT_MAX. 
	 * 
	 * Not available on Mac OS X. :-(
	 * 
	 * @param frequencies The desired intensity, ranging from 0 to 255. 
	 */
	void SetRightVibration(unsigned int vibration); 
	
	/**
	 * Get the current vibration setting for the lower frequencies. 
	 * 
	 * @return Current intensity, ranging from 0 to 65535. 
	 */
	const unsigned int GetLeftVibration(); 
	
	/**
	 * Get the current vibration setting for the higher frequencies. 
	 * 
	 * @return Current intensity, ranging from 0 to 65535. 
	 */
	const unsigned int GetRightVibration();
	
	/**
	 * Find out if this controller object is currently mapped to a real-world
	 *  controller and receiving input. 
	 * 
	 * @return True if this controller gets input
	 */
	const bool IsConnected() { return _connected; }
	
	/**
	 * Get the index this controller corresponds to in the ControllerManager.
	 * 
	 * @return The index that can be used in ControllerManager::GetController
	 */
	const int GetControllerID() { return _controllerID; }
	
protected:
	Controller();
	static Controller *s_Controller;
	
private:
	int _controllerID;
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
#elif defined(__linux__)
	int _deviceFD;
	int _ffFD;
	struct ff_effect _ffEffect;
	struct input_event _ffPlay;
#endif
};
