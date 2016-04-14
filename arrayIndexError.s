.set r0,0; .set SP,1; .set RTOC,2; .set r3,3; .set r4,4
.set r5,5; .set r6,6; .set r7,7; .set r8,8; .set r9,9
.set r10,10; .set r11,11; .set r12,12; .set r13,13; .set r14,14
.set r15,15; .set r16,16; .set r17,17; .set r18,18; .set r19,19
.set r20,20; .set r21,21; .set r22,22; .set r23,23; .set r24,24
.set r25,25; .set r26,26; .set r27,27; .set r28,28; .set r29,29
.set r30,30; .set r31,31
.set fp0,0; .set fp1,1; .set fp2,2; .set fp3,3; .set fp4,4
.set fp5,5; .set fp6,6; .set fp7,7; .set fp8,8; .set fp9,9
.set fp10,10; .set fp11,11; .set fp12,12; .set fp13,13; .set fp14,14
.set fp15,15; .set fp16,16; .set fp17,17; .set fp18,18; .set fp19,19
.set fp20,20; .set fp21,21; .set fp22,22; .set fp23,23; .set fp24,24
.set fp25,25; .set fp26,26; .set fp27,27; .set fp28,28; .set fp29,29
.set fp30,30; .set fp31,31
.set v0,0; .set v1,1; .set v2,2; .set v3,3; .set v4,4
.set v5,5; .set v6,6; .set v7,7; .set v8,8; .set v9,9
.set v10,10; .set v11,11; .set v12,12; .set v13,13; .set v14,14
.set v15,15; .set v16,16; .set v17,17; .set v18,18; .set v19,19
.set v20,20; .set v21,21; .set v22,22; .set v23,23; .set v24,24
.set v25,25; .set v26,26; .set v27,27; .set v28,28; .set v29,29
.set v30,30; .set v31,31
.set x0,0; .set x1,1; .set x2,2; .set x3,3; .set x4,4
.set x5,5; .set x6,6; .set x7,7; .set x8,8; .set x9,9
.set x10,10; .set x11,11; .set x12,12; .set x13,13; .set x14,14
.set x15,15; .set x16,16; .set x17,17; .set x18,18; .set x19,19
.set x20,20; .set x21,21; .set x22,22; .set x23,23; .set x24,24
.set x25,25; .set x26,26; .set x27,27; .set x28,28; .set x29,29
.set x30,30; .set x31,31; .set x32,32; .set x33,33; .set x34,34
.set x35,35; .set x36,36; .set x37,37; .set x38,38; .set x39,39
.set x40,40; .set x41,41; .set x42,42; .set x43,43; .set x44,44
.set x45,45; .set x46,46; .set x47,47; .set x48,48; .set x49,49
.set x50,50; .set x51,51; .set x52,52; .set x53,53; .set x54,54
.set x55,55; .set x56,56; .set x57,57; .set x58,58; .set x59,59
.set x60,60; .set x61,61; .set x62,62; .set x63,63
.set q0,0; .set q1,1; .set q2,2; .set q3,3; .set q4,4
.set q5,5; .set q6,6; .set q7,7; .set q8,8; .set q9,9
.set q10,10; .set q11,11; .set q12,12; .set q13,13; .set q14,14
.set q15,15; .set q16,16; .set q17,17; .set q18,18; .set q19,19
.set q20,20; .set q21,21; .set q22,22; .set q23,23; .set q24,24
.set q25,25; .set q26,26; .set q27,27; .set q28,28; .set q29,29
.set q30,30; .set q31,31
.set MQ,0; .set XER,1; .set FROM_RTCU,4; .set FROM_RTCL,5; .set FROM_DEC,6
.set LR,8; .set CTR,9; .set TID,17; .set DSISR,18; .set DAR,19; .set TO_RTCU,20
.set TO_RTCL,21; .set TO_DEC,22; .set SDR_0,24; .set SDR_1,25; .set SRR_0,26
.set SRR_1,27
.set BO_dCTR_NZERO_AND_NOT,0; .set BO_dCTR_NZERO_AND_NOT_1,1
.set BO_dCTR_ZERO_AND_NOT,2; .set BO_dCTR_ZERO_AND_NOT_1,3
.set BO_IF_NOT,4; .set BO_IF_NOT_1,5; .set BO_IF_NOT_2,6
.set BO_IF_NOT_3,7; .set BO_dCTR_NZERO_AND,8; .set BO_dCTR_NZERO_AND_1,9
.set BO_dCTR_ZERO_AND,10; .set BO_dCTR_ZERO_AND_1,11; .set BO_IF,12
.set BO_IF_1,13; .set BO_IF_2,14; .set BO_IF_3,15; .set BO_dCTR_NZERO,16
.set BO_dCTR_NZERO_1,17; .set BO_dCTR_ZERO,18; .set BO_dCTR_ZERO_1,19
.set BO_ALWAYS,20; .set BO_ALWAYS_1,21; .set BO_ALWAYS_2,22
.set BO_ALWAYS_3,23; .set BO_dCTR_NZERO_8,24; .set BO_dCTR_NZERO_9,25
.set BO_dCTR_ZERO_8,26; .set BO_dCTR_ZERO_9,27; .set BO_ALWAYS_8,28
.set BO_ALWAYS_9,29; .set BO_ALWAYS_10,30; .set BO_ALWAYS_11,31
.set CR0_LT,0; .set CR0_GT,1; .set CR0_EQ,2; .set CR0_SO,3
.set CR1_FX,4; .set CR1_FEX,5; .set CR1_VX,6; .set CR1_OX,7
.set CR2_LT,8; .set CR2_GT,9; .set CR2_EQ,10; .set CR2_SO,11
.set CR3_LT,12; .set CR3_GT,13; .set CR3_EQ,14; .set CR3_SO,15
.set CR4_LT,16; .set CR4_GT,17; .set CR4_EQ,18; .set CR4_SO,19
.set CR5_LT,20; .set CR5_GT,21; .set CR5_EQ,22; .set CR5_SO,23
.set CR6_LT,24; .set CR6_GT,25; .set CR6_EQ,26; .set CR6_SO,27
.set CR7_LT,28; .set CR7_GT,29; .set CR7_EQ,30; .set CR7_SO,31
.set TO_LT,16; .set TO_GT,8; .set TO_EQ,4; .set TO_LLT,2; .set TO_LGT,1

	.rename	H.4.NO_SYMBOL{PR},""
	.rename	H.14.NO_SYMBOL{TC},""
	.rename	H.16.NO_SYMBOL{RO},""
	.rename	E.18.__STATIC{RW},"_$STATIC"
	.rename	H.20.__STATIC{TC},"_$STATIC"
	.rename	H.24.SeqLoops_isLastIteration{TC},"SeqLoops_isLastIteration"
	.rename	H.28.main{TC},"main"
	.rename	H.32.isInDefinition{TC},"isInDefinition"

	.lglobl	H.4.NO_SYMBOL{PR}       
	.globl	.SeqLoops_isLastIteration
	.globl	.main                   
	.globl	.isInDefinition         
	.lglobl	H.16.NO_SYMBOL{RO}      
	.lglobl	E.18.__STATIC{RW}       
	.globl	SeqLoops_isLastIteration{DS}
	.globl	main{DS}                
	.globl	isInDefinition{DS}      
	.extern	.___fill64{PR}          
	.extern	.printf{PR}             


