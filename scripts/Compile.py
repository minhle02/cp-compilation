from ConfigParser import ConfigParser
import Constants

import os
import subprocess
import platform


class Compile:
    def __init__(self):
        self.config_parser = ConfigParser()

    def create_folder(self):
        workdir = self.config_parser.GetWorkDir()
        outdir = os.path.join(os.getcwd(), workdir)
        if False == os.path.exists(outdir):
            os.mkdir(outdir)
        return outdir
    
    def compile(self, source_code_path: str):
        if os.path.exists(source_code_path) == False or os.path.isfile(source_code_path) == False:
            print("ERROR: File does not exist")
            raise FileNotFoundError
        elif source_code_path.endswith(".cpp") == False:  
            print("ERROR: Not .cpp file")
            raise ValueError("Not cpp file")
        else:
            compiler = self.config_parser.GetCompiler()
            exec_file = Constants.CompileConst.exec_file
            out_dir = self.create_folder()
            output = f'{out_dir}/{exec_file}'
            subprocess.run([f'{compiler} {source_code_path} -o {output}'],
                        shell=True)
            return output
    
    def exec(self, path, input: str, output: str):
        # input = self.config_parser.GetDefaultInput()
        # output = self.config_parser.GetDefaultOutput()
        abs_path = os.path.abspath(path)
        if platform.system() == 'Windows':
            abs_path = abs_path + '.exe'
        if os.path.exists(abs_path) == True and os.path.isfile(abs_path):
            subprocess.run([f'{abs_path}'],
                        stdin=open(input, 'r'),
                        stdout=open(output, 'w'),
                        shell=True)
        else:
            raise FileNotFoundError
    
    def remove_bin(self, path):
        if (os.path.exists(path)):
            os.remove(path)
        else:
            raise FileNotFoundError
    
    def full_run(self, source_code_path, input, output):
        path = self.compile(source_code_path)
        self.exec(path, input, output)
        self.remove_bin(path)