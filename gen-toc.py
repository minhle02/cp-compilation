import argparse

ignore_prefix = r'[//]: <> (Ignore)'
inject_prefix = r'[//]: <> (Inject)'

def process_text(raw_text):
    text = raw_text.splitlines()
    include = True
    to_inject = 0
    process = []
    for i in range(len(text)):
        if i != 0 and ignore_prefix in text[i - 1]:
            continue
        if inject_prefix in text[i]:
            to_inject = i + 1
            continue

        if "```" in text[i]:
            include = not include

        if len(text[i]) > 1 and text[i][0] == '#' and include:
            process.append(text[i])
    return (to_inject, process)

def count_sharp(text):
    pass

def main():
    parser = argparse.ArgumentParser(description="Create TOC for Markdown")
    parser.add_argument('file_path', metavar='path-to-md', type=str)
    args = parser.parse_args()
    print(args.file_path)
    with open(args.file_path, "r") as file:
        (to_inject, text) = process_text(file.read())
    
    print(text)

main()