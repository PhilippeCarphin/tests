# This makefile is for experimenting with assembler
# code in the 32bit calling convention specified by
# -m32.

CALLING_CONVENTION_FLAG = -m32
DEBUG_INFO_FLAG = -gdwarf-2
CFLAGS = $(CALLING_CONVENTION_FLAG) $(DEBUG_INFO_FLAG) -MMD
ASMFLAGS = $(CALLING_CONVENTION_FLAG) $(DEBUG_INFO_FLAG)

# Source files
C_SRC = main.c
ASM_SRC = sum_s.s mat_s.s

# The assembler version of C source files
ASM_FROM_C = $(C_SRC:.c=.s)

# Object files for exectable made from the source files
OBJ = $(C_SRC:.c=.o) $(ASM_SRC:.s=.o)

# Executable file made from the object files
TRG = main.out

test:$(TRG)
	./$(TRG)

all:exe asm

exe:$(TRG)
asm:$(ASM_FROM_C)

$(TRG):$(OBJ)
	gcc -m32 $^ -o $@

%.o:%.c
	gcc $(CFLAGS) -c $< -o $@
%.o:%.s
	gcc $(ASMFLAGS) -c $< -o $@
%.s:%.c
	gcc $(CFLAGS) -S $< -o $@

vars:
	@echo "OBJ = $(OBJ)"
	@echo "C_SRC = $(C_SRC)"
	@echo "ASM_FROM_C = $(ASM_FROM_C)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "ASMFLAGS = $(ASMFLAGS)"

-include *.d

clean:
	rm -f $(OBJ)
	rm -f $(ASM_FROM_C)