# .text section
	.file	"arrayIndexError.c"     
	.machine	"ppc64"


	.csect	H.4.NO_SYMBOL{PR}, 7    
.SeqLoops_isLastIteration:              # 0x0000000000000000 (H.4.NO_SYMBOL)
	mfspr      r0,LR
	std        r31,-8(SP)
	std        r30,-16(SP)
	std        r0,16(SP)
	stdu       SP,-1296(SP)
	ld         r31,T.20.__STATIC(RTOC)
	ld         r30,T.14.NO_SYMBOL(RTOC)
	std        r3,1344(SP)
	std        r4,1352(SP)
	addi       r3,r0,8
	stw        r3,224(SP)
	addi       r3,SP,228
	addi       r4,r0,1020
	addi       r5,r0,0
	bl         .___fill64{PR}
	ori        r0,r0,0x0000
	lwa        r3,216(SP)
	addi       r3,r3,-4
	extsw      r3,r3
	rldicr     r3,r3,2,61
	add        r3,SP,r3
	addi       r3,r3,224
	std        r3,1264(SP)
	ori        r3,r30,0x0000
	lswi       r5,r3,20
	addi       r3,SP,120
	stswi      r5,r3,20
	lwa        r4,216(SP)
	ori        r3,r31,0x0000
	bl         .printf{PR}
	ori        r0,r0,0x0000
	ld         r4,1344(SP)
	ld         r5,1352(SP)
	addi       r3,r31,140
	bl         .printf{PR}
	ori        r0,r0,0x0000
	addi       r3,r31,192
	bl         .printf{PR}
	ori        r0,r0,0x0000
	ld         r3,1264(SP)
	lwa        r4,0(r3)
	lwa        r5,4(r3)
	lwa        r6,8(r3)
	lwa        r7,12(r3)
	addi       r3,r31,20
	bl         .printf{PR}
	ori        r0,r0,0x0000
	ld         r0,1312(SP)
	mtspr      LR,r0
	addi       SP,SP,1296
	ld         r30,-16(SP)
	ld         r31,-8(SP)
	bclr       BO_ALWAYS,CR0_LT
	.long	0x00000000
