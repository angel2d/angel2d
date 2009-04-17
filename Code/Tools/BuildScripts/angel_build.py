#############################################################################
## Copyright (C) 2008-2009, Shane J. M. Liesegang
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
import sys
import modulefinder
import compileall
import re
import inspect
import zipfile
import shutil

def recursive_copy(source, dest):
    if (os.path.basename(source)[0] == '.'):
        # print "Skipping", os.path.basename(source)
        return
    
    names = os.listdir(source)
    if not os.path.exists(dest):
        os.makedirs(dest)
    for name in names:
        srcname = os.path.join(source, name)
        dstname = os.path.join(dest, name)
        
        if (os.path.isdir(srcname)):
            recursive_copy(srcname, dstname)
        elif (os.path.basename(srcname)[0] != '.'):
            shutil.copyfile(srcname, dstname)



class PythonPackage:
    def __init__(self, script, remoteLib):
        self.script = script
        self.remoteLib = remoteLib
        
        # Get all the modules that aren't imported by just our scripts, but are
        #  necessary for the interpreter to load up without complaining. 
        self.implicits = [
            'warnings',
            'UserDict',
            'stat',
            'sre_parse',
            'sre_constants',
            'sre_compile',
            'site',
            're',
            'os',
            'ntpath',
            'locale',
            'linecache',
            'copy_reg',
            'codecs',
            ]
        self.mods = []
        self.builtins = []
        self.ignores = ['__main__']
        self.path = []
        
        self.mf = None
        
        
    def setup(self, script):
        pass
    
    def processStartScript(self, script):
        self.path = sys.path[:]
        self.path[0] = os.path.dirname(self.script)
        
        self.mf = modulefinder.ModuleFinder(self.path, 0, ['_angel'])
        
        for mod in self.implicits:
            self.mf.import_hook(mod)
        
        self.mf.run_script(script)
    
    def postProcessResults(self, script):
        alreadies = []
        dict = self.mf.modules
        self.mods = dict.keys()
        for mod in self.mods:
            # clear out any that we're already going to copy over
            if dict[mod].__file__:
                if os.path.dirname(dict[mod].__file__) == os.path.dirname(script):
                    alreadies.append(mod)
            
            # if there's no file (it's built-in to the interpreter), clear it
            if not dict[mod].__file__:
                self.builtins.append(mod)
        
        pre = self.mods
        self.mods = filter(lambda x: x not in self.builtins, self.mods)
        self.mods = filter(lambda x: x not in self.ignores, self.mods)
        self.mods = filter(lambda x: x not in alreadies, self.mods)
    
    
    def copyFiles(self, remoteLib):
        for mod in self.mods:
            fileName = self.mf.modules[mod].__file__
            remoteBase = ''
            loc = os.path.dirname(fileName)
            while (True):
                if (loc in self.path):
                    break
                else:
                    remoteBase = os.path.join(os.path.basename(loc), remoteBase)
                    loc = os.path.dirname(loc)
            
            src = self.mf.modules[mod].__file__
            dest = os.path.join(remoteLib, remoteBase)
            if not os.path.exists(dest):
                os.makedirs(dest)
            shutil.copyfile(src, os.path.join(dest, os.path.basename(src)))
    
    
    def makeItSnappy(self, script, remoteLib):
        compileall.compile_dir(remoteLib)
        compileall.compile_dir(os.path.dirname(script))
    
    
    def makeItTrim(self, remoteLib):
        pyZip = os.path.join(remoteLib, "..", "python25.zip")
        pyz = zipfile.PyZipFile(pyZip, 'w')
        pyz.writepy(remoteLib)
        pyz.close()
        shutil.rmtree(remoteLib)
        pass
    
    def run(self):
        print "Setup..."
        self.setup(self.script)
        print "Process script..."
        self.processStartScript(self.script)
        print "Post-process results..."
        self.postProcessResults(self.script)
        print "Copy files..."
        self.copyFiles(self.remoteLib)
        print "Make it snappy..."
        self.makeItSnappy(self.script, self.remoteLib)
        print "Make it trim..."
        self.makeItTrim(self.remoteLib)
        

