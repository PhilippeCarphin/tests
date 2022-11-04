# This test shows that the [ -n ${var} ] and [[ -n ${var} ]] constructs
# do not behave the same when the ${var} is empty or undefined.  They behave
# the same if we put quotes around ${var}.
#
# The bottom line is that
#     [[ -n ]] behaves the same way with or without quotes and does the right thing.
#     [ -n ] does the right thing except for an unquoted empty or undefined variable
#
# therefore, one should always use [[ ]] for -n and for every other test.
#
# The other thing to note is that [ -z ] and [[ -z ]] always behave correctly
# and therefore [ -z ] is not the opposite of [ -n ] in the case of an unquoted
# empty or undefined variable.
#
# Moral of the story : NEVER EVER use [ -n ] and for consistency always do tests
# using [[ ]] instead of [ ].
#

echo "============= Undefined"
echo "if [ -n \${undefined} ]"

if [ -n ${undefined} ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -n \${undefined} ]]"
if [[ -n ${undefined} ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi

echo "============= undefined with quotes"
echo "if [ -n \"\${undefined}\" ]"
if [ -n "${undefined}" ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -n \"\${undefined}\" ]]"
if [[ -n "${undefined}" ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi


echo "============= Empty"
empty=
echo "if [ -n \${empty} ]"

if [ -n ${empty} ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -n \${empty} ]]"
if [[ -n ${empty} ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi

echo "============= Empty with quotes"
empty=
echo "if [ -n \"\${empty}\" ]"

if [ -n "${empty}" ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -n \"\${empty}\" ]]"
if [[ -n "${empty}" ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi

echo "============= non_empty"
non_empty=asdf
echo "if [ -n \${non_empty} ]"

if [ -n ${non_empty} ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -n \${non_empty} ]]"
if [[ -n ${non_empty} ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi

echo ==========================================================================
echo ================================ -z =======================================

echo "============= Undefined"
echo "if [ -z \${undefined} ]"

if [ -z ${undefined} ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -z \${undefined} ]]"
if [[ -z ${undefined} ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi

echo "============= undefined with quotes"
echo "if [ -z \"\${undefined}\" ]"
if [ -z "${undefined}" ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -z \"\${undefined}\" ]]"
if [[ -z "${undefined}" ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi


echo "============= Empty"
empty=
echo "if [ -z \${empty} ]"

if [ -z ${empty} ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -z \${empty} ]]"
if [[ -z ${empty} ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi

echo "============= Empty with quotes"
empty=
echo "if [ -z \"\${empty}\" ]"

if [ -z "${empty}" ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -z \"\${empty}\" ]]"
if [[ -z "${empty}" ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi

echo "============= non_empty"
non_empty=asdf
echo "if [ -z \${non_empty} ]"

if [ -z ${non_empty} ] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
echo "if [[ -z \${non_empty} ]]"
if [[ -z ${non_empty} ]] ; then
    echo "    IF"
else
    echo "    ELSE"
fi
