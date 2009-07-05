CXX = g++
TARGET = IntroGame
ARCH := $(shell uname -m)
LIBANGEL = ../Angel/libangel.so

INCLUDE = 							\
	-I../Angel						\
	-I../Angel/Libraries/glfw/include			\
	-I../Angel/Libraries/Box2D-2.0.1/Include		\
	-I../Angel/Libraries/FMOD/inc 				\
	-I../Angel/Libraries/FTGL/include			\
	-I/usr/include/freetype2				\
	-I/usr/include/python2.5

LIBS = $(LIBANGEL)
ifeq ($(ARCH),x86_64)
	LIBS += ../Angel/Libraries/FMOD/lib/libfmodex64.so
else
	LIBS += ../Angel/Libraries/FMOD/lib/libfmodex.so
endif

SHLIBS = -lGL -lGLU -lpython2.5 -lfreetype -lXrandr -lfreeimage

SRCS =								\
	DemoGameManager.cpp					\
	DemoScreenBindingInstructions.cpp			\
	DemoScreenByeBye.cpp					\
	DemoScreenConsole.cpp					\
	DemoScreenControllerInstructions.cpp			\
	DemoScreenDefFile.cpp					\
	DemoScreenInstructions.cpp				\
	DemoScreenIntervals.cpp					\
	DemoScreenLayeredCollisionLevelFile.cpp			\
	DemoScreenLevelFile.cpp					\
	DemoScreenMessagePassing.cpp				\
	DemoScreenMovingActor.cpp				\
	DemoScreenMultipleControllers.cpp			\
	DemoScreenParticleActors.cpp				\
	DemoScreenPathfinding.cpp				\
	DemoScreenPhysicsActor.cpp				\
	DemoScreenRenderLayers.cpp				\
	DemoScreenSimpleActor.cpp				\
	DemoScreenStart.cpp					\
	DemoScreenTuningVariables.cpp				\
	stdafx.cpp						\
	Main.cpp

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

%.o: %.cpp
	$(CXX) -c $(INCLUDE) -Wno-write-strings -Wno-deprecated -o $@ $^

$(TARGET): $(LIBANGEL) $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS) $(SHLIBS)
	cp -Rp ../Angel/Scripting/EngineScripts/* Resources/Scripts
	cp -p ../Angel/Scripting/Interfaces/angel.py Resources/Scripts

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

$(LIBANGEL):
	cd ../Angel && make
