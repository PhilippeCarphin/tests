#!/users/dor/afsi/phc/Testing/testdomain/linux26-x86-64/bin/tclsh

package require Thread

proc readNodeinfoDB { } {

   set data_list [exec mtest]
   puts $data_list

   tsv::keylset PHIL the_keyed_list {*}$data_list

}

proc getCPU { nodeName } {
   return [tsv::keylget PHIL the_keyed_list $nodeName.resources.CPU]
}


proc getResource { nodeName resource } {
   return [tsv::keylget PHIL the_keyed_list $nodeName.resources.$resource]
}

proc getInfo { nodeName subkey } {
   return [tsv::keylget PHIL the_keyed_list $nodeName.$subkey]
}


readNodeinfoDB

set value [tsv::keylget PHIL the_keyed_list /EntryModulePhil.resources.CPU]
puts "resources.CPU of /EntryModulePhil : $value"
set value [tsv::keylget PHIL the_keyed_list /EntryModulePhil.depends.depname1]
puts "depends.depname1 of /EntryModulePhil : $value"


set nodeName /EntryModulePhil

set value [getCPU $nodeName]

puts "Value using wrapper function : $value"

set value [getResource $nodeName CPU]
puts "Value using general wrapper function : $value"

set value [getInfo $nodeName resources.CPU]
puts "Value using super wrapper function : $value"

# proc processLine { line } {
#    puts "Processing line : $line"
#
#    tsv::keylset my_keyed_list PHIL NODE $line
# }
#
# foreach line [split $lines "\n"] {
#    processLine $line
# }
#

# tsv::keylset sharedVar my_keyed_list NODES $lines
#
# tsv::keylget sharedVar my_keyed_list NODES
#
# puts "================================================="
# tsv::keylget sharedVar my_keyed_list NODES value
# puts "Found value: $value"


