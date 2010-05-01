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

import angel
from angel import World, TagCollection, Actor, Switchboard, Camera, SoundDevice, ControllerManager, CompoundLog, Tuning

# Singleton shortcuts
theWorld = World.GetInstance()
theTagList = TagCollection.GetInstance()
theSwitchboard = Switchboard.GetInstance()
theCamera = Camera.GetInstance()
theSound = SoundDevice.GetInstance()
theControllerManager = ControllerManager.GetInstance()
sysLog = CompoundLog.GetSystemLog()
theTuning = Tuning.GetInstance()

# Input accessors
theController = ControllerManager.GetInstance().GetController()
controllerOne = theController
controllerTwo = ControllerManager.GetInstance().GetController(1)

def reset():
    theWorld.ResetWorld()

def tune(varName, newVal):
    # Turn strings into proper Python values
    try:
        val = eval(newVal)
    except:
        val = newVal
    if isinstance(val, list):
        theTuning.SetVector(varName, val)
    elif isinstance(val, float):
        theTuning.SetFloat(varName, val)
    elif isinstance(val, int):
        theTuning.SetInt(varName, val)
    else:
        theTuning.SetString(varName, val)
    
    theTuning.AddToRuntimeTuningList(varName)

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
