import os
import sys

input_from_user = "$HOME/Documents"


print(os.path.expandvars(input_from_user))
input_from_user = "~/Desktop/"

print(os.path.expanduser(os.path.expandvars(input_from_user)))


os.mkdir("mike")

