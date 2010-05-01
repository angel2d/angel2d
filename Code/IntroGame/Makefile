CXX = g++
TARGET = IntroGame
ARCH := $(shell uname -m)
ALLEGRO_LIBS := $(shell allegro-config --libs 2>/dev/null)
LIBANGEL = ../Angel/libangel.so

INCLUDE = 							\
	-I.							\
	-IDemoScreens						\
	-I../Angel						\
	-I../Angel/Libraries/glfw/include			\
	-I../Angel/Libraries/Box2D-2.0.1/Include		\
	-I../Angel/Libraries/FMOD/inc 				\
	-I../Angel/Libraries/FTGL/include			\
	-I/usr/include/freetype2				\
	-I/usr/include/python2.6

LIBS = $(LIBANGEL)
ifeq ($(ARCH),x86_64)
	LIBS += ../Angel/Libraries/FMOD/lib/libfmodex64.so
else
	LIBS += ../Angel/Libraries/FMOD/lib/libfmodex.so
endif

SHLIBS = -lGL -lGLU -lpython2.6 -lfreetype -lXrandr -lIL -lILU -lILUT
SHLIBS += $(ALLEGRO_LIBS)

SRCS =								\
	DemoGameManager.cpp					\
	DemoScreens/DemoScreenBindingInstructions.cpp		\
	DemoScreens/DemoScreenByeBye.cpp			\
	DemoScreens/DemoScreenConsole.cpp			\
	DemoScreens/DemoScreenControllerInstructions.cpp	\
	DemoScreens/DemoScreenDefFile.cpp			\
	DemoScreens/DemoScreenInstructions.cpp			\
	DemoScreens/DemoScreenIntervals.cpp			\
	DemoScreens/DemoScreenLayeredCollisionLevelFile.cpp	\
	DemoScreens/DemoScreenLevelFile.cpp			\
	DemoScreens/DemoScreenMessagePassing.cpp		\
	DemoScreens/DemoScreenMovingActor.cpp			\
	DemoScreens/DemoScreenMultipleControllers.cpp		\
	DemoScreens/DemoScreenParticleActors.cpp		\
	DemoScreens/DemoScreenPathfinding.cpp			\
	DemoScreens/DemoScreenPhysicsActor.cpp			\
	DemoScreens/DemoScreenRenderLayers.cpp			\
	DemoScreens/DemoScreenSimpleActor.cpp			\
	DemoScreens/DemoScreenStart.cpp				\
	DemoScreens/DemoScreenTuningVariables.cpp		\
	stdafx.cpp						\
	Main.cpp

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

%.o: %.cpp
	$(CXX) -c $(INCLUDE) -Wno-write-strings -Wno-deprecated -o $@ $^

$(TARGET): $(LIBANGEL) $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS) $(SHLIBS)
	cp -p ../Angel/Scripting/EngineScripts/*.py Resources/Scripts
	mkdir -p Resources/Scripts/iniparse
	cp -p ../Angel/Scripting/EngineScripts/iniparse/* Resources/Scripts/iniparse
	cp -p ../Angel/Scripting/Interfaces/angel.py Resources/Scripts

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

$(LIBANGEL):
	cd ../Angel && make
