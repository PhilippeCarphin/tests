import os
import subprocess

def block():
    input("Press any key to continue")
# TL;DR:
# os.system(cmd) will pass your cmd to '/bin/sh'
# it will expand dollar-signs
# subprocess.run([program, arg1, arg2, ...]) takes a list and doesn't do
# dollar-sign expansion.
# It is the preferred way of running commands in Python
# especially if we want to get the output back.

# NOTE: The commands that I'm running here make no
# sense, we should be using python functions to do them
# I merely use 'echo' and 'ls' as placeholders for actual
# binary files that one might want to run.

# Run shell commands
print( """os.system(cmd) will pass your cmd to '/bin/sh' it will expand dollar-signs subprocess.run([program, arg1, arg2, ...]) takes a list and doesn't do dollar-sign expansion.  subprocess is the preferred way of running commands in Python especially if we want to get the output back.""")
print("PYTHON: os.system('echo $USER')")
os.system('echo $USER')
block()

print("\nMultiple os.system() do not form a shell session")
print("PYTHON: os.system('NEW_VAR=ALLO')")
os.system('NEW_VAR=ALLO')
print("PYTHON: os.system('echo $NEW_VAR')")
os.system('echo "NEW_VAR=${NEW_VAR}"')
block()

print("\nBut Python has variables and they're muche better!")
print("PYTHON: new_var = 'allo'")
new_var = 'allo'
print('PYTHON: print(f"new_var = \'{new_var}\'"))')
print(f"new_var = '{new_var}'")
block()

print(f'\nWe should use subprocess.run() to run commands inside of python')
print("PYTHON: subprocess.run(['echo', 'This is a subprocess'])")
subprocess.run(['echo', 'This is a subprocess'])
block()

# But what if I want to user environment variables in my command?
print(f'\nsubprocess.run() does not pass through a shell so no $VAR expansion')
print("PYTHON: subprocess.run(['ls', '$SPOOKI_DIR'])")
subprocess.run(['ls', '$SPOOKI_DIR'])
block()
# That didn't work, subprocess doesn't pass things through a shell
# so our program just gets argv[1] = '$SPOOKI_DIR'
print(f'\nos.system() does $VAR expansion, but is that a good thing?')
print("PYTHON: os.system('ls $SPOOKI_DIR')")
os.system('ls $SPOOKI_DIR')
print(f'No, because we wanted the content of $SPOOKI_DIR, this should fail but instead it just did something else than what we wanted')
# Well that worked ... but only because the variable SPOOKI_DIR
# was unset, and this just did an 'ls' of PWD.
# But we, as programmers, prefer when things blow up when the program
# can't do what we want.
block()

print(f'\nIf we use Python to do our things, the command will fail instead of doing something else than what we want')
try:
    print("PYTHON: subprocess.run(['ls', os.environ['SPOOKI_DIR']])")
    subprocess.run(['ls', os.environ['SPOOKI_DIR']])
except KeyError as e:
    print(f'KeyError {e}')
    print("Oh, there is no SPOOKI_DIR environment variable, cool, thanks for letting me know instead of doing an ls of PWD!")
block()
# APPENDIX ABOUT LS:
# Since I was using 'ls', I should mention how to
# actually do it in Python:
print("\nNOTE: We should simply have been using os.listdir()")
print(f"PYTHON: home_contents = os.listdir(os.environ['HOME'])")
print("print(home_contents)")
print(os.listdir(os.environ['HOME']))
# Different behavior from BASH, I know, BASH wouldn't have
# shown the hidden files...
print(f'\nPYTHON: Listing non-hidden files in $HOME, not useful')
home = os.listdir(os.environ['HOME'])
print([f for f in home if not f.startswith('.')])
# In all my time using Python to iterate over the contents
# of a directory, I've never felt the need to do this.
# It looks more like
print(f'\nPYTHON: Because our goal is probably not to do an "ls" in Python, it is more likely to be to iterate over the contents of a directory.  If our goal was to see what was in a directory, we would just cd into it and type ls.')
for f in os.listdir(os.environ['HOME']):
    if f.endswith('.json'):
        print(f"Got a JSON file : {f}")
# So hiding the hidden files is irrelevant.