def _create_descendant_mapping(class_children):
    """Take a dict of classes mapped to lists of children and return a dict of
    classes mapped to lists of all listed descendants."""
    class_descendants = dict((name, []) for name in class_children.iterkeys())
    for class_name in class_children.iterkeys():
        if not class_descendants[class_name]:
            _resolve_descendant_map(class_name, class_children, class_descendants)
    
    return class_descendants

def _resolve_descendant_map(class_name, class_children, class_descendants):
    """Find all descendants for a class and all of its descendants recursively, and
    insert the descendants into the list in class_descendants."""
    children = class_children[class_name]
    descendants = class_descendants[class_name]
    if not descendants:
        descendants = descendants + children
        for child in children:
            if child in class_descendants:
                if not class_descendants[child]:
                    _resolve_descendant_map(child, class_children, class_descendants)
                for new_descendant in class_descendants[child]:
                    if new_descendant not in descendants:
                        descendants.append(new_descendant)
        class_descendants[class_name] = descendants

def _write_typemaps(filename, class_data):
    inh_file = open(os.path.join(os.getcwd(), filename), 'w')
    inh_file.write("%include <factory.i>\n\n")
    for class_name in class_data.keys():
        inh_file.write("%factory(" + class_name + "*, " + ", ".join(class_data[class_name]) +");\n")
    inh_file.close()
    

def generate_typemaps(files, interface_directory):
    class_data = {}
    class_regex = re.compile(r"\sclass\s(\S*)\s([^\{]*)", re.MULTILINE | re.DOTALL)
    comment_regex = re.compile(r"/\*.*?\*/", re.MULTILINE | re.DOTALL)
    cpp_comment_regex = re.compile(r"//.*")
    for interface_file in files:
        if (os.path.exists(os.path.join(interface_directory, interface_file))):
            file_contents = open(os.path.join(interface_directory, interface_file), 'r').read()
            results = class_regex.findall(file_contents)
            if (results):
                for result in results:
                    derived = result[0]
                    inh = result[1]
                    if inh.find(":") >= 0:
                        # somewhere in here is inheritance
                        
                        # there's likely a more efficient way to do this. but "meh"
                        inh = comment_regex.sub('', inh)
                        inh = cpp_comment_regex.sub('', inh)
                        inh = inh.replace('\n', '')
                        inh = inh.replace(':', '')
                        inh = inh.replace('public', '')
                        inh = inh.replace('protected', '')
                        inh = inh.replace('private', '')
                        
                        for base in inh.split(','):
                            base = base.strip()
                            if base not in class_data.keys():
                                class_data[base] = []
                            class_data[base].append(derived)
                            
    
    descendant_mapping = _create_descendant_mapping(class_data)
    
    chains = {}
    for class_ in descendant_mapping:
        if len(descendant_mapping[class_]) > 0:
            chain = descendant_mapping[class_]
            chain.reverse()
            chains[class_] = chain
            
    out_strings = []
    for class_ in sorted(chains.keys()):
        out_strings.append(class_ + ": " + ", ".join(chains[class_]))
    
    out_string = "\n".join(out_strings)
    
    need_to_generate = False
    out_file_path = os.path.join(os.getcwd(), "build_cache", "typemaps.txt")
    if not os.path.exists(out_file_path):
        if not os.path.exists(os.path.dirname(out_file_path)):
            os.makedirs(os.path.dirname(out_file_path))
        out_file = open(out_file_path, 'w')
        out_file.write(out_string)
        out_file.close()
        need_to_generate = True
    else:
        out_file = open(out_file_path, 'r')
        current_file = out_file.read()
        out_file.close()
        if current_file != out_string:
            out_file = open(out_file_path, 'w')
            out_file.write(out_string)
            out_file.close()
            need_to_generate = True
    
    interface_file = os.path.join(interface_directory, "inheritance.i")
    if not os.path.exists(interface_file):
        need_to_generate = True
    
    if need_to_generate:
        _write_typemaps(interface_file, chains)
