#!/usr/bin/env raku

# About the type to enforce file existence:
#
# This is cool: it enforces that the file needs to exist
# but the problem is that if it doesn't exist, you just get the usage
# printed with no indication that distinguishes between failing to provide
# a required argument, mistyping an argument or providing a file that does
# not exist
#
# A solution to this is to make MAIN a multi sub and have the second one as
# shown at the end of the file.  However, if the program must take more than
# one file as an argument I don't think the solution scales.
#
# Then I think it becomes simpler to just have some string arguments and
# use some ifs like
#
#     if ! $file.IO.f {
#         say "ERROR: File $file does not exist*";
#         exit 1;
#     }
#
# for each file.
# *I'm not 100% sure what $file.IO.f tests.  I think it tests if we can read
# from the file which would mean it is a regular file or a link than can be
# followed to a regular file.  It does give false for directories and presumably
# for links that can be followed to a directory.  And I'm unsure what it would
# say for a socket.
#     

subset FilePath of Str:D where *.IO.f;

multi sub MAIN(FilePath :$file, Bool :$line-by-line, Bool :$array-of-lines, Str :$output = "")
{
    if $line-by-line {
        my $i = 1;
        for $file.IO.lines -> $line {
            say "Line $i : $line";
            $i++;
        }
    } elsif $array-of-lines {
        my @lines = $file.IO.lines;
        say "Array of lines is ", @lines
    } else {
        say $file.IO.slurp;
    }

    if $output {
        my $outfile = open $output, :w; # Truncates
        $outfile.say("first"); # Includes newline
        $outfile.print("second\n"); # Does not include newline
        $outfile.close;

        spurt $output, "data and stuff\n"; # Opens, writes and closes (truncates)

        $outfile = open $output, :a; # Appends
        $outfile.print("secudo\n");
        $outfile.close()
    }
}

multi sub MAIN(Str:D :$file, Bool :$line-by-line, Bool :$array-of-lines, Str :$output = "")
    is hidden-from-USAGE
{
    say "ERROR, the file $file does not exist";
    exit 1;
}
