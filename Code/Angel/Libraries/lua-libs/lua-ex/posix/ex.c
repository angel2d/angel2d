/*
 * "ex" API implementation
 * http://lua-users.org/wiki/ExtensionProposal
 * Copyright 2007 Mark Edgar < medgar123 at gmail com >
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

#include "environ.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define absindex(L,i) ((i)>0?(i):lua_gettop(L)+(i)+1)

#include "spawn.h"

/* -- nil error */
extern int push_error(lua_State *L)
{
  lua_pushnil(L);
  lua_pushstring(L, strerror(errno));
  return 2;
}


/* name -- value/nil */
static int ex_getenv(lua_State *L)
{
  const char *nam = luaL_checkstring(L, 1);
  char *val = getenv(nam);
  if (!val)
    return push_error(L);
  lua_pushstring(L, val);
  return 1;
}

/* name value -- true/nil error
 * name nil -- true/nil error */
static int ex_setenv(lua_State *L)
{
  const char *nam = luaL_checkstring(L, 1);
  const char *val = lua_tostring(L, 2);
  int err = val ? setenv(nam, val, 1) : unsetenv(nam);
  if (err == -1) return push_error(L);
  lua_pushboolean(L, 1);
  return 1;
}

/* -- environment-table */
static int ex_environ(lua_State *L)
{
  const char *nam, *val, *end;
  const char **env;
  lua_newtable(L);
  for (env = (const char **)environ; (nam = *env); env++) {
    end = strchr(val = strchr(nam, '=') + 1, '\0');
    lua_pushlstring(L, nam, val - nam - 1);
    lua_pushlstring(L, val, end - val);
    lua_settable(L, -3);
  }
  return 1;
}


/* -- pathname/nil error */
static int ex_currentdir(lua_State *L)
{
  char pathname[PATH_MAX + 1];
  if (!getcwd(pathname, sizeof pathname))
    return push_error(L);
  lua_pushstring(L, pathname);
  return 1;
}

/* pathname -- true/nil error */
static int ex_chdir(lua_State *L)
{
  const char *pathname = luaL_checkstring(L, 1);
  if (-1 == chdir(pathname))
    return push_error(L);
  lua_pushboolean(L, 1);
  return 1;
}

/* pathname -- true/nil error */
static int ex_mkdir(lua_State *L)
{
  const char *pathname = luaL_checkstring(L, 1);
  if (-1 == mkdir(pathname, 0777))
    return push_error(L);
  lua_pushboolean(L, 1);
  return 1;
}

/* Lua os.remove provides the correct semantics on POSIX systems */


static FILE *check_file(lua_State *L, int idx, const char *argname)
{
  FILE **pf;
  if (idx > 0) pf = luaL_checkudata(L, idx, LUA_FILEHANDLE);
  else {
    idx = absindex(L, idx);
    pf = lua_touserdata(L, idx);
    luaL_getmetatable(L, LUA_FILEHANDLE);
    if (!pf || !lua_getmetatable(L, idx) || !lua_rawequal(L, -1, -2))
      luaL_error(L, "bad %s option (%s expected, got %s)",
                 argname, LUA_FILEHANDLE, luaL_typename(L, idx));
    lua_pop(L, 2);
  }
  if (!*pf) return luaL_error(L, "attempt to use a closed file"), NULL;
  return *pf;
}

static FILE **new_file(lua_State *L, int fd, const char *mode)
{
  FILE **pf = lua_newuserdata(L, sizeof *pf);
  *pf = 0;
  luaL_getmetatable(L, LUA_FILEHANDLE);
  lua_setmetatable(L, -2);
  *pf = fdopen(fd, mode);
  return pf;
}


#define new_dirent(L) lua_newtable(L)