# traceback table
	.byte	0x00			# VERSION=0
	.byte	0x00			# LANG=TB_C
	.byte	0x20			# IS_GL=0,IS_EPROL=0,HAS_TBOFF=1
					# INT_PROC=0,HAS_CTL=0,TOCLESS=0
					# FP_PRESENT=0,LOG_ABORT=0
	.byte	0x41			# INT_HNDL=0,NAME_PRESENT=1
					# USES_ALLOCA=0,CL_DIS_INV=WALK_ONCOND
					# SAVES_CR=0,SAVES_LR=1
	.byte	0x80			# STORES_BC=1,FPR_SAVED=0
	.byte	0x02			# GPR_SAVED=2
	.byte	0x02			# FIXEDPARMS=2
	.byte	0x01			# FLOATPARMS=0,PARMSONSTK=1
	.long	0x00000000		# 
	.long	0x000000d4		# TB_OFFSET
	.short	24			# NAME_LEN
	.byte	"SeqLoops_isLastIteration"
	.byte	0			# padding
	.byte	0			# padding
# End of traceback table
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
.main:                                  # 0x0000000000000120 (H.4.NO_SYMBOL+0x0120)
	mfspr      r0,LR
	std        r31,-8(SP)
	std        r30,-16(SP)
	std        r0,16(SP)
	stdu       SP,-128(SP)
	ld         r31,T.20.__STATIC(RTOC)
	ld         r30,T.14.NO_SYMBOL(RTOC)
	std        r3,176(SP)
	std        r4,184(SP)
	ld         r3,176(SP)
	stw        r3,176(SP)
	addi       r3,r31,44
	addi       r4,r0,4
	bl         .printf{PR}
	ori        r0,r0,0x0000
	addi       r3,r31,92
	addi       r4,r0,8
	bl         .printf{PR}
	ori        r0,r0,0x0000
	ld         r3,32(r30)
	ld         r4,40(r30)
	bl         .SeqLoops_isLastIteration
	addi       r3,r0,0
	ld         r0,144(SP)
	mtspr      LR,r0
	addi       SP,SP,128
	ld         r30,-16(SP)
	ld         r31,-8(SP)
	bclr       BO_ALWAYS,CR0_LT
	.long	0x00000000
# traceback table
	.byte	0x00			# VERSION=0
	.byte	0x00			# LANG=TB_C
	.byte	0x20			# IS_GL=0,IS_EPROL=0,HAS_TBOFF=1
					# INT_PROC=0,HAS_CTL=0,TOCLESS=0
					# FP_PRESENT=0,LOG_ABORT=0
	.byte	0x41			# INT_HNDL=0,NAME_PRESENT=1
					# USES_ALLOCA=0,CL_DIS_INV=WALK_ONCOND
					# SAVES_CR=0,SAVES_LR=1
	.byte	0x80			# STORES_BC=1,FPR_SAVED=0
	.byte	0x02			# GPR_SAVED=2
	.byte	0x02			# FIXEDPARMS=2
	.byte	0x01			# FLOATPARMS=0,PARMSONSTK=1
	.long	0x00000000		# 
	.long	0x00000074		# TB_OFFSET
	.short	4			# NAME_LEN
	.byte	"main"
	.byte	0			# padding
	.byte	0			# padding
