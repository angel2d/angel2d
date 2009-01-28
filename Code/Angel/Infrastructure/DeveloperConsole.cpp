#include "../Infrastructure/DeveloperConsole.h"

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Camera.h"
#include "../Infrastructure/Vector2.h"
#include "../Infrastructure/TextRendering.h"
#include "../Util/FileUtil.h"
#include "../Util/MathUtil.h"
#include "../Util/StringUtil.h"


void ConsoleItem::SetFlag( int flag )
{
	_flags |= flag;
}

void ConsoleItem::ClearFlag( int flag )
{
	_flags &= ~flag;
}

bool ConsoleItem::HasFlag( int flag )
{
	return (_flags & flag) != 0;
}

void ConsoleVariable::SetStringVal(String val)
{
	//Don't set val if we're readonly
	if( HasFlag(CVF_READONLY) && !theDevConsole.IsReadingConfigFile() )
		return;

	_stringVal = val;
	DirtyCache();

	if( HasFlag(CVF_CONFIG) )
		theDevConsole.WriteConfigCvars();
}

void ConsoleVariable::SetFloatVal(float val)
{
	SetStringVal( FloatToStr(val) );
}

void ConsoleVariable::SetIntVal(int val)
{
	SetStringVal( IntToString(val) );
}

void ConsoleVariable::SetVector2Val( const Vector2& val )
{
	SetStringVal( Vector2ToString(val) );
}


void AddSpaces( int numSpaces, String& toVal )
{
	for( int i = 0; i < numSpaces; i++ )
	{
		toVal += " ";
	}
}

void ConsoleVariable::UpdateCachedFloat( float& val )
{
	val = StringToFloat( _stringVal );
}

void ConsoleVariable::UpdateCachedInt( int& val )
{
	val = StringToInt( _stringVal );
}

void ConsoleVariable::UpdateCachedVector( Vector2& val )
{
	val = StringToVector2( _stringVal );
}


void ConsoleVariable::DirtyCache()
{
	_floatCache.Dirty();
	_intCache.Dirty();
	_vectorCache.Dirty();
}

namespace CvarFlagNames
{
	static String sFlagsKeyword("FLAGS=");
	static String Config("CONFIG");
	static String ReadOnly("READONLY");
}

String ConsoleVariable::GetDescInternal( bool toFile )
{
	String retVal = GetId();
	int valPos = MathUtil::Max( (int)(25 - retVal.length()), 1 );

	AddSpaces( valPos, retVal );

	if( !toFile )
		retVal += "= ";
	String stringVal = GetStringVal();
	retVal += stringVal;

	if( _flags )
	{
		int flagPos = MathUtil::Max( (int)(20 - stringVal.length()), 1 );
		AddSpaces(flagPos, retVal );
		if( toFile )
			retVal += "| ";
		retVal += CvarFlagNames::sFlagsKeyword + " ";
		if( HasFlag(CVF_CONFIG) )
			retVal += CvarFlagNames::Config + " ";
		if( HasFlag(CVF_READONLY) )
			retVal += CvarFlagNames::ReadOnly + " ";

	}
	if( toFile )
		return String("DeclareCVar " ) + retVal;
	return retVal;
}

String ConsoleVariable::GetFullDescription()
{
	return GetDescInternal();
}

String ConsoleVariable::Serialize()
{
	return GetDescInternal(true);
}

void ConsoleVariable::DeserializeParams( const StringList& params )
{
	//Zero'th entry is the cvar decl. We want the next entry
	for( unsigned int i = 1; i < params.size(); i++ )
	{
		String par = ToUpper(TrimString(params[i]));
		if( par.find( CvarFlagNames::sFlagsKeyword ) == 0 )
		{
			//If we found flags at the start
			StringList flags = SplitString(par.substr(CvarFlagNames::sFlagsKeyword.length()));
			for( unsigned int j = 0; j < flags.size(); j++ )
			{
				String flag = ToUpper(flags[j]);
				if( flag == CvarFlagNames::Config )
					SetFlag(CVF_CONFIG);
				else if( flag == CvarFlagNames::ReadOnly )
					SetFlag(CVF_READONLY);
			}
		}
	}
}


CCmdMemberFunctorOwner::~CCmdMemberFunctorOwner()
{
	if( _consoleItemMgr != NULL )
	{
		//Tell the console manager to clean up his act
		_consoleItemMgr->RemoveCCmdsBoundTo( this );
	}

}