/* pathname/file [entry] -- entry */
static int ex_dirent(lua_State *L)
{
  struct stat st;
  switch (lua_type(L, 1)) {
  default: return luaL_typerror(L, 1, "file or pathname");
  case LUA_TSTRING: {
    const char *name = lua_tostring(L, 1);
    if (-1 == stat(name, &st))
      return push_error(L);
    } break;
  case LUA_TUSERDATA: {
    FILE *f = check_file(L, 1, NULL);
    if (-1 == fstat(fileno(f), &st))
      return push_error(L);
    } break;
  }
  if (lua_type(L, 2) != LUA_TTABLE) {
    lua_settop(L, 1);
    new_dirent(L);
  }
  else {
    lua_settop(L, 2);
  }
  if (S_ISDIR(st.st_mode))
    lua_pushliteral(L, "directory");
  else
    lua_pushliteral(L, "file");
  lua_setfield(L, 2, "type");
  lua_pushnumber(L, st.st_size);
  lua_setfield(L, 2, "size");
  return 1;
}

#define DIR_HANDLE "DIR*"

/* ...diriter... -- ...diriter... pathname */
static int diriter_getpathname(lua_State *L, int index)
{
  lua_pushvalue(L, index);
  lua_gettable(L, LUA_REGISTRYINDEX);
  return 1;
}

/* ...diriter... pathname -- ...diriter... */
static int diriter_setpathname(lua_State *L, int index)
{
  size_t len;
  const char *path = lua_tolstring(L, -1, &len);
  if (path && path[len - 1] != *LUA_DIRSEP) {
    lua_pushliteral(L, LUA_DIRSEP);
    lua_concat(L, 2);
  }
  lua_pushvalue(L, index);              /* ... pathname diriter */
  lua_insert(L, -2);                    /* ... diriter pathname */
  lua_settable(L, LUA_REGISTRYINDEX);   /* ... */
  return 0;
}

/* diriter -- diriter */
static int diriter_close(lua_State *L)
{
  DIR **pd = lua_touserdata(L, 1);
  if (*pd) {
    closedir(*pd);
    *pd = 0;
  }
  lua_pushnil(L);
  diriter_setpathname(L, 1);
  return 0;
}

static int isdotfile(const char *name)
{
  return name[0] == '.' && (name[1] == '\0'
         || (name[1] == '.' && name[2] == '\0'));
}

/* pathname -- iter state nil */
/* diriter ... -- entry */
static int ex_dir(lua_State *L)
{
  const char *pathname;
  DIR **pd;
  struct dirent *d;
  switch (lua_type(L, 1)) {
  default: return luaL_typerror(L, 1, "pathname");
  case LUA_TSTRING:
    pathname = lua_tostring(L, 1);
    lua_pushcfunction(L, ex_dir);       /* pathname ... iter */
    pd = lua_newuserdata(L, sizeof *pd);/* pathname ... iter state */
    *pd = opendir(pathname);
    if (!*pd) return push_error(L);
    luaL_getmetatable(L, DIR_HANDLE);   /* pathname ... iter state M */
    lua_setmetatable(L, -2);            /* pathname ... iter state */
    lua_pushvalue(L, 1);                /* pathname ... iter state pathname */
    diriter_setpathname(L, -2);         /* pathname ... iter state */
    return 2;
  case LUA_TUSERDATA:
    pd = luaL_checkudata(L, 1, DIR_HANDLE);
    do d = readdir(*pd);
    while (d && isdotfile(d->d_name));
    if (!d) { diriter_close(L); return push_error(L); }
    new_dirent(L);                      /* diriter ... entry */
    diriter_getpathname(L, 1);          /* diriter ... entry dir */
    lua_pushstring(L, d->d_name);       /* diriter ... entry dir name */
    lua_pushvalue(L, -1);               /* diriter ... entry dir name name */
    lua_setfield(L, -4, "name");        /* diriter ... entry dir name */
    lua_concat(L, 2);                   /* diriter ... entry fullpath */
    lua_replace(L, 1);                  /* fullpath ... entry */
    lua_replace(L, 2);                  /* fullpath entry ... */
    return ex_dirent(L);
  }
  /*NOTREACHED*/
}


static int file_lock(lua_State *L,
                     FILE *f, const char *mode, long offset, long length)
{
  struct flock k;
  switch (*mode) {
    case 'w': k.l_type = F_WRLCK; break;
    case 'r': k.l_type = F_RDLCK; break;
    case 'u': k.l_type = F_UNLCK; break;
    default: return luaL_error(L, "invalid mode");
  }
  k.l_whence = SEEK_SET;
  k.l_start = offset;
  k.l_len = length;
  if (-1 == fcntl(fileno(f), F_SETLK, &k))
    return push_error(L);
  /* return the file */
  lua_settop(L, 1);
  return 1;
}

