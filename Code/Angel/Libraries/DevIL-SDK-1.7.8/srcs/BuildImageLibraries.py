# This file builds all the mac version of the image libraries. 
# It won't work on Windows as it's using the Unix build methods. 

import os
import sys

FILE_PATH = os.path.abspath(__file__)
ROOT_DIR = os.path.dirname(FILE_PATH)
INST_DIR = ROOT_DIR + "/install/"

BASE_CFLAGS = "-I%sinclude -L%sinclude -m32" % (INST_DIR, INST_DIR)
BASE_CFLAGS += " -O -g -isysroot /Developer/SDKs/MacOSX10.5.sdk -mmacosx-version-min=10.5"
BASE_CPPFLAGS = BASE_CFLAGS
BASE_LDFLAGS = "-L%slib -m32 -arch i386" % (INST_DIR)
BASE_ARCHFLAGS = "-arch i386"
CLEAN = False

LIBLIST = {
    "DevIL-1.7.8.tar.gz" : "devil-1.7.8",
    "jasper-1.900.1.zip" : "jasper-1.900.1",
    "jpegsrc.v8a.tar.gz" : "jpeg-8a",
    "lcms-1.19.tar.gz" : "lcms-1.19",
    "libpng-1.4.1.tar.gz" : "libpng-1.4.1",
    "libmng-1.0.10.tar.gz" : "libmng-1.0.10",
    "tiff-3.9.2.tar.gz" : "tiff-3.9.2",
    "zlib-1.2.3.tar.gz" : "zlib-1.2.3"
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
    for lib, directory in LIBLIST.iteritems():
        if (os.path.exists(directory)):
            print "Clearing out %s" % directory
            os.system("rm -rf %s" % directory)

#####################################
# unarchive everything              #
#####################################
for lib, directory in LIBLIST.iteritems():
    if os.path.exists(directory):
        print "Skipping %s, %s already exists" % (lib, directory)
        continue
    if lib.endswith(".zip"):
        print "Unzipping %s..." % lib
        os.system("unzip %s > /dev/null" % lib)
    elif (lib.endswith(".tar.gz") or lib.endswith(".tgz")):
        print "Untarring %s..." % lib
        os.system("tar -xzf %s > /dev/null" % lib)
    else:
        print "Problem, don't know how to unarchive %s" % lib

#####################################
# build zlib                        #
#####################################
resetStuff()
os.chdir("zlib-1.2.3")
config_string = "./configure --prefix=%s " % (INST_DIR)
os.system(config_string)
os.system('make install')

#####################################
# build libpng                      #
#####################################
resetStuff()
os.chdir("libpng-1.4.1")
config_string = "./configure --disable-shared --enable-static --disable-dependency-tracking --prefix=%s " % (INST_DIR)
os.system(config_string)
os.system('make install')

#####################################
# build libjpeg                     #
#####################################
resetStuff()
os.chdir("jpeg-8a")
config_string = "./configure --prefix=%s --disable-shared --enable-static " % (INST_DIR)
os.system(config_string)
os.system('make install')

#####################################
# build libtiff                     #
#####################################
resetStuff()
os.chdir("tiff-3.9.2")
config_string = "./configure --prefix=%s --disable-shared --enable-static " % (INST_DIR)
os.system(config_string)
os.system('make install')

#####################################
# build liblcms                     #
#####################################
resetStuff()
os.chdir("lcms-1.19")
config_string = "./configure --prefix=%s --disable-shared --enable-static " % (INST_DIR)
os.system(config_string)
os.system('make install')

#####################################
# build libmng                      #
#####################################
resetStuff()
os.chdir("libmng-1.0.10")
os.environ['LIBTOOLIZE'] = "glibtoolize"
os.system("ln -s makefiles/configure.in .")
os.system("ln -s makefiles/acinclude.m4 .")
os.system("ln -s makefiles/Makefile.am .")
os.system("autoreconf -fi")
config_string = "./configure --prefix=%s --disable-shared --enable-static " % (INST_DIR)
os.system(config_string)
os.system('make install')

#####################################
# build libjasper                   #
#####################################
resetStuff()
os.chdir("jasper-1.900.1")
config_string = "./configure --prefix=%s --disable-shared --enable-static " % (INST_DIR)
os.system(config_string)
os.system('make install')

#####################################
# build libil                       #
#####################################
resetStuff()
os.chdir("devil-1.7.8")

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

config_string = "./configure --disable-shared --enable-static --prefix=%s --enable-ILU --enable-ILUT --host=i686-apple-darwin10" % (INST_DIR)
os.system(config_string)
os.system('make install')

#####################################
# cleanup                           #
#####################################
# we don't care about the extra stuff that most of these libs install
for dd in ["bin", "man", "share", "lib/pkgconfig", "lib/*.la"]:
    dd = os.path.join(INST_DIR, dd)
    os.system("rm -rf %s" % dd)


