.global _main

_main:
# Create stack frame
   pushq %rbp
   movq %rsp, %rbp

# Allocate and initalize variables
   subq $16, %rsp
   movq $1, -8(%rbp)    # Iterator variable
   movq $100, -16(%rbp) # Loop bound

# Subtract 100 from iterator and continue if the result is negative
check_continue:
   movq -8(%rbp), %rax
   subq -16(%rbp), %rax
   jle loop_body
   jmp loop_end

# Call fizzbuzz with iterator variable as first argument
loop_body:
   movq -8(%rbp), %rsi
   callq fizzbuzz

# Advance iteration by incrementing iterator variable by 1
loop_iterate:
   addq $1, -8(%rbp)
   jmp check_continue

loop_end:
main_end:

# deallocate stack space
   addq $16, %rsp
# Undo stack frame
   popq %rbp
# Return to caller
   retq


remainder:
   # Create stack frame
   pushq %rbp
   movq %rsp, %rbp

   # Put first argument in eax
   movl %edi, %eax
   cltd
   # Divide by second argument
   idiv %esi

   # Put remainder in eax
   movq $0, %rax
   movl %edx, %eax
   # Undo stack frame and return
   popq %rbp
   retq


fizzbuzz:
   # Stack frame
	pushq	%rbp
	movq	%rsp, %rbp

   # Allocate stack space and initialise
   subq $16, %rsp
   movq %rsi, -8(%rbp)
   # -16(%rbp) will be used to remember if the number is divisible by 3

########################### Output "fizz" if divisible by 3 ####################
check_divis_3:
   # Call remainder() with argument of fizzbuzz as first argument and with
   # 3 as second argument
   movq -8(%rbp), %rdi
   movq $3, %rsi
   callq remainder
   movq %rax, -16(%rbp)
   cmpl $0, %eax
   jne not_divis_3
divis_3:
   leaq fizz(%rip), %rdi
   callq _printf
   jmp check_divis_5
not_divis_3:

########################### Output "buzz" if divisible by 5 ####################
check_divis_5:
   movq -8(%rbp), %rdi
   movq $5, %rsi
   callq remainder
   cmpl $0, %eax
   jne not_divis_5
divis_5:
   leaq buzz(%rip), %rdi
   callq _printf
   jmp fizzbuzz_end

########## If not divisible by 5, check that also not divisible by 3 ##########
not_divis_5:
   cmpq $0, -16(%rbp)
   jne print_number
   jmp fizzbuzz_end
print_number:
   leaq number_fmt(%rip), %rdi
   movq -8(%rbp), %rsi
   callq _printf

##################### Output newline and return ################################
fizzbuzz_end:
   leaq newline(%rip), %rdi
   callq _printf

   addq $16, %rsp
	popq %rbp
	retq

fizz:
   .asciz "fizz"

buzz:
   .asciz "buzz"

number_fmt:
   .asciz "%d"

debug_fmt:
   .asciz "debug: rax=%d\n"

newline:
   .asciz "\n"

div_3:
   .long 0