void CCmdMemberFunctorOwner::SetConsoleItemManager( ConsoleItemManager* pMgr )
{
	_consoleItemMgr = pMgr;
}


ConsoleCommand::ConsoleCommand( String id, Functor* fptr, ConsoleItemManager* mgr )
: ConsoleItem(id)
, _command(fptr)
{
	if( _command != NULL )
		_command->UpdateMemberFunctorOwner( mgr );

}

bool ConsoleCommand::BoundToObjectHash( CCmdMemberFunctorOwner* memHash )
{
	if( _command != NULL )
		return _command->BoundToObjectHash(memHash);

	return false;
}

ConsoleCommand::~ConsoleCommand()
{
	if( _command != NULL )
		delete _command;
}

void ConsoleCommand::Execute( const String& input )
{
	if( HasFlag(CCF_CONFIG) && !theDevConsole.IsReadingConfigFile() )
		return;

	if( _command )
		_command->Execute( input );
}



ConsoleItemManager::~ConsoleItemManager()
{
	//Delete cvars
	{
		CVarTable::iterator itr = _cvarTable.begin();
		for( ; itr != _cvarTable.end(); itr++ )
		{
			ConsoleVariable* pVar = (*itr).second;
			delete pVar;
		}
		_cvarTable.clear();
	}

	//Delete ccmds
	{
		CCmdTable::iterator itr = _ccmdTable.begin();
		for( ; itr != _ccmdTable.end(); itr++ )
		{
			ConsoleCommand* pCmd  = (*itr).second;
			if( pCmd != NULL )
				delete pCmd;
		}
		_ccmdTable.clear();
	}

}


ConsoleVariable* ConsoleItemManager::GetCVar( const String& id )
{
	String useId = ToUpper( id );
	ConsoleVariable* pCVar = GetCVarInternal( useId );

	if( pCVar != NULL )
		return pCVar;

	return CreateConsoleVariable( useId );
}

ConsoleVariable* ConsoleItemManager::FindCVar( const String& id )
{
	String useId = ToUpper( id );
	ConsoleVariable* pCVar = GetCVarInternal( useId );

	if( pCVar != NULL )
		return pCVar;

	return NULL;
}


void ConsoleItemManager::AddCCmd( const String& id, ConsoleCommand::Functor* command, int flags )
{
	String useId = ToUpper( id );
	CCmdTable::iterator itr = _ccmdTable.find(useId);
	//If it already exists, replace the existing one
	if( itr != _ccmdTable.end() )
	{
		ConsoleCommand* pCmd = (*itr).second;
		if( pCmd != NULL )
			delete pCmd;
	}

	ConsoleCommand* pNewCommand = new ConsoleCommand( useId, command, this );
	pNewCommand->SetFlag( flags );
	_ccmdTable[useId] = pNewCommand;
}

bool ConsoleItemManager::ExecuteCCmd( const String& id, const String& input )
{
	String useId = ToUpper( id );
	CCmdTable::iterator itr = _ccmdTable.find(useId);
	if( itr == _ccmdTable.end() )
		return false;

	ConsoleCommand* pCmd = (*itr).second;
	if( pCmd != NULL )
	{
		pCmd->Execute( input );
		return true;
	}
	return false;
}

void ConsoleItemManager::RemoveCCmdsBoundTo( CCmdMemberFunctorOwner* owner )
{
	CCmdTable::iterator itr = _ccmdTable.begin();
	for( ; itr != _ccmdTable.end(); itr++ )
	{
		ConsoleCommand* pCmd  = (*itr).second;
		if( pCmd != NULL && pCmd->BoundToObjectHash(owner) )
		{
			delete pCmd;
			(*itr).second = NULL;
		}
	}
}

void TryWriteConsoleItemsToList( ConsoleItem* pCItem, const String& againstSubstring, StringList& out_ids )
{
	if( pCItem != NULL && !pCItem->IgnoreForAutoComplete())
	{
		String id = pCItem->GetId().substr(0, MathUtil::Min(againstSubstring.length(), pCItem->GetId().length()) );
		if( againstSubstring == id )
		{
			String compareText = pCItem->GetId();
			String insertText = pCItem->GetFullDescription();
			//Insert sorted
			for( StringList::iterator itr = out_ids.begin(); itr != out_ids.end(); itr++ )
			{
				String& val = *itr;
				if( compareText < val )
				{
					out_ids.insert( itr, insertText );
					return;
				}
			}
			//otherwise, push it on the back
			out_ids.push_back( insertText );
		}
	}
}

