.globl int_to_string
.globl _int_to_string

int_to_string:
_int_to_string:
	pushq %rbp
	movq %rsp, %rbp

	# store our parameter in a local variable at -8(%rbp)
	subq $8, %rsp
	movl %edi, -8(%rbp)

	# char *s = malloc(21);
	pushq $0 # char *s at -16(%rbp)
	movl $21, %edi # 21)
	call malloc # malloc(
	movq %rax, -16(%rbp) # -> s
    # char *p = s
    pushq -16(%rbp) # p at -24(%rbp)
    jmp check_continue
loop_body:
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	$12, %eax
	cltd
	idivl	-4(%rbp)
	movl	%edx, %eax
    addl $48, %eax
    movq -24(%rbp), %rdx
    movb %al, (%rdx)
    leaq 1(%rdx), %rdi
    movb $0, (%rdi)
    jmp out

check_continue:
    jmp loop_body
out:
	movq -16(%rbp), %rax
    leave
	ret
