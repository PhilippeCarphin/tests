	.globl	_sum_s

_sum_s:

	# Début de la fonction
	pushl %ebp
	movl %esp, %ebp

	# Soustrait 8 a esp
	pushl $0 # sum = 0 à -4(%ebp)
	pushl $0 # i = 0 à -8(%ebp)


check_continue:
	movl -8(%ebp), %eax
	cmpl 8(%ebp), %eax
	jge done

add_to_sum:
	# eax = i + sum
	movl -8(%ebp), %eax
	addl -4(%ebp), %eax

	# i + sum -> sum
	movl %eax, -4(%ebp)

	# i = i + 1;
	movl -8(%ebp), %eax
	addl $1, %eax
	movl %eax, -8(%ebp)

	jmp check_continue

done:
	# retour de la fonction
	movl -4(%ebp), %eax

	# cleanup du stack
	addl $8, %esp
	popl %ebp

	# jump à l'instruction suivante
	ret
