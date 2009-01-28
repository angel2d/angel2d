###########################################################################
# GLFW top level Makefile
# $Date: 2007/03/30 20:17:42 $
# $Revision: 1.10 $
#
# This file works as a top level makefile for all supported systems and
# compilers. It builds both the GLFW link library and the supplied example
# programs.
###########################################################################

###########################################################################
# If your make program does not set the $(MAKE) variable correctly,
# uncomment the following line and make sure that the name of the make
# tool is correct.
###########################################################################
# MAKE = make


###########################################################################
# If no system/compiler is specified, display a list of available options
###########################################################################
default:
	@echo "This is the makefile for the GLFW link library and example programs."
	@echo "Type one of the following:"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) win32-mgw         for MinGW32 for Windows"
	@echo "  $(MAKE) cross-mgw         for MinGW32 for Windows on a Unix machine" 
	@echo "  $(MAKE) cross-mgw-install to install the GLFW library and header"
	@echo "  $(MAKE) cross-mgw-clean   fo clean the GLFW library and header"
	@echo "  $(MAKE) win32-cygwin      for Cygwin for Windows"
	@echo "  $(MAKE) win32-lcc         for LCC-Win32 for Windows"
	@echo "  $(MAKE) win32-bcc         for Borland C++ Builder 5.x for Windows"
	@echo "  $(MAKE) win32-msvc        for MS Visual C++ 6.x for Windows"
	@echo "  $(MAKE) win32-ow          for OpenWatcom for Windows"
	@echo "  $(MAKE) win32-pellesc     for Pelles C for Windows"
	@echo "  $(MAKE) win32-clean       to remove any compiled files for Windows"
	@echo "  $(MAKE) cygwin-clean      to remove any compiled files for Cygwin/Windows"
	@echo "  $(MAKE) cygwin-install    to install the GLFW library and header into Cygwin"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) x11               for Unix/X11 (auto-configuring)"
	@echo "  $(MAKE) x11-clean         to remove any compiled files for Unix/X11"
	@echo "  $(MAKE) x11-install       to install the GLFW library and header"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) macosx-gcc        for GCC for Mac OS X (free Apple SDK)"
	@echo "  $(MAKE) macosx-clean      to remove any compiled files for Mac OS X"
	@echo "  $(MAKE) macosx-install    to install the GLFW library and header"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) amigaos-gcc       for AmigaOS for GCC (Geek Gadgets)"
	@echo "  $(MAKE) amigaos-vbcc      for AmigaOS for VBCC"
	@echo "  $(MAKE) amigaos-clean     to remove any compiled files for AmigaOS"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) dos-djgpp         for DOS for DJGPP"
	@echo "  $(MAKE) dos-clean         to remove any compiled files for DOS"
	@echo "-----------------------------------------------------------------------------"


###########################################################################
# List of example programs (used for cleanup)
###########################################################################
EXAMPLES = boing \
           gears \
           keytest \
           listmodes \
           mipmaps \
           mtbench \
           mthello \
           particles \
           pong3d \
           splitview \
           triangle \
           wave


###########################################################################
# Windows
###########################################################################

# Cleanup for Windows
win32-clean:
	@.\\compile.bat CLEAN

# Cleanup for Cygwin (Cygwin Make does not support local BAT-files)
cygwin-clean:
	cd lib/win32 && $(MAKE) -f Makefile.win32.cygwin clean
	cd examples  && $(MAKE) -f Makefile.win32.cygwin clean

cygwin-install: win32-cygwin
	cd lib/win32 && $(MAKE) -f Makefile.win32.cygwin install

# Cleanup for MinGW32 Cross compilation from Unix
cross-mgw-install: cross-mgw 
	cd lib/win32 && $(MAKE) -f Makefile.win32.cross-mgw install 

cross-mgw-clean:
	cd lib/win32 && $(MAKE) -f Makefile.win32.cross-mgw clean 
	cd examples  && $(MAKE) -f Makefile.win32.cross-mgw clean


