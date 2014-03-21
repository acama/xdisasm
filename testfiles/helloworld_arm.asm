    .text
    .global _start

_start:
    adr r1, hello
    mov r0, #1
    mov r2, #12
    mov r7, #4
    svc 0x0
    mov r7, #1
    svc 0x0
hello:
    .ascii "Hello World\n"
