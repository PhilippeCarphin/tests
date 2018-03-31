	.globl	sum_s

sum_s:

	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
	jmp	check_continue
for_body:
	movl	-8(%ebp), %eax
	imull	-8(%ebp), %eax
	addl	%eax, -4(%ebp)
	addl	$1, -8(%ebp)
check_continue:
	movl	-8(%ebp), %eax
	cmpl	8(%ebp), %eax
	jl	for_body
	movl	-4(%ebp), %eax
	leave
	ret
