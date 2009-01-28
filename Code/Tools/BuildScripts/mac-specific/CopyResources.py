import os
import shutil
import glob
import sys

sys.path.append('Tools/BuildScripts')
from angel_build import recursive_copy


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

os.chdir(os.path.join(os.environ['PROJECT_DIR'], 'Angel', 'Scripting', 'EngineScripts'))
dest = os.path.join(
        os.environ['PROJECT_DIR'],
        'build',
        os.environ['CONFIGURATION'],
        os.environ['EXECUTABLE_NAME'] + '.app',
        'Contents',
        'Resources',
        'Scripts'
    )
for fileName in glob.glob('*.py'):
    dstname = os.path.join(dest, fileName)
    shutil.copyfile(fileName, dstname)
