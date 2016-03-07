#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/wish

proc phil { a b c } {
   puts $a
   puts $b
   puts $c

   return {a c}
}

set newVar cock
proc arrayParam { arr } {
   upvar $arr myArray
   puts $myArray(mamelons)
   puts $myArray(boobs)
   set myArray(boobs) doubleD
   set newVar Taisha
   puts "The most complicated joseki is $newVar"
}
set boner 0
proc command { arg  } {
   upvar $arg value
   if { [expr $value == 1]} {
      phil yoguourt a b
   } else {
      phil lol caca bonjour
   }
}

proc toggleValue { arg } {
   upvar $arg value
   if { $value == 1 } {
      set value 0
   } else {
      set value 1 
   }
}

set butt [button .lol -text set_var -command {toggleValue boner}]
set buttox [button .boner -text complex_cmd -command {command boner} ]

array set phil {
   mamelons sensible
   boobs big
   hello bonjour
}
# Call the function with array as a parameter
arrayParam phil 
# Function modifies the parameter
# and also declares a new variable
# Value of the global array
puts $phil(boobs)
# puts $newVar #The variable cant be read

arrayParam phil
puts $newVar

grid $butt
grid $buttox

