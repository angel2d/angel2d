/** @file */
#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Renderable.h"
#include "../Infrastructure/Color.h"
#include "../Infrastructure/Interval.h"
#include "../Messaging/Message.h"
#include "../Util/StringUtil.h"

#define MAX_SPRITE_FRAMES 64

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
    ADS_Circle
};

///Basic simulation element for Angel.
/**
 * Actor is the basic unit of simulation in Angel. It's not just an abstract base class -- 
 *  you can actually do a good deal of your game just using plain Actors, depending on how 
 *  you want to structure your logic. 
 *
 * Note that you have to add the Actor to the World if you want to see it on screen. 
 * 
 * If you want to subclass Actor, the two most important functions are #Render and Update,
 *  which will get called on each Actor in the World every frame. 
 */
class Actor : public Renderable, public MessageListener
{
public:
	/**
	 * The constructor doesn't do anything special. It defaults to a square Actor with a 
	 *  side-length of 1.0f, no texture, white, and at the origin. 
	 */
	Actor();
	
	/**
	 * The destructor ensures that the Actor has been unsubscribed from all messages, 
	 *  removed from all tag lists, and purged from the list of unique names. 
	 */
	virtual ~Actor();
	
	/**
	 * Set the size of this Actor. 
	 * 
	 * @param x Horizontal size in OpenGL units -- negative numbers treated as zero
	 * @param y Vertical size in OpenGL units -- if less than or equal to zero, assumed to be equal to x
	 */
	void SetSize(float x, float y = -1.f); 	// equal dimensions by default
	
	/**
	 * Set the size of this Actor. 
	 * 
	 * @param newSize Desired size of Actor in OpenGL units. If either dimension is negative, it's 
	 *  clamped to zero. 
	 */
	void SetSize(Vector2 newSize);
	
	/**
	 * Return the size of this Actor.
	 * 
	 * @return Actor's size as a Vector2
	 */
	const Vector2 GetSize();
	
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
	virtual void SetPosition(Vector2 pos);
	
	/**
	 * Return the position of this Actor.
	 * 
	 * @return Actor's position as a Vector2
	 */
	const Vector2 GetPosition();
	
	/**
	 * Sets the rotation of the Actor. Positive rotations are counter-clockwise.
	 * 
	 * @param rotation Desired rotation in degrees
	 */
	void SetRotation(float rotation);
	
	/**
	 * Return the rotation of this Actor.
	 * 
	 * @return Actor's rotation
	 */
	const float GetRotation();
	
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
	void SetColor(Color color);
	
	/**
	 * Return the Color of this Actor.
	 * 
	 * @return Actor's current color as a Color object
	 */
	const Color GetColor();
	
	/**
	 * Set the transparency of the Actor, independent of the other color components.
	 * 
	 * @param newAlpha Desired transparency (1.0f is opaque, 0.0f is invisible)
	 */
	void SetAlpha(float newAlpha);
	
	/**
	 * Get current transparency for this Actor.
	 * 
	 * @return Actor's current transparency value.
	 */
	const float GetAlpha();
	
	/**
	 * Set the shape of the Actor when it's drawn.
	 * 
	 * @see actorDrawShape
	 * @param drawShape Desired shape
	 */
	void SetDrawShape( actorDrawShape drawShape );
	
	/**
	 * Get the current shape of this Actor.
	 *
	 * @return Actor's shape
	 */
	const actorDrawShape GetDrawShape();
	
	/**
	 * A "fire and forget" function that moves an Actor to a new position over a 
	 *  designated amount of time. This lets you handle movements without having 
	 *  to set up your own timers and keep track of them yourself. At the moment,
	 *  it's limited to purely linear movement. 
	 * 
	 * @see RotateTo
	 * @see ChangeColorTo
	 * @see ChangeSizeTo
	 * @param newPosition The target position for the movement
	 * @param duration How long it should take to get there
	 * @param onCompletionMessage If specified, a Message of this type will be sent 
	 *  when the movement is complete, letting you know when it's done. You will
	 *  have to manually subscribe to this Message, though. 
	 */
	void MoveTo(Vector2 newPosition, float duration, String onCompletionMessage="");
	
