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

/** @file */
#pragma once

#include "../Infrastructure/Renderable.h"
#include "../Infrastructure/Color.h"
#include "../Infrastructure/Interval.h"
#include "../Messaging/Message.h"

#define MAX_SPRITE_FRAMES 64
#define CIRCLE_DRAW_SECTIONS 32

/**
 * An enumeration for the type of animations that can be given to an Actor. 
 */
enum spriteAnimationType
{
	SAT_None,
	SAT_Loop,
	SAT_PingPong,
	SAT_OneShot
};

/**
 * An enumeration for the shape of an Actor when it gets drawn to the screen.
 *  Note that at present, circular actors can't use textures. 
 */
enum actorDrawShape
{
	ADS_Square,
	ADS_Circle,
	ADS_CustomList
};

///Basic simulation element for Angel.
/**
 * Actor is the basic unit of simulation in Angel. It's not just an abstract 
 *  base class -- you can actually do a good deal of your game just using 
 *  plain Actors, depending on how you want to structure your logic. 
 *
 * Note that you have to add the Actor to the World if you want to see it on 
 *  screen. 
 * 
 * If you want to subclass Actor, the two most important functions are #Render 
 *  and Update, which will get called on each Actor in the World every frame. 
 */
class Actor : public Renderable, public MessageListener
{
public:
	/**
	 * The constructor doesn't do anything special. It defaults to a square 
	 *  Actor with a side-length of 1.0f, no texture, white, and at the 
	 *  origin. 
	 */
	Actor();
	
	/**
	 * The destructor ensures that the Actor has been unsubscribed from all 
	 *  Messages, removed from all tag lists, and purged from the list of 
	 *  unique names. 
	 */
	virtual ~Actor();
	
	/**
	 * Set the size of this Actor. 
	 * 
	 * @param x Horizontal size in OpenGL units -- negative numbers treated as 
	 *   zero
	 * @param y Vertical size in OpenGL units -- if less than or equal to 
	 *   zero, assumed to be equal to x
	 */
	virtual void SetSize(float x, float y = -1.f); 	// equal dimensions by default
	
	/**
	 * Set the size of this Actor. 
	 * 
	 * @param newSize Desired size of Actor in OpenGL units. If either 
	 *  dimension is negative, it's clamped to zero. 
	 */
	virtual void SetSize(const Vector2& newSize);
	
	/**
	 * Return the size of this Actor.
	 * 
	 * @return Actor's size as a Vector2
	 */
	const Vector2& GetSize() const;
	
	/**
	 * Return the BoundingBox for this Actor.
	 *
	 * @return Actor's bounding box
	 */
	virtual BoundingBox GetBoundingBox() const;
	
	/**
	 * Set the position of the Actor in world coordinates. 
	 * 
	 * @param x X-coordinate in OpenGL units
	 * @param y Y-coordinate in OpenGL units
	 */
	virtual void SetPosition(float x, float y);
	
	/**
	 * Set the position of the Actor in world coordinates.
	 * 
	 * @param pos Desired X and Y coordinates wrapped up into a Vector2
	 */
	virtual void SetPosition(const Vector2& pos);
	
	/**
	 * Return the position of this Actor.
	 * 
	 * @return Actor's position as a Vector2
	 */
	const Vector2& GetPosition() const;
	
	/**
	 * Sets the rotation of the Actor. Positive rotations are 
	 *  counter-clockwise.
	 * 
	 * @param rotation Desired rotation in degrees
	 */
	virtual void SetRotation(float rotation);
	
	/**
	 * Return the rotation of this Actor.
	 * 
	 * @return Actor's rotation in degrees
	 */
	const float GetRotation() const;
	
	/**
	 * Sets the color of the Actor with individual components.
	 * 
	 * @param r Red
	 * @param g Green
	 * @param b Blue
	 * @param a Alpha (1.0f is opaque)
	 */
	void SetColor(float r, float g, float b, float a=1.0f);
	
	/**
	 * Sets the color of the Actor from a Color object.
	 * 
	 * @param color Desired color
	 */
	void SetColor(const Color& color);
	
