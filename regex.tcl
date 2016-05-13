#!/ssm/net/isst/maestro/1.4.3-rc4/linux26-x86-64/bin/tclsh

# Should not match
set time_delta(0) -1h2f5j

# Should match
set time_delta(1) -1h2d

# Should match
set time_delta(2) -1h2days

# Should match
set time_delta(3) 1h2m4s

# Should not match
set time_delta(4) 1t2k4l

set keys [list 0 1 2 3 4]

set time_delta_regex {^[-+]?([0-9]+[dhms][^0-9]*)+$}
# ^       Beginning of line then ...
# [-+]?   One or zero of '+' or '-' then ...
# (...)+  One or more unit groups then ...
# $       the end of the line/string
# where a unit group [0-9]+[dhms][^0-9]* is a number followed by 'd', 'h', 'm' or 's' and 0 or more non-digits.


proc regex {regex  input } {

   if { [regexp $regex $input ] } {
      puts "$input MATCHES"
   } else {
      puts "$input NO_MATCH"
   }
}

puts "Regex is $time_delta_regex"
foreach key $keys {
   regex $time_delta_regex $time_delta($key)
}


foreach key $keys {
   puts [regexp $time_delta_regex $time_delta($key)]
}