void ConsoleItemManager::GetConsoleItemIds( const String& againstSubstring, StringList& out_ids )
{
	if( againstSubstring.length() == 0 )
		return;

	GetConsoleCommandIds( againstSubstring, out_ids );
	GetConsoleVariableIds( againstSubstring, out_ids );
}

void ConsoleItemManager::GetConsoleVariableIds( const String& againstSubstring, StringList& out_ids )
{
	String checkSubst = ToUpper(againstSubstring);
	//check against cvarTable
	for( CVarTable::iterator itr = _cvarTable.begin(); itr != _cvarTable.end(); itr++ )
	{
		ConsoleItem* pCItem  = (*itr).second;
		TryWriteConsoleItemsToList( pCItem, checkSubst, out_ids );
	}
}

void ConsoleItemManager::GetConsoleCommandIds( const String& againstSubstring, StringList& out_ids )
{
	String checkSubst = ToUpper(againstSubstring);
	//check against cmdTable
	for( CCmdTable::iterator itr = _ccmdTable.begin(); itr != _ccmdTable.end(); itr++ )
	{
		ConsoleItem* pCItem = (*itr).second;
		TryWriteConsoleItemsToList( pCItem, checkSubst, out_ids );
	}
}


void ConsoleItemManager::SerializeConfigCVars( StringList& configCvars )
{
	//check against cvarTable
	for( CVarTable::iterator itr = _cvarTable.begin(); itr != _cvarTable.end(); itr++ )
	{
		ConsoleVariable* pCvar = (*itr).second;
		if( pCvar != NULL && pCvar->HasFlag(ConsoleVariable::CVF_CONFIG) )
		{
			configCvars.push_back( pCvar->Serialize() );
		}
	}

}


ConsoleVariable* ConsoleItemManager::GetCVarInternal( const String& id )
{
	CVarTable::iterator itr = _cvarTable.find( id );
	if( itr == _cvarTable.end() )
		return NULL;

	return (*itr).second;

}

ConsoleVariable* ConsoleItemManager::CreateConsoleVariable( const String& id )
{
	ConsoleVariable* pNewVar = new ConsoleVariable( id );
	//Add to map
	_cvarTable[id] = pNewVar;

	return pNewVar;
}


DeveloperConsole *DeveloperConsole::s_Console = NULL;

DeveloperConsole &DeveloperConsole::GetInstance()
{
	if( s_Console == NULL )
	{
		s_Console = new DeveloperConsole();
		s_Console->Initialize();
	}
	return *s_Console;
}

void DeveloperConsole::Destroy()
{
	if( s_Console != NULL )
	{
		delete s_Console;
		s_Console = NULL;
	}
}


DeveloperConsole::DeveloperConsole()
: _enabled(false)
, _consoleLogPos(0)
, _inputHistoryPos(0)
, _inConfigFileOp(false)
{
	SetPrompt("<) ");
	_silenced = false;
}

bool DeveloperConsole::IsTextKey(unsigned char key)
{
	if( key >= ' ' && key <= '}' )
		return true;

	return false;

}

void DeveloperConsole::ExecuteFile(const String& fileName)
{
	//Readonly writes are allowed during config file load
	bool bCached = _inConfigFileOp;
	_inConfigFileOp=true;
	char commentChar = ';';
	StringList lines;
	if( GetLinesFromFile(fileName, lines ) )
	{
		//Ignore commented lines (and partial lines)
		StringList::iterator itr = lines.begin();
		for( ; itr != lines.end(); itr++ )
		{
			const String& line = *itr;

			String consoleInput = TrimString( line );
			//If this line starts with commentChar, skip it
			if( consoleInput.length() == 0 || consoleInput[0] == commentChar )
				continue;

			//Otherwise, check to see if there's a trailing comment
			StringList commentSplit = SplitString( consoleInput, String() + commentChar );
			consoleInput = commentSplit[0];

			Execute( consoleInput );
		}
	}
	else
	{
		AddToConsoleLog( String("Couldn't open file: ") + fileName );
	}

	_inConfigFileOp=bCached;
}

