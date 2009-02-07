import angel
from angel import World, TagCollection, Actor, Switchboard, Camera, SoundDevice

# Singleton shortcuts
theWorld = World.GetInstance()
theTagList = TagCollection.GetInstance()
theSwitchboard = Switchboard.GetInstance()
theCamera = Camera.GetInstance()
theSound = SoundDevice.GetInstance()

def reset():
    theWorld.ResetWorld()

COLOR_MAP = {
    'white'     : [1.0, 1.0, 1.0],
    'black'     : [0.0, 0.0, 0.0],
    'red'       : [1.0, 0.0, 0.0],
    'green'     : [0.0, 1.0, 0.0],
    'blue'      : [0.0, 0.0, 1.0],
    'yellow'    : [1.0, 1.0, 0.0],
    'magenta'   : [1.0, 0.0, 1.0],
    'cyan'      : [0.0, 1.0, 1.0],
    'purple'    : [0.5, 0.0, 1.0],
    'orange'    : [1.0, 0.5, 0.0],
}

def paint(self, color):
    if color in COLOR_MAP.keys():
        col = COLOR_MAP[color]
    else:
        print "No color", color, "defined. Print COLOR_MAP to see the list."
    
    if not (color == None or col == None):
        for color_name in COLOR_MAP.keys():
            self.Untag(color_name)
        self.SetColor(col)
        self.Tag(color)

Actor.paint = paint
