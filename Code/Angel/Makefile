CXX = g++
CXXFLAGS =
TARGET = libangel.so
CWD := $(shell pwd)
CODE_DIR := $(shell dirname $(CWD))
ARCH := $(shell uname -m)
ifeq ($(ARCH),x86_64)
	CXXFLAGS += -fPIC
endif

INCLUDE = 							\
	-ILibraries/glfw/include				\
	-ILibraries/Box2D-2.0.1/Include				\
	-ILibraries/FMOD/inc 					\
	-ILibraries/FTGL/include				\
	-I/usr/include/freetype2				\
	-I/usr/include/python2.6

LIBS = 								\
	Libraries/glfw/lib/x11/libglfw.a			\
	Libraries/Box2D-2.0.1/Source/Gen/float/libbox2d.a	\
	Libraries/FTGL/unix/src/.libs/libftgl.a

SRCS =								\
	Actors/Actor.cpp					\
	Actors/FullScreenActor.cpp				\
	Actors/GridActor.cpp					\
	Actors/HUDActor.cpp					\
	Actors/ParticleActor.cpp				\
	Actors/TextActor.cpp					\
	AI/BoundingShapes.cpp					\
	AI/Brain.cpp						\
	AIEvents/GotoAIEvent.cpp				\
	AIEvents/GotoTargetAIEvent.cpp				\
	AIEvents/NamedEventAIEvent.cpp				\
	AIEvents/TimerAIEvent.cpp				\
	AIEvents/TraversalAIEvent.cpp				\
	AI/PathFinder.cpp					\
	AI/Ray2.cpp						\
	AI/Sentient.cpp						\
	AI/SpatialGraph.cpp					\
	AI/Traversal.cpp					\
	Infrastructure/Camera.cpp				\
	Infrastructure/Color.cpp				\
	Infrastructure/Console.cpp				\
	Infrastructure/GameManager.cpp				\
	Infrastructure/Log.cpp					\
	Infrastructure/RenderableIterator.cpp			\
	Infrastructure/SoundDevice.cpp				\
	Infrastructure/TagCollection.cpp			\
	Infrastructure/TextRendering.cpp			\
	Infrastructure/Textures.cpp				\
	Infrastructure/TuningVariable.cpp			\
	Infrastructure/Vector2.cpp				\
	Infrastructure/Vector3.cpp				\
	Infrastructure/World.cpp				\
	Input/Controller.cpp					\
	Input/Input.cpp						\
	Input/InputManager.cpp					\
	Input/MouseInput.cpp					\
	Messaging/Message.cpp					\
	Messaging/Switchboard.cpp				\
	Physics/PhysicsActor.cpp				\
	Physics/PhysicsDebugDraw.cpp				\
	Scripting/Interfaces/AngelPythonWrapping.cpp		\
	Scripting/PythonModule.cpp				\
	Util/DrawUtil.cpp					\
	Util/FileUtil.cpp					\
	Util/MathUtil.cpp					\
	Util/StringUtil.cpp

all: $(TARGET)

SWIG_Wrappers:
	python ../Tools/BuildScripts/swig_wrap.py -p $(CODE_DIR)

SWIG_Wrappers-clean:
	rm -f Scripting/Interfaces/AngelPythonWrapping.h
	rm -f Scripting/Interfaces/AngelPythonWrapping.cpp
	rm -f Scripting/Interfaces/angel.py

FTGL:
ifeq ($(ARCH),x86_64)
	cd Libraries/FTGL/unix && (test -e Make.conf || \
		CXXFLAGS="-g -O2 -fPIC" ./configure) && make
else
	cd Libraries/FTGL/unix && (test -e Make.conf || ./configure) && make
endif

FTGL-clean:
	touch Libraries/FTGL/unix/Make.conf
	cd Libraries/FTGL/unix && make clean
	cd Libraries/FTGL/unix && rm -f config.log config.status ftgl.pc \
		Make.conf libtool demo/FTGLDemo docs/doc-stamp

GLFW:
	cd Libraries/glfw && make x11

GLFW-clean:
	cd Libraries/glfw && make x11-clean

Box2D:
	cd Libraries/Box2D-2.0.1/Source && make

Box2D-clean:
	cd Libraries/Box2D-2.0.1/Source && make clean

libraries: SWIG_Wrappers FTGL GLFW Box2D

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

%.o: %.cpp
	$(CXX) -c $(INCLUDE) -Wno-write-strings -Wno-deprecated $(CXXFLAGS) -o $@ $^

$(TARGET): libraries $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LIBS)

clean: SWIG_Wrappers-clean FTGL-clean GLFW-clean Box2D-clean
	rm -f $(OBJS) $(TARGET)
