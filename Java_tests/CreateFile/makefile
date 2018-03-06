test_args = bonjour/boner.txt
clean_files = *.txt *.class
clean_dirs = bonjour

jsrc = $(wildcard *.java)
jclass = $(jsrc:.java=.class)
j = $(jclass:.class=)

all:$(jclass)

$(jclass):$(jsrc)
	javac $(jsrc)

test:all
	java $(j) $(test_args)

vars:
	@echo "jsrc = $(jsrc)"
	@echo "jclass = $(jclass)"
	@echo "j = $(j)"

clean:
	$(RM) $(clean_files)
	$(RM) -r $(clean_dirs)
