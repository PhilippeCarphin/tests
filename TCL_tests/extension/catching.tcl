#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/tclsh
load ./libhello[info sharedlibextension]

proc sep {} {
   puts "================================================================"
}

proc call_hello {arg} {

   sep
   set result [catch {hello $arg}]
   if {$result} {
      puts "Return value was not TCL_OK"
      if {$result == 1} {
         puts "Return value was TCL_ERROR"
      }
      return
   }

   puts "Return value was TCL_OK"

}

proc use_obj_result {} {
   sep
   set obj_result [hello A B C]
   puts "Returned object has value $obj_result"
}


call_hello TCL_OK

call_hello TCL_ERROR

use_obj_result