void DeveloperConsole::ExecConfigFile( const String& fileName )
{
	//TODO: get accessor for config dir
	ExecuteFile( String("Config//" + fileName + ".cfg" ) );
}

void DeveloperConsole::CCmdList( const String& filter )
{
	StringList out_list;

	String trimmed = TrimString(filter);

	_consoleItemManager.GetConsoleCommandIds( trimmed, out_list );
	AddToConsoleLog( out_list );
	AddToConsoleLog( " " );
	AddToConsoleLog( " " );
	AddToConsoleLog( "-------------" );
	if( trimmed.length() > 0 )
		AddToConsoleLog( "Listing all ConsoleCommands that begin with " + trimmed );
	else
		AddToConsoleLog( "Listing all ConsoleCommands");
	AddToConsoleLog( " " );
	AddToConsoleLog( " " );

}

void DeveloperConsole::Echo(const String& input )
{
	AddToConsoleLog( input );
}

void DeveloperConsole::CVarList( const String& filter )
{
	StringList out_list;

	String trimmed = TrimString(filter);

	_consoleItemManager.GetConsoleVariableIds( trimmed, out_list );
	AddToConsoleLog( out_list );
	AddToConsoleLog( " " );
	AddToConsoleLog( " " );
	AddToConsoleLog( "-------------" );
	if( trimmed.length() > 0 )
		AddToConsoleLog( "Listing all ConsoleVariables that begin with " + trimmed );
	else
		AddToConsoleLog( "Listing all ConsoleVariables");
	AddToConsoleLog( " " );
	AddToConsoleLog( " " );
}


void DeveloperConsole::WriteConfigCvars()
{
	//Don't write out to config files if we're in the middle of reading one
	if( _inConfigFileOp )
		return;

	StringList configCvars;
	_consoleItemManager.SerializeConfigCVars( configCvars );
	String configVarFileName = "Config//ConfigCvars.cfg";
	if( WriteLinesToFile( configVarFileName, configCvars ) )
	{
		AddToConsoleLog( String("Wrote config cvars out to: ") + configVarFileName );
	}

}


void DeveloperConsole::Execute( String input )
{
	if( input.length() == 0 )
		return;

	StringList inputStrings = SplitString( input );

	int numInputStrings = inputStrings.size();
	//Ignore a bunch of spaces
	if( numInputStrings == 0 )
		return;

	String car, cdr;
	GetCarCdr( inputStrings, car, cdr, numInputStrings );

	//Attempt to execute console command
	if( _consoleItemManager.ExecuteCCmd( car, cdr ) )
	{
		return;
	}

	//Attempt to set a console variable
	ConsoleVariable* cvar = _consoleItemManager.FindCVar( car );
	if( cvar == NULL )
	{
		if( !_silenced )
			AddToConsoleLog( String("Unable to find console item: ") + car );
		return;
	}

	//if there's no input, just print out the cvar value
	if( cdr.length() == 0 )
	{
		if( !_silenced )
			AddToConsoleLog( cvar->GetFullDescription() );
	}
	else
	{
		//Otherwise, set the value
		cvar->SetStringVal( cdr );
		if( !_silenced )
			AddToConsoleLog( cvar->GetFullDescription() );
	}
}

void DeveloperConsole::AcceptCurrentInput()
{
	Execute( _currentInput );

	//Consume current input
	UpdateInputHistory(_currentInput);
	SetCurrentInput("");
}

void DeveloperConsole::AcceptAutocomplete()
{
	if( _autoCompleteList.size() == 0 )
		return;

	//otherwise, take the top
	StringList conItemDef = SplitString(_autoCompleteList[0]);
	//TODO: allow user to select autocomplete
	SetCurrentInput( conItemDef[0] + " " );
}

void DeveloperConsole::Initialize()
{
	CONSOLE_DECLARECMDMETHOD( ExecuteFile, this, DeveloperConsole, ExecuteFile );
	CONSOLE_DECLARECMDMETHOD( ExecConfigFile, this, DeveloperConsole, ExecConfigFile );
	CONSOLE_DECLARECMDMETHOD( ToggleConsole, this, DeveloperConsole, ToggleConsole );
	CONSOLE_DECLARECMDMETHOD( DeclareCVar, this, DeveloperConsole, DeclareCVar );
	CONSOLE_DECLARECMDMETHOD( CCmdList, this, DeveloperConsole, CCmdList );
	CONSOLE_DECLARECMDMETHOD( CVarList, this, DeveloperConsole, CVarList );
	CONSOLE_DECLARECMDMETHOD( Echo, this, DeveloperConsole, Echo );

	RegisterFont("Resources/Fonts/Inconsolata.otf", 24, "Console");
	RegisterFont("Resources/Fonts/Inconsolata.otf", 18, "ConsoleSmall");
}

