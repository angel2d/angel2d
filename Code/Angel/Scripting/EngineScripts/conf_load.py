import sys
import os
import re
import glob
import ConfigParser

import angel
from angel import *
from sugar import theWorld


def _LoadActorDefs(filename):
    """Load actor definitions from Config/ActorDef/<filename>.ini.
    
    Instantiate an Actor from a definition with Actor.Create(<name>)
    
    If called a second time, it will reload the file, so the definitions
    will be updated, but any existing Actors that were created from them
    remain the same. 
    """
    path_try = os.path.join("Config", "ActorDef", filename + ".ini")
    if not (os.path.exists(path_try)):
        raise IOError, "Couldn't find " + path_try
    if not hasattr(Actor, "_defs"):
        Actor._defs = {}
    config = ConfigParser.ConfigParser()
    config.read(path_try)
    for section in config.sections():
        definition = {}
        for item in config.items(section):
            definition[item[0]] = item[1]
        if 'class' not in definition:
            definition["class"] = "Actor"
        Actor._defs[section] = definition

def _Create(actor_type):
    """Instantiate an Actor from a previously loaded definition file.
    
    Returns the Actor -- it still has to be added to the World to 
    receive Update and Render calls. 
    """
    if not hasattr(Actor, "_defs"):
        print "No Actor definitions loaded."
        return
    if actor_type not in Actor._defs:
        raise KeyError, "Actor definition %s not loaded." % actor_type
    class_name = Actor._defs[actor_type]["class"]
    try:
        class_type = globals()[class_name]
        a = class_type()
    except KeyError:
        raise NameError, "No class called %s is available." % class_name
    for config, value in Actor._defs[actor_type].iteritems():
        # skip the class declaration
        if config == 'class':
            continue
        _ApplyToActor(a, config, value)
    
    return a

def _ApplyToActor(actor, config, value):
    """Apply a configuration value to an Actor.

    We check for different forms the name might take:
      If the config file listed "display_name", we would try to call
      SetDisplayName, DisplayName, and display_name, as well as set
      any attributes that have those forms. Once one is found, we
      stop trying. An error prints if no suitable match is found. 
    """
    # Turn strings into proper Python values
    try:
        val = eval(value)
    except:
        val = value

    # Generate names
    camel_case_name = "".join(map(lambda x: x.capitalize(), config.split("_")))
    name_checks = (
        config,
        camel_case_name,
        "Set" + camel_case_name
    )

    # Try to set the value
    found = False
    for name in name_checks:
        func = getattr(actor, name, None)
        if not func:
            if hasattr(actor, name):
                setattr(actor, name, val)
                found = True
                break
        if callable(func):
            found = True
            ok = True
            try:
                func(val)
            except:
                try:
                    func(*val)
                except TypeError:
                    found = False
            break
    if not found:
        print "WARNING: No method or attribute found for %s, %s, or %s" % name_checks

def _LoadLevelDef(filename):
    """Load level definitions from Config/Level/<filename>.ini.
    
    Call LoadLevel(<name>) to actually load all the Actors described in
    the file. 
    
    If called a second time, it will reload the file, so the definitions
    will be updated, but the existing world won't be affected. 
    """
    path_try = os.path.join("Config", "Level", filename + ".ini")
    if not (os.path.exists(path_try)):
        raise IOError, "Couldn't find " + path_try
    
    if not hasattr(angel, "_levels"):
        angel._levels = {}
    angel._levels[filename] = {}
    config = ConfigParser.ConfigParser()
    config.read(path_try)
    for section in config.sections():
        actor = {}
        for item in config.items(section):
            actor[item[0]] = item[1]
        angel._levels[filename][section] = actor

def LoadLevel(level_name):
    """Instantiate and add all Actors described in a previously loaded
    Level definition file.
    
    Call theWorld.ResetWorld() to remove all existing Actors beforehand
    if you want to start over.
    """
    if level_name not in angel._levels:
        raise KeyError, "Level definition %s not loaded." % level_name
    for name, configs in angel._levels[level_name].iteritems():
        if 'type' not in configs:
            raise StandardError, "Actor %s has no type specified." % name
        a = Actor.Create(configs['type'])
        a.SetName(name)
        try:
            layer = int(configs['layer'])
        except:
            layer = 0
        for config, value in configs.iteritems():
            if config == 'type' or config == 'layer':
                continue
            _ApplyToActor(a, config, value)
        theWorld.Add(a, layer)
        if globals()['PhysicsActor'] in (type(a),) + type(a).__bases__:
            a.InitPhysics()

def ReloadLevelDefs():
    """Loads all levels in the Config/Level directory into the working
    definitions list.

    Can be called again to reload all the level definitions. 
    """
    files = glob.glob(os.path.join("Config", "Level/") + "*.ini")
    for filename in files:
        try:
            _LoadLevelDef(os.path.splitext(os.path.basename(filename))[0])
        except:
            out = (filename,) + sys.exc_info()
            print "Error loading %s:\n\t %s: %s\n%s" % out
    

def ReloadActorDefs():
    """Loads all actor definitions in the Config/ActorDef directory into
    the working definitions list.

    Can be called again to reload all the actor definitions. 
    """
    files = glob.glob(os.path.join("Config", "ActorDef/") + "*.ini")
    for filename in files:
        try:
            _LoadActorDefs(os.path.splitext(os.path.basename(filename))[0])
        except:
            out = (filename,) + sys.exc_info()
            print "Error loading %s:\n\t %s: %s\n%s" % out
    

Actor.Create = staticmethod(_Create)

