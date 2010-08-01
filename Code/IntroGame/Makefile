CXX = g++
TARGET = IntroGame
ARCH := $(shell uname -m)
ALLEGRO_LIBS := $(shell allegro-config --libs 2>/dev/null)
CWD := $(shell pwd)
CODE_DIR := $(shell dirname "$(CWD)")
LIBANGEL = ../Angel/libangel.a
LUA = ../Angel/Libraries/angel-lua-build/lua
WRAPPER = ../Angel/Scripting/Interfaces/AngelLuaWrappingIntroGame.cpp

INCLUDE = 							\
	-I.							\
	-IDemoScreens						\
	-I../Angel						\
	-I../Angel/Libraries/glfw/include			\
	-I../Angel/Libraries/Box2D-2.0.1/Include		\
	-I../Angel/Libraries/FMOD/inc 				\
	-I../Angel/Libraries/FTGL/include			\
	-I../Angel/Libraries/lua-5.1.4/src			\
	-I/usr/include/freetype2
	
LIBS = 									\
	$(LIBANGEL)							\
	../Angel/Libraries/glfw/lib/x11/libglfw.a			\
	../Angel/Libraries/Box2D-2.0.1/Source/Gen/float/libbox2d.a	\
	../Angel/Libraries/FTGL/unix/src/.libs/libftgl.a		\
	../Angel/Libraries/angel-lua-build/liblua.a

ifeq ($(ARCH),x86_64)
	LIBS += ../Angel/Libraries/FMOD/lib/libfmodex64.so
else
	LIBS += ../Angel/Libraries/FMOD/lib/libfmodex.so
endif

SHLIBS = -lGL -lGLU -ldl -lfreetype -lXrandr -lX11 -lIL -lILU -lILUT
SHLIBS += $(ALLEGRO_LIBS)

SYSSRCS = 							\
	$(WRAPPER)

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

SYSOBJS = $(patsubst %.cpp,%.o,$(SYSSRCS))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: clean all SWIG-Wrapper

%.o: %.cpp
	$(CXX) -c $(INCLUDE) -Wno-write-strings -Wno-deprecated -o $@ $^

all: $(TARGET)

SWIG-Wrapper:
	$(LUA) ../Tools/BuildScripts/swig_wrap.lua -p "$(CODE_DIR)" -D INTROGAME

$(WRAPPER): SWIG-Wrapper

$(TARGET): $(LIBANGEL) $(OBJS) $(SYSOBJS) $(WRAPPER)
	$(CXX) -o $@ $(OBJS) $(SYSOBJS) $(LIBS) $(SHLIBS)
	cp -p ../Angel/Scripting/EngineScripts/*.lua Resources/Scripts

clean:
	rm -f $(OBJS) $(SYSOBJS) $(TARGET) $(WRAPPER)

$(LIBANGEL):
	cd ../Angel && make