	/**
	 * Return the Color of this Actor.
	 * 
	 * @return Actor's current color as a Color object
	 */
	const Color& GetColor() const;
	
	/**
	 * Set the transparency of the Actor, independent of the other color 
	 *  components.
	 * 
	 * @param newAlpha Desired transparency (1.0f is opaque, 0.0f is 
	 *  invisible)
	 */
	void SetAlpha(float newAlpha);
	
	/**
	 * Get current transparency for this Actor.
	 * 
	 * @return Actor's current transparency value.
	 */
	const float GetAlpha() const;
	
	/**
	 * Set the shape of the Actor when it's drawn.
	 * 
	 * @see actorDrawShape
	 * @param drawShape Desired shape
	 */
	virtual void SetDrawShape( actorDrawShape drawShape );
	
	/**
	 * Get the current shape of this Actor.
	 *
	 * @return Actor's shape
	 */
	const actorDrawShape& GetDrawShape() const;

	/**
	* Use a display list index for drawing rather than a built-in shape.
	*
	* @param listIndex The index to use (generate using glGenLists()) 
	*/
	void UseDisplayList(int listIndex)
	{
		_displayListIndex = listIndex;
		SetDrawShape(ADS_CustomList);
	}
	
	/**
	 * A "fire and forget" function that moves an Actor to a new position over 
	 *  a designated amount of time. This lets you handle movements without 
	 *  having to set up your own timers and keep track of them yourself. At 
	 *  the moment, it's limited to purely linear movement. 
	 * 
	 * @see RotateTo
	 * @see ChangeColorTo
	 * @see ChangeSizeTo
	 * @param newPosition The target position for the movement
	 * @param duration How long it should take to get there
	 * @param smooth Whether the function should use MathUtil::SmoothStep 
	 *  instead of MathUtil::Lerp
	 * @param onCompletionMessage If specified, a Message of this type will be 
	 *  sent when the movement is complete, letting you know when it's done. 
	 *  You will have to manually subscribe to this Message, though. 
	 */
	virtual void MoveTo(const Vector2& newPosition, float duration, bool smooth=false, String onCompletionMessage="");
	
	/**
	 * A "fire and forget" function that rotates an Actor over a designated 
	 *  amount of time. 
	 * 
	 * @see MoveTo
	 * @param newRotation The target rotation
	 * @param duration How long it should take
	 * @param smooth Whether the function should use MathUtil::SmoothStep 
	 *  instead of MathUtil::Lerp
	 * @param onCompletionMessage the type of Message to be sent on completion
	 */
	virtual void RotateTo(float newRotation, float duration, bool smooth=false, String onCompletionMessage="");
	
	/**
	 * A "fire and forget" function that changes an Actor's color over a 
	 *  designated amount of time. 
	 * 
	 * @see MoveTo
	 * @param newColor The target color
	 * @param duration How long it should take
	 * @param smooth Whether the function should use MathUtil::SmoothStep 
	 *  instead of MathUtil::Lerp
	 * @param onCompletionMessage the type of Message to be sent on completion
	 */
	void ChangeColorTo(const Color& newColor, float duration, bool smooth=false, String onCompletionMessage="");
	
	/**
	 * A "fire and forget" function that changes an Actor's size over a 
	 *  designated amount of time. This version uses a Vector2 if you want to 
	 *  set a non-uniform target size.
	 * 
	 * @see MoveTo
	 * @param newSize The target size
	 * @param duration How long it should take
	 * @param smooth Whether the function should use MathUtil::SmoothStep 
	 *  instead of MathUtil::Lerp
	 * @param onCompletionMessage the type of Message to be sent on completion
	 */
	virtual void ChangeSizeTo(const Vector2& newSize, float duration, bool smooth=false, String onCompletionMessage="");
	
	/**
	 * A "fire and forget" function that changes an Actor's size over a 
	 *  designated amount of time.
	 * 
	 * @see MoveTo
	 * @param newSize The target size
	 * @param duration How long it should take
	 * @param smooth Whether the function should use MathUtil::SmoothStep 
	 *  instead of MathUtil::Lerp
	 * @param onCompletionMessage the type of Message to be sent on completion
	 */
	virtual void ChangeSizeTo(float newSize, float duration, bool smooth=false, String onCompletionMessage="");
		
