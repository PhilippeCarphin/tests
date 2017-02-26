filename=$HOME/Desktop/Notes/Install/`hostname`_install_notes.txt
program=gvim

if [ "$2" != "" ] ; then
   program=$2
fi

echo "
`date +20%y-%m-%d--%H:%M:%S` $1
   Reference 
      
   Action
      
   Remarks
      " >> $filename


if [ $program = vim -o $program = gvim ]; then
   $program $filename '+:$-5'
else
   $program $filename
fi