static const char *opt_mode(lua_State *L, int *pidx)
{
  if (lua_type(L, *pidx) != LUA_TSTRING)
    return "u";
  return lua_tostring(L, (*pidx)++);
}

/* file [mode] [offset [length]] -- file/nil error */
static int ex_lock(lua_State *L)
{
  FILE *f = check_file(L, 1, NULL);
  int argi = 2;
  const char *mode = opt_mode(L, &argi);
  long offset = luaL_optnumber(L, argi, 0);
  long length = luaL_optnumber(L, argi + 1, 0);
  return file_lock(L, f, mode, offset, length);
}


static int closeonexec(int d)
{
  int fl = fcntl(d, F_GETFD);
  if (fl != -1)
    fl = fcntl(d, F_SETFD, fl | FD_CLOEXEC);
  return fl;
}

/* -- in out/nil error */
static int ex_pipe(lua_State *L)
{
  int fd[2];
  if (-1 == pipe(fd))
    return push_error(L);
  closeonexec(fd[0]);
  closeonexec(fd[1]);
  new_file(L, fd[0], "r");
  new_file(L, fd[1], "w");
  return 2;
}


/* seconds --
 * interval units -- */
static int ex_sleep(lua_State *L)
{
  lua_Number interval = luaL_checknumber(L, 1);
  lua_Number units = luaL_optnumber(L, 2, 1);
  usleep(1e6 * interval / units);
  return 0;
}


static void get_redirect(lua_State *L,
                         int idx, const char *stdname, struct spawn_params *p)
{
  lua_getfield(L, idx, stdname);
  if (!lua_isnil(L, -1))
    spawn_param_redirect(p, stdname, fileno(check_file(L, -1, stdname)));
  lua_pop(L, 1);
}

/* filename [args-opts] -- proc/nil error */
/* args-opts -- proc/nil error */
static int ex_spawn(lua_State *L)
{
  struct spawn_params *params;
  int have_options;
  switch (lua_type(L, 1)) {
  default: return luaL_typerror(L, 1, "string or table");
  case LUA_TSTRING:
    switch (lua_type(L, 2)) {
    default: return luaL_typerror(L, 2, "table");
    case LUA_TNONE: have_options = 0; break;
    case LUA_TTABLE: have_options = 1; break;
    }
    break;
  case LUA_TTABLE:
    have_options = 1;
    lua_getfield(L, 1, "command");      /* opts ... cmd */
    if (!lua_isnil(L, -1)) {
      /* convert {command=command,arg1,...} to command {arg1,...} */
      lua_insert(L, 1);                 /* cmd opts ... */
    }
    else {
      /* convert {arg0,arg1,...} to arg0 {arg1,...} */
      size_t i, n = lua_objlen(L, 1);
      lua_rawgeti(L, 1, 1);             /* opts ... nil cmd */
      lua_insert(L, 1);                 /* cmd opts ... nil */
      for (i = 2; i <= n; i++) {
        lua_rawgeti(L, 2, i);           /* cmd opts ... nil argi */
        lua_rawseti(L, 2, i - 1);       /* cmd opts ... nil */
      }
      lua_rawseti(L, 2, n);             /* cmd opts ... */
    }
    if (lua_type(L, 1) != LUA_TSTRING)
      return luaL_error(L, "bad command option (string expected, got %s)",
                        luaL_typename(L, 1));
    break;
  }
  params = spawn_param_init(L);
  /* get filename to execute */
  spawn_param_filename(params, lua_tostring(L, 1));
  /* get arguments, environment, and redirections */
  if (have_options) {
    lua_getfield(L, 2, "args");         /* cmd opts ... argtab */
    switch (lua_type(L, -1)) {
    default:
      return luaL_error(L, "bad args option (table expected, got %s)",
                        luaL_typename(L, -1));
    case LUA_TNIL:
      lua_pop(L, 1);                    /* cmd opts ... */
      lua_pushvalue(L, 2);              /* cmd opts ... opts */
      if (0) /*FALLTHRU*/
    case LUA_TTABLE:
      if (lua_objlen(L, 2) > 0)
        return
          luaL_error(L, "cannot specify both the args option and array values");
      spawn_param_args(params);         /* cmd opts ... */
      break;
    }
    lua_getfield(L, 2, "env");          /* cmd opts ... envtab */
    switch (lua_type(L, -1)) {
    default:
      return luaL_error(L, "bad env option (table expected, got %s)",
                        luaL_typename(L, -1));
    case LUA_TNIL:
      break;
    case LUA_TTABLE:
      spawn_param_env(params);          /* cmd opts ... */
      break;
    }
    get_redirect(L, 2, "stdin", params);    /* cmd opts ... */
    get_redirect(L, 2, "stdout", params);   /* cmd opts ... */
    get_redirect(L, 2, "stderr", params);   /* cmd opts ... */
  }
  return spawn_param_execute(params);   /* proc/nil error */
}


