#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/tclsh

set newname "a"
set impSel newExperiment
set destExpName [expr $newname == "" ? $impSel: $newname]

puts "destExpName is $destExpName "
