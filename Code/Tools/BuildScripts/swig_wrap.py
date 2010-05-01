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

# This script checks the included files in the aggregate scripting interface 
#  and touches it if any of them are newer than the generated wrapper. 

import os
import sys
import getopt
import re

from stat import *
from angel_build import generate_typemaps


def main(proj_dir):
    INTERFACE_DIRECTORY = os.path.join(proj_dir, "Angel", "Scripting", "Interfaces")
    MASTER_FILE = "angel.i"
    WRAPPER_FILE = "AngelPythonWrapping.cpp"
    AGGREGATE_INTERFACE = os.path.join(INTERFACE_DIRECTORY, MASTER_FILE)
    WRAPPER_SOURCE = os.path.join(INTERFACE_DIRECTORY, WRAPPER_FILE)
        
    if (sys.platform[:3] == 'win'):
        SWIG_PATH = os.path.join(proj_dir, "Tools", "swigwin-1.3.36", "swig.exe")
    elif (sys.platform == 'darwin'):
        SWIG_PATH = "swig"
    else:
        if (os.system("which swig") != 0):
            sys.stderr.write("ERROR: swig not found.\n")
            exit(1)
        SWIG_PATH = "swig"
    SWIG_OPTIONS = " -c++ -python -Werror -o " + WRAPPER_SOURCE + " " + AGGREGATE_INTERFACE
    
    
    os.chdir(os.path.join(proj_dir, "Tools", "BuildScripts"))
    
    if not os.path.exists(AGGREGATE_INTERFACE):
        sys.stderr.write("ERROR: Couldn't find " + AGGREGATE_INTERFACE + ".")
        exit(1)
    
    interface_file = open(AGGREGATE_INTERFACE, 'r')
    lines = interface_file.readlines()
    
    files = []
    for line in lines:
        if not re.match(r'^%include', line):
            continue
        files.append(os.path.join(INTERFACE_DIRECTORY, line.split(" ")[1]))
    files.append(os.path.join(INTERFACE_DIRECTORY, MASTER_FILE))
    
    files = map(lambda x: x.replace("\n", ""), files)
    
    generate_typemaps(files, INTERFACE_DIRECTORY)
    
    if os.path.exists(WRAPPER_SOURCE):
        wrapper_modification = os.stat(WRAPPER_SOURCE)[ST_MTIME]
        interface_modification = os.stat(AGGREGATE_INTERFACE)[ST_MTIME]
        
        update = False
        
        for interface_file in files:
            if (os.path.exists(os.path.join(INTERFACE_DIRECTORY, interface_file))):
                if wrapper_modification < os.stat(os.path.join(INTERFACE_DIRECTORY, interface_file))[ST_MTIME]:
                    update = True
                    print "At least", interface_file, "was newer than", WRAPPER_FILE, "-- touching", MASTER_FILE, "and regenerating", WRAPPER_FILE
                    os.utime(AGGREGATE_INTERFACE, None)
                    os.remove(WRAPPER_SOURCE)
                    break
        
        if not update:
            print "Interface files are up to date."
        else:
            os.system(SWIG_PATH + SWIG_OPTIONS)
        
    else:
        print "No existing wrapper file; generating", WRAPPER_FILE
        os.system(SWIG_PATH + SWIG_OPTIONS)
    


if (__name__ == '__main__'):
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'p:')
    except getopt.error, msg:
        print msg
        exit(1)
    
    proj_dir = ''
    for o, a in opts:
        if o == '-p':
            proj_dir = a
    
    if (proj_dir == ''):
        print "Need to provide a project directory."
        exit(1)
    else:
        main(proj_dir)

