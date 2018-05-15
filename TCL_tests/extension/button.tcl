#!/usr/bin/wish
load ./libhello[info sharedlibextension]
set external [button .asdf -text external -command {puts [hello]}]
grid $external
