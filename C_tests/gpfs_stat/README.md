Just a demo of using GPFS stat.  Supposedly it's different from the regular
stat function in certain circumstances but I haven't been able to produce
a case where we can see that difference.

Also, I had trouble understanding what I was supposed to do after running
`gpfs_stat()`.  I had to poke around in the header file to find out that
`gpfs_stat_t` was the same thing as a regular `stat_t`.  In the documentation
that I found on IBM's website, I didn't see anywhere how you're supposed to
get yourself an instance of `gpfs_stat_t` and it looks to be implemented as an
opaque type.

I decided to create a `struct stat_t` and cast its address as a `*gpfs_stat_t`
and pass it to `gpfs_stat()`.  It worked and produced good results but nowhere
did it say to do that in the documentation.

