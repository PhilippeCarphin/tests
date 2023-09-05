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

.PHONY: main_iso_c99 main_xopen_source-400 main_strict_ansi
test-macros: main_iso_c99 main_xopen_source-400 main_strict_ansi
main_iso_c99: main.c
	gcc -MMD  $< -o $@ -DJUST_AFTER -D_ISOC99_SOURCE && ./$@

main_xopen_source-400: main.c
	gcc -MMD  $< -o $@ -DJUST_AFTER -D_XOPEN_SOURCE=400 && ./$@

main_strict_ansi: main.c
	gcc -MMD  $< -o $@ -DJUST_AFTER -D__STRICT_ANSI__ && ./$@

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



