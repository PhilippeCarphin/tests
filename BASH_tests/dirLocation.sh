echo "\$0          :$0"
echo "BASH_SOURCE :${BASH_SOURCE[0]}"
dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null && pwd )"

# Robust enough for me.  
rldir="$( dirname "$( readlink -f $0 )" )"
echo cd/dirname/pwd : $dir
echo rldir = $rldir


