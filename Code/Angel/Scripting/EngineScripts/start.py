#############################################################################
## Copyright (C) 2008-2010, Shane J. M. Liesegang
## All rights reserved.
## 
## Redistribution and use in source and binary forms, with or without 
## modification, are permitted provided that the following conditions are met:
## 
##     * Redistributions of source code must retain the above copyright 
##       notice, this list of conditions and the following disclaimer.
##     * Redistributions in binary form must reproduce the above copyright 
##       notice, this list of conditions and the following disclaimer in the 
##       documentation and/or other materials provided with the distribution.
##     * Neither the name of the copyright holder nor the names of any 
##       contributors may be used to endorse or promote products derived from 
##       this software without specific prior written permission.
## 
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
## IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
## ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
## LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
## CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
## SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
## INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
## CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
## POSSIBILITY OF SUCH DAMAGE.
##############################################################################

import sys
sys.argv = ["AngelPython"] # some modules expect this, but we don't have it when we're embedded
import traceback

sys.path.append('./Resources/Scripts')

# Yes, the 'from X import *' lines are evil, but this way we
#  expose all our wrapped functions to the console. 
from angel import *
from sugar import *
from angel_console import AngelConsole
import conf_load
from conf_load import LoadLevel, SaveTuningVariables


# Something about the Debug build of Python on Windows makes
#  it run into the call stack limit much earlier. We'll want
#  to figure this out at some point. In the meanwhile, if
#  this is causing a problem for you, call
#  sys.setrecursionlimit(<number>) in your client_start and
#  rebuild the engine in Release mode. 
#  (Note that the default recursion limit for Python is 1000.)
#  
# TODO: Find out why the Python Debug build on Win32 kills the
#  call stack so early.
if (sys.platform[:3] == 'win'):
    sys.setrecursionlimit(250)


# Register our console
ac = AngelConsole(locals())
World.GetInstance().RegisterConsole(ac)


# Set up exception catching so they don't make their way back
#  into the engine proper. 
def sys_exc_replacement(_type, value, tb):
    outString = "".join(traceback.format_exception(_type, value, tb))
    ac.write(outString)
    sysLog.Log(outString)
sys.excepthook = sys_exc_replacement


# Load the definitions from the Config directory
conf_load.ReloadLevelDefs()
conf_load.ReloadActorDefs()

# Set up the auto-updater
confUp = conf_load.ConfigUpdater()
confUp.__disown__() # make sure Python doesn't garbage collect the config updater


# If you have your own initialization code that you need to run,
#  create a client_start.py file and do it there. This file
#  (start.py) gets overwritten whenever you rebuild your client
#  project. 
try:
    import client_start
    from client_start import *
except ImportError:
    pass
