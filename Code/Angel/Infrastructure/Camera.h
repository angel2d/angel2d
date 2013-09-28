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

#include "../Actors/Actor.h"
#include "../Infrastructure/Vector3.h"

#define theCamera Camera::GetInstance()

///The class that handles displaying the appropriate viewport.
/** 
 * The Camera class is how you control what your players see at any time. 
 *  It uses the singleton pattern; you can't actually declare a new instance
 *  of a Camera. To access the Camera in your world, use "theCamera" to retrieve
 *  the singleton object. "theCamera" is defined in both C++ and Lua. 
 * 
 * If you're not familiar with the singleton pattern, this paper is a good 
 *  starting point. (Don't be afraid that it's written by Microsoft.)
 * 
 * http://msdn.microsoft.com/en-us/library/ms954629.aspx
 * 
 * Camera is an Actor so that you can apply motion to it the same way you would
 *  any other Actor in your world. 
 * 
 * By default the camera is positioned 10 units away from the origin, looking
 *  down the Z-axis (0.0, 0.0, 10.0). The visible world stretches from 
 *  (-13.3, -10) to (13.3, 10).
 * 
 * Whenever the Camera updates its position or the viewport, it broadcasts a 
 *  "CameraChange" Message that you can subscribe to if you need notifications. 
 */
class Camera : public Actor 
{
public:
	/**
	 * Used to access the singleton instance of this class. As a shortcut, 
	 *  you can just use "theCamera". 
	 * 
	 * @return The singleton
	 */
	static Camera &GetInstance();
	
	#if !ANGEL_MOBILE
		/**
		 * The callback used by GLFW to alert us when the user changes the size
		 *  of the window. You shouldn't need to mess with this. 
		 * 
		 * @param w New width in pixels
		 * @param h New height in pixels
		 */
		static void ResizeCallback(GLFWwindow* window, int w, int h);
	#endif
	
	/**
	 * Deletes and NULLs out the singleton -- should only get called at World
	 *  destruction when the program is exiting. 
	 */
	void Destroy();
	
	/**
	 * Override of actor's Update method to deal with the actor lock
	 */
	virtual void Update(float dt);
	
	/**
	 * Makes sure the view matrix is properly set up on every frame. Called 
	 *  by the world before rendering anything else. 
	 */
	void Render();
	
	/**
	 * Resets the viewport to its default. 
	 */
	void Reset();
	
	/**
	 * Locks the camera to a specific Actor so it will track
	 *  it around.
	 *
	 * @param locked The actor to track
	 * @param lockX Whether to track the actor's X position
	 * @param lockY Whether to track the actor's Y position
	 * @param lockRotation Whether to track the actor's rotation
	 */
	void LockTo(Actor* locked, bool lockX=true, bool lockY=true, bool lockRotation=false);
	
	/**
	 * Get the actor that the camera is currently tracking. 
	 * 
	 * @return The tracked actor (NULL if not tracking anything)
	 */
	Actor* GetLockedActor() { return _locked; }
	
	/**
	 * Get the window's current height. 
	 * 
	 * @return Height in pixels. 
	 */
	const int GetWindowHeight() const;
	
	/**
	 * Get the window's current width. 
	 * 
	 * @return Width in pixels.
	 */
	const int GetWindowWidth() const;
	
	/**
	 * If you were to draw a circle inscribed in the viewport, this function
	 *  will let you know the size of its radius. This is useful for determining
	 *  how much of the world is currently being displayed. 
	 * 
	 * Note that if you have a non-square viewport, the circle is bounded by
	 *  the \b smaller dimension.
	 * 
	 * @return The radius size in GL units. 
	 */
	const double GetViewRadius() const;
	
	/**
	 * Get the world coordinate of the top-right point of the window. 
	 * 
	 * @return The world coordinate (GL units).
	 */
	const Vector2 GetWorldMaxVertex() const;
	
	/**
	 * Get the world coordinate of the bottom-left point of the window. 
	 * 
	 * @return The world coordinate (GL units).
	 */
	const Vector2 GetWorldMinVertex() const;

	/**
	 * Set the position of the camera. Note that the camera is the only
	 *  Actor that can take a Z coordinate for its position -- you can zoom
	 *  in and out. 
	 * 
	 * @param x The new X position for the camera
	 * @param y The new Y position for the camera
	 * @param z The new Z position for the camera
	 */
	virtual void SetPosition(float x, float y, float z);
	
