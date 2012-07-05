#!/usr/bin/python

# This file builds all the mac version of the image libraries. 
# It won't work on Windows as it's using the Unix build methods. 

import os
import sys
import shutil

FILE_PATH = os.path.abspath(__file__)
ROOT_DIR = os.path.dirname(FILE_PATH)
INST_DIR = os.path.join(ROOT_DIR, "install")

BASE_CFLAGS = "-I%s/include -L%s/lib -m32" % (INST_DIR, INST_DIR)
BASE_CFLAGS += " -O -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk -mmacosx-version-min=10.7 -arch i386"
BASE_CPPFLAGS = BASE_CFLAGS
BASE_LDFLAGS = "-L%s/lib -lstdc++ -m32 -arch i386" % (INST_DIR)
BASE_ARCHFLAGS = "-arch i386"
CLEAN = False

LIBLIST = {
    "devil": ["DevIL-1.7.8.tar.gz", "devil-1.7.8", ["libIL.dylib", "libILU.dylib", "libILUT.dylib"]],
    "jasper": ["jasper-1.900.1.zip", "jasper-1.900.1", ["libjasper.dylib"]],
    "libjpeg": ["jpegsrc.v8a.tar.gz", "jpeg-8a", ["libjpeg.dylib"]],
    "lcms": ["lcms-1.19.tar.gz", "lcms-1.19", ["liblcms.dylib"]],
    "libpng": ["libpng-1.4.1.tar.gz", "libpng-1.4.1", ["libpng.dylib"]],
    "libmng": ["libmng-1.0.10.tar.gz", "libmng-1.0.10", ["libmng.dylib"]],
    "libtiff": ["tiff-3.9.2.tar.gz", "tiff-3.9.2", ["libtiff.dylib"]],
    }

def resetStuff():
    os.chdir(ROOT_DIR)
    os.environ['CFLAGS'] = BASE_CFLAGS
    os.environ['CPPFLAGS'] = BASE_CPPFLAGS
    os.environ['LDFLAGS'] = BASE_LDFLAGS
    os.environ['ARCHFLAGS'] = BASE_ARCHFLAGS


#####################################
# clean up if necessary             #
#####################################
if "clean" in sys.argv:
    CLEAN = True

if (CLEAN):
    if (os.path.exists(INST_DIR)):
        os.system("rm -rf %s" % INST_DIR)
    for lib, data in LIBLIST.iteritems():
        if (os.path.exists(data[1])):
            print "Clearing out %s" % data[1]
            os.system("rm -rf %s" % data[1])
    sys.exit(0)

#####################################
# unarchive everything              #
#####################################
for libname, data in LIBLIST.iteritems():
    lib = data[0]
    directory = data[1]
    if os.path.exists(directory):
        print "Skipping %s, %s already exists" % (lib, directory)
        continue
    if (libname == "libpng"):
        print "Copying libpng from Angel libraries..."
        os.system("cp -R ../../libpng-1.4.1 ./")
    elif lib.endswith(".zip"):
        print "Unzipping %s..." % lib
        os.system("unzip %s > /dev/null" % lib)
    elif (lib.endswith(".tar.gz") or lib.endswith(".tgz")):
        print "Untarring %s..." % lib
        os.system("tar -xzf %s > /dev/null" % lib)
    else:
        print "Problem, don't know how to unarchive %s" % lib

#####################################
# build libpng                      #
#####################################
if ("libpng" in LIBLIST.keys()):
    resetStuff()
    os.chdir(LIBLIST["libpng"][1])
    config_string = "./configure --disable-dependency-tracking --prefix=%s --host=i686-apple-darwin10 " % (INST_DIR)
    os.system(config_string)
    os.system('make install')
    os.system('install_name_tool -id @executable_path/../Frameworks/libpng.dylib %s/lib/libpng.dylib' % (INST_DIR))

#####################################
# build libjpeg                     #
#####################################
if ("libjpeg" in LIBLIST.keys()):
    resetStuff()
    os.chdir(LIBLIST["libjpeg"][1])
    config_string = "./configure --prefix=%s --host=i686-apple-darwin10 " % (INST_DIR)
    os.system(config_string)
    os.system('make install')
    os.system('install_name_tool -id @executable_path/../Frameworks/libjpeg.dylib %s/lib/libjpeg.dylib' % (INST_DIR))
    
#####################################
# build libtiff                     #
#####################################
if ("libtiff" in LIBLIST.keys()):
    resetStuff()
    os.chdir(LIBLIST["libtiff"][1])
    config_string = "./configure --prefix=%s --enable-shared --host=i686-apple-darwin10 " % (INST_DIR)
    os.system(config_string)
    os.system('make install')
    os.system('install_name_tool -id @executable_path/../Frameworks/libtiff.dylib %s/lib/libtiff.dylib' % (INST_DIR))

#####################################
# build liblcms                     #
#####################################
if ("lcms" in LIBLIST.keys()):
    resetStuff()
    os.chdir(LIBLIST["lcms"][1])
    config_string = "./configure --prefix=%s --host=i686-apple-darwin10 " % (INST_DIR)
    os.system(config_string)
    os.system('make install')
    os.system('install_name_tool -id @executable_path/../Frameworks/liblcms.dylib %s/lib/liblcms.dylib' % (INST_DIR))

