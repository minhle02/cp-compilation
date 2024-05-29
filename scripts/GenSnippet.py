from ConfigParser import ConfigParser
# import pyperclip

class GenSnippet:
    def __init__(self):
        self.config_parser = ConfigParser()
        self.path = self.config_parser.GetSnippetInput()
    
    def set_path(self, path: str):
        self.path = path
    
    def gen(self):
        input = self.path
        # with open(input, 'r') as f:
        data = open(input, 'r').read()
        output = []
        special_char = ['\\', '"']
        for line in data.splitlines():
            for char in special_char:
                if char in line:
                    line = line.replace(char, '\\' + char)
            output.append(line)
        ret = '\n'.join(output)
        # pyperclip.copy(ret)
        return ret

# obj = GenSnippet()

# print(obj.gen())
            
