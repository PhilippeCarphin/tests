echo "sourcing .phil_complete"
################################################################################
# This file shows an example of how to setup custom auto-complete for commands
# of our making.
#
# We start with a function that just prints it's arguments and define another
# function that will be called when we press TAB during the completion of that
# command.
################################################################################

################################################################################
# Function representing the command for which we will be doing auto-complete
################################################################################
to_complete(){
	echo "to_complete() function called"
	echo "Args are $@"
}

################################################################################
# This is the function that will be called when we press TAB.  It's purpose is
# to examine the current command line (as represented by the array COMP_WORDS)
# and to determine what the autocomplete should reply through the array
# COMPREPLY.
################################################################################
__phil_complete()
{
	COMPREPLY=()

	# The word we are trying to complete
	local cur="${COMP_WORDS[COMP_CWORD]}"

	# The word before that
	local prev="${COMP_WORDS[COMP_CWORD-1]}"

	# Candidates to use for completion
	local candidates="apple apricot bananna cherry"
	# Based on prev and possibly on the other words on the command line, we
	# might have a different list of candidates.

	# Compgen: takes the list of candidates and selects those matching ${cur}.
	# Once COMPREPLY is set, the shell does the rest.
	COMPREPLY=( $(compgen -W "${candidates}" -- ${cur}))

	return 0
}

__complete_one_candidate(){
    COMPREPLY=()
	local cur="${COMP_WORDS[COMP_CWORD]}"
	COMPREPLY=( $(compgen -W "apple" -- ${cur}))
}



################################################################################
# Arrange for the __phil_complete() function to be called when completing the
# command "to_complete".
################################################################################
complete -F __phil_complete to_complete
complete -F __complete_one_candidate one
