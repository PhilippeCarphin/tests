# While $# (the number of positionnal parameters) > 1
# while [[ $# > 1 ]] ; do
   # echo $1;
   # shift
# done
do_a() {
   echo $1
}

declara -A long_to_short
long_to_short=([allo]=a [bonjour]=b)

position=0
# Iterate over $@, the array of arguments.
while [[ $# > 0 ]] ; do
   option=""
   if [[ "$1" != "" ]] ; then
      if [[ "${1:0:2}" = "--" ]] ; then
         # look at what comes after the "--" that's the option
         option=${long_to_short["$1"]}
         # depending on the option, eat an argument too
      elif [[ "${1:0:1}" = "-" ]] ; then
         # look at the character that comes after the "-". that's the option
         option=$1
         # depending on the option, eat an argument too
      else # it's a positionnal parameter
         # store argument in posargs array
         # posargs(position++) = $1
         true
      fi
   fi

   # if option has argument and option isn't with an "=" sign
   #    shift
   #    arg = $1
   # elif option has "=" sign
   #    arg = ${1#*=}
   # else
   #    arg = ""
   # fi

   echo ==========================
   echo Option = $option 
   echo Arg1   = $2
   if [[ "$option" != "" ]] ; then
      case $option in
         a) # This is for allo,a,allo=*.
            echo a\) option=$option
            ;;
         *)
            echo Unknown option : $1
            ;;
      esac
   else
      echo positionnal param $1
   fi

   
   shift
done

