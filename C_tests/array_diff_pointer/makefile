CFLAGS += -Wall
CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
PROG=demo.out

all:$(PROG)
$(PROG):$(OFILES)
	$(CC) $(OFILES) -o $@

run:$(PROG)
	./$^


.PHONY:clean vars

clean:
	rm -f *.o
	rm -f *.out

vars:
	@echo "CFILES: $(CFILES)"
	@echo "OFILES: $(OFILES)"


