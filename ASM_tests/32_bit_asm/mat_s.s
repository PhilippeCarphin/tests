
	.globl mat_transpose_s

mat_transpose_s:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl %ecx
	pushl %ebx
	movl 8(%ebp), %ecx

	movl $0, 12(%ebp)

	movl	$0, -4(%ebp)
	jmp	check_continue_outer
outer_loop_body:

################ INNER LOOP #######################
	movl	$0, -8(%ebp)
	jmp	check_continue_inner
inner_loop_body:

	# i * size -> edx
	movl	-4(%ebp), %eax # i -> eax
	imull	16(%ebp), %eax # eax *= size
	movl	%eax, %edx

	# i * size + j -> eax
	movl	-8(%ebp), %eax # j -> eax
	addl	%edx, %eax # add 

	# mem[%ecx + 4*%eax] -> %edx
	movl (%ecx, %eax, 4), %edx

	# sum += %edx
	addl 12(%ebp), %edx
	movl %edx, 12(%ebp)

incr_inner:
	addl	$1, -8(%ebp)
check_continue_inner:
	movl	-8(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	inner_loop_body
###################################################
incr_outer:
	addl	$1, -4(%ebp)
check_continue_outer:
	movl	-4(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	outer_loop_body
	nop


	movl 12(%ebp), %eax

done:
	popl %ebx
	popl %ecx
	leave
	ret
