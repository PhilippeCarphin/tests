This test is to demonstrate how the setuid bit works.  The program
reads and prints the `~/.ssh/config` file of user phc001.

Normally, another user running this program would see `/home/phc001/.ssh/config: Permission denied`
since the file belongs to me and is inside `~/.ssh` which has permissions `rwx------`.

By doing `chmod +s` on the executable, I set it's "Setuid bit".  This means that
I allow users running this program to essentialy become me in terms of permissions.

When this is done, a user running the program will be able to read my `~/.ssh/config`
file.

NOTE: Setting the setuid bit only works on binary executables, with scripts the
potential for a security vulnerability is such that Linux disables it.  You can
do `chmod +s myscript.sh` but it won't have an effect.

By calling our script though a link named `-i`, we would be able to get an
an interactive shell with another user's privileges.  Now, doing `./-i` would
not work but by doing something like.

python3
>>> import os
>>> os.execl('-i', '-i')
bash-4.4$ _

Also, adding $PWD to our PATH doesn't make it work, when bash finds a command
in the path, it calls it with its full name.

I.E.
export PATH=${PWD}:${PATH}
-i

> $0 = '/home/phc001/-i'
