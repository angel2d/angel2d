import sys
import os
import getopt
import shutil
import ConfigParser
from angel_build import recursive_copy, PythonPackage

def main(input_d, output_d, game_name):
    try:
        os.chdir(input_d)
    except (OSError, WindowsError), msg:
        print msg
        exit(1)

    title = None
    if (os.path.exists("build.ini")):
        config = ConfigParser.ConfigParser()
        config.read("build.ini")
        title = config.get("game_info", "name")
    if title == None:
        title = os.path.splitext(game_name)[0]
    
    bits_path = os.path.join(output_d, "bits")
    if not os.path.exists(bits_path):
        os.makedirs(bits_path)
    
    files_ex = ["FreeImage.dll", "python25.dll", "fmodex.dll"]
    files_base = ["GameInfo.txt", "Attributions.txt"]
    directories = ["Resources", "Config", "Logs"]
    
    for file_ex in files_ex:
        shutil.copyfile(os.path.join(input_d, file_ex), os.path.join(bits_path, file_ex))
    for file_base in files_base:
        shutil.copyfile(os.path.join(input_d, file_base), os.path.join(output_d, file_base))
    for directory in directories:
        recursive_copy(os.path.join(input_d, directory), os.path.join(bits_path, directory))
    
    shutil.copyfile(os.path.join(input_d, "Release", game_name), os.path.join(bits_path, title + ".exe"))
    
    script = os.path.join("Resources", "Scripts", "start.py")
    remoteLib = os.path.join(bits_path, "pylib")
    p = PythonPackage(script, remoteLib)
    p.run()
    
    batch = open(os.path.join(output_d, title + ".bat"), "w")
    batch.write("cd bits\n\"" + title + ".exe\"")
    batch.close()
    


if __name__ == '__main__':
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'i:o:g:')
    except getopt.error, msg:
        print msg
        exit(1)
    
    input_d = ''
    output_d = ''
    game_name = 'ClientGame.exe'

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