	/**
	 * Set the position of the camera. Using this two-dimensional function,
	 *  the position on the Z-axis stays fixed. 
	 * 
	 * @param x The new X position for the camera 
	 * @param y The new Y position for the camera
	 */
	virtual void SetPosition(float x, float y);
	
	/**
	 * Set the position of the camera. Note that the camera is the only
	 *  Actor that can take a Z coordinate for its position -- you can zoom
	 *  in and out. 
	 *
	 * @param v3 The new position for the camera. 
	 */
	virtual void SetPosition(const Vector3& v3);
	
	/**
	 * Set the position of the camera. Using this two-dimensional function, 
	 *  the position on the Z-axis stays fixed. 
	 * 
	 * @param v2 The new position for the Camera
	 */
	virtual void SetPosition(const Vector2& v2);
    
    /**
     * Interval movement for the camera in three dimensions.
     * 
     * @see Actor::MoveTo
	 * @param newPosition The target position for the movement
	 * @param duration How long it should take to get there
	 * @param smooth Whether the function should use MathUtil::SmoothStep
	 *  instead of MathUtil::Lerp
	 * @param onCompletionMessage If specified, a Message of this type will be
	 *  sent when the movement is complete, letting you know when it's done.
	 *  You will have to manually subscribe to this Message, though.
     */
    void MoveTo(const Vector3& newPosition, float duration, bool smooth=false, String onCompletionMessage="");
	
	/**
	 * Gets the position of the Camera. Only returns the X and Y position so
	 *  as to fit with the other GetPosition functions in the engine. To get
	 *  the Z coordinate, see below. 
	 * 
	 * @return The (X, Y) position of the camera. 
	 */
	virtual Vector2 GetPosition() const;
	
	/**
	 * Get the position of the camera on the Z-axis. 
	 * 
	 * @return The camera's Z coordinate. 
	 */
	virtual float GetZ() const;
	
	/**
	 * Set the rotation of the camera. Only rotates about the Z-axis,
	 *  since we prefer the 2-dimensional.
	 * 
	 * @param v2 The new rotation for the Camera. As with Actors, positive
	 *   rotations are counter-clockwise.
	 */
	virtual void SetRotation(float rotation);
	
	/**
	* Get the Z value necessary to achieve the requested view radius. 
	* 
	* @param radius The desired view radius.
	* @return The Z value. 
	*/
	virtual float GetZForViewRadius(float radius);

	/**
	* Get the near clip distance.
	* 
	* @return The near clip distance. 
	*/
	virtual float GetNearClipDist();

	/**
	* Get the far clip distance.
	* 
	* @return The far clip distance. 
	*/
	virtual float GetFarClipDist();

	/**
	* Set the Z value necessary to achieve the requested view radius. 
	* 
	* @param newRadius The desired view radius.
	*/
	virtual void SetZByViewRadius(float newRadius);

	/**
	* Set the near clip distance.
	*  Note this will cause a Resize() to properly update the clipping planes
	* 
	* @param dist The near clip distance. 
	*/
	virtual void SetNearClipDist(float dist);

	/**
	* Set the far clip distance.
	*  Note this will cause a Resize() to properly update the clipping planes
	* 
	* @param dist The far clip distance. 
	*/
	virtual void SetFarClipDist(float dist);

	/**
	 * Set the point towards which the camera should aim. Since Angel is a 
	 *  predominantly 2D world, be very careful setting this too far off of
	 *  perpendicular. 
	 * 
	 * @param x The X coordinate at which the Camera will aim. 
	 * @param y The Y coordinate at which the Camera will aim. 
	 * @param z The Z coordinate at which the Camera will aim. 
	 */
	virtual void SetViewCenter(float x, float y, float z);
	
	/**
	 * Get the current look-at target of the camera. 
	 * 
	 * @return The point where the Camera is currently looking. 
	 */
	virtual const Vector3& GetViewCenter() const;
	
	/**
	 * Used by the SetName function to create a basename for this class. 
	 *  Overridden from Actor::GetClassName.
	 * 
	 * @return The string "Camera"
	 */
	virtual const String GetClassName() const { return "Camera"; }

protected:
	Camera();
	static Camera *s_Camera;

	void Resize(int w, int h);

private:
	int _windowWidth;
	int _windowHeight;
	double _aperture;
	Vector3 _camera3DPosition;
	Vector3 _view;
	Vector3 _up;

	float _zNearClip;
	float _zFarClip;
	
	Actor* _locked;
	bool _lockX;
	bool _lockY;
	bool _lockRotation;
    
    Interval<Vector3> _3dPositionInterval;
    String _3dPositionIntervalMessage;
};
