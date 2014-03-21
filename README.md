xdisasm
=======

Simple binary file disassembler based on libopcodes and bfd from binutils. Currently supports x86, arm, ppc and mips. It attempts to mimic the ndisasm program.

Examples:
---------
./xdisasm -m arm testfiles/helloworld_arm_le.bin

00000000  E28F1014             add	r1, pc, #20
00000004  E3A00001             mov	r0, #1
00000008  E3A0200C             mov	r2, #12
0000000C  E3A07004             mov	r7, #4
00000010  EF000000             svc	0x00000000
00000014  E3A07001             mov	r7, #1
00000018  EF000000             svc	0x00000000
0000001C  6C6C6548             cfstr64vs	mvdx6, [ip], #-288	; 0xfffffee0
00000020  6F57206F             svcvs	0x0057206f
00000024  0A646C72             beq	0x191b1f4

./xdisasm -m arm testfiles/helloworld_arm_be.bin -lb
00000000  E28F1014             add	r1, pc, #20
00000004  E3A00001             mov	r0, #1
00000008  E3A0200C             mov	r2, #12
0000000C  E3A07004             mov	r7, #4
00000010  EF000000             svc	0x00000000
00000014  E3A07001             mov	r7, #1
00000018  EF000000             svc	0x00000000
0000001C  48656C6C             stmdami	r5!, {r2, r3, r5, r6, sl, fp, sp, lr}^
00000020  6F20576F             svcvs	0x0020576f
00000024  726C640A             rsbvc	r6, ip, #167772160	; 0xa000000
