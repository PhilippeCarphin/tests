use strict;
use warnings;

my $filename = $ARGV[0];

print "filename = $filename\n";

open(my $file_handle, '<:encoding(UTF-8)', $filename);

while (my $line = <$file_handle>){
	chomp $line;
	print "line = $line";
}
print "\n"
