# This file gets automatically imported when the engine is started. It's a good place
#  to declare your own functions (or import other stuff you need) without having to 
#  mess around in the engine scripts. 

from sugar import *
from angel import Color

c1 = Color(1.0, 1.0, 0.0, 0.5)
c2 = Color(1.0, 0.0, 1.0, 1.0)


def add_texture():
    """A function to add a texture to a specific actor, for demoing the console. """
    a = Actor.GetNamed('ForDemoConsole')
    a.SetSprite("Resources/Images/angel.png")

def change_size(new_size):
    """A function to change the size of a specific actor, for demoing the console."""
    a = Actor.GetNamed('ForDemoConsole')
    a.SetSize(new_size)

