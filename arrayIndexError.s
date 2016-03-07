	.file	"arrayIndexError.c"
	.text
	.globl	isInDefinition
	.type	isInDefinition, @function
isInDefinition:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	-4(%rbp), %eax
	movl	-8(%rbp), %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	-16(%rbp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L2
	cmpl	$0, -16(%rbp)
	jle	.L3
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jg	.L3
	movl	-4(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jle	.L4
.L3:
	cmpl	$0, -16(%rbp)
	jns	.L2
	movl	-12(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jg	.L2
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jg	.L2
.L4:
	movl	$1, %eax
	jmp	.L5
.L2:
	movl	$0, %eax
.L5:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	isInDefinition, .-isInDefinition
	.section	.rodata
.LC0:
	.string	"%x, %x, %x, %x, \n"
	.text
	.globl	SeqLoops_isLastIteration
	.type	SeqLoops_isLastIteration, @function
SeqLoops_isLastIteration:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1184, %rsp
	movq	%rdi, -1176(%rbp)
	movq	%rsi, -1184(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$-859045374, -136(%rbp)
	movl	$-1431699199, -132(%rbp)
	movl	$-859045374, -128(%rbp)
	movl	$-1431699199, -124(%rbp)
	movl	$-859045374, -120(%rbp)
	movl	$-1431699199, -116(%rbp)
	movl	$-859045374, -112(%rbp)
	movl	$-1431699199, -108(%rbp)
	movl	$-859045374, -104(%rbp)
	movl	$-1431699199, -100(%rbp)
	movl	$-859045374, -96(%rbp)
	movl	$-1431699199, -92(%rbp)
	movl	$-859045374, -88(%rbp)
	movl	$-1431699199, -84(%rbp)
	movl	$-859045374, -80(%rbp)
	movl	$-1431699199, -76(%rbp)
	movl	$0, -64(%rbp)
	movl	$1, -60(%rbp)
	movl	$1, -56(%rbp)
	movl	$0, -52(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -44(%rbp)
	movl	$1, -40(%rbp)
	movl	-36(%rbp), %eax
	cltq
	subq	$4, %rax
	leaq	0(,%rax,4), %rdx
	leaq	-1168(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -72(%rbp)
	leaq	-32(%rbp), %rax
	movq	$-1, (%rax)
	movq	$-1, 8(%rax)
	movl	$-1, 16(%rax)
	movq	-72(%rbp), %rax
	addq	$12, %rax
	movl	(%rax), %edi
	movq	-72(%rbp), %rax
	addq	$8, %rax
	movl	(%rax), %ecx
	movq	-72(%rbp), %rax
	addq	$4, %rax
	movl	(%rax), %edx
	movq	-72(%rbp), %rax
	movl	(%rax), %esi
	movl	$.LC0, %eax
	movl	%edi, %r8d
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L7
	call	__stack_chk_fail
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	SeqLoops_isLastIteration, .-SeqLoops_isLastIteration
	.section	.rodata
	.align 8
.LC1:
	.string	"On this system/compiler, sizeof(int) = %d \n"
	.align 8
.LC2:
	.string	"On this system/compiler, sizeof(char*) = %d \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$.LC1, %eax
	movl	$4, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$.LC2, %eax
	movl	$8, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movabsq	$-4919094222705983489, %rsi
	movabsq	$1229801703532086340, %rdi
	call	SeqLoops_isLastIteration
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
