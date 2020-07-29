# When to use BASH

- Creating a script that will be sourced to modify the environment
- Creating a script that has to source other BASH scripts
- You get a significant performance gain from piping commands

# BASH red flags

- You script defines functions that call other functions
- You have for loops
- You have a lot of ifs
- Your script has sections delimited with rows of '#'
- You have associative arrays or arrays of any kind
- You have arrays of arrays

# When to use Python

- Your script doesn't need to be sourced
- Your script doesn't need to source BASH scripts