	/**
	 * A "fire and forget" function that rotates an Actor over a designated amount
	 *  of time. 
	 * 
	 * @see MoveTo
	 * @param newRotation The target rotation
	 * @param duration How long it should take
	 * @param onCompletionMessage the type of Message to be sent on completion
	 */
	void RotateTo(float newRotation, float duration, String onCompletionMessage="");
	
	/**
	 * A "fire and forget" function that changes an Actor's color over a designated 
	 *  amount of time. 
	 * 
	 * @see MoveTo
	 * @param newColor The target color
	 * @param duration How long it should take
	 * @param onCompletionMessage the type of Message to be sent on completion
	 */
	void ChangeColorTo(Color newColor, float duration, String onCompletionMessage="");
	
	/**
	 * A "fire and forget" function that changes an Actor's size over a designated 
	 *  amount of time. This version uses a Vector2 if you want to set a non-uniform
	 *  target size.
	 * 
	 * @see MoveTo
	 * @param newSize The target size
	 * @param duration How long it should take
	 * @param onCompletionMessage the type of Message to be sent on completion
	 */
	void ChangeSizeTo(Vector2 newSize, float duration, String onCompletionMessage="");
	
	/**
	 * A "fire and forget" function that changes an Actor's size over a designated 
	 *  amount of time.
	 * 
	 * @see MoveTo
	 * @param newSize The target size
	 * @param duration How long it should take
	 * @param onCompletionMessage the type of Message to be sent on completion
	 */
	void ChangeSizeTo(float newSize, float duration, String onCompletionMessage="");
		
	const int GetSpriteTexture(int frame = 0);
	
	bool SetSprite(String filename, int frame = 0, GLint clampmode = GL_CLAMP, GLint filtermode = GL_LINEAR, bool optional=0);
	void ClearSpriteInfo();
	void LoadSpriteFrames(String firstFilename, GLint clampmode = GL_CLAMP, GLint filtermode = GL_LINEAR);
	void PlaySpriteAnimation(float delay, spriteAnimationType animType = SAT_Loop, int startFrame = -1, int endFrame = -1, const char* _animName = NULL); //rb - TODO - Add a way to associate anim type, and frame indices to a name.
	void SetSpriteFrame(int frame);
	void UpdateSpriteAnimation(float dt);
	bool IsSpriteAnimPlaying()
	{
		return (_spriteFrameDelay > 0);
	}
	void SetUVs(const Vector2 upright, const Vector2 lowleft);
	void GetUVs(Vector2 &upright, Vector2 &lowleft) const;
	
	/**
	 * Returns whether or not this Actor has been given a particular tag. 
	 * 
	 * @see TagCollection
	 * @param tag the tag in question
	 * @return True if the Actor has the tag
	 */
	const bool IsTagged(String tag);
	
	/**
	 * Adds a tag to an Actor. If the Actor already has this tag, no action is taken.
	 * 
	 * @see TagCollection
	 * @param newTag The tag to add
	 */
	void Tag(String newTag);
	
	/**
	 * Removes a tag from an Actor. If the Actor doesn't have this tag, no action is taken.
	 * 
	 * @see TagCollection
	 * @param oldTag The tag to remove
	 */
	void Untag(String oldTag);
	
	/**
	 * Get all the tags for this ACtor. 
	 * 
	 * @see TagCollection
	 * @return A StringSet (std::vector<std::string>) of all the Actor's tags
	 */
	const StringSet GetTags();
	
	/**
	 * Give this Actor a name that can later be used as a unique identifier. The 
	 *  the actual name given may differ from what is passed in, but is guaranteed
	 *  to be unique. (Numbers will be appended until the name is distinct.)
	 * 
	 * @param newName The desired name
	 * @return The actual name that was given
	 */
	const String SetName(String newName);
	
	/**
	 * Get the unique name assigned to this Actor.
	 * 
	 * @return The Actor's current name.
	 */
	const String GetName();
	
	/**
	 * A static function of the Actor class which returns an Actor from a name.
	 * 
	 * @param nameLookup The name index to look for
	 * @return The Actor with the given name. Will be NULL if there's no match
	 */
	static const Actor* GetNamed(String nameLookup);
	
