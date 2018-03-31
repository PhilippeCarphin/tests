
trg=factorial
src=factorial.hs

test:all
	./$(trg)

all:$(trg)

$(trg):$(src)
	ghc --make $<

clean:
	rm -f $(trg)
	rm -f $(src:.hs=.hi)
