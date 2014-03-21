    .text
    .global _start

_start:
    b hello

write:
    li r3, 1
    li r5, 12
    mflr r4
    li r0, 4
    sc
    li r0, 1
    sc
hello:
    bl write
    .ascii "Hello World\n"
