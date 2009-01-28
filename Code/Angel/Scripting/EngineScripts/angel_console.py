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
        if "." in input:
            return self._instance_matches(input)
        else:
            return self._global_matches(input)
    
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