	/**
	 * Gets the OpenGL texture reference that the Actor is currently using
	 *  when it draws itself. 
	 * 
	 * @param frame If the Actor has an animation, you can retrieve the 
	 *   reference for a specific frame
	 * @return The OpenGL texture reference
	 */
	int GetSpriteTexture(int frame = 0) const;
	
	/**
	 * Apply texture information to an Actor. The file can be any image format
	 *  supported by DevIL, and transparency in the image will be used
	 *  when drawing the Actor. 
	 * 
	 * @param filename The path to an image file
	 * @param frame If you're building an animation for this Actor, you can
	 *   specify the frame to which this texture should be assigned. 
	 * @param clampmode The OpenGL clamp mode to use when drawing this sprite.
	 *   can be either GL_CLAMP or GL_REPEAT. 
	 * @param filtermode The OpenGL filter mode to use when drawing this 
	 *   sprite. One of GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST,
	 *   GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, or 
	 *   GL_LINEAR_MIPMAP_LINEAR
	 * @param optional If set to true, the engine won't complain if it can't
	 *   load this texture. 
	 * @return True if the sprite was successfully set, false otherwise
	 */
	bool SetSprite(const String& filename, int frame = 0, GLint clampmode = GL_CLAMP, GLint filtermode = GL_LINEAR, bool optional=false);
	
	/**
	 * Remove all sprite information from an Actor
	 */
	void ClearSpriteInfo();

	/**
	 * A convenience function for loading up a directory of image files as an
	 *  animation. We expect the name of the first image to end in _#,
	 *  where # represents a number. The number of digits you put at the end 
	 *  doesn't matter, but we are internally limited to 64 frames. If you 
	 *  want more, just change MAX_SPRITE_FRAMES in Actor.h. 
	 * 
	 * From the first file that you pass the function, it will iterate through
	 *  the file's directory and sequentially load up any images that follow
	 *  the same naming pattern. So if you had a directory with \c 
	 *  anim_001.png, \c anim_002.png, and \c anim_003.png, you could load
	 *  the three-frame animation by passing "anim_001.png" to this function. 
	 * 
	 * @param firstFilename The starting file for the animation
	 * @param clampmode The clamp mode to be used by the #SetSprite function
	 * @param filtermode The filter mode to be used by the #SetSprite function
	 */
	void LoadSpriteFrames(const String& firstFilename, GLint clampmode = GL_CLAMP, GLint filtermode = GL_LINEAR);
	
	//rb - TODO - Add a way to associate anim type, and frame indices to a name.
	/**
	 * Actually triggers the loaded animation to start playing. 
	 * 
	 * @param delay The amount of time between frames
	 * @param animType How the animation should behave when it's finished. 
	 *   Options are SAT_Loop, SAT_PingPong, and SAT_OneShot. 
	 * @param startFrame The starting frame of the animation to play
	 * @param endFrame The ending frame of the animation to play
	 * @param animName The name of the animation so you can get the event
	 *   when it finishes. 
	 */
	void PlaySpriteAnimation(float delay, spriteAnimationType animType = SAT_Loop, int startFrame = -1, int endFrame = -1, const char* animName = NULL); 
	
	/**
	 * Manually set the frame to draw. This way you can have an "animation" of
	 *  frames that just represent states of your actor and swap between them
	 *  without having to reload the textures all the time. 
	 * 
	 * @param frame The frame to switch to
	 */
	void SetSpriteFrame(int frame);
	
	/**
	 * Get the current animation frame, ranging from 0 to MAX_SPRITE_FRAMES.
	 * 
	 * @return The current animation frame.
	 */
	int GetSpriteFrame() const { return _spriteCurrentFrame; }
	
	/**
	 * Lets you find out if an animation is currently playing on this Actor.
	 * 
	 * @return True if there's an animation playing, false if there isn't. 
	 */
	const bool IsSpriteAnimPlaying() const
	{
		return (_spriteFrameDelay > 0);
	}
	
