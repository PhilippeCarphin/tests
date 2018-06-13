
# This is just a record of what I did to get it to work since it's been a long
# time since I had worked on this.

# First I did this
autoreconf

   # It finished with errors but it told me to do the the following command.

# The fact that autoreconf needs me to do this suggests that I could run this
# first but it needs files that were created by autoreconf but this is not the
# case.  Autoreconf is simply letting me know that the configure script that it
# created will expect some things to be installed.
automake --add-missing

   # It adds some files and now my configure script is ready to go.


./configure


