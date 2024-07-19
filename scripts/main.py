from ConfigParser import ConfigParser
from GenSnippet import GenSnippet
from Compile import Compile
import argparse
import pyperclip

def handler_snippet(args):
    path = args.path
    gen_snip = GenSnippet()
    gen_snip.set_path(path)
    snip = gen_snip.gen()
    pyperclip.copy(snip)
    print("*******Snippet generated:******\n")
    print(snip)
    return

def handler_compile(args):
    path = args.file_path
    input = args.input
    output = args.output
    obj = Compile()
    verbose = args.verbose
    obj.full_run(path, input, output, verbose)
    return

def parse_args():
    config_parser = ConfigParser()
    parser = argparse.ArgumentParser(
        prog="CP Util",
        description="Help with compiling"
    )
    sub_parser = parser.add_subparsers(help="Subparser", required=True)

    parser_snippet = sub_parser.add_parser('gen-snip', help="Generate c++ snippet for vscode")
    parser_snippet.add_argument('-p', '--path', type=str, default=config_parser.GetSnippetInput())
    parser_snippet.set_defaults(func=handler_snippet)

    parser_compile = sub_parser.add_parser('comp-run', help='Compile and run program')
    parser_compile.add_argument('file_path', type=str, help='source code input')
    parser_compile.add_argument('-i', '--input', type=str, default=config_parser.GetDefaultInput(), help='Input to program (txt file)')
    parser_compile.add_argument('-o', '--output', type=str, default=config_parser.GetDefaultOutput(), help='where to write output')
    parser_compile.add_argument('-v', '--verbose', action='store_true')
    parser_compile.set_defaults(func=handler_compile)

    return parser.parse_args()

def main():
    args = parse_args()
    args.func(args)


main()