void DeveloperConsole::ToggleConsole( const String& /*input*/ )
{
	Enable( !IsEnabled() );
}

void DeveloperConsole::DeclareCVar( const String& input )
{
	StringList byParams = SplitString( input, "|" );

	//Early out if we have no meaningful input
	if( byParams.size() == 0 )
	{
		AddToConsoleLog( "Failed to declare new console variable" );
		return;
	}

	StringList cvarDef = SplitString(byParams[0]);
	//Early out if we don't have a true cvar definition
	if( cvarDef.size() < 2 )
	{
		AddToConsoleLog( "Failed to declare new console variable" );
		return;
	}

	String car, cdr;
	GetCarCdr( cvarDef, car, cdr );

	ConsoleVariable* cvar = CONSOLE_GETVAR( car );
	if( cvar == NULL )
		return;

	cvar->SetStringVal( cdr );

	cvar->DeserializeParams( byParams );

	//TODO: handle the remainder of params
}


void DeveloperConsole::UpdateInputHistory( const String& input )
{
	//If we're already in the input history, remove the current entry and add to end
	StringList::iterator inputHistPos = GetInputHistoryPos(input);
	if( inputHistPos != _inputHistory.end() )
	{
		_inputHistory.erase( inputHistPos );
	}

	_inputHistory.push_back(input);
	_inputHistoryPos = _inputHistory.size();

}


StringList::iterator DeveloperConsole::GetInputHistoryPos( const String& input )
{
	String allCapsInput = ToUpper( input );
	for( StringList::iterator itr = _inputHistory.begin(); itr != _inputHistory.end(); itr++ )
	{
		String comp = ToUpper( *itr );
		if( allCapsInput == comp )
		{
			return itr;
		}
	}
	return _inputHistory.end();
}

void DeveloperConsole::AdvanceInputHistory( int byVal )
{
	//If we have no input history, ignore this
	if( _inputHistory.size() == 0 )
		return;

	//If we're at the bottom of our input history, do nothing
	int lastInputIndex = _inputHistory.size() - 1;
	if( byVal >= 0 && _inputHistoryPos == lastInputIndex )
		return;


	_inputHistoryPos += byVal;
	if( _inputHistoryPos > lastInputIndex )
		_inputHistoryPos = lastInputIndex;
	else if( _inputHistoryPos < 0 )
		_inputHistoryPos = 0;

	//otherwise, write over our current input
	SetCurrentInput( _inputHistory[_inputHistoryPos] );
}

void DeveloperConsole::AdvanceConsoleLog( int byVal )
{
	int numLines = _consoleLog.NumLogLines();
	if( numLines == 0 )
		return;

	_consoleLogPos += byVal;
	if( _consoleLogPos >= numLines )
		_consoleLogPos = numLines - 1;
	else if( _consoleLogPos < 0 )
		_consoleLogPos = 0;

}


void DeveloperConsole::UpdateAutoComplete()
{
	_autoCompleteList.clear();
	_consoleItemManager.GetConsoleItemIds(TrimString(_currentInput), _autoCompleteList);
}

void DeveloperConsole::SetCurrentInput(const String& newVal)
{
	_currentInput = newVal;
	UpdateAutoComplete();
}

void DeveloperConsole::AddToConsoleLog( StringList& refList )
{
	for( unsigned int i = 0; i < refList.size(); i++ )
	{
		AddToConsoleLog( refList[i] );
	}
}

void DeveloperConsole::AddToConsoleLog( const String& input )
{
	bool bAtBottomOfConsole = false;
	if( _consoleLogPos >= _consoleLog.NumLogLines() - 1 )
		bAtBottomOfConsole = true;

	WriteToOutput(input + "\n");
	_consoleLog.Log( input );
	if( bAtBottomOfConsole )
		AdvanceConsoleLog( _consoleLog.NumLogLines() );
}
