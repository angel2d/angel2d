%module angel

#ifndef INTROGAME
%include inheritance.i
#else
%include inheritance_intro.i
#endif

%include <std_string.i>

typedef std::string			String;

#ifdef SWIGLUA
%typemap(out) std::vector<String>
%{
	{
		lua_newtable(L);
		
		if ($1.size() > 0)
		{
			for (unsigned int i=1; i <= $1.size(); i++)
			{
				lua_pushnumber(L, i);
				lua_pushstring(L, $1.at(i-1).c_str()); 
				lua_rawset(L, -3);
			}
		}
		
		SWIG_arg += 1; 
	}
%}

%typemap(out) std::set<String>
%{
	{
		lua_newtable(L);
	
		std::set<String>::iterator it = $1.begin();
		int setCounter = 1;
		while (it != $1.end())
		{
			lua_pushnumber(L, setCounter++);
			lua_pushstring(L, (*it).c_str()); 
			lua_settable(L, -3);
		
			it++;
		}
	
		SWIG_arg += 1; 
	}
%}
#endif

typedef std::set<String>	StringSet;
typedef std::vector<String>	StringList;

%include vectors.i
%include color.i
%include messaging.i
%include renderable.i
%include util.i

%include world.i
%include log.i
%include tuning.i
%include preferences.i
%include sound.i

#ifndef ANGEL_MOBILE
%include console.i
%include controller.i
%include mouse.i
#endif
%include multitouch.i

%include actor.i
%include camera.i
%include physics_actor.i
%include particles.i
%include text_actor.i
%include misc_actors.i
%include textures.i

#ifndef INTROGAME
%include ../../../ClientGame/script_interface.i
#else
%include ../../../IntroGame/script_interface.i
#endif
