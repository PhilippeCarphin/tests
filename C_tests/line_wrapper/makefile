SOURCE = $(wildcard *.c)
EXEC = $(SOURCE:.c=.out)
TEST_ARGS = \"Tasdf asdfasdf asdf asdf asdf asd fsad fas df asdf as df asdf asd fa sdf asd fas df asdf as df asd fas df as df asdf sad fsad\" 15
PROJ_COMPILER = $(CC)

all:

$(EXEC):$(SOURCE)
	$(PROJ_COMPILER) $^ -o $@

.PHONY:test vars
test:$(EXEC)
	./$(EXEC) $(TEST_ARGS)

vars:
	@echo "SOURCE : $(SOURCE)"
	@echo "EXEC : $(EXEC)"
	@echo "TEST_ARGS : $(TEST_ARGS)"
	@echo "PROJECT_COMPILER : $(PROJ_COMPILER)"
