#############################################################################
## Copyright (C) 2008-2010, Shane J. M. Liesegang
## All rights reserved.
## 
## Redistribution and use in source and binary forms, with or without 
## modification, are permitted provided that the following conditions are met:
## 
##     * Redistributions of source code must retain the above copyright 
##       notice, this list of conditions and the following disclaimer.
##     * Redistributions in binary form must reproduce the above copyright 
##       notice, this list of conditions and the following disclaimer in the 
##       documentation and/or other materials provided with the distribution.
##     * Neither the name of the copyright holder nor the names of any 
##       contributors may be used to endorse or promote products derived from 
##       this software without specific prior written permission.
## 
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
## IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
## ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
## LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
## CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
## SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
## INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
## CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
## POSSIBILITY OF SUCH DAMAGE.
##############################################################################

import os
import shutil

BASEDIR = os.path.join(os.environ['PROJECT_DIR'], "Angel", "Libraries", "freetype-2.3.7")
FILES = ['libfreetype.6.dylib', 'libfreetype.a']
BUILT_DIR = os.path.join(BASEDIR, "built")
LIB_DIR = os.path.join(BUILT_DIR, "lib")

os.chdir(BASEDIR)


def build():
    conf_string = 'env CFLAGS='
    conf_string +=   '"-O -g -isysroot /Developer/SDKs/MacOSX10.5.sdk -arch i386 -arch ppc" '
    conf_string += 'LDFLAGS='
    conf_string +=   '"-arch i386 -arch ppc" '
    conf_string += './configure --prefix='
    conf_string +=   BUILT_DIR
    os.system(conf_string)
    os.system('make install 2> /dev/null')

for fileName in FILES:
    src = os.path.join(LIB_DIR, fileName)
    if not os.path.exists(src):
        build()
        if not os.path.exists(src):
            print "Building FreeType didn't produce %s." % fileName
            exit(1)
