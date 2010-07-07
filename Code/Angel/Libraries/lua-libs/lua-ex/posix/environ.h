/*
 * "ex" API implementation
 * http://lua-users.org/wiki/ExtensionProposal
 * Copyright 2009 Mark Edgar < medgar123 at gmail com >
 */

#ifdef __APPLE__

#include <crt_externs.h>
#define environ (*_NSGetEnviron())

#else

extern char **environ;

#endif
