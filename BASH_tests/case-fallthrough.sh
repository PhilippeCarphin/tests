case $1 in
    a*)
        echo "$1 starts with 'a'"
        echo "super-fallthrough (;&), run the next case no matter what"
        ;&

    # If the previous case ran, this one will run wheter the string
    # ends with 'b' or not.
    *b) echo "$1 ends with 'b' or starts with an 'a'"
        echo "fallthrough (;;&), go to the next matching case"
        ;;&

    *c*)  echo "$1 contains a 'c'" ;;

    # Runs if the string contains a 'd' but also doesn't contain
    # a 'c'.
    *d*) echo "$1 contains a d" ;;
esac
