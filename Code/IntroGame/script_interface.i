// This file gets automatically pulled in by SWIG when it creates the mappings
//  from the Angel engine to Lua. All relevant Angel classes are already mapped,
//  but classes that you define need to be exposed also if you want to use them
//  in ActorDef or Level files (since both of those rely on Lua scripting for 
//  their magic.)

#ifndef ANGEL_MOBILE
%module angel  // makes sure we're able to properly inherit from Angel classes
%{
// Any header files that define classes should be here. 
//  Note the paths, which are relative to Angel/Scripting/Interfaces/angel.i
//  (the central wrapping file). 
#include "../../../IntroGame/DemoScreens/DemoScreenPathfinding.h"
%}

// The full declaration of MazeFinder is copied in a comment block below. 
//  To expose a class to SWIG, you just need to declare its relevant inheritance
//  and methods here. 
//
// Note that by default private and protected functions will not be wrapped. 
//  In this example, we've only wrapped the constructor, since we don't plan on
//  calling any of MazeFinder's unique functions from script. 
//
// SWIG is very flexible, but it can also be a bit fragile if you feed it datatypes
//  that it doesn't understand. For more information, check the SWIG documentation
//  (http://www.swig.org/Doc1.3/) and the Scripting/Interfaces directory. 
class MazeFinder : public Actor
{
public:
	MazeFinder();
};
#endif

/*
class MazeFinder : public Actor
{
public:
	MazeFinder();
	void GoTo(Vector2 newDestination);
	virtual void Render();
	virtual void ReceiveMessage(Message *message);
	
	void ToggleDrawPath(bool draw);
	
private:
	Vector2List _pathPoints;
	unsigned int _pathIndex;
	bool _drawPath;
	
	void GetToNextPoint();
};
*/