src = $(wildcard *.f90)
obj = $(src:.f90=.o)

%.o:%.f90
	gfortran -c $< -o $@
main: $(obj)
	gfortran $^ -o $@

test: main
	./$<

clean:
	rm -f *.o a.out
