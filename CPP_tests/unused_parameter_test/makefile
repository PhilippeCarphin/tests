CXXFLAGS += -Wall -Wunused-parameter

test:all
	./main.out

all:main.out

main.out:main.o
	g++ $< -o $@


clean:
	rm -f main.out
	rm -f main.o
