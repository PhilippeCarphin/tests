#!/bin/bash
# localized.sh
#  Script by Stéphane Chazelas,
#+ modified by Bruno Haible, bugfixed by Alfredo Pironti.

. gettext.sh

this_dir=$(cd $(dirname $0) && pwd)
this_file=$(basename $0)

# It's gonna look for French in ${TEXTDOMAINDIR}/fr/LC_MESSAGES
# for a file named named ${TEXTDOMAIN}.po
export TEXTDOMAINDIR=$this_dir
export TEXTDOMAIN=localized.sh
if false ; then
    E_CDERROR=65

    error()
    {
      printf "$@" >&2
      exit $E_CDERROR
    }

    cd $var || error "`eval_gettext \"Can\'t cd to \\\$var.\"`"
    #  The triple backslashes (escapes) in front of $var needed
    #+ "because eval_gettext expects a string
    #+ where the variable values have not yet been substituted."
    #    -- per Bruno Haible
    read -p "`gettext \"Enter the value: \"`" var
else
	#!/bin/bash
	# localized.sh

	E_CDERROR=65

	error() {
	  local format=$1
	  shift
	  printf "$(gettext -s "$format")" "$@" >&2
	  exit $E_CDERROR
	}
	cd $var || error "Can't cd to %s." "$var"
	read -p "$(gettext -s "Enter the value: ")" var
fi
# ...
#  ...


#  ------------------------------------------------------------------
#  Alfredo Pironti comments:

#  This script has been modified to not use the $"..." syntax in
#+ favor of the "`gettext \"...\"`" syntax.
#  This is ok, but with the new localized.sh program, the commands
#+ "bash -D filename" and "bash --dump-po-string filename"
#+ will produce no output
#+ (because those command are only searching for the $"..." strings)!
#  The ONLY way to extract strings from the new file is to use the
# 'xgettext' program. However, the xgettext program is buggy.

# Note that 'xgettext' has another bug.
#
# The shell fragment:
#    gettext -s "I like Bash"
# will be correctly extracted, but . . .
#    xgettext -s "I like Bash"
# . . . fails!
#  'xgettext' will extract "-s" because
#+ the command only extracts the
#+ very first argument after the 'gettext' word.


#  Escape characters:
#
#  To localize a sentence like
#     echo -e "Hello\tworld!"
#+ you must use
#     echo -e "`gettext \"Hello\\tworld\"`"
#  The "double escape character" before the `t' is needed because
#+ 'gettext' will search for a string like: 'Hello\tworld'
#  This is because gettext will read one literal `\')
#+ and will output a string like "Bonjour\tmonde",
#+ so the 'echo' command will display the message correctly.
#
#  You may not use
#     echo "`gettext -e \"Hello\tworld\"`"
#+ due to the xgettext bug explained above.



# Let's localize the following shell fragment:
#     echo "-h display help and exit"
#
# First, one could do this:
#     echo "`gettext \"-h display help and exit\"`"
#  This way 'xgettext' will work ok,
#+ but the 'gettext' program will read "-h" as an option!
#
# One solution could be
#     echo "`gettext -- \"-h display help and exit\"`"
#  This way 'gettext' will work,
#+ but 'xgettext' will extract "--", as referred to above.
#
# The workaround you may use to get this string localized is
#     echo -e "`gettext \"\\0-h display help and exit\"`"
#  We have added a \0 (NULL) at the beginning of the sentence.
#  This way 'gettext' works correctly, as does 'xgettext.'
#  Moreover, the NULL character won't change the behavior
#+ of the 'echo' command.
#  ----------------------------------------------------------------
