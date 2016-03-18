
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

.PHONY:clean

OS=`uname`
all: opt_parser

opt_parser:$(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)
	rm -rf ./$(OS)
	mkdir ./$(OS)
	cp opt_parser ./$(OS)/opt_parser
	rm opt_parser
	./$(OS)/opt_parser --argopt argopt_argument posarg1 --badopt badopt_argument --flagOpt1 posarg2 posarg3 --flagOpt2

.c.o:
	$(CC) -c $<

clean:
	rm *.o *.exe
