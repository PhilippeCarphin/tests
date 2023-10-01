#!/usr/bin/env raku

sub add(Int $a, Int $b) { return $a + $b; }

sub multi-return(Int $a, Int $b)
{
    if $a % 2 == 0 {
        "$a is even";
    } else {
        42;
    }
}

# Runtime error depending on what multi-return returns
sub constrained-return(Int $a, Int $b) returns Int
{
    multi-return($a, $b);
}

sub returns-array(Int $a, Int $b) returns Array of Int
{
    my @arr of Int = [$a, $b];
}

sub MAIN(
        Int $a, #= An integer
        Int $b #= Another integer
)
{
    say "$a + $b is &add($a,$b)";
    say "&multi-return($a, $b)";
    say "&constrained-return($a, $b)";
    say "&returns-array($a, $b)";
}
