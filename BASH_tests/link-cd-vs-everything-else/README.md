This test demonstrates the different handling of `..` by the bash builtin `cd`
versus pretty much everything else including `[[ ]]` tests.

The script `demo.sh` prints the commands that it runs, their result, and
explanations.  This is the result:

```txt
tree of directory link-cd-vs-everything-else
============================================

a
├── a-file
├── b
│   ├── b-file
│   └── c
│       ├── c-file
│       └── d
│           └── d-file
└── lc -> b/c

5 directories, 4 files


Question
========

When we cd to 'a/lc/d', what does '../..' mean relative to that?
Is it 'a' because each '..' cancels out one token of 'a/lc/d' or
is it 'a/b' because it is the parent of the parent of the
directory we find ourselves in?

EXPLANATION
===========

We are in a/lc but really we are in 'a/b/c/d' since lc -> c/b

The directory we are in only has one parent and that is 'c', which only has
one parent and that parent is 'b':

        ls ../..' lists the content of '${this_dir}/a/b'"

But if we do 'cd a/lc', we kinda want 'cd ..' to bring us back to 'a'. So
'cd' cares about 'how we got there' and PWD=${this_dir}/a/lc/d
has this information.

'cd' works only by string manipulation on $PWD where '..' simply "consumes" or
cancels out the preceding path component $PWD (unless we use 'cd -P')

        'cd ../..' goes to '${this_dir}/a'"

DEMONSTRATIONS
==============


==> ls ../..
b-file
c
Note: does not contain 'b' (cause it *is* b)

==> (cd ../.. ; ls)
a-file
b
lc
Note: does yes contain 'b'

==> [[ -d ../../b ]]
FAIL
Note: [[ -d ]] does filesystem resolution

==> [[ -d $(realpath ../../b) ]]
realpath: ../../b: No such file or directory
FAIL
Note: realpath does filesystem resolution

==> (cd ../../b)
SUCCESS
Note: cd does string manipulation

==> [[ -d $(bash_normpath $PWD/../../b) ]]
SUCCESS
Note: bash_normpath does string manipulation\n"
        $(bash_normpath ${this_dir}/a/lc/d/../../b)\n"
        -> ${this_dir}/a/b\n"
      After that we have a path without '..'s and [[ -d ]] can't be confused\n"

==> [[ -d $(cd ../../b && pwd) ]]
SUCCESS
```
