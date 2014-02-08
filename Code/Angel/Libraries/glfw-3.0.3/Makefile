CC = cc
CFLAGS = -D_GLFW_USE_CONFIG_H -Wall
AR = ar rcu
RANLIB = ranlib
TARGET = src/libglfw3.a

SRCS =				\
	src/clipboard.c		\
	src/context.c		\
	src/gamma.c		\
	src/init.c		\
	src/input.c		\
	src/joystick.c		\
	src/monitor.c		\
	src/time.c		\
	src/window.c		\
	src/x11_clipboard.c	\
	src/x11_gamma.c		\
	src/x11_init.c		\
	src/x11_joystick.c	\
	src/x11_monitor.c	\
	src/x11_time.c		\
	src/x11_window.c	\
	src/x11_unicode.c	\
	src/glx_context.c

all: $(TARGET)

OBJS = $(patsubst %.c,%.o,$(SRCS))

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(TARGET): $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

clean: 
	rm -f $(OBJS) $(TARGET)
