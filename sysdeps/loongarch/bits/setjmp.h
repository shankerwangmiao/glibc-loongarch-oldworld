/* Define the machine-dependent type `jmp_buf'.  RISC-V version.
   Copyright (C) 2011-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _LOONGARCH_BITS_SETJMP_H
#define _LOONGARCH_BITS_SETJMP_H

typedef struct __jmp_buf_internal_tag
  {
    /* Program counter.  */
    long int __pc;
    /* TLS */
    long int __tp;
    /* Stack pointer.  */
    long int __sp;
    /* Global pointer*/
    long int __x;
    /* Frame pointer. */
    long int __fp;
    /* Callee-saved registers.  */
    long int __regs[9];

    /* Callee-saved floating point registers.  */
   double __fpregs[8];
  } __jmp_buf[1];

#endif /* _LOONGARCH_BITS_SETJMP_H */