	/**
	 * A function you can override in the subclass if you you want your Actor
	 *  to do certain things when an animation finishes. This function will
	 *  get called by the animation system and pass in the string you assigned
	 *  when calling #PlaySpriteAnimation. 
	 * 
	 * @param animName The animation's name
	 */
	virtual void AnimCallback(String animName) {}
	
	/**
	 * If you're doing fancy things with moving textures, this function lets
	 *  you alter the UV (texture coordinates) of the actor. 
	 * 
	 * @param lowleft The desired lower left UV
	 * @param upright The desired upper right UV
	 */
	void SetUVs(const Vector2& lowleft, const Vector2& upright);
	
	/**
	 * Get the current UV coordinates being used by the Actor to draw. 
	 * 
	 * @param lowleft An out parameter that will be set to the current lower
	 *   left UV
	 * @param upright An out parameter that will be set to the current upper 
	 *   right UV
	 */
	void GetUVs(Vector2 &lowleft, Vector2 &upright) const;
	
	/**
	 * Returns whether or not this Actor has been given a particular tag. 
	 * 
	 * @see TagCollection
	 * @param tag the tag in question
	 * @return True if the Actor has the tag
	 */
	const bool IsTagged(const String& tag);
	
	/**
	 * Adds a tag to an Actor. If the Actor already has this tag, no action is 
	 *  taken.
	 * 
	 * @see TagCollection
	 * @param newTag The tag to add
	 */
	void Tag(const String& newTag);
	
	/**
	 * Removes a tag from an Actor. If the Actor doesn't have this tag, no 
	 *  action is taken.
	 * 
	 * @see TagCollection
	 * @param oldTag The tag to remove
	 */
	void Untag(const String& oldTag);
	
	/**
	 * Get all the tags for this ACtor. 
	 * 
	 * @see TagCollection
	 * @return A StringSet (std::vector<std::string>) of all the Actor's tags
	 */
	const StringSet& GetTags() const;
	
	/**
	 * Give this Actor a name that can later be used as a unique identifier. 
	 *  The the actual name given may differ from what is passed in, but is 
	 *  guaranteed to be unique. (A global monotonically increasing number
	 *  will be appended until the name is distinct.)
	 * 
	 * @param newName The desired name
	 * @return The actual name that was given
	 */
	const String& SetName(String newName);
	
	/**
	 * Get the unique name assigned to this Actor.
	 * 
	 * @return The Actor's current name.
	 */
	const String& GetName() const;
	
	/**
	 * A static function of the Actor class which returns an Actor from a 
	 *  name.
	 * 
	 * @param nameLookup The name index to look for
	 * @return The Actor with the given name. Will be NULL if there's no match
	 */
	static Actor* const GetNamed(const String& nameLookup);
	
	/**
	 * An implementation of the MessageListener interface, which will be 
	 *  called when a message gets delivered. 
	 * 
	 * There is no actual implementation in the base class, but you can 
	 *  override in the subclass. 
	 * 
	 * @see MessageListener
	 * @param message The message getting delivered. 
	 */
	virtual void ReceiveMessage(Message* message) {}
		
	/**
	 * Set a new rendering layer for this Actor. 
	 * 
	 * Layers are ordered from bottom to top by index. No space is wasted by 
	 *  leaving empty layers in between, so feel free to pad out your indices 
	 *  if you want. 
	 * 
	 * @param layerIndex the index of the render layer you want to assign
	 */
	void SetLayer(int layerIndex);
	
	/**
	 * Set a new rendering layer for this Actor by the name of the layer. 
	 * 
	 * The name of the layer has to be set up first by calling 
	 *  World::NameLayer. If you pass an invalid layer name, this Actor will 
	 *  be put on layer 0. 
	 * 
	 * @see SetLayer
	 * @param layerName the name of the render layer you want to assign
	 */
	void SetLayer(const String& layerName);
	
	/**
	 * A function which makes the necessary updates to the Actor. The base 
	 *  implementation just updates the animations and intervals, but a 
	 *  subclass override can perform whatever extra magic is necessary. Make 
	 *  sure to call the base class's Update if you subclass. 
	 * 
	 * @param dt The amount of time that's elapsed since the beginning of the 
	 *   last frame. 
	 */
	virtual void Update(float dt);
	
