import sys

sys.path.append('./Resources/Scripts')

# Yes, the 'from X import *' lines are evil, but this way we
#  expose all our wrapped functions to the console. 
from angel import *
from sugar import *
from angel_console import AngelConsole
import conf_load
from conf_load import LoadLevel


if (sys.platform[:3] == 'win'):
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
    sys.setrecursionlimit(250)


# Register our console
ac = AngelConsole(locals())
World.GetInstance().RegisterConsole(ac)

# Load the definitions from the Config directory
conf_load.ReloadLevelDefs()
conf_load.ReloadActorDefs()

# If you have your own initialization code that you need to run,
#  create a client_start.py file and do it there. This file
#  (start.py) gets overwritten whenever you rebuild your client
#  project. 
try:
    import client_start
    from client_start import *
except ImportError:
    pass
