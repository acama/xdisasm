/*  xdisasm.h -- xdisasm header file
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

#ifndef XDISASM_H
#define XDISASM_H

#define ARCH_arm 1
#define ARCH_mips 2
#define ARCH_powerpc 3
#define ARCH_x86 4

int disassemble(unsigned int vma, char * rawbuf, size_t buflen, int arch, int bits, int endian);

#endif
