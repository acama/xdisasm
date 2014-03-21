    .text
    .global __start

__start:
    nop
    nop
    nop
    nop
    nop
    nop
begin:
    j hello
write:
    li $a1, 1
    move $a1, $ra
    li $a2, 12
    li $v0, 4004
    syscall
    li $v0, 4001
    syscall

hello:
    jal write
    .ascii "Hello World\n"
