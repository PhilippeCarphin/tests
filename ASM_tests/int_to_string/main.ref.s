	.file	"main.c"
	.text
.Ltext0:
	.globl	phil_struct_func
	.type	phil_struct_func, @function
phil_struct_func:
.LFB2:
	.file 1 "main.c"
	.loc 1 13 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, %rax
	movq	%rsi, %rcx
	movq	%rcx, %rdx
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	.loc 1 14 0
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	.loc 1 15 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	phil_struct_func, .-phil_struct_func
	.globl	phil_struct_func_s
	.type	phil_struct_func_s, @function
phil_struct_func_s:
.LFB3:
	.loc 1 17 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, %rax
	movq	%rsi, %rcx
	movq	%rcx, %rdx
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	.loc 1 18 0
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	.loc 1 19 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	phil_struct_func_s, .-phil_struct_func_s
	.globl	module
	.type	module, @function
module:
.LFB4:
	.loc 1 22 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	.loc 1 23 0
	movl	-20(%rbp), %eax
	cltd
	idivl	-24(%rbp)
	movl	%edx, -4(%rbp)
	.loc 1 24 0
	movl	-4(%rbp), %eax
	addl	$48, %eax
	.loc 1 25 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	module, .-module
	.section	.rodata
.LC0:
	.string	"int_to_string(input) == %s\n"
.LC1:
	.string	" "
.LC2:
	.string	" %d = %d * 10 + %d\n"
.LC3:
	.string	"a != qb + r"
.LC4:
	.string	"phil_struct_func(p) = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.loc 1 29 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -68(%rbp)
	movq	%rsi, -80(%rbp)
	.loc 1 30 0
	movl	$1, -64(%rbp)
	movl	$2, -60(%rbp)
	movl	$3, -56(%rbp)
	movl	$4, -52(%rbp)
	.loc 1 44 0
	movl	$1337, -4(%rbp)
	.loc 1 46 0
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	int_to_string
	movq	%rax, -16(%rbp)
	.loc 1 47 0
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	.loc 1 48 0
	cmpl	$0, -4(%rbp)
	je	.L8
	.loc 1 48 0 is_stmt 0 discriminator 1
	movl	$.LC1, %edi
	call	puts
