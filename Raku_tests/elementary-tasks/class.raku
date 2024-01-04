
class MyThing {
    has Int $.my-int = 42;
    has Str $.my-str;
    has Bool $.my-bool;

    # method display(){
    #     say "MyClass(\$.my-int=$.my-int, \$.my-str=$.my-str, \$my-bool=$.my-bool"
    # }
}

my $my-thing = MyThing.new(:my-str("Booggers"), :my-bool(True));

# $my-thing.display;
say $my-thing.^name;
say $my-thing.raku;
say $my-thing.gist;
$my-thing.say;
