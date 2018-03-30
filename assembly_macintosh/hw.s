

.section __DATA,__data
str:
	.asciz "Hello world!\n"

.section __TEXT,__text
.globl _main
_main:
	movl $0x2000004, %eax        #preparing system call 4
	movl $1, %edi                #STDOUT file descriptor is 1
	movq str@GOTPCREL(%rip),%rsi #the value to print
	
	
	syscall
	



	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	movl $5, -8(%rsp)

	addq $8, %rsp
	popq %rbp

	movl $0, %ebx
	movl $0x2000001, %eax        # exit 0

	syscall
	
