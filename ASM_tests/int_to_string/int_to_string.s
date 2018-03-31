.globl int_to_string
int_to_string:
	pushq %rbp
	movq %rsp, %rbp

	# store our parameter in a local variable at -8(%rbp)
	subq $8, %rsp
	movl %edi, (%rsp)

	# char *s = malloc(21);
	pushq $0 # char *s
	movl $21, %edi # 21)
	call malloc # malloc(
	movq %rax, -16(%rbp)

out:
	movq -16(%rbp), %rax
	addq $16, %rsp
	popq %rbp
	ret
