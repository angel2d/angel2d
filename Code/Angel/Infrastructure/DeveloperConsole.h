#pragma once

#include "../Util/StringUtil.h"
#include "../Infrastructure/Console.h"
#include "../Infrastructure/ValueCache.h"
#include "../Infrastructure/Log.h"
#include "../Infrastructure/Vector2.h"

//Forward decl
class ConsoleVariable;
class ConsoleCommand;
class ConsoleItemManager;

/*abstract*/ class ConsoleItem
{
public:
	ConsoleItem( String id )
	: _id(id)
	, _flags(0)
	{

	}
	virtual ~ConsoleItem() {}

	const String& GetId() {return _id;}
	virtual String GetFullDescription() {return GetId();}

	void SetFlag( int flag );
	void ClearFlag( int flag );
	bool HasFlag( int flag );

	virtual bool IgnoreForAutoComplete() {return false;}

protected:
	String _id;
	int _flags;
};

#if defined(WIN32)
	#pragma warning(push)
	#pragma warning(disable:4355)
#endif
class ConsoleVariable : public ConsoleItem
{
private:
	//We can only be newed by console item manager
	friend class ConsoleItemManager;
	ConsoleVariable( String id )
	: ConsoleItem(id)
	, _floatCache( CREATE_VALUECACHE_FUNCTOR( float, ConsoleVariable, this, UpdateCachedFloat) )
	, _intCache( CREATE_VALUECACHE_FUNCTOR( int, ConsoleVariable, this, UpdateCachedInt) )
	, _vectorCache( CREATE_VALUECACHE_FUNCTOR( Vector2, ConsoleVariable, this, UpdateCachedVector ) )
	{
	}

	~ConsoleVariable() {}

public:

	enum CVarFlags
	{
		CVF_CONFIG = 0x1,
		CVF_READONLY = 0x2,
	};

	String GetStringVal()				{return _stringVal;}
	float GetFloatVal()				{return _floatCache.Value();}
	int GetIntVal()					{return _intCache.Value();}
	const Vector2& GetVector2Val()	{return _vectorCache.Value();}

	bool HasVal()					{return _stringVal.length() > 0;}

	void SetStringVal(String val);
	void SetFloatVal(float val);
	void SetIntVal(int val);
	void SetVector2Val( const Vector2& val );

	virtual String GetFullDescription();

	String Serialize();
	void DeserializeParams( const StringList& params );

	//Macro funcs
	String _Str()					{return GetStringVal();}
	float _float()				{return GetFloatVal();}
	int _int()					{return GetIntVal();}
	const Vector2& _Vector2()	{return GetVector2Val();}

private:
	String GetDescInternal( bool toFile = false );
	void UpdateCachedFloat( float& val );
	void UpdateCachedInt( int& val );
	void UpdateCachedVector( Vector2& val );

	void DirtyCache();

private:

	String _stringVal;
	ValueCache<float, ConsoleVariable> _floatCache;
	ValueCache<int, ConsoleVariable> _intCache;
	ValueCache<Vector2, ConsoleVariable> _vectorCache;

};
#if defined(WIN32)
	#pragma warning(pop)
#endif

class CCmdMemberFunctorOwner
{
public:
	CCmdMemberFunctorOwner() : _consoleItemMgr(NULL) {}
	~CCmdMemberFunctorOwner();
	void SetConsoleItemManager( ConsoleItemManager* pMgr );

private:
	ConsoleItemManager* _consoleItemMgr;
};


class ConsoleCommand : public ConsoleItem
{
private:
	friend class ConsoleItemManager;
public:
	enum CCmdFlags
	{
		CCF_CONFIG = 0x1,
	};

	class Functor
	{
	public:
		virtual ~Functor() {}
		virtual void Execute(const String& input) = 0;
		virtual bool BoundToObjectHash( CCmdMemberFunctorOwner* /*funcOwner*/ ) {return false;}
		virtual void UpdateMemberFunctorOwner(ConsoleItemManager* /*mgr*/) {}
	};

	class StaticFunctor : public Functor
	{
	public:
		StaticFunctor( void (*fpt)(const String&) )
		: _delegate(fpt)
		{}

		virtual void Execute(const String& input)
		{
			if( _delegate )
				(*_delegate)(input);
		}
	private:
		void (*_delegate)(const String&);
	};

	template<class T>
	class MemberFunctor : public Functor
	{
	public:
		MemberFunctor( T* obj, void(T::*fpt)( const String& ) )
		{
			_obj = obj;
			_delegate = fpt;
		}

		~MemberFunctor() {_obj->SetConsoleItemManager(NULL);}

		void Execute(const String& input)
		{
			if( _obj != NULL)
				(*_obj.*_delegate)(input);
		}
		virtual bool BoundToObjectHash( CCmdMemberFunctorOwner* funcOwner ) {return funcOwner == _obj;}
		virtual void UpdateMemberFunctorOwner(ConsoleItemManager* mgr) { _obj->SetConsoleItemManager(mgr); }
	private:
		T* _obj;
		void (T::*_delegate)( const String& );

	};

	virtual ~ConsoleCommand();

