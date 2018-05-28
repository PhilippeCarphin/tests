#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/wish
load ./libhello[info sharedlibextension]

proc call_hello {} {
   set result [hello bonjour 456]
   puts "TCL : Result received from C extension : $result"
}
set external [button .asdf -text external -command {call_hello}]
grid $external
