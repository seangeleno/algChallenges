pushq %rbp  #to be used for preserving frame info, so is %rpb
movq %rsp, %rbp  #push base register %rbp ontop stack by pushq %rbp, then copy stack register %rsp for space
subq $4, %rsp #reserve 4 bytes oon stack
movl $5, -4(%rbp)  # use base register instead of stack pointer to access data

addq $4, %rsp #release the stack
popq %rbp #restoer old %rbp
retq  #function ends
