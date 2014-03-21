xdisasm
=======

xdisasm is a simple binary file disassembler based on libopcodes and bfd from binutils. It uses the libxdisasm library which currently supports x86, x86_64, arm, ppc and mips. The idea is to try and mimic the output given by the ndisasm program which unfortunately only supports x86/x86_64.

Build Instructions:
-------------------
First Build binutils with the appropriate flags. You can get the source from http://ftp.gnu.org/gnu/binutils/. By default binutils will install the shared libraries in /usr/local/lib. If this is not in your library path you might run into some issues. Run the following commands in the directory where you extracted the binutils archive:
```
./configure --enable-targets=al --enable-shared
make
sudo make install
```
Then you can build xdisasm. From the top level directory, run the following command:
```
make
```

Examples:
---------
```
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
```
```
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
```
```
./xdisasm -m x86 -b64 testfiles/helloworld_x86_64.bin

00000000  488D3518000000       lea    rsi,[rip+0x18]        # 0x1f
00000007  B801000000           mov    eax,0x1
0000000C  BF01000000           mov    edi,0x1
00000011  BA0C000000           mov    edx,0xc
00000016  0F05                 syscall 
00000018  B83C000000           mov    eax,0x3c
0000001D  0F05                 syscall 
0000001F  48                   rex.W
00000020  65                   gs
00000021  6C                   ins    BYTE PTR es:[rdi],dx
00000022  6C                   ins    BYTE PTR es:[rdi],dx
00000023  6F                   outs   dx,DWORD PTR ds:[rsi]
00000024  20576F               and    BYTE PTR [rdi+0x6f],dl
00000027  726C                 jb     0x95
00000029  64                   fs
0000002A  0A                   .byte 0xa
```
```
./xdisasm -m powerpc testfiles/helloworld_ppc_le.bin

00000000  48000020             b       0x20
00000004  38600001             li      r3,1
00000008  38A0000C             li      r5,12
0000000C  7C8802A6             mflr    r4
00000010  38000004             li      r0,4
00000014  44000002             sc      
00000018  38000001             li      r0,1
0000001C  44000002             sc      
00000020  4BFFFFE5             bl      0x4
00000024  6C6C6548             xoris   r12,r3,25928
00000028  6F57206F             xoris   r23,r26,8303
0000002C  0A646C72             tdi     19,r4,27762
```
