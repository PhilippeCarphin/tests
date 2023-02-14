all: test-gcc

-include *.d
i: main-gcc-i.c
main-gcc: main.c
	@printf "\033[1;32mBuilding $@\033[0m\n"
	gcc -MMD $< -o $@
main-gcc.i.c: main.c
	@printf "\033[32mPreprocessing $@\033[0m\n"
	cpp -v $< > $@
test-gcc: main-gcc
	@printf "\033[1;36mRunning $<\033[0m\n"
	@./main-gcc
clean:
	rm -f main-*

ifneq ($(shell which icc 2>/dev/null),)
all: test-intel
main-intel.i.c: main.c
	@printf "\033[32mPreprocessing $@\033[0m\n"
	icc -C -E $< > $@
main-intel: main.c
	@printf "\033[1;32mBuilding $@\033[0m\n"
	icc -MMD $< -o $@
test-intel: main-intel
	@printf "\033[1;36mRunning $<\033[0m\n"
	@./main-intel
i: main-intel.i.c
endif



