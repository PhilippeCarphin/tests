#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/wish
load ./libhello[info sharedlibextension]
set external [button .asdf -text external -command {puts [hello bonjour 456]}]
grid $external