	/**
	 * A function to draw the Actor to the screen. By default, this does the 
	 *  basic drawing based on the texture, color, shape, size, position, and 
	 *  rotation that have been applied to the Actor. Can be overridden in a 
	 *  subclass if necessary. 
	 * 
	 * This will get called on every Actor once per frame, after the #Update. 
	 */
	virtual void Render();
	
	/** 
	 * Called for every actor that doesn't get unloaded in World::UnloadAll().
	 * This is a good place to clear out any cached pointers, etc.
	 */
	virtual void LevelUnloaded() {}
	
	/**
	 * Yes, this looks pointless and redundant. But it has a function for the 
	 *  scripting layer -- it activates the inheritance downcasts so you can
	 *  get a derived object from its base pointer.
	 * 
	 * In most instances, an Actor* getting thrown to the script layer will be
	 *  wrapped correctly as a PhysicsActor, TextActor, etc. BUT, if it's
	 *  coming from an STL container, then it won't. Rather than trying to 
	 *  fiddle with the SWIG typemaps which wrap the STL, this solution is 
	 *  more robust. It does require an extra call in the script, but c'est la 
	 *  vie.
	 * 
	 * @return the Actor's "this" pointer
	 */
	Actor* GetSelf()
	{
		return this;
	}
	
	/**
	 * Create an Actor from an archetype defined in a .lua file in 
	 *  Config/ActorDef. Automatically adds the Actor to the World. 
	 * 
	 * The table names in the .lua files designate the name of the archetype, 
	 *  while the values in each table specify the properties for that 
	 *  archetype. Any function that can be called on an Actor can be used as 
	 *  a property -- things like SetSize can be called simply "size." 
	 * 
	 * Colors and Vectors can be defined as tables, so the following 
	 *  definition is valid. 
	 * 
	 * \code
	 * my_actor = {
	 *   color = {1, 0, 1},
	 *   alpha = 0.5,
	 *   size = 5,
	 * }
	 * \endcode
	 * 
	 * @param archetype the name of the Actor archetype (the table name from 
	 *   the .lua file)
	 */
	static Actor* Create(const String& archetype);
	
	/**
	 * This static function is used internally by the scripting layer to
	 *  let the core engine get at Actors that created in script. If that
	 *  doesn't make complete sense to you, you probably have no need to
	 *  call this function. 
	 * 
	 * @param a The actor that was just created in script
	 */
	static void SetScriptCreatedActor(Actor* a) { _scriptCreatedActor = a; }

	/**
	 * Used by the SetName function to create a basename for this class. 
	 *  Overridden in derived classes.
	 * 
	 * @return The string "Actor"
	 */
	virtual const String GetClassName() const { return "Actor"; }
	
protected:
	Vector2 _size;
	Vector2 _position;
	Color _color;
	float _rotation;
	
	float _UV[8];
	
	actorDrawShape _drawShape;
	static const float _squareVertices[];
	static float _circleVertices[];
	static float _circleTextureCoords[];

	int					_spriteCurrentFrame;
	int					_spriteNumFrames;
	float				_spriteFrameDelay;
	float				_spriteCurrentFrameDelay;
	int					_spriteTextureReferences[MAX_SPRITE_FRAMES];
	spriteAnimationType _spriteAnimType;
	int					_spriteAnimStartFrame;
	int					_spriteAnimEndFrame;
	int					_spriteAnimDirection;
	int					_displayListIndex;

	StringSet _tags;

	String _name;
	static std::map<String, Actor*> _nameList;

	String _currentAnimName;
	static Actor* _scriptCreatedActor;

private:
	void SetSpriteTexture(int texRef, int frame = 0);
	void UpdateSpriteAnimation(float dt);
	
	Interval<Vector2> _positionInterval; String _positionIntervalMessage;
	Interval<float> _rotationInterval; String _rotationIntervalMessage;
	Interval<Color> _colorInterval; String _colorIntervalMessage;
	Interval<Vector2> _sizeInterval; String _sizeIntervalMessage;
};

typedef std::vector<Actor*>		ActorList;
typedef std::set<Actor*>		ActorSet;

