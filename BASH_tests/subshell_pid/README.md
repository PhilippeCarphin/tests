This test demonstrates certain aspects of process creation in the context of
subshells.

The script `demo.sh` runs `script.sh` in different ways, subshell, sourcing,
sourcing in a subshell, and more.

The main thing to remember is that `$$` in BASH does not necessarily represent
the PID of the process that is executing the command `echo $$`.

```
$ echo $$
$ (echo $$)
```

So `$$` is meant to represent the "main" shell's PID.

will both print the same thing even if the second one executes in a subshell
which is a different process.

The secon

```
$ echo $$
$ (bash -c 'echo ${PPID}')
$ (bash -c 'echo ${PPID}' ; a=1)
```
