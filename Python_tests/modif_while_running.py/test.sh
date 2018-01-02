#!/bin/bash

echo "$(tput setaf 5) ======================= Launch python and sleep before modifying the file  ========= $(tput sgr 0)"
echo "import time

print(\"py_file.py : start\")
print(\"py_file.py : done\")" > py_file.py

python py_file.py &

# This sleep makes a difference in whether we will see the print("extra_line")
#
# Without it, we see the extra line, and with it we don't.  This leads me to
# believe that there is an amount of time between when the the command
#
#	$ python py_file.py &
#
# is made and the time when the interpreter is launched and loads the file into
# memory.  Without the sleep, we add the extra line before that happens and with
# the sleep, python loads the file, and THEN we add the line, in which case it
# doesn't show up.
sleep 1
# One thing that serves as evidence but is not reliable is that when we don't
# have the sleep, we see "modifying python file" before we see the "starting
# python sleep".  Even though stdout is buffered, they both output to stdout so
# the order should be the same, but nevertheless, I am always skeptical of
# trusting the order of appearance of print statements.

# However, the appearance or non-appearance is trustworthy and confirms that one
# can modify a python file while it is executing since it is copied in memory
# and then executed.

echo "./test.sh : Modifying python file"
echo "print(\"py_file : Extra_line\")" >> py_file.py
echo "print(\"py_file : now really done\")" >> py_file.py
sleep 5

echo "$(tput setaf 5) ============================== without sleep ========= $(tput sgr 0)"
echo "import time

print(\"py_file.py : start\")
print(\"py_file.py : done\")" > py_file.py

python py_file.py &

echo "$0 : Modifying python file"
echo "print(\"py_file : Extra_line\")" >> py_file.py
echo "print(\"py_file : now really done\")" >> py_file.py
sleep 7

