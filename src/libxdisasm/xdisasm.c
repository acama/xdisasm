/*
    xdisasm.c -- disassembling library  
    Copyright (C) 2014  Amat I. Cama                                     
                                                                         
    This file is part of xdisasm.                                        
                                                                         
    Xdisasm is free software: you can redistribute it and/or modify      
    it under the terms of the GNU General Public License as published by 
    the Free Software Foundation, either version 3 of the License, or    
    (at your option) any later version.                                  
                                                                         
    Xdisasm is distributed in the hope that it will be useful,           
    but WITHOUT ANY WARRANTY; without even the implied warranty of       
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        
    GNU General Public License for more details.                         
                                                                         
    You should have received a copy of the GNU General Public License    
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "package.h"
#include <stdlib.h>
#include <stdarg.h>
#include <bfd.h>     
#include <dis-asm.h>
#include <malloc.h>
#include <string.h>
#include "xdisasm.h"

#define MAX_INS_STRSIZE 2048 // Output would be truncated if libopcodes gave
                             // an instruction longer than 2048. But this
                             // is not very likely

char curr_insn_str[MAX_INS_STRSIZE] = {0};
char * currptr = curr_insn_str;

void print_as_hex(char * buf, unsigned int siz, int endian){
    int i = 0;
    char * tmpbuf = NULL;
    char * tmptr = NULL;

    tmpbuf = malloc(siz);
  
    if(!tmpbuf){
        perror("malloc");
        exit(-1);
    }
    
    memset(tmpbuf, 0, siz);
    tmptr = tmpbuf;

    if(endian){
        for(; i < siz; i++){
            tmptr += sprintf(tmptr, "%02X", ((unsigned char *)buf)[i]);
        }
    }else{
         for(i = siz - 1; i >= 0; i--){
            tmptr += sprintf(tmptr, "%02X", ((unsigned char *)buf)[i]);
        }
    }

    if(siz >= 15) printf("%-40s", tmpbuf);
    else printf("%-20s", tmpbuf);
    free(tmpbuf);
}

void override_print_address(bfd_vma addr, struct disassemble_info *info){
    sprintf(currptr, "0x%x", (unsigned int) addr);
}

int my_fprintf(void* stream, const char * format, ...){
    va_list arg;

    va_start(arg, format);
    vsnprintf(currptr, MAX_INS_STRSIZE - (currptr - curr_insn_str),format, arg);
    currptr = curr_insn_str + strlen(curr_insn_str);
    return 0;
}

/* Disassemble the bytes pointed to by buf */
int disassemble(unsigned int vma, char * rawbuf, size_t buflen, int arch, int bits, int endian){
    bfd_byte* buf = NULL;
    disassemble_info* dis = NULL;
    unsigned int count = 0;
    int endian_print;
    size_t pos = 0, length = 0, max_pos = 0;
    disassembler_ftype disas; 

    dis = (struct disassemble_info*) calloc(1, sizeof(disassemble_info));
    init_disassemble_info (dis, stdout, my_fprintf);
    buf = (bfd_byte*) rawbuf;

    dis->buffer_vma = vma;
    dis->buffer = buf;
    dis->buffer_length = buflen;
    dis->print_address_func = override_print_address;

    length = dis->buffer_length;
    max_pos = dis->buffer_vma + length;
    pos = vma;

    switch(arch){
        case ARCH_arm:
            if(endian) disas = print_insn_big_arm;
            else disas = print_insn_little_arm; 
            break;

        case ARCH_mips: // TODO: add mips64 support
            if(endian) disas = print_insn_big_mips;
            else disas = print_insn_little_mips; 
            break;

        case ARCH_powerpc: // TODO: add powerpc64 support
            if(endian) disas = print_insn_big_powerpc;
            else disas = print_insn_little_powerpc;
            dis->arch = bfd_arch_powerpc;       // ppc cares about this
            disassemble_init_for_target(dis);   // otherwise segfault
            break;

        case ARCH_x86:
            if (bits == 16) dis->mach = bfd_mach_i386_i8086;
            else if (bits == 64) dis->mach = !(bfd_mach_i386_i8086 | bfd_mach_i386_i386);
            else dis->mach = bfd_mach_i386_i386;
            disas = print_insn_i386_intel;
            break;

        default:
            fprintf(stderr, "libxdisasm: Invalid architecture\n");
            return -1;
    } 
   
    // because of how printing function works, need to do this
    if(arch == ARCH_x86) endian_print = 1;
    else endian_print = endian;

    while(pos < max_pos)
      {
        printf("%08X  ", (unsigned int) pos);
        unsigned int size = disas((bfd_vma) pos, dis);
        print_as_hex(rawbuf + (pos - vma), size, endian_print);
        printf(" %s", curr_insn_str);
        memset(curr_insn_str, 0, sizeof(curr_insn_str));
        currptr = curr_insn_str;
        pos += size;
        count++;
        fprintf(stdout, "\n");
      }
    free(dis);
    return 0;
}
