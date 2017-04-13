make clean > /dev/null
#Reset paul.h
echo '#define PAUL "awesome"' > paul.h

pause(){
	echo -n "$(tput setaf 5)

$0 : Press any key to continue...$(tput sgr 0)"
	read
}

echocolor(){
	if [[ "$(which tput)" == "" ]] ; then
		echo "$0 : $1"
	else
		echo "$(tput setaf 3)$0 : $1 $(tput sgr 0)"
	fi
}


echocolor "First we run make.
$ make"
make

echocolor "Open the makefile and notice that although
	the dependancy that is written is
		main.o: main.c
	the dependency that we see when we do 'echo \$@:\$^ is
		main.o:main.c phil.h paul.h"
pause

echocolor "Now, we run make again to prove that I didn't do
	something to just have it compile everytime even if main.o
	is up to date.
$ make"
make

pause
echocolor "Let's run the executable : "
make run

pause
echocolor "Let's define MACRO_IN_PAUL in paul.h which
	is included in phil.h which is included in main.c.  We'll
	if main.c is recompiled as it should be.
\$ echo '#define MACRO_IN_PAUL_H' >> paul.h"
echo '#define MACRO_IN_PAUL_H' >> paul.h

pause
echocolor "Noticing that the dependency in the
	makefile is explicitely written as
		main.o: main.c
	and that we never told make explicitely that main.o is
	actually dependant on phil.h or paul.h, what do we think
	will happen? Will main.c be recompiled or will make say
	'nothing to be done for all'?"
pause
echocolor "$ make"
make

echocolor "Well would you look at that.  The bane of makefile
	users all around the world was solved a long time ago and
	we just didn't know about it!

	All this is because of the -MMD flag when we compile, and
	the -include *.d in the makefile!

	Let's run the executable one last time.
$ make run"
make run

# Reset paul.h
echo '#define PAUL "awesome"' > paul.h
