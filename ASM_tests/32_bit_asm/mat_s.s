	.globl mat_transpose_s # Name for Linux
	.globl _mat_transpose_s # Name for Darwin

mat_transpose_s:
_mat_transpose_s:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
 # +-----------------+
 # |      sum        | = -12(%ebp)
 # +-----------------+
 # |       j         | = -8(%ebp)
 # +-----------------+
 # |       i         | = -4(%ebp)
 # +-----------------+
 # |    OLD EBP      | <-- %ebp
 # +-----------------+
 # |      RET        | = 4(%ebp)
 # +-----------------+
 # |      in         | = 8(%ebp)
 # +-----------------+
 # |      out        | = 12(%ebp)
 # +-----------------+
 # |     size        | = 16(%ebp)
 # +-----------------+
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

	# mem[in + 4*%eax] -> %edx
	movl 8(%ebp), %ecx
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
	leave
	ret
