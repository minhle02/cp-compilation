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
    return text.count("#")

def gen_toc(text):
    default_sharp = 2
    
    toc = []
    num = 1
    for line in text:
        des = line.split('#')[-1].strip()
        order = count_sharp(line) - default_sharp
        if order == 0:
            content = '[' + des + ']'
            des = des.lower().split(' ')
            des = '-'.join(des)
            content = content + '(#' +  des + ')'
            toc.append(str(num) + '. ' + content)
            num += 1
        else:
            pass
    return toc

def main():
    parser = argparse.ArgumentParser(description="Create TOC for Markdown")
    parser.add_argument('file_path', metavar='path-to-md', type=str)
    args = parser.parse_args()
    print(args.file_path)
    with open(args.file_path, "r") as file:
        (to_inject, text) = process_text(file.read())
    
    toc = gen_toc(text)
    with open(args.file_path, "r") as f:
        contents = f.readlines()

    contents.insert(to_inject, '\n\n'.join(toc))

    with open(args.file_path, "w") as f:
        contents = "".join(contents)
        f.write(contents)

main()