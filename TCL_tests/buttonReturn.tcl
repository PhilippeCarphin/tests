#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/wish

proc phil { a b c } {
   puts $a
   puts $b
   puts $c

   return {a c}
}

set commande [list phil L O L]
set cmderp  "phil l o l"
set boner 0
set boobs [button .boobs -text simple_cmd -command $cmderp]
set butt [button .lol -text set_var -command {set boner 1}]
set buttox [button .boner -text complex_cmd -command { if { [expr $boner == 1]} {
                                                            return
                                                         }
                                                            "$cmderp"}]
grid $butt
grid $buttox
grid $boobs

