import os
import shutil

os.chdir(os.path.join(os.environ['PROJECT_DIR'], "Angel", "Libraries", "freetype-2.3.7"))

files = ['libfreetype.6.dylib', 'libfreetype.a']
for fileName in files:
    src = "objs/.libs/" + fileName
    dest = os.path.join(os.environ['PROJECT_DIR'], "Angel", "Libraries", "freetype-2.3.7", "built", fileName)
    shutil.copyfile(src, dest)
