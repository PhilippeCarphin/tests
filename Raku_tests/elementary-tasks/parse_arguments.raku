#!/usr/bin/env raku

# Happens before MAIN is called
say "ARGS = ", @*ARGS;

sub MAIN(
    Str :$file = "hello.txt",  #= A file to do stuff with
    Num :$number = Num(8.5E3), #= A number for some reason
    Bool :$flag = False #= A switch to do something
)
{
    say "ARGS = ", @*ARGS;
    say "  file = $file";
    say "number = $number";
    say "  flag = $flag";

}
