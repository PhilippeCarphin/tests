	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.globl	_array_experiment       ## -- Begin function array_experiment
	.p2align	4, 0x90
_array_experiment:                      ## @array_experiment
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	%edi, -12(%rbp)
	movl	-12(%rbp), %ecx
	movl	%ecx, %eax
	movq	%rsp, %rdx
	movq	%rdx, -24(%rbp)
	leaq	15(,%rax,8), %rdx
	andq	$-16, %rdx
	movq	%rax, -48(%rbp)         ## 8-byte Spill
	movq	%rdx, %rax
	callq	____chkstk_darwin
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	-48(%rbp), %rdx         ## 8-byte Reload
	movq	%rdx, -32(%rbp)
	movl	$0, -36(%rbp)
	movq	%rax, -56(%rbp)         ## 8-byte Spill
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-36(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	cvtsi2sdl	-36(%rbp), %xmm0
	movslq	-36(%rbp), %rax
	movq	-56(%rbp), %rcx         ## 8-byte Reload
	movsd	%xmm0, (%rcx,%rax,8)
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_1
LBB0_4:
	movl	-12(%rbp), %eax
	movq	-24(%rbp), %rcx
	movq	%rcx, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movl	%eax, -60(%rbp)         ## 4-byte Spill
	jne	LBB0_6
## %bb.5:
	movl	-60(%rbp), %eax         ## 4-byte Reload
	movq	%rbp, %rsp
	popq	%rbp
	retq
LBB0_6:
	callq	___stack_chk_fail
	ud2
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
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	-8(%rbp), %edi
	callq	_array_experiment
	xorl	%ecx, %ecx
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
