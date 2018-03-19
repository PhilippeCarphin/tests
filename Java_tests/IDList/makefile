test_args =
clean_files = *.txt *.class

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
