#
# First of all, pipes create subprocesses, but this is an example where
# it is easy to forget that it does.
#
sum=0
echo $'1\n2\n3\n4' | while read n ; do
    ((sum+=n))
done

#
# The <(...) construct allows us to send something to the standard input of
# a command without creating an additional process.
#
# A process is indeed created for the evaluation of the <(...) but the output
# of that process is the input of the main shell process whose PID is $$.
#
while read n ; do
    ((sum+=n))
done < <(echo $'1\n2\n3\n4')

#
# This also works for connecting the output of a command to *this process*
# by going through a file.  If the original source is a file, then that's great
# otherwise use the previous technique.
#
echo $'1\n2\n3\n4' > n.txt
while read n ; do
    ((sum+=n))
done < n.txt
echo "sum=$sum"
