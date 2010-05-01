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
import re
import keyword
import __builtin__
from code import InteractiveConsole, softspace
from codeop import compile_command

import angel

class AngelConsole(angel.Console, InteractiveConsole):
        
    def __init__(self, local_space):
        angel.Console.__init__(self)
        InteractiveConsole.__init__(self, local_space, "[AngelConsole]")
        self.ps1 = ">>> "
        self.ps2 = "... "
        self.prompt = self.ps1
        self.SetPrompt(self.prompt)
        self.silenced = False
        self._local_space = local_space
        sys.stdout = self
        sys.stderr = self
        
        
        message = self.word_wrap("This console is almost the same as the Python interactive interpreter. Just make sure not to run any code that blocks on console input, or the whole engine will hang.")
        
        self.write("Python %s on %s: [%s]\n%s\n\n" %
                   (sys.version, sys.platform, self.__class__.__name__, message)
                   )
        
    def Execute(self, input_text):
        self.write(self.prompt + input_text + '\n')
        try:
            more = self.push(input_text)
            if (more):
                self.prompt = self.ps2
                self.SetPrompt(self.prompt)
            else:
                self.prompt = self.ps1
                self.SetPrompt(self.prompt)
        except SystemExit:
            print "Can't exit game from console."
            self.resetbuffer()
        except:
            self.showtraceback()
            self.resetbuffer()
    
    def GetCompletions(self, input):
        try:
            if "." in input:
                return self._instance_matches(input)
            else:
                return self._global_matches(input)
        except NameError:
            return []
    
    def _instance_matches(self, input):
        m = re.match(r"(\w+(\.\w+)*)\.(\w*)", input)
        if not m:
            return []
        expr, attr = m.group(1,3)
        obj = eval(expr, globals(), self._local_space)
        words = dir(obj)
        if hasattr(obj, '__class__'):
            words.append('__class__')
            words = words + self._get_class_members(obj.__class__)
        matches = []
        n = len(attr)
        for word in words:
            if word[:n] == attr and word != "__builtins__":
                insertion = "%s.%s" % (expr, word)
                if insertion not in matches:
                    matches.append(insertion)
        return matches
    
    def _global_matches(self, input):
        matches = []
        n = len(input)
        for keywords in [keyword.kwlist, __builtin__.__dict__.keys(), self._local_space.keys()]:
            for word in keywords:
                if word[:n] == input and word != "__builtins__":
                    if word not in matches:
                        matches.append(word)
        return matches
    
    def _get_class_members(self, klass):
        ret = dir(klass)
        if hasattr(klass, '__bases__'):
            for base in klass.__bases__:
                ret = ret + self._get_class_members(base)
        return ret
    
    def word_wrap(self, text, width=100):
        return reduce(lambda line, word, width=width: '%s%s%s' %
                      (line,
                       ' \n'[(len(line)-line.rfind('\n')-1
                             + len(word.split('\n',1)[0]
                                  ) >= width)],
                       word),
                      text.split(' ')
                     )
    
    def write(self, data):
        if self.silenced:
            return
        self.WriteToOutput(  self.word_wrap(str(data))  )


