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
import glob
import sys

sys.path.append('Tools/BuildScripts')
from angel_build import recursive_copy

os.chdir(os.path.join(os.environ['PROJECT_DIR'], 'Angel', 'Scripting', 'EngineScripts'))
if (os.environ['CONFIGURATION'] == 'Debug'):
    dest = os.path.join(
            os.environ['PROJECT_DIR'],
            os.environ['EXECUTABLE_NAME'],
            'Resources',
            'Scripts'
        )
else:
    dest = os.path.join(
            os.environ['PROJECT_DIR'],
            'build',
            os.environ['CONFIGURATION'],
            os.environ['EXECUTABLE_NAME'] + '.app',
            'Contents',
            'Resources',
            'Scripts'
        )
if not os.path.exists(dest):
    os.makedirs(dest)
for fileName in glob.glob('*.py'):
    dstname = os.path.join(dest, fileName)
    shutil.copyfile(fileName, dstname)
# just grabbing this manually for now; if we want to have more libraries,
#  we'll have to find a more scalable way of doing this
source = "iniparse"
recursive_copy(source, os.path.join(dest, "iniparse"))

if (os.environ['CONFIGURATION'] == 'Debug'):
    exit(0)

source = os.path.join(os.environ['PROJECT_DIR'], os.environ['EXECUTABLE_NAME'], 'Resources')
dest = os.path.join(
        os.environ['PROJECT_DIR'],
        'build',
        os.environ['CONFIGURATION'],
        os.environ['EXECUTABLE_NAME'] + '.app',
        'Contents',
        'Resources'
    )
recursive_copy(source, dest)

source = os.path.join(os.environ['PROJECT_DIR'], os.environ['EXECUTABLE_NAME'], 'Config')
dest = os.path.join(
        os.environ['PROJECT_DIR'],
        'build',
        os.environ['CONFIGURATION'],
        os.environ['EXECUTABLE_NAME'] + '.app',
        'Contents',
        'Config'
    )
recursive_copy(source, dest)

log_path = os.path.join(
            os.environ['PROJECT_DIR'],
            'build',
            os.environ['CONFIGURATION'],
            os.environ['EXECUTABLE_NAME'] + '.app',
            'Contents',
            'Logs'
        )
if not os.path.exists(log_path):
    os.mkdir(log_path)