# End of traceback table
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
.isInDefinition:                        # 0x00000000000001c0 (H.4.NO_SYMBOL+0x01c0)
	stdu       SP,-112(SP)
	std        r3,160(SP)
	std        r4,168(SP)
	std        r5,176(SP)
	std        r6,184(SP)
	ld         r3,160(SP)
	stw        r3,160(SP)
	ld         r3,168(SP)
	stw        r3,168(SP)
	ld         r3,176(SP)
	stw        r3,176(SP)
	ld         r3,184(SP)
	stw        r3,184(SP)
	lwa        r4,168(SP)
	lwa        r3,160(SP)
	subf       r6,r3,r4
	lwa        r5,184(SP)
	divw       r7,r6,r5
	mulld      r7,r5,r7
	subf       r6,r7,r6
	cmpi       0,0,r6,0
	bc         BO_IF_NOT,CR0_EQ,__L268
	cmpi       0,0,r5,0
	bc         BO_IF_NOT,CR0_GT,__L238
	cmp        0,0,r4,r3
	bc         BO_IF,CR0_GT,__L238
	lwa        r4,176(SP)
	cmp        0,0,r3,r4
	bc         BO_IF,CR0_GT,__L238
	b          __L260
__L238:                                 # 0x0000000000000238 (H.4.NO_SYMBOL+0x0238)
	lwa        r3,184(SP)
	cmpi       0,0,r3,0
	bc         BO_IF_NOT,CR0_LT,__L268
	lwa        r3,176(SP)
	lwa        r4,160(SP)
	cmp        0,0,r4,r3
	bc         BO_IF,CR0_LT,__L268
	lwa        r3,168(SP)
	cmp        0,0,r3,r4
	bc         BO_IF,CR0_LT,__L268
__L260:                                 # 0x0000000000000260 (H.4.NO_SYMBOL+0x0260)
	addi       r3,r0,1
	b          __L26c
__L268:                                 # 0x0000000000000268 (H.4.NO_SYMBOL+0x0268)
	addi       r3,r0,0
__L26c:                                 # 0x000000000000026c (H.4.NO_SYMBOL+0x026c)
	addi       SP,SP,112
	bclr       BO_ALWAYS,CR0_LT
	.long	0x00000000
# traceback table
	.byte	0x00			# VERSION=0
	.byte	0x00			# LANG=TB_C
	.byte	0x20			# IS_GL=0,IS_EPROL=0,HAS_TBOFF=1
					# INT_PROC=0,HAS_CTL=0,TOCLESS=0
					# FP_PRESENT=0,LOG_ABORT=0
	.byte	0x40			# INT_HNDL=0,NAME_PRESENT=1
					# USES_ALLOCA=0,CL_DIS_INV=WALK_ONCOND
					# SAVES_CR=0,SAVES_LR=0
	.byte	0x80			# STORES_BC=1,FPR_SAVED=0
	.byte	0x00			# GPR_SAVED=0
	.byte	0x04			# FIXEDPARMS=4
	.byte	0x01			# FLOATPARMS=0,PARMSONSTK=1
	.long	0x00000000		# 
	.long	0x000000b4		# TB_OFFSET
	.short	14			# NAME_LEN
	.byte	"isInDefinition"
# End of traceback table
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
# End	csect	H.4.NO_SYMBOL{PR}

# .data section


	.toc	                        # 0x0000000000000300 
T.24.SeqLoops_isLastIteration:
	.tc	H.24.SeqLoops_isLastIteration{TC},SeqLoops_isLastIteration{DS}
T.20.__STATIC:
	.tc	H.20.__STATIC{TC},E.18.__STATIC{RW}
T.14.NO_SYMBOL:
	.tc	H.14.NO_SYMBOL{TC},H.16.NO_SYMBOL{RO}
T.28.main:
	.tc	H.28.main{TC},main{DS}  
T.32.isInDefinition:
	.tc	H.32.isInDefinition{TC},isInDefinition{DS}


	.csect	SeqLoops_isLastIteration{DS}, 3
	.llong	.SeqLoops_isLastIteration# "\0\0\0\0\0\0\0\0"
	.llong	TOC{TC0}                # "\0\0\0\0\0\0\003\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
