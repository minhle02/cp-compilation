import argparse
import os
import subprocess
import platform

COMPILER = "g++"
BIN_FILE = "__main__"

def compile(source_code_path: str):
    if os.path.exists(source_code_path) == False or os.path.isfile(source_code_path) == False:
        print("ERROR: File does not exist")
        raise FileNotFoundError
    elif source_code_path.endswith(".cpp") == False:  
        print("ERROR: Not .cpp file")
        raise ValueError("Not cpp file")
    else:
        subprocess.run([f'{COMPILER} {source_code_path} -o {BIN_FILE}'],
                    shell=True)

def exec(path, input: str, output: str):
    abs_path = os.path.abspath(path)
    if platform.system() == 'Windows':
        abs_path = abs_path + '.exe'
    if os.path.exists(abs_path) == True and os.path.isfile(abs_path):
        p = subprocess.run([f'{abs_path}'],
                stdin=open(input, 'r'),
                stdout=open(output, 'w'),
                shell=True)
        print(p)
    else:
        raise FileNotFoundError

def remove_bin(path):
    if (os.path.exists(path)):
        os.remove(path)
    else:
        pass

def handle(args):
    prog_path = args.prog_path
    input_file = args.i
    output_file = args.o

    compile(prog_path)
    exec(path=BIN_FILE, input=input_file, output=output_file)
    remove_bin(BIN_FILE)

parser = argparse.ArgumentParser(prog="run code file")
parser.add_argument("prog_path", metavar="p", type=str)
parser.add_argument("-i", type=str, default="input.txt")
parser.add_argument("-o", type=str, default="output.txt")

args = parser.parse_args()
handle(args)
