	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"Correct answer"
.LC1:
	.string	"Wrong answer"
	.text
	.globl	test_add
	.type	test_add, @function
test_add:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$88, %esi
	movl	$77, %edi
	call	add
	cmpl	$165, %eax
	jne	.L2
	movl	$.LC0, %edi
	call	puts
	movl	$0, %eax
	jmp	.L3
.L2:
	movl	$.LC1, %edi
	call	puts
	movl	$1, %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	test_add, .-test_add
	.section	.rodata
	.align 8
.LC2:
	.string	"Calling my assembler add function : %d\n"
.LC3:
	.string	"sum(1,2,3,4,5,6,7,8,9) = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$88, %esi
	movl	$77, %edi
	call	add
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf

	# Calling my function sum
	# =======================
	# use 32 bytes on stack for parameters and 8 extra bytes ?
	subq	$8, %rsp # Extra bytes, don't know what this is for
	pushq	$9       # last parameter
	pushq	$8       # next-to-last param
	pushq	$7       # ...
	movl	$6, %r9d # First 6 params passed with registers
	movl	$5, %r8d # ...
	movl	$4, %ecx # ...
	movl	$3, %edx # ...
	movl	$2, %esi # ...
	movl	$1, %edi # ...
	call	sum      # push address of next instruction and jmp sum
	addq	$32, %rsp# Deallocate the 32 bytes from the stack

	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
