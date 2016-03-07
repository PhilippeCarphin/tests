#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/tclsh
puts "================================"
set normalVar "Declared in outer scope"
global globalVar
set globalVar "Lee Sedol might beat alpha go"

namespace eval myNS {
   global NSglobalVar 
   set NSglobalVar "Declared with global inside a namespace"
}

array set garbage {
   a 1
   b 2
   c 3
}
puts "Garbage: $garbage(a)"

# array unset garbage
array set garbage {
   a ""
   b 2
   c 3
}

puts "Garbage: $garbage(a)"

proc testProc { } {
   # puts $normalVar
   # Can't read variable

   # puts $globalVar
   # can't read variable

   puts $myNS::NSglobalVar
   # successful
}

# puts "myNS::garbage :$myNS::garbage"



proc myNS::declareVar { } {
   puts "myNS::declareVar{} declaring variable garbage"
   variable garbage
   set garbage "GarbageValue (assigned in myNS::declareVar)"
}


myNS::declareVar
puts "myNS::garbage after executing declareVar{} :$myNS::garbage"

testProc