	void Execute( const String& input );
	
	virtual bool IgnoreForAutoComplete() {return HasFlag(CCF_CONFIG);}
private:
	ConsoleCommand( String id, Functor* fptr, ConsoleItemManager* mgr );
	bool BoundToObjectHash( CCmdMemberFunctorOwner* memHash );
private:
	Functor* _command;
};


class ConsoleItemManager
{
	typedef hashmap_ns::hash_map<String, ConsoleVariable*> CVarTable;
	typedef hashmap_ns::hash_map<String, ConsoleCommand*> CCmdTable;
public:
	~ConsoleItemManager();

	ConsoleVariable* GetCVar( const String& id );
	ConsoleVariable* FindCVar( const String& id );

	void AddCCmd( const String& id, ConsoleCommand::Functor* command, int flags );
	bool ExecuteCCmd( const String& id, const String& input );

	void RemoveCCmdsBoundTo( CCmdMemberFunctorOwner* owner );

	void GetConsoleItemIds( const String& againstSubstring, StringList& out_ids );
	void SerializeConfigCVars( StringList& configCvars );
	void GetConsoleCommandIds( const String& againstSubstring, StringList& out_ids );
	void GetConsoleVariableIds( const String& againstSubstring, StringList& out_ids );
private:

	ConsoleVariable* GetCVarInternal( const String& id );
	ConsoleVariable* CreateConsoleVariable( const String& id );

private:
	CVarTable _cvarTable;
	CCmdTable _ccmdTable;

};

#define CONSOLE_GETVAR( cvar ) \
	theDevConsole.GetConsoleItemManager().GetCVar( cvar );

#define CONSOLE_DECLAREVAR( cvar ) \
	static ConsoleVariable* cvar = CONSOLE_GETVAR( #cvar )

#define CONSOLE_ONCVARCHANGED( cvar, type, func ) \
{ \
	CONSOLE_DECLAREVAR(cvar); \
	static type _cvarNewVal; \
	static type _cvarOldVal; \
	if( cvar->HasVal() && cvar->_##type () != _cvarNewVal ) \
	{ \
		_cvarOldVal = _cvarNewVal; \
		_cvarNewVal = cvar->_##type (); \
		func; \
	} \
}

#define CONSOLE_DECLARECCMDINTERNAL( ccmd, functor, flags ) \
	theDevConsole.GetConsoleItemManager().AddCCmd( #ccmd, functor, flags );

#define CONSOLE_DECLARECMDSTATIC( ccmd, func ) \
	CONSOLE_DECLARECMDSTATICFLAGS( ccmd, func, 0 )

#define CONSOLE_DECLARECMDMETHOD( ccmd, obj, class, func ) \
	CONSOLE_DECLARECMDMETHODFLAGS( ccmd, obj, class, func, 0 )

#define CONSOLE_DECLARECMDSTATICFLAGS( ccmd, func, flags ) \
	CONSOLE_DECLARECCMDINTERNAL( ccmd, new ConsoleCommand::StaticFunctor(func), flags )

#define CONSOLE_DECLARECMDMETHODFLAGS( ccmd, obj, class, func, flags ) \
	CONSOLE_DECLARECCMDINTERNAL( ccmd, new ConsoleCommand::MemberFunctor<class>(obj, &class::func), flags )


#define theDevConsole DeveloperConsole::GetInstance()

class DeveloperConsole : public Console, public CCmdMemberFunctorOwner
{
public:
	static DeveloperConsole &GetInstance();
	void Destroy();

	ConsoleItemManager& GetConsoleItemManager()	{return _consoleItemManager;}

	virtual void Execute( String input );
	virtual StringList GetCompletions(String input) { return StringList(); }
	void ExecuteFile( const String& fileName );
	void ExecConfigFile( const String& fileName );
	void CCmdList( const String& filter );
	void CVarList( const String& filter );
	void Echo( const String& input );
	bool IsReadingConfigFile() {return _inConfigFileOp;}
	void WriteConfigCvars();

	void SetSilence(bool silence) { _silenced = silence; }

	void AddToConsoleLog( const String& input );
	void AddToConsoleLog( StringList& refList );
private:
	bool IsTextKey(unsigned char key);
	void AcceptCurrentInput();
	void AcceptAutocomplete();
	void Initialize();
	void ToggleConsole( const String& input );
	void DeclareCVar( const String& input );
	void UpdateInputHistory( const String& input );
	StringList::iterator GetInputHistoryPos( const String& input );
	void AdvanceInputHistory( int byVal );
	void AdvanceConsoleLog( int byVal );
	void UpdateAutoComplete();
	void SetCurrentInput( const String& newVal );

protected:
	DeveloperConsole();
	static DeveloperConsole *s_Console;

private:
	bool					_enabled;
	ConsoleItemManager		_consoleItemManager;
	ConsoleLog				_consoleLog;
	int						_consoleLogPos;
	String					_currentInput;
	StringList				_inputHistory;
	int						_inputHistoryPos;
	bool					_inConfigFileOp;

	StringList				_autoCompleteList;
	
	bool					_silenced;

};

