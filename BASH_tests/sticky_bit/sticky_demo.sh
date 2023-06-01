#
# Because this demo requires three users.  We have to imagine that the commands
# below are run by the user stated above them.
#
# I did the test on MacOS where I had three users.
#
# The thing to know is that permission to create and delete files is governed
# by the directory where the files are or are created.
#
# In a normal directory with 777 permission, users could delete each other's
# files.  Adding the sticky bit to a directory prevents this.  In a sticky
# directory with 777 permission, users cannot delete files that they do not own
# except for the owner of the directory.
#
###############################################################################
# Dad creates two 777 directories, one with the sticky bit the other without
# Everyone creates a file with their name in each of these directories
###############################################################################

#
# User dad
#
mkdir sticky
chmod 777 sticky
touch sticky/dad

mkdir slippery
chmod 777 slippery
touch sticky/dad

#
# User paul
#
touch sticky/paul
touch slippery/paul

#
# User phil
#
touch sticky/phil
touch slippery/phil

###############################################################################
# Who can remove the files?
###############################################################################

#
# User paul
# Slippery: can delete anything
# Sticky: Only his files
#
rm slippery/*              # Success
rm sticky/paul             # Success
rm sticky/dad sticky/phil  # Fail

#
# User phil
# Slippery: can delete anything
# Sticky: Only his files
#
rm slippery/*              # Success
rm sticky/phil             # Success
rm sticky/dad sticky/paul  # Fail

#
# User dad
# Because he is the owner of the sticky directory, he
# can delete anything that is in it.
# For the slippery directory anyone can delete anything
#
rm sticky/*        # Success
rm slippery/*      # Success


