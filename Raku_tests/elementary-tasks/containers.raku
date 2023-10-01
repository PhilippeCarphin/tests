#!/usr/bin/env raku

sub MAIN()
{
    # There are arrays and lists, it seems like lists are like Python tuples
    # and arrays are like python lists.
    my $list = (1,"ias",3,4);
    say $list.^name;
    say "element 3 of list is $list[3]";
    # $list.append(5); # Cannot call append on an immutable list
    # $list[2] = 8; # Cannot modify an immutable List.

    my @arr = [1,2,3,4];
    say @arr.^name;
    say @arr[0].^name;
    @arr.append("boobs");
    say @arr[*-1].^name;
    say @arr;

    my @typed-array of Int = [1,2,3];
    my $len = @typed-array.elems;
    say "My array has $len elements";
    for 0..$len-1 -> $i {
        say "Index is $i";
    }

    my %my-hash = 1 => 2, "bag of" => "marbles";
    say "type of %my-hash is ", %my-hash.^name;
    %my-hash.say;
    say %my-hash{1};
    say %my-hash{8}; # Returns (Any)
    if %my-hash{8} {  # (Any) is falsy
        say "8 is a key"
    } else {
        say "8 is not a key"
    }

    for %my-hash -> (:$key, :$value) {
        say "the value of key '$key' is '$value'";
    }

    # Constraining types.  We can constrain just the types of the keys or
    # just the types of the values
    my %power-levels{Str} of Int = "Goku" => 9000;
    # %power-levels<vegeta> = "not as much as Goku"; # Error because of value
    # %power-levels{9} = 8; # Error because of key

    
}
