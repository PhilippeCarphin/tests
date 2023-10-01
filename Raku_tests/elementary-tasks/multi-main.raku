#!/usr/bin/env raku

# Someone on the Raku Discord server gave me this
# as a way to show an error if the file doesn't exist
# while still using the type system to say that the
# file must exist

subset FilePath of Str:D where *.IO.f;

multi sub MAIN(
    FilePath :$file, #= A file to do stuff with
) { 
    say $file 
}   

multi sub MAIN(
    Str:D :$file
) is hidden-from-USAGE { 
    say "ERROR: The file '$file' does not exist"; 
    exit 1;
}   
