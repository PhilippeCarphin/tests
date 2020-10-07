import os

import json
import sys
# This is my favorite one in terms of what is easier in Python
# than in BASH
#
# It may not seem like it is at first, but once you have done one
# or two of them, it becomes an idiom and it's pretty easy to
# do.

# Root will start with the initial directory and traverse the directory tree.
# At each iteration, we are given the regular files (non-directories)
# in root,

# The dirs variable is somewhat unnecessary since the {root}/{d} for d in dirs
# will eventually be hit by root
# This is equivalent to the shell command "find ."
for root, dirs, files in os.walk(os.getcwd()):
    for f in files:
        print(os.path.join(root, f))
    for d in dirs:
        print(os.path.join(root, d))

def get_json_files(dir):
    for root, _, files in os.walk(dir):
        for f in files:
            if f.endswith('.json'):
                print(f'found {f} in {root}')
                yield os.path.join(root, f)

print(list(get_json_files(os.getcwd())))


# Once you do it a couple times, it becomes really easy.  It's pretty much always
# going to be
# for root, dirs, files in os.walk(something):
#     for f in files:
#          filepath = os.path.join(root, f)
#              if ...
#                  yield filepath
#
# If you just want all the links, then sure, doing a 'find' in BASH will work
# but if you actually want to do something with the files (-exec command {} \;)
# then you're probably going to go faster in Python

# for example, say I have a directory tree that has a bunch of json files.  And
# I want to rename a toplevel key, then I could make a python script like.

# def rename_key_json(file, old_key, new_key):
#     assert(old_key != new_key)
#     with open(file, 'r') as f:
#         d = json.load(f)
#         print(d)
#     d[new_key] = d.pop(old_key)
#     with open(file, 'w') as f:
#         json.dump(d,f)
#
# if __name__ == "__main__":
#     import sys
#     rename_key_json(sys.argv[1], sys.argv[2], sys.argv[3])

# And in a shell, I could do this:
# find . -name '*.json' -exec python3 rename_json_key.py {} old_key new_key \;

# OR the more simple approach:

#
# for root, _, files in os.walk(os.getcwd()):
#     for f in files:
#         if f.endswith('.json'):
#             rename_key_json(os.path.join(root, f), "key", "new_key")

# and I can start by just doing a print to check that I've got things right which
# would be equivalent to doing ls in the find shell command.  Then when I'm
# happy, I put the actual function call instead of the print.
# I can throw away the script after, I don't have to keep it.

