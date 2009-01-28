import os

os.chdir(os.path.join(os.environ['PROJECT_DIR'], "Angel", "Libraries", "freetype-2.3.7"))

if not os.path.exists('objs/ftmodule.h'):
    os.system('env CFLAGS="-O -g -isysroot /Developer/SDKs/MacOSX10.5.sdk -arch i386 -arch ppc" LDFLAGS="-arch i386 -arch ppc" ./configure --prefix=')
    os.system('make')
