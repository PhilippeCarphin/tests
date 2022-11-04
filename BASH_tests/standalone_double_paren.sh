#!/bin/bash

set -e

i=0

echo "before doing ((i++)) i=$i"
((i++))
echo "after doing ((i++)) i=$i"