# End	csect	SeqLoops_isLastIteration{DS}


	.csect	main{DS}, 3             
	.llong	.main                   # "\0\0\0\0\0\0\001 "
	.llong	TOC{TC0}                # "\0\0\0\0\0\0\003\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
# End	csect	main{DS}


	.csect	isInDefinition{DS}, 3   
	.llong	.isInDefinition         # "\0\0\0\0\0\0\001\300"
	.llong	TOC{TC0}                # "\0\0\0\0\0\0\003\0"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x00000000              # "\0\0\0\0"
# End	csect	isInDefinition{DS}


	.csect	E.18.__STATIC{RW}, 3    
	.long	0x56616c75              # "Valu"
	.long	0x65206f66              # "e of"
	.long	0x20693a20              # " i: "
	.long	0x2564200a              # "%d \n"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x20202020              # "    "
	.long	0x25782c20              # "%x, "
	.long	0x25782c20              # "%x, "
	.long	0x25782c20              # "%x, "
	.long	0x25782c20              # "%x, "
	.long	0x0a000000              # "\n\0\0\0"
	.long	0x4f6e2074              # "On t"
	.long	0x68697320              # "his "
	.long	0x73797374              # "syst"
	.long	0x656d2f63              # "em/c"
	.long	0x6f6d7069              # "ompi"
	.long	0x6c65722c              # "ler,"
	.long	0x2073697a              # " siz"
	.long	0x656f6628              # "eof("
	.long	0x696e7429              # "int)"
	.long	0x203d2025              # " = %"
	.long	0x6c75200a              # "lu \n"
	.long	0x00000000              # "\0\0\0\0"
	.long	0x4f6e2074              # "On t"
	.long	0x68697320              # "his "
	.long	0x73797374              # "syst"
	.long	0x656d2f63              # "em/c"
	.long	0x6f6d7069              # "ompi"
	.long	0x6c65722c              # "ler,"
	.long	0x2073697a              # " siz"
	.long	0x656f6628              # "eof("
	.long	0x63686172              # "char"
	.long	0x2a29203d              # "*) ="
	.long	0x20256c75              # " %lu"
	.long	0x200a0000              # " \n\0\0"
	.long	0x46756e63              # "Func"
	.long	0x74696f6e              # "tion"
	.long	0x2063616c              # " cal"
	.long	0x6c203a20              # "l : "
	.long	0x5365714c              # "SeqL"
	.long	0x6f6f7073              # "oops"
	.long	0x5f69734c              # "_isL"
	.long	0x61737449              # "astI"
	.long	0x74657261              # "tera"
	.long	0x74696f6e              # "tion"
	.long	0x28202570              # "( %p"
	.long	0x2c202570              # ", %p"
	.long	0x20290a00              # " )\n\0"
	.long	0x56616c75              # "Valu"
	.long	0x65732069              # "es i"
	.long	0x6e206172              # "n ar"
	.long	0x72617920              # "ray "
	.long	0x696e742a              # "int*"
	.long	0x206c6173              # " las"
	.long	0x74446566              # "tDef"
	.long	0x203d2026              # " = &"
	.long	0x65787072              # "expr"
	.long	0x65737369              # "essi"
	.long	0x6f6e4172              # "onAr"
	.long	0x7261795b              # "ray["
	.long	0x5f69202d              # "_i -"
	.long	0x20345d3a              # " 4]:"
# End	csect	E.18.__STATIC{RW}
	.long	0x0a000000              # "\n\0\0\0"
	.long	0x00000000              # "\0\0\0\0"


	.csect	H.16.NO_SYMBOL{RO}, 3   
	.long	0xffffffff              # "\377\377\377\377"
	.long	0xffffffff              # "\377\377\377\377"
	.long	0xffffffff              # "\377\377\377\377"
	.long	0xffffffff              # "\377\377\377\377"
	.long	0xffffffff              # "\377\377\377\377"
	.long	0xffffffff              # "\377\377\377\377"
	.long	0xffffffff              # "\377\377\377\377"
	.long	0xffffffff              # "\377\377\377\377"
	.long	0x11112222              # "\021\021"""
	.long	0x33334444              # "33DD"
	.long	0xbbbbdddd              # "\273\273\335\335"
	.long	0xeeeeffff              # "\356\356\377\377"
# End	csect	H.16.NO_SYMBOL{RO}



# .bss section


# dwarf sections

# end dwarf sections