	/**
	 * An implementation of the MessageListener interface, which will be called
	 *  when a message gets delivered. 
	 * 
	 * There is no actual implementation in the base class, but you can override
	 *  in the subclass. 
	 * 
	 * @see MessageListener
	 * @param message The message getting delivered. 
	 */
	virtual void ReceiveMessage(Message* message) {}
	
	virtual void OnCollision(Actor* other);
	
	/**
	 * Set a new rendering layer for this Actor. 
	 * 
	 * Layers are ordered from bottom to top by index. No space is wasted by leaving
	 *  empty layers in between, so feel free to pad out your indices if you want. 
	 * 
	 * @param layerIndex the index of the render layer you want to assign
	 */
	void SetLayer(int layerIndex);
	
	/**
	 * Set a new rendering layer for this Actor by the name of the layer. 
	 * 
	 * The name of the layer has to be set up first by calling World::NameLayer. 
	 *  If you pass an invalid layer name, this Actor will be put on layer 0. 
	 * 
	 * @see SetLayer
	 * @param layerName the name of the render layer you want to assign
	 */
	void SetLayer(String layerName);
	
	/**
	 * A function which makes the necessary updates to the Actor. The base implementation
	 *  just updates the animations and intervals, but a subclass override can perform
	 *  whatever extra magic is necessary. Make sure to call the base class's Update
	 *  if you subclass. 
	 * 
	 * @param dt The amount of time that's elapsed since the beginning of the last frame. 
	 */
	virtual void Update(float dt);
	
	/**
	 * A function to draw the Actor to the screen. By default, this does the basice
	 *  drawing based on the texture, color, shape, size, position, and rotation 
	 *  that have been applied to the Actor. Can be overridden in a subclass if 
	 *  necessary. 
	 * 
	 * This will get called on every Actor once per frame, after the #Update. 
	 */
	virtual void Render();
	
	virtual void AnimCallback(String /*animName*/) {}
	
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
	 *  fiddle with the SWIG typemaps which wrap the STL, this solution is more
	 *  robust. It does require an extra call in the script, but c'est la vie.
	 * 
	 * @return the Actor's "this" pointer
	 */
	Actor* GetSelf()
	{
		return this;
	}
	
	/**
	 * Create an Actor from an archetype defined in an .ini file in 
	 *  Config/ActorDef. Automatically adds the Actor to the World. 
	 * 
	 * The section titles in the .ini files designate the name of the archetype,
	 *  while the values in each section specify the properties for that 
	 *  archetype. Any function that can be called on an Actor can be used
	 *  as a property -- things like SetSize can be called simply "size." 
	 * 
	 * Colors and Vectors can be defined as arrays, so the following definition
	 *  is valid. 
	 * 
	 * \code
	 * [my_actor]
	 * color=[1, 0, 1]
	 * alpha=0.5
	 * size=5
	 * \endcode
	 * 
	 * @param the name of the Actor archetype (the section header from the .ini)
	 */
	static Actor* Create(String archetype);

protected:
	Vector2 _size;
	Vector2 _position;
	Color _color;
	float _rotation;

	Vector2 UV_rightup;
	Vector2 UV_leftlow;

    actorDrawShape _drawShape;

	int					_spriteCurrentFrame;
	int					_spriteNumFrames;
	float				_spriteFrameDelay;
	float				_spriteCurrentFrameDelay;
	int					_spriteTextureReferences[MAX_SPRITE_FRAMES];
	spriteAnimationType _spriteAnimType;
	int					_spriteAnimStartFrame;
	int					_spriteAnimEndFrame;
	int					_spriteAnimDirection;

	StringSet _tags;

	String _name;
	static std::map<String, Actor*> _nameList;

	String _currentAnimName;

private:
	void SetSpriteTexture(int texRef, int frame = 0);
	
	Interval<Vector2> _positionInterval; String _positionIntervalMessage;
	Interval<float> _rotationInterval; String _rotationIntervalMessage;
	Interval<Color> _colorInterval; String _colorIntervalMessage;
	Interval<Vector2> _sizeInterval; String _sizeIntervalMessage;
};

typedef std::vector<Actor*>		ActorList;
typedef std::set<Actor*>		ActorSet;

