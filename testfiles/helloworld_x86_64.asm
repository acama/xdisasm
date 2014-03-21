USE64
DEFAULT REL

    section .text
    global _start

hello:
    db "Hello World",0xa

_start:
    lea rsi, [hello]
    mov rax, 1
    mov rdi, 1
    mov rdx, 12
    syscall
    mov rax, 60
    syscall
