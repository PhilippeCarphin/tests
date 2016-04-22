# SETUP THE TEST ENVIRONMENT
. ssmuse-sh -d /users/dor/afsi/phc/Testing/testdomain
export SEQ_MAESTRO_SHORTCUT=". ssmuse-sh -d /users/dor/afsi/phc/Testing/testdomain"
export SEQ_TRACE_LEVEL=TL_FULL_TRACE

prefix=$(date +%F%H:%M)
path=$HOME/Documents/GitCMC/listings

if [ "$1" = "" ]; then
   signal=begin
else
   signal=$1
fi

exp=/home/ops/afsi/phc/Documents/Experiences/sample_1.4.1
nodeA=dependant_12            
nodeB=dep_hs_no_default_br12_t
fileA=$path/${prefix}.$nodeA.lst
fileB=$path/${prefix}.$nodeB.lst

maestro -n /test/bug5557/$nodeA -s $signal -f continue -l l1=0 -e $exp > $fileA  2>&1
maestro -n /test/bug5557/$nodeB -s $signal -f continue -l l2=0 -e $exp > $fileB  2>&1

echo -n $prefix > $path/latest.txt

if [ "$2" = "" ]; then
   vimdiff $fileA $fileB
else
   $2 $fileA $fileB
fi