.L8:
	.loc 1 49 0 is_stmt 1
	movl	$1234, %edi
	call	malloc
	movq	%rax, -24(%rbp)
	.loc 1 50 0
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -24(%rbp)
	movb	$48, (%rax)
	.loc 1 51 0
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -24(%rbp)
	movb	$66, (%rax)
	.loc 1 52 0
	movq	-24(%rbp), %rax
	movb	$0, (%rax)
	.loc 1 53 0
	movl	-4(%rbp), %eax
	movl	%eax, -28(%rbp)
	.loc 1 54 0
	movl	-28(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -32(%rbp)
	.loc 1 55 0
	movl	-28(%rbp), %ecx
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
	movl	%eax, -36(%rbp)
	.loc 1 56 0
	movl	-36(%rbp), %ecx
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	.loc 1 58 0
	movl	-32(%rbp), %eax
	leal	10(%rax), %edx
	movl	-36(%rbp), %eax
	addl	%edx, %eax
	cmpl	-28(%rbp), %eax
	je	.L9
	.loc 1 59 0
	movl	$.LC3, %edi
	call	puts
.L9:
	.loc 1 61 0
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
	call	phil_struct_func
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	.loc 1 62 0
	movl	$0, %eax
	.loc 1 63 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-redhat-linux/6.4.1/include/stddef.h"
	.file 3 "/usr/include/bits/types.h"
	.file 4 "/usr/include/libio.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "/usr/include/bits/sys_errlist.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x486
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF65
	.byte	0xc
	.long	.LASF66
	.long	.LASF67
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF8
	.byte	0x2
	.byte	0xd8
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF1
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF2
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF3
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF4
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF5
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0x83
	.long	0x46
	.uleb128 0x2
	.long	.LASF10
	.byte	0x3
	.byte	0x84
	.long	0x46
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF11
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0x9c
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF12
	.uleb128 0x7
	.long	0x9c
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF13
	.uleb128 0x8
	.long	.LASF43
	.byte	0xd8
	.byte	0x4
	.byte	0xf1
	.long	0x22c
	.uleb128 0x9
	.long	.LASF14
	.byte	0x4
	.byte	0xf2
	.long	0x3f
	.byte	0
	.uleb128 0x9
	.long	.LASF15
	.byte	0x4
	.byte	0xf7
	.long	0x96
	.byte	0x8
	.uleb128 0x9
	.long	.LASF16
	.byte	0x4
	.byte	0xf8
	.long	0x96
	.byte	0x10
	.uleb128 0x9
	.long	.LASF17
	.byte	0x4
	.byte	0xf9
	.long	0x96
	.byte	0x18
	.uleb128 0x9
	.long	.LASF18
	.byte	0x4
	.byte	0xfa
	.long	0x96
	.byte	0x20
	.uleb128 0x9
	.long	.LASF19
	.byte	0x4
	.byte	0xfb
	.long	0x96
	.byte	0x28
	.uleb128 0x9
	.long	.LASF20
	.byte	0x4
	.byte	0xfc
	.long	0x96
	.byte	0x30
	.uleb128 0x9
	.long	.LASF21
	.byte	0x4
	.byte	0xfd
	.long	0x96
	.byte	0x38
	.uleb128 0x9
	.long	.LASF22
	.byte	0x4
	.byte	0xfe
	.long	0x96
	.byte	0x40
	.uleb128 0xa
	.long	.LASF23
	.byte	0x4
	.value	0x100
	.long	0x96
	.byte	0x48
	.uleb128 0xa
	.long	.LASF24
	.byte	0x4
	.value	0x101
	.long	0x96
	.byte	0x50
	.uleb128 0xa
	.long	.LASF25
	.byte	0x4
	.value	0x102
	.long	0x96
	.byte	0x58
	.uleb128 0xa
	.long	.LASF26
	.byte	0x4
	.value	0x104
	.long	0x264
	.byte	0x60
	.uleb128 0xa
	.long	.LASF27
	.byte	0x4
	.value	0x106
	.long	0x26a
	.byte	0x68
	.uleb128 0xa
	.long	.LASF28
	.byte	0x4
	.value	0x108
	.long	0x3f
	.byte	0x70
	.uleb128 0xa
	.long	.LASF29
	.byte	0x4
	.value	0x10c
	.long	0x3f
	.byte	0x74
	.uleb128 0xa
	.long	.LASF30
	.byte	0x4
	.value	0x10e
	.long	0x77
	.byte	0x78
	.uleb128 0xa
	.long	.LASF31
	.byte	0x4
	.value	0x112
	.long	0x5b
	.byte	0x80
	.uleb128 0xa
	.long	.LASF32
	.byte	0x4
	.value	0x113
	.long	0x69
	.byte	0x82
	.uleb128 0xa
	.long	.LASF33
	.byte	0x4
	.value	0x114
	.long	0x270
	.byte	0x83
	.uleb128 0xa
	.long	.LASF34
	.byte	0x4
	.value	0x118
	.long	0x280
	.byte	0x88
	.uleb128 0xa
	.long	.LASF35
	.byte	0x4
	.value	0x121
	.long	0x82
	.byte	0x90
	.uleb128 0xa
	.long	.LASF36
	.byte	0x4
	.value	0x129
	.long	0x94
	.byte	0x98
	.uleb128 0xa
	.long	.LASF37
	.byte	0x4
	.value	0x12a
	.long	0x94
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF38
	.byte	0x4
	.value	0x12b
	.long	0x94
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF39
	.byte	0x4
	.value	0x12c
	.long	0x94
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF40
	.byte	0x4
	.value	0x12e
	.long	0x2d
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF41
	.byte	0x4
	.value	0x12f
	.long	0x3f
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF42
	.byte	0x4
	.value	0x131
	.long	0x286
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF68
	.byte	0x4
	.byte	0x96
	.uleb128 0x8
	.long	.LASF44
	.byte	0x18
	.byte	0x4
	.byte	0x9c
	.long	0x264
	.uleb128 0x9
	.long	.LASF45
	.byte	0x4
	.byte	0x9d
	.long	0x264
	.byte	0
	.uleb128 0x9
	.long	.LASF46
	.byte	0x4
	.byte	0x9e
	.long	0x26a
	.byte	0x8
	.uleb128 0x9
	.long	.LASF47
	.byte	0x4
	.byte	0xa2
	.long	0x3f
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x233
	.uleb128 0x6
	.byte	0x8
	.long	0xaf
	.uleb128 0xc
	.long	0x9c
	.long	0x280
	.uleb128 0xd
	.long	0x8d
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x22c
	.uleb128 0xc
	.long	0x9c
	.long	0x296
	.uleb128 0xd
	.long	0x8d
	.byte	0x13
	.byte	0
	.uleb128 0xe
	.long	.LASF69
	.uleb128 0xf
	.long	.LASF48
	.byte	0x4
	.value	0x13b
	.long	0x296
	.uleb128 0xf
	.long	.LASF49
	.byte	0x4
	.value	0x13c
	.long	0x296
	.uleb128 0xf
	.long	.LASF50
	.byte	0x4
	.value	0x13d
	.long	0x296
	.uleb128 0x6
	.byte	0x8
	.long	0xa3
	.uleb128 0x7
	.long	0x2bf
	.uleb128 0x10
	.long	.LASF51
	.byte	0x5
	.byte	0xaa
	.long	0x26a
	.uleb128 0x10
	.long	.LASF52
	.byte	0x5
	.byte	0xab
	.long	0x26a
	.uleb128 0x10
	.long	.LASF53
	.byte	0x5
	.byte	0xac
	.long	0x26a
	.uleb128 0x10
	.long	.LASF54
	.byte	0x6
	.byte	0x1a
	.long	0x3f
	.uleb128 0xc
	.long	0x2c5
	.long	0x301
	.uleb128 0x11
	.byte	0
	.uleb128 0x7
	.long	0x2f6
	.uleb128 0x10
	.long	.LASF55
	.byte	0x6
	.byte	0x1b
	.long	0x301
	.uleb128 0x8
	.long	.LASF56
	.byte	0x10
	.byte	0x1
	.byte	0x5
	.long	0x346
	.uleb128 0x12
	.string	"a"
	.byte	0x1
	.byte	0x6
	.long	0x3f
	.byte	0
	.uleb128 0x12
	.string	"b"
	.byte	0x1
	.byte	0x7
	.long	0x3f
	.byte	0x4
	.uleb128 0x12
	.string	"c"
	.byte	0x1
	.byte	0x8
	.long	0x3f
	.byte	0x8
	.uleb128 0x12
	.string	"d"
	.byte	0x1
	.byte	0x9
	.long	0x3f
	.byte	0xc
	.byte	0
	.uleb128 0x13
	.long	.LASF61
	.byte	0x1
	.byte	0x1c
	.long	0x3f
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0x3e1
	.uleb128 0x14
	.long	.LASF57
	.byte	0x1
	.byte	0x1c
	.long	0x3f
	.uleb128 0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0x14
	.long	.LASF58
	.byte	0x1
	.byte	0x1c
	.long	0x3e1
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x15
	.string	"p"
	.byte	0x1
	.byte	0x1e
	.long	0x311
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x16
	.long	.LASF59
	.byte	0x1
	.byte	0x1f
	.long	0x3f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x16
	.long	.LASF60
	.byte	0x1
	.byte	0x2e
	.long	0x96
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x15
	.string	"str"
	.byte	0x1
	.byte	0x31
	.long	0x96
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x15
	.string	"a"
	.byte	0x1
	.byte	0x35
	.long	0x3f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x15
	.string	"q"
	.byte	0x1
	.byte	0x36
	.long	0x3f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x15
	.string	"r"
	.byte	0x1
	.byte	0x37
	.long	0x3f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x96
	.uleb128 0x17
	.long	.LASF62
	.byte	0x1
	.byte	0x15
	.long	0x3f
	.quad	.LFB4
	.quad	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x42d
	.uleb128 0x18
	.string	"a"
	.byte	0x1
	.byte	0x15
	.long	0x3f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x18
	.string	"b"
	.byte	0x1
	.byte	0x15
	.long	0x3f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x15
	.string	"d"
	.byte	0x1
	.byte	0x17
	.long	0x3f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x17
	.long	.LASF63
	.byte	0x1
	.byte	0x10
	.long	0x3f
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x45d
	.uleb128 0x14
	.long	.LASF64
	.byte	0x1
	.byte	0x10
	.long	0x311
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x19
	.long	.LASF70
	.byte	0x1
	.byte	0xc
	.long	0x3f
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x14
	.long	.LASF64
	.byte	0x1
	.byte	0xc
	.long	0x311
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF9:
	.string	"__off_t"
.LASF15:
	.string	"_IO_read_ptr"
.LASF27:
	.string	"_chain"
.LASF8:
	.string	"size_t"
.LASF33:
	.string	"_shortbuf"
.LASF50:
	.string	"_IO_2_1_stderr_"
.LASF21:
	.string	"_IO_buf_base"
.LASF13:
	.string	"long long unsigned int"
.LASF64:
	.string	"param"
.LASF2:
	.string	"long long int"
.LASF6:
	.string	"signed char"
.LASF65:
	.string	"GNU C11 6.4.1 20170727 (Red Hat 6.4.1-1) -mtune=generic -march=x86-64 -g"
.LASF28:
	.string	"_fileno"
.LASF16:
	.string	"_IO_read_end"
.LASF1:
	.string	"long int"
.LASF14:
	.string	"_flags"
.LASF22:
	.string	"_IO_buf_end"
.LASF31:
	.string	"_cur_column"
.LASF70:
	.string	"phil_struct_func"
.LASF30:
	.string	"_old_offset"
.LASF35:
	.string	"_offset"
.LASF44:
	.string	"_IO_marker"
.LASF51:
	.string	"stdin"
.LASF5:
	.string	"unsigned int"
.LASF0:
	.string	"long unsigned int"
.LASF69:
	.string	"_IO_FILE_plus"
.LASF19:
	.string	"_IO_write_ptr"
.LASF54:
	.string	"sys_nerr"
.LASF46:
	.string	"_sbuf"
.LASF4:
	.string	"short unsigned int"
.LASF23:
	.string	"_IO_save_base"
.LASF66:
	.string	"main.c"
.LASF34:
	.string	"_lock"
.LASF29:
	.string	"_flags2"
.LASF41:
	.string	"_mode"
.LASF52:
	.string	"stdout"
.LASF48:
	.string	"_IO_2_1_stdin_"
.LASF60:
	.string	"output"
.LASF11:
	.string	"sizetype"
.LASF20:
	.string	"_IO_write_end"
.LASF68:
	.string	"_IO_lock_t"
.LASF43:
	.string	"_IO_FILE"
.LASF47:
	.string	"_pos"
.LASF55:
	.string	"sys_errlist"
.LASF26:
	.string	"_markers"
.LASF3:
	.string	"unsigned char"
.LASF7:
	.string	"short int"
.LASF62:
	.string	"module"
.LASF32:
	.string	"_vtable_offset"
.LASF49:
	.string	"_IO_2_1_stdout_"
.LASF59:
	.string	"input"
.LASF12:
	.string	"char"
.LASF45:
	.string	"_next"
.LASF10:
	.string	"__off64_t"
.LASF17:
	.string	"_IO_read_base"
.LASF25:
	.string	"_IO_save_end"
.LASF36:
	.string	"__pad1"
.LASF37:
	.string	"__pad2"
.LASF38:
	.string	"__pad3"
.LASF39:
	.string	"__pad4"
.LASF40:
	.string	"__pad5"
.LASF63:
	.string	"phil_struct_func_s"
.LASF42:
	.string	"_unused2"
.LASF53:
	.string	"stderr"
.LASF58:
	.string	"argv"
.LASF56:
	.string	"Phil"
.LASF24:
	.string	"_IO_backup_base"
.LASF67:
	.string	"/home/pcarphin/Documents/GitHub/tests/ASM_tests/int_to_string"
.LASF57:
	.string	"argc"
.LASF61:
	.string	"main"
.LASF18:
	.string	"_IO_write_base"
	.ident	"GCC: (GNU) 6.4.1 20170727 (Red Hat 6.4.1-1)"
	.section	.note.GNU-stack,"",@progbits
