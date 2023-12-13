# This is a test of localization with $"..." strings
#
this_dir=$(cd $(dirname $0) && pwd)
this_file=$(basename $0)

# It's gonna look for French in ${TEXTDOMAINDIR}/fr/LC_MESSAGES
# for a file named named ${TEXTDOMAIN}.po
export TEXTDOMAINDIR=$this_dir/locale
export TEXTDOMAIN=localized.sh

read -p $"Please enter a value" value
echo $"You have entered the value ${value}"

if (( ${value} % 2 == 0 )) ; then
    echo $"Your value is even"
else
    echo $"Your value is odd"
fi

echo $"Another message to translate"

echo $"Again another message"
