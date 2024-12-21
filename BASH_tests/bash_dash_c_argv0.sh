
#
# This test demonstrates that $0 is taken from the first
# argument to `bash -c CODE` if there is one:
#

bash -c 'echo "\$0=$0"'
bash -c 'echo "\$0=$0"' dollar_0
bash -c 'echo "\$0=$0, \$*=\"$*\""' dollar_0 arg1 arg2 arg3

