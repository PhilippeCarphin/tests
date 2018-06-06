	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"TABLE : %s\n"
	.text
	.globl	show_tables
	.type	show_tables, @function
show_tables:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	statement_str.3189(%rip), %rsi
	leaq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	movl	$0, %r8d
	movq	%rdx, %rcx
	movl	$-1, %edx
	movq	%rax, %rdi
	call	sqlite3_prepare_v2
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	sqlite3_column_text
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.L2:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	sqlite3_step
	cmpl	$101, %eax
	jne	.L3
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	sqlite3_finalize
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	show_tables, .-show_tables
	.globl	show_column
	.type	show_column, @function
show_column:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	-28(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	sqlite3_column_type
	cmpl	$2, %eax
	je	.L7
	cmpl	$3, %eax
	je	.L8
	cmpl	$1, %eax
	je	.L9
	jmp	.L5
.L8:
	movl	-28(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	sqlite3_column_text
	movq	%rax, -8(%rbp)
	jmp	.L5
.L9:
	movl	-28(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	sqlite3_column_int
	movl	%eax, -12(%rbp)
	jmp	.L5
.L7:
	movl	-28(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	sqlite3_column_double
	unpcklpd	%xmm0, %xmm0
	cvtpd2ps	%xmm0, %xmm1
	movss	%xmm1, -16(%rbp)
	nop
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	show_column, .-show_column
	.section	.rodata
	.align 8
.LC1:
	.string	"id_rapport=%d, id_stn=%s, lat=%f, lon=%f\n"
	.text
	.globl	print_Rapport
	.type	print_Rapport, @function
print_Rapport:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	sqlite3_column_double
	movsd	%xmm0, -48(%rbp)
	movq	-48(%rbp), %r12
	movq	-40(%rbp), %rax
	movl	$6, %esi
	movq	%rax, %rdi
	call	sqlite3_column_double
	movsd	%xmm0, -48(%rbp)
	movq	-48(%rbp), %rbx
	movq	-40(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	sqlite3_column_text
	movq	%rax, %r13
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	sqlite3_column_int
	movq	%r12, -48(%rbp)
	movsd	-48(%rbp), %xmm1
	movq	%rbx, -48(%rbp)
	movsd	-48(%rbp), %xmm0
	movq	%r13, %rdx
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$2, %eax
	call	printf
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	print_Rapport, .-print_Rapport
	.globl	print_row
	.type	print_row, @function
print_row:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	sqlite3_column_count
	movl	%eax, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L12
.L13:
	movl	-4(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	show_column
	addl	$1, -4(%rbp)
.L12:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L13
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	print_row, .-print_row
	.section	.rodata
.LC2:
	.string	"SELECT * FROM Rapport;"
	.text
	.globl	show_rapport
	.type	show_rapport, @function
show_rapport:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	leaq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movl	$0, %r8d
	movq	%rdx, %rcx
	movl	$-1, %edx
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	sqlite3_prepare_v2
	movl	$0, -4(%rbp)
	jmp	.L15
.L16:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	print_row
	addl	$1, -4(%rbp)
.L15:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	sqlite3_step
	cmpl	$101, %eax
	jne	.L16
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	sqlite3_finalize
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	show_rapport, .-show_rapport
	.section	.rodata
.LC3:
	.string	"acars.sqlite"
.LC4:
	.string	"Can't open database: %s\n"
.LC5:
	.string	"nb_rapports = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	$.LC3, -8(%rbp)
	leaq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	sqlite3_open
	movl	%eax, -12(%rbp)
	cmpl	$0, -12(%rbp)
	je	.L19
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	sqlite3_errmsg
	movq	%rax, %rdx
	movq	stderr(%rip), %rax
	movl	$.LC4, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	sqlite3_close
	movl	$1, %eax
	jmp	.L21
.L19:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	show_tables
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	show_rapport
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	sqlite3_close
	movl	$0, %eax
.L21:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC6:
	.string	"SELECT name FROM sqlite_master WHERE type='table';"
	.data
	.align 8
	.type	statement_str.3189, @object
	.size	statement_str.3189, 8
statement_str.3189:
	.quad	.LC6
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.4) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