/* register functions from 'lib' in table 'to' by copying existing
 * closures from table 'from' or by creating new closures */
static void copyfields(lua_State *L, const luaL_reg *l, int from, int to)
{
  for (to = absindex(L, to); l->name; l++) {
    lua_getfield(L, from, l->name);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 1);
      lua_pushcfunction(L, l->func);
    }
    lua_setfield(L, to, l->name);
  }
}

int luaopen_ex(lua_State *L)
{
  const char *name = lua_tostring(L, 1);
  int ex;
  const luaL_reg ex_iolib[] = {
    {"pipe",       ex_pipe},
#define ex_iofile_methods (ex_iolib + 1)
    {"lock",       ex_lock},
    {"unlock",     ex_lock},
    {0,0} };
  const luaL_reg ex_oslib[] = {
    /* environment */
    {"getenv",     ex_getenv},
    {"setenv",     ex_setenv},
    {"environ",    ex_environ},
    /* file system */
    {"currentdir", ex_currentdir},
    {"chdir",      ex_chdir},
    {"mkdir",      ex_mkdir},
    {"dir",        ex_dir},
    {"dirent",     ex_dirent},
    /* process control */
    {"sleep",      ex_sleep},
    {"spawn",      ex_spawn},
    {0,0} };
  const luaL_reg ex_diriter_methods[] = {
    {"__gc",       diriter_close},
    {0,0} };
  const luaL_reg ex_process_methods[] = {
    {"__tostring", process_tostring},
#define ex_process_functions (ex_process_methods + 1)
    {"wait",       process_wait},
    {0,0} };
  /* diriter metatable */
  luaL_newmetatable(L, DIR_HANDLE);           /* . D */
  luaL_register(L, 0, ex_diriter_methods);    /* . D */
  /* proc metatable */
  luaL_newmetatable(L, PROCESS_HANDLE);       /* . P */
  luaL_register(L, 0, ex_process_methods);    /* . P */
  lua_pushvalue(L, -1);                       /* . P P */
  lua_setfield(L, -2, "__index");             /* . P */
  /* make all functions available via ex. namespace */
  luaL_register(L, name, ex_oslib);           /* . P ex */
  luaL_register(L, 0, ex_iolib);
  copyfields(L, ex_process_functions, -2, -1);
  ex = lua_gettop(L);
  /* extend the os table */
  lua_getglobal(L, "os");                     /* . os */
  if (lua_isnil(L, -1)) return luaL_error(L, "os not loaded");
  copyfields(L, ex_oslib, ex, -1);
  lua_getfield(L, -1, "remove");
  lua_setfield(L, ex, "remove");
  /* extend the io table */
  lua_getglobal(L, "io");                     /* . io */
  if (lua_isnil(L, -1)) return luaL_error(L, "io not loaded");
  copyfields(L, ex_iolib, ex, -1);
  lua_getfield(L, ex, "pipe");                /* . io ex_pipe */
  lua_getfield(L, -2, "open");                /* . io ex_pipe io_open */
  lua_getfenv(L, -1);                         /* . io ex_pipe io_open E */
  lua_setfenv(L, -3);                         /* . io ex_pipe io_open */
  /* extend the io.file metatable */
  luaL_getmetatable(L, LUA_FILEHANDLE);       /* . F */
  if (lua_isnil(L, -1)) return luaL_error(L, "can't find FILE* metatable");
  copyfields(L, ex_iofile_methods, ex, -1);
  return 1;
}
