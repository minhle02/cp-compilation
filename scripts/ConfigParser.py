import configparser
import os
import Constants


class ConfigParser:
    def __init__(self):
        self.parser = configparser.ConfigParser()
        file_path = Constants.ConfigConst.config_file
        try:
            self.parser.read(file_path)
        except:
            print("Unable to read from " + file_path)
    
    def GetCompiler(self):
        return str(self.parser['DEFAULT']['CompilerPath'])
    
    def GetDefaultInput(self):
        return str(self.parser['DEFAULT']['Input'])
    
    def GetDefaultOutput(self):
        return str(self.parser['DEFAULT']['Output'])

    def GetWorkDir(self):
        return str(self.parser['DEFAULT']['WorkDir'])
    
    def GetSnippetInput(self):
        return str(self.parser['SNIPPET']['InputFile'])

