
#
# This test demonstrates testing that a directory is empty
# using read.  I don't know why I tried this, I can do
#
# res=$(find $1 -maxdepth 1 -mindepth 1 -print -quit)
# if (( ${#res} > 0 )) ; then
#       non-empty
# else
#       empty
# fi
#
# Oh I guess this was to show that the option pipefail made a difference
# but it turns out that the option pipefail doesn't make a difference
# which surprised me
#

dir_is_empty(){
    if find $1 -maxdepth 1 -mindepth 1 2>/dev/null | read ; then
        printf "%10s\t%s\n" "$1" "is NOT empty"
    else
        printf "%10s\t%s\n" "$1" "is YES empty"
    fi
}

mkdir -p empty nonempty
touch nonempty/something

set +o pipefail

echo "WITHOUT PIPEFAIL"


dir_is_empty empty      # shows empty
dir_is_empty nonempty   # shows nonempty
dir_is_empty noexist    # shows empty

echo "=========================="
echo "WITH PIPEFAIL"
set -o pipefail

dir_is_empty empty
dir_is_empty nonempty
dir_is_empty noexist
