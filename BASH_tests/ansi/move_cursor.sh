#!/bin/bash
set -euo pipefail

printf "Hello World\n"
echo "Press Enter to continue"
read res
printf "\033[3A" # Move cursor up by 3
printf "\r" # Move cursor to beginning of line (\r is carriage return)
printf "\033[32m" # Set foreground (text) color to green
printf "Hello World" # Re print the Hello World (in green this time)
printf "\033[0m" # Reset colors to default
printf "\033[2B" # Go down two lines (pressing enter made us go down one line, so we had to go up three to get to where the H is but we want to return the cursor to where it was before we pressed enter.
printf "\r"  # Put the cursor back to the start of the line
for((i=31; i<37; i++)); do
    read res
    # Same thing as above but in a single Printf command
    printf "\033[3A\r\033[${i}mHello World\033[0m\033[2B\r"
done


