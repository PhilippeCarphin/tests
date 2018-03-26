	.globl	sum_s

sum_s:

	# Début de la fonction
	pushl %ebp
	movl %esp, %ebp

	movl $42, %eax

	popl %ebp
	# jump à l'instruction suivante
	ret
