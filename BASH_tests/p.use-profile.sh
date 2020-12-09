#!/bin/bash
p.base-env(){
    ssh localhost env | grep -v '^SSH\|^PWD|^LANG=|^LC_'
    echo "SSH_CONNECTION=\"$SSH_CONNECTION\""
    echo "SSH_CLIENT=\"$SSH_CLIENT\""
    echo "TERM=$TERM"
    echo "DISPLAY=$DISPLAY"
}

p.use-profile(){
    local username=$1
    if [ -z $username ] ; then
        echo "$0 : ERROR : Please provide a username" >&2
        return 1
    fi

    local userdir=$(eval echo ~$username)
    cd $userdir 2>/dev/null 
    if [[ $? != 0 ]] ; then
        echo "$0 : ERROR : Could not cd to '$userdir'" >&2
        return 1
    fi

    eval env -i "$(p.base-env)" USER=$username HOME=$userdir bash -l
}

if [[ "$1" == '--help' ]] || [[ "$1" == "-h" ]] ; then
    echo "Usage : $0 USERNAME

    Pretend to be user USERNAME by creating fresh
    bare environment and setting cd-ing to user's home
    setting HOME=~\$USERNAME and starting 'bash -l'" >&2

    if [[ $1 == '--help' ]] ; then
    echo "
    Note on DISPLAY: X11 authentication looks in your
    home for stuff, so after loading the user's
    environment, set HOME=\$YOUR_REAL_HOME for X11
    things to work.

    See below for an attempt to do that automatically.
    It prevents us from getting the user's prompt string
    and who knows what else.  Bottom line, if you need
    X11 stuff, set HOME=\$YOUR_REAL_HOME manually" >&2
    fi
    exit
fi

p.use-profile $@


# NOTES ABOUT DISPLAY
# Use this
#
#   eval env -i "$(p.base-env)" HOME=$userdir bash -l -i <<< "HOME=$HOME ; exec </dev/tty"
#
# to set HOME back to your home after logging in for
# Display stuff to work immediately
#
# This will make x11 stuff work right off the bat but
# the starting condition of BASH is that is is not connected
# to a TTY, this means that some parts of the loading
# of the users profile may behave differently and we won't
# be reproducing the user's environment as reliably
