#!/bin/bash

# This is used for adding an entry to a colon-separated list like path.
# Normally PATH is always not empty so we can alwasy do
# export PATH=/usr/bin:$PATH but if it were empty, we would have an unnecessary
# colon.

# BASICALLY: this way adds a string to a separated list without adding a colon
# if the list is initially an empty string.

my_string=
my_string=phil${my_string:+:${my_string}}
echo "my_string = $my_string"
my_string=phil${my_string:+:${my_string}}


my_other_str=
my_other_str=phil:$my_other_str
echo "my_other_str = $my_other_str"