# Windows, MinGW32
win32-mgw:
	@./compile.bat $(MAKE) mgw

# Cross compilation from unix to win32 
cross-mgw:
	cd lib/win32 && $(MAKE) -f Makefile.win32.cross-mgw
	cd examples  && $(MAKE) -f Makefile.win32.cross-mgw 

# Windows, Cygwin (Cygwin Make does not support local BAT-files)
win32-cygwin:
	cd lib/win32 && $(MAKE) -f Makefile.win32.cygwin
	cd examples  && $(MAKE) -f Makefile.win32.cygwin

# Windows, LCC-Win32
win32-lcc:
	@.\\compile.bat $(MAKE) lcc

# Windows, Borland C++ Builder Compiler 5.x
win32-bcc:
	@.\\compile.bat $(MAKE) bcc

# Windows, Microsoft Visual C++
win32-msvc:
	@.\\compile.bat $(MAKE) msvc

# Windows, OpenWatcom
win32-ow:
	@.\\compile.bat $(MAKE) ow

# Windows, Pelles C
win32-pellesc:
	@.\\compile.bat $(MAKE) pellesc


###########################################################################
# X11 (Unix and Unix-like systems)
###########################################################################

MAKEFILES_X11_IN  = lib/x11/Makefile.x11.in  examples/Makefile.x11.in
MAKEFILES_X11     = lib/x11/Makefile.x11     examples/Makefile.x11

# Cleanup for X11 (must be here due to generated makefile)
x11-clean:
	rm -f $(MAKEFILES_X11)
	rm -f config.log
	rm -f lib/x11/*.o
	rm -f lib/x11/libglfw.a
	rm -f lib/x11/libglfw.so
	rm -f lib/x11/libglfw.pc
	rm -f lib/x11/libglfw.pc.in
	cd examples; rm -f $(EXAMPLES)

# Auto configuration for X11
$(MAKEFILES_X11) : compile.sh $(MAKEFILES_X11_IN)
	@sh ./compile.sh

# X11
x11: $(MAKEFILES_X11)
	cd lib/x11;  $(MAKE) -f Makefile.x11
	cd examples; $(MAKE) -f Makefile.x11

# X11 install
x11-install: x11
	cd lib/x11;  $(MAKE) -f Makefile.x11 install


###########################################################################
# Mac OS X
###########################################################################

# Cleanup for Mac OS X
macosx-clean:
	cd lib/macosx; $(MAKE) -f Makefile.macosx.gcc clean
	cd examples;   $(MAKE) -f Makefile.macosx.gcc clean

# Mac OS X, GCC
macosx-gcc: macosx-gcc-library macosx-gcc-examples

macosx-gcc-library:
	cd lib/macosx; $(MAKE) -f Makefile.macosx.gcc

macosx-gcc-examples:
	cd examples;   $(MAKE) -f Makefile.macosx.gcc

# Mac OS X, GCC install
macosx-install: macosx-gcc-library
	cd lib/macosx; $(MAKE) -f Makefile.macosx.gcc install


###########################################################################
# AmigaOS
###########################################################################

# Cleanup for AmigaOS
amigaos-clean:
	@execute compile.ami CLEAN

# AmigaOS, VBCC
amigaos-vbcc:
	@execute compile.ami $(MAKE) vbcc

# AmigaOS, GCC
amigaos-gcc:
	@execute compile.ami $(MAKE) gcc


###########################################################################
# DOS
###########################################################################

# Cleanup for DOS
dos-clean:
	@rm -f lib/dos/*.o
	@rm -f lib/dos/libglfw.a
	@rm -f examples/*.exe

# DOS, DJGPP (GCC)
dos-djgpp:
	@cd lib\dos;  $(MAKE) -f Makefile.dos.djgpp
	@cd examples; $(MAKE) -f Makefile.dos.djgpp

