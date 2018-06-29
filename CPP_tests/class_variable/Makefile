.PHONY: all

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

trg = a.out

all:test


$(trg):$(obj)
	g++ $(obj) -o $@

test:$(trg)
	./$(trg)

