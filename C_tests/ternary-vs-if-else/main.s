	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.globl	_ternary_max            ## -- Begin function ternary_max
	.p2align	4, 0x90
_ternary_max:                           ## @ternary_max
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	LBB0_2
## %bb.1:
	movl	-4(%rbp), %eax
	movl	%eax, -16(%rbp)         ## 4-byte Spill
	jmp	LBB0_3
LBB0_2:
	movl	-8(%rbp), %eax
	movl	%eax, -16(%rbp)         ## 4-byte Spill
LBB0_3:
	movl	-16(%rbp), %eax         ## 4-byte Reload
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_if_else_max            ## -- Begin function if_else_max
	.p2align	4, 0x90
_if_else_max:                           ## @if_else_max
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	LBB1_2
## %bb.1:
	movl	-4(%rbp), %eax
	movl	%eax, -12(%rbp)
	jmp	LBB1_3
LBB1_2:
	movl	-8(%rbp), %eax
	movl	%eax, -12(%rbp)
LBB1_3:
	movl	-12(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	$5, -8(%rbp)
	movl	$9, -12(%rbp)
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jle	LBB2_2
## %bb.1:
	movl	-8(%rbp), %eax
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	jmp	LBB2_3
LBB2_2:
	movl	-12(%rbp), %eax
	movl	%eax, -20(%rbp)         ## 4-byte Spill
LBB2_3:
	movl	-20(%rbp), %eax         ## 4-byte Reload
	movl	%eax, -16(%rbp)
	movl	$5, %edi
	movl	$9, %esi
	callq	_ternary_max
	movl	$5, %edi
	movl	$9, %esi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	callq	_if_else_max
	movl	-4(%rbp), %ecx
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
