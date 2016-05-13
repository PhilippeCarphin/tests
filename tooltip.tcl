#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/wish
package require tooltip
set button [button .button -text simple_cmd -command "puts HELLO"]
tooltip::tooltip .button "This button will print 'HELLO' to the console :)"
grid $button
