all:	libglut.a

CFLAGS=	-g -O2 -DTARGET_HOST_UNIX_X11 -DHAVE_FCNTL_H -DHAVE_SYS_IOCTL_H


OBJECTS=	\
	freeglut_callbacks.o \
	freeglut_cursor.o \
	freeglut_display.o \
	freeglut_ext.o \
	freeglut_font_data.o \
	freeglut_font.o \
	freeglut_gamemode.o \
	freeglut_geometry.o \
	freeglut_glutfont_definitions.o \
	freeglut_init.o \
	freeglut_joystick.o \
	freeglut_main.o \
	freeglut_menu.o \
	freeglut_misc.o \
	freeglut_overlay.o \
	freeglut_state.o \
	freeglut_stroke_mono_roman.o \
	freeglut_stroke_roman.o \
	freeglut_structure.o \
	freeglut_teapot.o \
	freeglut_videoresize.o \
	freeglut_window.o

libglut.a:	$(OBJECTS)
	ar cr libglut.a $(OBJECTS)
	ranlib libglut.a

clean:
	rm -f $(OBJECTS) libglut.a
