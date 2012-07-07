/*
** LuaFileSystem
** Copyright Kepler Project 2003 (http://www.keplerproject.org/luafilesystem)
**
** $Id: lfs.h,v 1.5 2008/02/19 20:08:23 mascarenhas Exp $
*/

/* Define 'chdir' for systems that do not implement it */
#ifdef NO_CHDIR
#define chdir(p)	(-1)
#define chdir_error	"Function 'chdir' not provided by system"
#else
#define chdir_error	strerror(errno)
#endif

#undef luaL_register
#define luaL_register(L,n,f) \
{ if ((n) == NULL) luaL_setfuncs(L,f,0); else luaL_newlib(L,f); }


int luaopen_lfs (lua_State *L);
