	.file	"main.c"
	.section	.rodata
.lcd:
	.string "phil string %s\n"
.LC0:
	.string	"need one argument"
.LC1:
	.string	"%d"
.LC2:
	.string	"Need an integer argument"
.LC3:
	.string	"input is %d\n"
.LC4:
	.string	"int_to_string(input) == %s\n"
.LC5:
	.string	" "
.LC6:
	.string	" %d = %d * 10 + %d\n"
.LC7:
	.string	"a != qb + r"
	.text
	.globl	main
	.type	main, @function
phil_struct_func:
	movq $0, %rax;
	ret
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -68(%rbp)
	movq	%rsi, -80(%rbp)
	movl	$1, -48(%rbp)
	movl	$2, -44(%rbp)
	movl	$3, -40(%rbp)
	movl	$4, -36(%rbp)
	cmpl	$1, -68(%rbp)
	jg	.L2
	movl	$.LC0, %edi
	call	puts
	movl	$8, %eax
	jmp	.L7
.L2:
	movq	-80(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	leaq	-52(%rbp), %rdx
	movl	$.LC1, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf
	cmpl	$1, %eax
	je	.L4
	movl	$.LC2, %edi
	call	puts
	movl	$9, %eax
	jmp	.L7
.L4:
	movl	-52(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	-52(%rbp), %eax
	movl	%eax, %edi
	call	int_to_string
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	-52(%rbp), %eax
	testl	%eax, %eax
	je	.L5
	movl	$.LC5, %edi
	call	puts
.L5:
	movl	$1234, %edi
	call	malloc
	movq	%rax, -16(%rbp)  # str is at -16(%rbp)
	# *str++ = 'A' 
	movq	-16(%rbp), %rax  # rax <- str
	movb	$65, (%rax)      # (%rax) <- 'A'
	leaq	1(%rax), %rdx    # rdx <- str + 1
	movq	%rdx, -16(%rbp)  # str <- rdx
	# *str++ = 'B' 
	movq	-16(%rbp), %rax  # rax <- str
	movb	$66, (%rax)      # (%rax) <- 'A'
	leaq	1(%rax), %rdx    # rdx <- str + 1
	movq	%rdx, -16(%rbp)  # str <- rdx
	# *str++ = 0
	movq	-16(%rbp), %rax  # rax <- str
	movb	$0, (%rax)      # (%rax) <- 'A'
	leaq	1(%rax), %rdx    # rdx <- str + 1
	movq	%rdx, -16(%rbp)  # str <- rdx

	movq 16(%rbp), %rsi
	movq $.lcd, %rdi
	movl $0, %eax
	call printf

		

	movl	-52(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -24(%rbp)
	movl	-20(%rbp), %ecx
	movl	$-1518422781, %edx
	movl	%ecx, %eax
	imull	%edx
	leal	(%rdx,%rcx), %eax
	sarl	$6, %eax
	movl	%eax, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	imull	$99, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %ecx
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	movl	-24(%rbp), %eax
	leal	10(%rax), %edx
	movl	-28(%rbp), %eax
	addl	%edx, %eax
	cmpl	-20(%rbp), %eax
	je	.L6
	movl	$.LC7, %edi
	call	puts
.L6:
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
	call	phil_struct_func
	movl	$0, %eax
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
