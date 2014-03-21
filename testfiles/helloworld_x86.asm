USE32
    section .text
    global _start

_start:
    jmp hello
write:
    pop ecx
    mov ebx, 1
    mov edx, 12
    mov eax, 4
    int 80h
    mov eax, 1
    int 80h

hello:
    call write
    db "Hello World",0xa
