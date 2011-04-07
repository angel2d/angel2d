DIST = $(shell ./distcheck.sh)
FUSE_LIB = /usr/lib/libfuse.so
ifeq ($(DIST),Fedora)
	FUSE_LIB = /lib/libfuse.so
endif

all: runtime AppRun AppImageAssistant

AppImageAssistant: runtime
	cp runtime ./AppImageAssistant.appdir
	./AppImageAssistant.appdir/package ./AppImageAssistant.appdir ./AppImageAssistant

runtime: fuseiso.o isofs.o runtime.o
	gcc -Os -D_FILE_OFFSET_BITS=64 -D_FILE_OFFSET_BITS=64 -I/usr/include/fuse -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -Wall -g -pthread -o runtime ./runtime.o ./fuseiso.o ./isofs.o /usr/lib/libglib-2.0.so -lz $(FUSE_LIB) -lrt -ldl
	strip ./runtime
	# ./exepak ./runtime

fuseiso.o: fuseiso.c
	gcc -Os -DHAVE_CONFIG_H -I. -D_FILE_OFFSET_BITS=64 `pkg-config --cflags fuse glib-2.0` -Wall -g -MT fuseiso.o -MD -MP -MF ".deps/fuseiso.Tpo" -c -o fuseiso.o fuseiso.c

isofs.o: isofs.c
	gcc -Os -DHAVE_CONFIG_H -I. -D_FILE_OFFSET_BITS=64 `pkg-config --cflags fuse glib-2.0` -Wall -g -MT isofs.o -MD -MP -MF ".deps/isofs.Tpo" -c -o isofs.o isofs.c

runtime.o: runtime.c
	gcc -Os runtime.c -c

AppRun: 
	gcc -Os -s -ffunction-sections -fdata-sections -Wl,--gc-sections AppRun.c -o AppRun
	strip --strip-all ./AppRun

clean:
	rm -f *.a *.o runtime AppRun AppImageAssistant ./AppImageAssistant.appdir/runtime
