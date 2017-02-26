#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/tclsh

set wr [open "outputFile" w+ 777]

puts $wr BONJOUR

close $wr
