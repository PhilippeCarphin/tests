#	pushq	$9
#	pushq	$8
#	pushq	$7
#	movl	$6, %r9d
#	movl	$5, %r8d
#	movl	$4, %ecx
#	movl	$3, %edx
#	movl	$2, %esi
#	movl	$1, %edi
#	call	sum_4

.global sum
sum:
	pushq %rbp
	movq %rsp, %rbp


	movq 32(%rbp), %rax # 9
	addq 24(%rbp), %rax # 8
	addq 16(%rbp), %rax # 7
	addl %r9d, %eax # g
	addl %r8d, %eax # f
	addl %ecx, %eax # d
	addl %edx, %eax # c
	addl %esi, %eax # b
	addl %edi, %eax # a

	popq %rbp
	ret
