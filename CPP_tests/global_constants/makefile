src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
trg = phil.out

$(trg):$(obj)
	g++ -o $@ $(obj)

%.o : %.cpp
	g++ -g -c -o $@ $<

clean:
	rm -f *.o
	rm -f *.out
