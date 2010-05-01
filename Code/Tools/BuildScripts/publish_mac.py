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

import sys
import os
import getopt
import shutil
import ConfigParser
import platform
from angel_build import recursive_copy, PythonPackage

def main(input_d, output_d, game_name):
    try:
        os.chdir(input_d)
    except (OSError), msg:
        print msg
        exit(1)
    
    title = None
    if (os.path.exists("build.ini")):
        config = ConfigParser.ConfigParser()
        config.read("build.ini")
        title = config.get("game_info", "name")
    if title == None:
        title = os.path.splitext(game_name)[0]
    
    output_d = os.path.join(output_d, title)
    
    if not os.path.exists(output_d):
        os.makedirs(output_d)
    
    files_base = ["GameInfo.txt", "Attributions.txt"]
    for file_base in files_base:
        shutil.copyfile(os.path.join(input_d, file_base), os.path.join(output_d, file_base))
    
    app_path = os.path.join(output_d, title + ".app")
    if os.path.exists(app_path):
        shutil.rmtree(app_path)
    shutil.copytree(os.path.join(output_d, "..", "..", "Release", game_name), app_path)
    
    script = os.path.join(app_path, "Contents", "Resources", "Scripts", "start.py")
    py_version = ".".join(map(str, platform.python_version_tuple()[0:2]))
    remotePy = os.path.join(app_path, "Contents", "Frameworks", "Python.framework")
    remotePyCurrent = os.path.join(remotePy, "Versions", py_version)
    remoteLib = os.path.join(remotePyCurrent, "lib", "python" + py_version)
    p = PythonPackage(script, remoteLib)
    p.run()
    
    shutil.copy2("/System/Library/Frameworks/Python.framework/Versions/%s/Python" % py_version, os.path.join(remotePyCurrent, "Python"))
    
    os.chdir(remotePyCurrent)
    os.chdir("..")
    os.symlink(py_version, "Current")
    os.chdir("..")
    os.symlink("Versions/Current/Python", "Python")
    
    exe_path = os.path.join(app_path, "Contents", "MacOS", "ClientGame")
    if not os.path.exists(exe_path):
        exe_path = os.path.join(app_path, "Contents", "MacOS", "IntroGame")
    if not os.path.exists(exe_path):
        print "No executable could be found."
        exit(1)
    command = ["otool", "-L", exe_path]
    put, get, err = os.popen3(command)
    put.close()
    data = get.read()
    get.close()
    err_out = err.read()
    err.close()
    if err_out:
        print "Something went wrong calling otool: %s" % err_out
        exit(1)
    lines = data.split('\n')
    py_path = None
    for line in lines:
        if line.find("Python") > 0:
            py_path = line.split()[0]
    if py_path == None:
        print "The ClientGame is not trying to link to Python in the first place. Odd."
        exit(1)
    
    pyLinkPath = "@executable_path/../Frameworks/Python.framework/Python"
    command = ["install_name_tool", "-change", py_path, pyLinkPath, exe_path]
    put, get, err = os.popen3(command)
    put.close()
    data = get.read()
    get.close()
    err_out = err.read()
    err.close()
    if err_out:
        print "Something went wrong calling install_name_tool: %s" % err_out
        exit(1)
    


if __name__ == '__main__':
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'i:o:g:')
    except getopt.error, msg:
        print msg
        exit(1)
    
    input_d = ''
    output_d = ''
    game_name = 'ClientGame.app'
    
    for o, a in opts:
        if o == "-i":
            input_d = a
        elif o == '-o':
            output_d = a
        elif o == '-g':
            game_name = a
    
    if (input_d == '' or output_d == ''):
        print "Need to provide an input and output directory."
        exit(1)
    else:
        main(input_d, output_d, game_name)

