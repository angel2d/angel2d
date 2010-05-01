CXX = g++
TARGET = ClientGame
ARCH := $(shell uname -m)
ALLEGRO_LIBS := $(shell allegro-config --libs 2>/dev/null)
LIBANGEL = ../Angel/libangel.so

INCLUDE = 							\
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
