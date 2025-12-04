#!/usr/bin/env bash
echo "Enter a number or something" >&2

# Remove the 'I was killed by a signal attribute'
# as described in https://www.cons.org/cracauer/sigint.html
trap 'exit 130' INT

# Terminal is different when called by a bind -x function
read -N 1 number

# printf 'read result %q\n' "${number}" >&2
echo "${number}"

