	.file	"parseTest.c"
	.globl	initPhil
	.bss
	.align 4
	.type	initPhil, @object
	.size	initPhil, 4
initPhil:
	.zero	4
	.comm	uninitPhil,4,4
	.section	.rodata
	.align 8
.LC0:
	.string	"In the words of Tracy Jordan: Too small"
	.text
	.globl	readline
	.type	readline, @function
readline:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movq	%rdx, -56(%rbp)
	movl	$18, uninitPhil(%rip)
	movq	$0, -24(%rbp)
	jmp	.L2
	.cfi_offset 3, -24
.L4:
	movq	-24(%rbp), %rax
	addq	-40(%rbp), %rax
	movb	%bl, (%rax)
	addq	$1, -24(%rbp)
	movl	-44(%rbp), %eax
	cltq
	cmpq	-24(%rbp), %rax
	jge	.L2
	movl	$.LC0, %eax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$-1, %eax
	jmp	.L3
.L2:
	movq	-24(%rbp), %rax
	addq	-56(%rbp), %rax
	movzbl	(%rax), %ebx
	cmpb	$10, %bl
	jne	.L4
	movq	-24(%rbp), %rax
	addq	-40(%rbp), %rax
	movb	$0, (%rax)
	movl	$16, initPhil(%rip)
	movq	-24(%rbp), %rax
.L3:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	readline, .-readline
	.section	.rodata
.LC1:
	.string	"./resources.def"
	.align 8
.LC2:
	.string	"=============================="
	.align 8
.LC3:
	.string	"here is the number of the file descriptor : %d \n"
	.align 8
.LC4:
	.string	"here is what happens when I open the same file : %d \n"
.LC5:
	.string	"readline() = %d: ,LINE: %s--\n"
.LC6:
	.string	" %[^= ] = %[^\n]"
.LC7:
	.string	"defkey : %s--\n"
.LC8:
	.string	"defval : %s--"
.LC9:
	.string	"\n===========================\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$2224, %rsp
	movl	%edi, -2212(%rbp)
	movq	%rsi, -2224(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -2024(%rbp)
	movq	$.LC1, -2056(%rbp)
	movl	$.LC2, %edi
	call	puts
	movq	-2056(%rbp), %rax
	movl	$2050, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open
	movl	%eax, -2020(%rbp)
	movl	$.LC3, %eax
	movl	-2020(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movq	-2056(%rbp), %rax
	movl	$2050, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open
	movl	%eax, %edx
	movl	$.LC4, %eax
	movl	%edx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	leaq	-2208(%rbp), %rdx
	movl	-2020(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fstat
	movq	-2160(%rbp), %rax
	movl	-2020(%rbp), %edx
	movl	$0, %r9d
	movl	%edx, %r8d
	movl	$1, %ecx
	movl	$3, %edx
	movq	%rax, %rsi
	movl	$0, %edi
	call	mmap
	movq	%rax, -2048(%rbp)
	movl	-2020(%rbp), %eax
	movl	%eax, %edi
	call	close
	movq	-2048(%rbp), %rax
	movq	%rax, -2064(%rbp)
	movq	-2160(%rbp), %rax
	addq	-2048(%rbp), %rax
	movq	%rax, -2040(%rbp)
	movl	$1000, %edi
	call	malloc
	movq	%rax, -2032(%rbp)
.L6:
	movq	-2064(%rbp), %rdx
	movq	-2032(%rbp), %rax
	movl	$1000, %esi
	movq	%rax, %rdi
	call	readline
	addl	$1, %eax
	movl	%eax, -2024(%rbp)
	movl	-2024(%rbp), %eax
	cltq
	addq	%rax, -2064(%rbp)
	movl	$.LC5, %eax
	movq	-2032(%rbp), %rdx
	movl	-2024(%rbp), %ecx
	movl	%ecx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$.LC6, %esi
	movq	-2032(%rbp), %rax
	leaq	-1008(%rbp), %rcx
	leaq	-2016(%rbp), %rdx
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf
	movl	$.LC7, %eax
	leaq	-2016(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$.LC8, %eax
	leaq	-1008(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$.LC9, %edi
	call	puts
	movq	-2064(%rbp), %rax
	cmpq	-2040(%rbp), %rax
	jb	.L6
	movl	$0, %eax
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
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
