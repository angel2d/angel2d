#include "../Actors/ActorFactory.h"

#include "../Actors/ParticleActor.h"
#include "../Actors/Actor.h"
#include "../Infrastructure/DeveloperConsole.h"
#include "../Infrastructure/World.h"
#include "../Physics/PhysicsActor.h"
#include "../Physics/PhysicsEventActor.h"
#include "../AI/Sentient.h"
#include "../Util/StringUtil.h"


ActorFactory *ActorFactory::s_ActorFactory = NULL;

ActorFactory &ActorFactory::GetInstance()
{
	if( s_ActorFactory == NULL )
	{
		s_ActorFactory = new ActorFactory();
		s_ActorFactory->Initialize();
	}
	return *s_ActorFactory;
}

void ActorFactoryBeginActor( const String& input )
{
	StringList vals = SplitString( input );

	if( vals.size() < 1 )
		return;

	theActorFactory.BeginActor( vals[0], 1);
}

void ActorFactoryEndActor( const String& /*input*/ )
{
	theActorFactory.EndActor();
}

void ActorFactoryInitializeActorClass( const String& input )
{
	theActorFactory.InitializeActor(TrimString(input));
}

void AF_LoadLevel( const String& input )
{
	String levelName = TrimString( input );
	
	if( levelName.size() == 0 )
		return;

	//TODO: get accessor for level dir
	theDevConsole.ExecuteFile( String("Config/Level/" + levelName + ".lvl" ) );

}

void ActorFactory::Initialize()
{
	//TODO: Setup console commands
	CONSOLE_DECLARECMDSTATICFLAGS( BeginActor, ActorFactoryBeginActor, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( EndActor, ActorFactoryEndActor, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactoryInitializeActorClass, ActorFactoryInitializeActorClass, ConsoleCommand::CCF_CONFIG );

	CONSOLE_DECLARECMDSTATIC( AF_LoadLevel, AF_LoadLevel );


	//Add delegates
	AddActorFactoryDelegate( "ACTOR", new ActorFactoryDelegate() );
	AddActorFactoryDelegate( "PHYSICSACTOR", new PhysicsActorFactoryDelegate() );
	AddActorFactoryDelegate( "PHYSICSEVENTACTOR", new PhysicsEventActorFactoryDelegate() );
	AddActorFactoryDelegate( "SENTIENT", new SentientFactoryDelegate() );
	AddActorFactoryDelegate( "PARTICLEACTOR", new ParticleActorFactoryDelegate() );
}

void ActorFactory::Destroy()
{
	if( s_ActorFactory != NULL )
	{
		delete s_ActorFactory;
		s_ActorFactory = NULL;
	}
}

void ActorFactory::AddActorFactoryDelegate( const String& className, ActorFactoryDelegate* del )
{
	String useName = ToUpper(className);
	ActorFactoryDelegate* foundDelegate = FindDelegate(useName);
	if( foundDelegate != NULL )
		delete foundDelegate;

	_factoryDelegateTable[useName] = del;

	del->RegisterOriginalConsoleCommands();
}

void ActorFactory::BeginActor( String actorDefFile, int /*layer*/ )
{
	actorDefFile = TrimString(actorDefFile);

	if( actorDefFile.size() == 0 )
		return;

	//Execute file
	//TODO: get accessor for actor def dir
	theDevConsole.ExecuteFile( String("Config//ActorDef//" + actorDefFile + ".adf" ) );

}

void ActorFactory::InitializeActor( const String& className )
{

	_currentDelegate = FindDelegate(className);
	if( _currentDelegate == NULL )
	{
		//TODO: Log error
		return;
	}

	_currentDelegate->InitializeDelegate();
	_currentActor = _currentDelegate->CreateInstance();
}

Actor* ActorFactory::EndActor()
{
	if( _currentDelegate == NULL || _currentActor == NULL )
		return NULL;

	_currentDelegate->FinishInstance( _currentActor );

	theWorld.Add(_currentActor, _currentDelegate->_renderLayer);

	Actor* pRetVal = _currentActor;
	_currentActor = NULL;
	_currentDelegate = NULL;

	return pRetVal;
}

Actor* ActorFactory::CreateActor( String actorDefFile, const String& name, int layer=0, void (*CustomInitActor)(Actor*)=NULL )
{
	BeginActor( actorDefFile, layer );
	//TODO: callback to set custom variables
	if( (_currentActor != NULL) && (CustomInitActor != NULL) )
		CustomInitActor(_currentActor);
	Actor* pRetVal = EndActor();
	pRetVal->SetName(name);

	//theWorld.AddSpawnedDuringUpdate( pRetVal, layer );

	return pRetVal;
}



ActorFactoryDelegate* ActorFactory::FindDelegate( const String& className )
{
	String useName = ToUpper(className);

	FactoryDelegateTable::iterator itr = _factoryDelegateTable.find( useName );
	if( itr == _factoryDelegateTable.end() )
		return NULL;

	return itr->second;
}

ActorFactory::ActorFactory()
: _currentDelegate(NULL)
, _currentActor(NULL)
{

}

ActorFactory::~ActorFactory()
{
	//Destroy delegates
	for ( FactoryDelegateTable::iterator itr = _factoryDelegateTable.begin(); itr != _factoryDelegateTable.end(); itr++ )
	{
		delete itr->second;
	}
}
