#
# This demonstrates the weird behavior of 'if' in BASH when the condition
# is some kind of thing that works out to an empty if.
#
# The last three are not surprising: they cause errors.
#
# What is surprising is that the first three, which after varialble expansion,
# are all like the very last one, produce no error message and go inside the
# IF.
#

# Goes in the IF, no error message
echo "=== DOESNT_EXIST"
if $DOESNT_EXIST ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi

# Goes in the IF, no error message
echo "=== EMPTY_VAR"
EMPTY_VAR=
if $EMPTY_VAR ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi

# Goes in the IF, no error message
echo "=== EMPTY_STRING_VAR"
EMPTY_STRING_VAR=""
if $EMPTY_STRING_VAR ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi

# Goes in the ELSE, Error message that command '' is not found
echo "=== quoted EMPTY_STRING_VAR"
EMPTY_STRING_VAR=""
if "$EMPTY_STRING_VAR" ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi

# Goes in the ELSE, Error message that command '' is not found
echo "=== EMPTY STRING LITTERAL"
if "" ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi

# Does not go in the IF or the ELSE because it is a syntax error
# and it stops the program.
echo "=== Completely empty if"
if  ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi


