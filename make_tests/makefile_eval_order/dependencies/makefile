src = a.c b.c
objects = a.o b.o
trg = exe.out

a.o:a.c c.h
all:$(trg)

$(trg):$(objects)
	@echo "'building' $@ from $^"
	@echo "Dependency = $^ and objects = $(objects)"
	touch $(trg)

.c.o:
	@echo "'building' $@ from $^"
	touch $@

objects += c.o

clean:
	rm -rf *.o $(trg)

