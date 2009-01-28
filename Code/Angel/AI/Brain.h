#pragma once

#include "../Infrastructure/Common.h"
#include "../Util/StringUtil.h"

class AIBrainState;
class Sentient;

class AIBrain
{
	typedef hashmap_ns::hash_map<String, AIBrainState*> BrainStateTable;
public:
	AIBrain();
	void SetActor( Sentient* actor ) {_actor = actor;}

	virtual ~AIBrain();

	virtual void AddState( const String& id, AIBrainState* state );
	
	virtual void Update( float dt);
	virtual void GotoState( const String& id );

	Sentient* GetActor() {return _actor;}

	void Render();
	void GotoNullState();

protected:
	BrainStateTable		_brainStateTable;
	BrainStateTable::iterator _current;
	Sentient*			_actor;
};


class AIEvent;

/*abstract*/ class AIBrainState
{
	typedef std::vector<AIEvent*> EventList;
public:
	virtual ~AIBrainState() {}
	virtual void Initialize( AIBrain* brain ) {_brain = brain;}
	void Update(float dt);
	virtual void CustomUpdate(float /*dt*/) {}
	virtual void BeginState( AIBrainState* /*previousState*/ ) {}
	void EndState( AIBrainState* nextState );
	virtual void CustomEndState( AIBrainState* /*nextState*/ ) {}

protected:
	virtual void GotoState( const String& id );
	virtual AIEvent* RegisterEvent( AIEvent* newEvent );
	virtual void UnregisterEvent( AIEvent* oldEvent );
	Sentient* GetActor() {return _brain->GetActor();}
private:
	void ClearEvents();
	void StopEvent( AIEvent* pEvent );
protected:
	AIBrain*		_brain;
	EventList		_eventList;
};


#define DECLARE_AISTATE(cls) \
	typedef cls MyClass;


#define DECLARE_BASESTATE( BaseStateID, StateDataType ) \
class BaseStateID : public AIBrainState \
{ \
public: \
	BaseStateID( StateDataType& _StateData ) \
	: StateData(_StateData) \
{} \
protected: \
	StateDataType& StateData; \
};

#define DECLARE_SHAREDDATASTATE( ThisStateID, BaseStateID, StateDataType ) \
	DECLARE_AISTATE(ThisStateID) \
	ThisStateID( StateDataType& _StateData ) \
	: BaseStateID( _StateData ) \
{}


/*abstract*/ class AIEvent
{
public:
	virtual ~AIEvent() {}
	virtual void Stop() {}
	virtual void Update(float /*dt*/) {}

	void SetBrain( AIBrain* pBrain ) {_brain = pBrain;}

protected:
	AIBrain* GetBrain() {return _brain;}
	Sentient* GetActor() {return _brain->GetActor();}
	virtual void IssueCallback() {}
private:
	AIBrain*	_brain;
};

#define REGISTER_AIEVENT( ev, cb, params ) \
	((ev##Template<MyClass>*)this->RegisterEvent( new ev##Template<MyClass>(this, &MyClass::cb) ))->Initialize params

#define UNREGISTER_AIEVENT(oldEvent) \
	UnregisterEvent(oldEvent)
	

#define DECLARE_AIEVENT_BASE( FromClass ) \
template<class T> \
class FromClass##Template : public FromClass \
{ \
public: \
	typedef void(T::*AIBrainStateCallback)( FromClass* newEvent ); \
	FromClass##Template( T* cbObj, AIBrainStateCallback cb ) \
		: _cbObj(cbObj) \
		, _cb(cb) \
	{} \
protected: \
	virtual void IssueCallback()\
	{ \
		(*_cbObj.*_cb)(this); \
	} \
private: \
	T*						_cbObj; \
	AIBrainStateCallback	_cb; \
};

