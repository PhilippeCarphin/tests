filename=$( basename $1)
LaTeX_file=$filename.tex
PDF_file=$filename.pdf
target=$( dirname $1 )
write_makefile() {
   echo "
##### automatic target names ####

FILENAME=$filename

.PHONY: clean 

# Make targets:

all: \$(FILENAME).pdf

%.pdf:%.tex
	pdflatex $<

#### Cleanup ####
# Je sais que c'est laid, mais rm *.log marchait pas avec make sur windows.
clean: 
	rm -f *.log 
	rm -f *.aux 
	rm -f *.pdf 
	rm -f *_latexmk 
	rm -f *.syntex.gz

#####                    EOF                   #####" > $target/makefile
}

write_change_script() {
   echo "make" > $target/change.sh
   chmod u+x $target/change.sh
}

write_LaTeX_doc() {
   cp "$HOME/Templates/LaTeX Document.tex" $target/$LaTeX_file
}

write_set_file_watch() {
   echo "fswatch -o ./$LaTeX_file | xargs -n1 ./change.sh" > set_file_watch.sh
   chmod u+x ./set_file_watch.sh
}


write_LaTeX_doc
write_makefile
write_change_script
write_set_file_watch
