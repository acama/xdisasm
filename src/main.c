/*  main.c -- Main file
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


#include "libxdisasm/package.h"
#include <bfd.h>
#include <dis-asm.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "libxdisasm/xdisasm.h"


void print_version(){
    printf("%s %s\n", PACKAGE, PACKAGE_VERSION);
    exit(0);
}

void print_usage(){
    printf("Usage: xdisasm -m arch [-b bits] [-e bytes] [-v] [-h] inputfile\n");
    printf("\t -b (16 | 32 | 64) sets the processor mode\n");
    printf("\t -m (arm | mips | powerpc | x86) sets the architecture\n");
    printf("\t -v displays the version number\n");
    printf("\t -l big endian\n");
    printf("\t -e skips <bytes> of header\n");
    printf("\t -a rellocate at given address\n");
    printf("\t -h prints this menu\n");
    exit(0);
}

int main(int argc, char **argv){
    FILE * fp = NULL;
    int opt, endian = 0;
    int fb = 0, fv = 0, fh = 0, bits = 0, arch = 0, fl = 0;
    char * bval = NULL;
    char * mval = NULL;
    char * eval = NULL;
    char * aval = NULL;
    char * infile = NULL;
    char * data = NULL;
    size_t datalen = 0;
    size_t hdrlen = 0;
    unsigned int vma = 0;

    while((opt = getopt(argc, argv, "b:m:e:a:vhl")) != -1){
        switch(opt){
            case 'b':
                fb = 1;
                bval = optarg;
                break;
            case 'm':
                mval = optarg;
                break;
            case 'e':
                eval = optarg;
                break;
            case 'v':
                fv = 1;
                break;
            case 'h':
                fh = 1;
                break;
            case 'l':
                fl = 1;
                break;
            case 'a':
                aval = optarg;
                break;
            default:
            case '?':
                print_usage();
        }
    }

    if(fv){
        print_version();
    }

    if(fh){
        print_usage();
    }

    if (argv[optind] == NULL) {
        print_usage();
    }

    infile = argv[optind];

    if(aval){
        vma = strtol(aval, NULL, 0);
        if(vma == LONG_MAX || vma == LONG_MIN || vma == 0){
            perror("strtol");
            exit(-1);
        }
    }

    if(fb){
        bits = strtol(bval, NULL, 10);
        if(bits != 16 && bits != 32 && bits != 64){
            print_usage(); 
        }
    }

    if(fl){
        endian = 1;
    }

    if(mval){
        if(!strcmp(mval, "arm")){
            arch = ARCH_arm;
        }
        else if(!strcmp(mval, "powerpc")){
            arch = ARCH_powerpc;
        } 
        else if(!strcmp(mval, "x86")){
            arch = ARCH_x86;
        } 
        else if(!strcmp(mval, "mips")){
            arch = ARCH_mips;
        }
        else{
            print_usage();
        }
    }else{
        print_usage();
    }

    if(eval){ 
        hdrlen = strtol(eval, NULL, 10);
        if(hdrlen == LONG_MAX || hdrlen == LONG_MIN || hdrlen == 0){
            perror("strtol");
            exit(-1);
        }
    }

    fp = fopen (infile, "rb");

    if (fp){
        fseek (fp, hdrlen, SEEK_END);
        datalen = ftell (fp);       // TODO: maybe check if vma + datalen will overflow address range
        if(datalen < 0){
            perror("ftell");
            exit(-1);
        }
        if(datalen == 0){
            printf("%s: file %s is empty", argv[0], infile);
        }
        fseek (fp, hdrlen, SEEK_SET);
        data = malloc (datalen);
        if (data)
        {
            fread (data, 1, datalen, fp);
        }else{
            perror("malloc");
            exit(-1);
        }
        fclose (fp);
    }else{
        perror("fopen");
        exit(-1);
    }

    disassemble(vma, data, datalen, arch, bits, endian);
    free(data); 
    return 0;
}
