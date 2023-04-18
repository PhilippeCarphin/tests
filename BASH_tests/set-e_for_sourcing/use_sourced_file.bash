set -e

set -x
PS4='+ [${BASH_SOURCE[0]}:${LINENO}] '

source sourced_file_tryhard.bash

echo "After sourcing"
