
proc printme { str } {
   puts $str
   # return $str
   return -code error
}

puts [printme obama]

if { [catch { printme Obama }] } {
   puts "True"
} else {
   puts "false"
}
