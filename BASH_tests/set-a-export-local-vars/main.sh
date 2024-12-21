
#
# This test demonstrates the effect of `set -a` and the fact that local
# variables can be exported.
#
# set -a: (set -o allexport) mark variables which are modified or created for
#         export.
#
# exporting locals: A local variable can be exported (marked for export) and
#                   it will be in the environment of child processes created
#                   while the variable is in scope.  The variable will be unset
#                   when the function ends

myfunc(){

    echo "begin myfunc()"
    local hello_local=world
    local -x hello_local_x=world_local_x
    hello_global=world_global
    export hello_global_x=world_global_x
    env | grep ^hello | sed 's/.*/   \0/'
    echo "end myfunc()"
}


echo "======== calling myfunc before set -a"
# in the child process env, we see hello_local_x and hello_global_x
myfunc
echo "======== running env after myfunc"
# after the function, hello_local_x is unset so the child process doesn't see it.
# hello_global_x is marked for export and is still visible
env | grep ^hello | sed 's/.*/   \0/'
echo "======== calling myfunc after set -a"
# All 4 variables are exported
set -a
myfunc
echo "======== running env after final myfunc"
# The two local variables are unset when we leave the function but hello_global
# has joined the export set because set -a was activated when it was assigned to.
env | grep ^hello | sed 's/.*/   \0/'
