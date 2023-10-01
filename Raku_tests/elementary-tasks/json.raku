#!/usr/bin/env raku

# Installed with 'zef install JSON::Fast'
use JSON::Fast;

# Also possbile:
# use JSON::Tiny;


sub MAIN()
{
    # Various assignments X-from-Y where X is the type we are assigning to
    # so %,$,@ and Y is the type of the JSON object being dict for {} and array
    # for [].
    #
    # No matter what, when we assign to a scalar, it works out but if we assign
    # a dict to a @, we get an array of {key => value} pairs and if we
    # assign an array to a %, it takes successive pairs from the array to form
    # key=>value pairs for the hash we are assigning to.
    #
    # So if you know your JSON contains an array or a dict, I would use @ or %
    # but if you don't know, a scalar would seem to be the best choice.

    say "======== Assign to %hash-from-dict ================";
    # When we assign to a %, we get a hash-from-dict
    my %hash-from-dict = from-json("dict.json".IO.slurp);
    say %hash-from-dict{"str"};
    %hash-from-dict{"booggers"} = "balls";
    %hash-from-dict{"list"}.append(9);
    say %hash-from-dict;
    say "Type of %hash-from-dict: ", %hash-from-dict.^name;
    say to-json(%hash-from-dict);

    say "======== Assign JSON dict to @array-from-dict ================";
    # When we assign to a @, we get an array of pairs
    my @array-from-dict = from-json("dict.json".IO.slurp);
    say "array-from-dict = ", @array-from-dict;
    say "type of array-from-dict: ", @array-from-dict.^name;
    say @array-from-dict[0].^name;
    say @array-from-dict[0];
    say @array-from-dict[1].^name;
    say @array-from-dict[1];
    say to-json(@array-from-dict);
    # say @array-from-dict<str>; # Array does not support associative indexing

    say "======== Assign JSON dict to \$scalar-from-dict ==============";
    # Assigning to a scalar seems to also give us a hash
    # that supports all the same syntax as %hash above.
    my $scalar-from-dict = from-json("dict.json".IO.slurp);
    say "Type of scalar-from-dict = ", $scalar-from-dict.^name;
    say "scalar-from-dict : $scalar-from-dict";
    say "list: ", $scalar-from-dict<list>;
    say "str: ", $scalar-from-dict<str>;
    $scalar-from-dict<list>.append(9);
    say $scalar-from-dict;
    say to-json($scalar-from-dict);

    say "======== Assign JSON array to \$scalar-from-array ==============";
    # Assigning to a scalar seems to also give us a hash
    # that supports all the same syntax as %hash above.
    my $scalar-from-array = from-json("array.json".IO.slurp);
    say "Type of scalar-from-array = ", $scalar-from-array.^name;
    say "scalar-from-array[2] : $scalar-from-array[2]";
    say $scalar-from-array;
    say to-json($scalar-from-array);
    
    say "======== Assign to @array-from-array ===================";
    # If our JSON file is indeed an array-from-array and we assign to a @, we get
    # what we expect
    my @array-from-array = from-json("array.json".IO.slurp);
    say @array-from-array;
    @array-from-array.append(8);
    say @array-from-array;
    say to-json(@array-from-array);

    say "======== Assign to @hash-from-array ===================";
    # If our JSON file is an hash-from-array and we assign it to a %hash,
    # it takes successive pairs of elements in the hash-from-array to form
    # key-value pairs in our %hash.
    # So JSON [1,2,3,4] gives {1=>2, 3=>4}.
    my %hash-from-array = from-json("array.json".IO.slurp);
    %hash-from-array.append({4=>5});
    say %hash-from-array;
    say to-json(%hash-from-array);
}
