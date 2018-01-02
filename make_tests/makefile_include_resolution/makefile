
GENERATE_DEPENDENCIES = -MMD
CFLAGS += $(GENERATE_DEPENDENCIES)
REMOVE = rm -f
SOURCE_FILES = $(wildcard *.c)
OBJ_FILES = $(SOURCE_FILES:.c=.o)
EXEC = phil.out

# BUILTIN VARIABLES
# $@ : name of target
# $^ : list of prerequisites
# $< : the first prerequisite in the list in the of prerequisites

all:$(EXEC)

$(EXEC):$(OBJ_FILES)
	$(CC) -o $@ $(LDFLAGS) $^

run:$(EXEC)
	./$(EXEC)


# explicit main.o: main.c
# général %.o:%.c          (filename.o depends on filename.c)
# nouveau .c.o             (dot c to dot o)
main.o: main.c
	@echo "Dependency: $@:$^"
	$(CC) $(CFLAGS) $< -c


-include *.d

.PHONY:clean
clean:
	$(REMOVE) $(EXEC)
	$(REMOVE) $(OBJ_FILES)
	$(REMOVE) *.d *.gch

vars:
	@echo "SOURCE_FILES : $(SOURCE_FILES)"
	@echo "OBJ_FILES : $(OBJ_FILES)"
	@echo "EXEC : $(EXEC)"
