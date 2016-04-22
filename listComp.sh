# USAGE, 
#        listComp [signal difftool]
# positionnal parameters, so if you want to specify a difftool, you also need to
# specify a signal. I'm only human after all :)
#
# Enter the experiment, and the nodes whose listing you want to compare.
# The path where the listings will be saved must exist.  Please also modify the
# SETUP TEST ENVIRONMENT part to match your setup. These lines are not necessary
# if the script is run in a test environmet, but I have so many shells open that
# it's too easy to make the mistake of running in an operational environment.


expA=/home/ops/afsi/phc/Documents/Experiences/sample_1.4.1
containerA=/test/bug5557
nodeA=dep_hs_no_default_00

expB=/home/ops/afsi/phc/Documents/Experiences/sample
containerB=/sample_module/Dependency_Examples
nodeB=Dep_outerloop

default_signal=submit
path=$HOME/Documents/GitCMC/listings

# SETUP THE TEST ENVIRONMENT
. ssmuse-sh -d /users/dor/afsi/phc/Testing/testdomain
export SEQ_MAESTRO_SHORTCUT=". ssmuse-sh -d /users/dor/afsi/phc/Testing/testdomain"

prefix=$(date +%F%H:%M)
if [ "$1" = "" ]; then
   signal=default_signal
else
   signal=$1
fi
fileA=$path/${prefix}.$nodeA.lst
fileB=$path/${prefix}.$nodeB.lst

export SEQ_TRACE_LEVEL=TL_FULL_TRACE
maestro -n $containerA/$nodeA -s $signal -f continue -l l1=0 -e $expA > $fileA  2>&1
maestro -n $containerB/$nodeB -s $signal -f continue -l l2=0 -e $expB > $fileB  2>&1

if [ "$2" = "" ]; then
   vimdiff $fileA $fileB
else
   $2 $fileA $fileB
fi
