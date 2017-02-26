#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/wish

proc phil { a b c } {
   puts $a
   puts $b
   puts $c

   return {a c}
}

puts "Start here"

puts [list [phil a b c]]

puts "Like in the TCL ifle "
set commande [list phil L O L]

set butt [button .lol -text LOL -command $commande]
grid $butt
phil a b c