#####################################
# build libmng                      #
#####################################
if ("libmng" in LIBLIST.keys()):
    resetStuff()
    os.chdir(LIBLIST["libmng"][1])
    os.environ['LIBTOOLIZE'] = "glibtoolize"
    os.system("ln -s makefiles/configure.in .")
    os.system("ln -s makefiles/acinclude.m4 .")
    os.system("ln -s makefiles/Makefile.am .")

    # need to patch the configure file to build with latest autoconf
    srcFile = "configure.in"
    srcFileHandle = open(srcFile)
    srcData = srcFileHandle.read()
    srcFileHandle.close()
    badString = "\nAM_C_PROTOTYPES"
    goodString = ""
    srcData = srcData.replace(badString, goodString)
    srcFileHandle = open(srcFile, 'w')
    srcFileHandle.write(srcData)
    srcFileHandle.close()

    os.system("autoreconf -fvi")
    config_string = "./configure --prefix=%s --host=i686-apple-darwin10 " % (INST_DIR)
    os.system(config_string)
    os.system('make install')
    os.system('install_name_tool -id @executable_path/../Frameworks/libmng.dylib %s/lib/libmng.dylib' % (INST_DIR))

#####################################
# build libjasper                   #
#####################################
if ("jasper" in LIBLIST.keys()):
    resetStuff()
    os.chdir(LIBLIST["jasper"][1])
    config_string = "./configure --prefix=%s --enable-shared --host=i686-apple-darwin10 " % (INST_DIR)
    os.system(config_string)
    os.system('make install')
    os.system('install_name_tool -id @executable_path/../Frameworks/libjasper.dylib %s/lib/libjasper.dylib' % (INST_DIR))

#####################################
# build libil                       #
#####################################
if ("devil" in LIBLIST.keys()):
    resetStuff()
    os.chdir(LIBLIST["devil"][1])

    # ILU contains a bug that keeps it from building on OS X. Let's patch it. 
    srcFile = "src-ILU/ilur/ilur.c"
    srcFileHandle = open(srcFile)
    srcData = srcFileHandle.read()
    srcFileHandle.close()
    badString = """
    #include <malloc.h>
    """
    goodString = """
    #if defined(__APPLE__)
        #include "sys/malloc.h"
    #else
        #include <malloc.h>
    #endif
    """
    srcData = srcData.replace(badString, goodString)
    srcFileHandle = open(srcFile, 'w')
    srcFileHandle.write(srcData)
    srcFileHandle.close()

    # replace old png functions with new hotness
    for oldFile in ['src-IL/src/il_icon.c', 'src-IL/src/il_png.c']:
        oldFileHandle = open(oldFile)
        oldData = oldFileHandle.read()
        oldFileHandle.close()
        badString = "png_set_gray_1_2_4_to_8"
        goodString = "png_set_expand_gray_1_2_4_to_8"
        oldData = oldData.replace(badString, goodString)
        badString = "png_check_sig(Signature, 8);"
        goodString = "!png_sig_cmp(Signature, 0, 8);"
        newData = oldData.replace(badString, goodString)
        oldFileHandle = open(oldFile, 'w')
        oldFileHandle.write(newData)
        oldFileHandle.close()

    config_string = "./configure --prefix=%s --enable-ILU --enable-ILUT --host=i686-apple-darwin10" % (INST_DIR)
    print(config_string)
    os.system(config_string)
    os.system('make install')
    for f in ['IL', 'ILU', 'ILUT']:
        correction_string = "install_name_tool -id @executable_path/../Frameworks/lib%s.dylib %s/lib/lib%s.1.dylib" % (f, INST_DIR, f)
        os.system(correction_string)
        if (f == 'ILU' or f == 'ILUT'):
            correction_string = "install_name_tool -change %s/lib/libIL.1.dylib @executable_path/../Frameworks/libIL.dylib %s/lib/lib%s.1.dylib" % (INST_DIR, INST_DIR, f)
            os.system(correction_string)
        if (f == 'ILUT'):
            correction_string = "install_name_tool -change %s/lib/libILU.1.dylib @executable_path/../Frameworks/libILU.dylib %s/lib/lib%s.1.dylib" % (INST_DIR, INST_DIR, f)
            os.system(correction_string)
        move_string = "mv %s/lib/lib%s.1.dylib %s/lib/lib%s.dylib" % (INST_DIR, f, INST_DIR, f)
        os.system(move_string)


#####################################
# copying                           #
#####################################
resetStuff()

libpath = os.path.join(INST_DIR, "lib") 
exppath = os.path.join(INST_DIR, "exp")
if not os.path.exists(libpath):
    os.makedirs(libpath)
if not os.path.exists(exppath):
    os.makedirs(exppath)

os.chdir(libpath)

for libname, data in LIBLIST.iteritems():
    files = data[2]
    for f in files:
        true_lib = os.path.realpath(f)
        shutil.copyfile(true_lib, os.path.join(exppath, f))


#####################################
# cleanup                           #
#####################################
# we don't care about the extra stuff that most of these libs install
# for dd in ["bin", "man", "share", "lib/pkgconfig", "lib/*.la"]:
    # dd = os.path.join(INST_DIR, dd)
    # os.system("rm -rf %s" % dd)


