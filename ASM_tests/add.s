########################################################
# int add(int a, int b){ return a+b; }
#    +---------+
#    | OLD RBP | <-- RBP
#    +---------+
#    |   RET   | -8(%rbp)
#    +---------+
#    |    A    | -16(%rbp)
#    +---------+
#    |    B    | -24(%rbp)
#    +---------+
#######################################################
.globl add
add:
	pushq %rbp
	movq %rsp, %rbp
	movq $0, %rax
	addl %esi, %eax
	addl %edi, %eax
	popq %rbp
	ret
