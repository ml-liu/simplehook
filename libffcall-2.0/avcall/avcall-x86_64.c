/**
  Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2017 Bruno Haible <bruno@clisp.org>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
/*----------------------------------------------------------------------
  Foreign function interface for an x86_64 (a.k.a. amd64) with gcc
  using the Unix ABI ('gcc -mabi=sysv').

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  x86_64 Argument Passing Conventions on Unix:

  Documentation is at https://github.com/hjl-tools/x86-psABI/wiki/X86-psABI

  * Arguments:
    - Integer or pointer arguments:
      The first 6 integer or pointer arguments get passed in integer
      registers (%rdi, %rsi, %rdx, %rcx, %r8, %r9).
      The remaining ones (as an entire word each) on the stack.
    - Floating-point arguments:
      Up to 8 float/double arguments are passed in SSE registers
      (%xmm0..%xmm7).
      The remaining ones (as an entire word each) on the stack.
    - Structure arguments:
      Structure args are passed as true structures embedded in the
      argument stack.
  * Return value:
    Integers are returned in %rax, %rdx. Float/double values are returned
    in %xmm0, %xmm1. To return a structure larger than 16 bytes, the called
    function copies the value to space pointed to by its first argument,
    and all other arguments are shifted down by one.
  * Call-used registers: rax,rdx,rcx,rsi,rdi,r8-r11

  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

/*register __avword iarg1 __asm__("rdi");*/
/*register __avword iarg2 __asm__("rsi");*/
/*register __avword iarg3 __asm__("rdx");*/
/*register __avword iarg4 __asm__("rcx");*/
/*register __avword iarg5 __asm__("r8");*/
/*register __avword iarg6 __asm__("r9");*/

register double farg1 __asm__("xmm0");
register double farg2 __asm__("xmm1");
register double farg3 __asm__("xmm2");
register double farg4 __asm__("xmm3");
register double farg5 __asm__("xmm4");
register double farg6 __asm__("xmm5");
register double farg7 __asm__("xmm6");
register double farg8 __asm__("xmm7");

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("rsp");	/* C names for registers */
/*register __avword	iretreg	 __asm__("rax");*/
  register __avword	iret2reg __asm__("rdx");
  register double	dret	__asm__("xmm0");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = l->aptr - l->args;
  int farglen = l->faptr - l->fargs;
  __avword iret, iret2;

  {
    int i;
    for (i = 0; i < arglen; i++)	/* push function args onto stack */
      argframe[i] = l->args[i];
  }

  /* Call function.
     It's OK to pass 8 values in SSE registers even if the called function takes
     less than 8 float/double arguments. Similarly for the integer arguments. */
  if (l->rtype == __AVfloat) {
    *(float*)l->raddr =
      (*(float(*)())l->func)(l->iargs[0],
                             l->iargs[1],
                             l->iargs[2],
                             l->iargs[3],
                             l->iargs[4],
                             l->iargs[5],
                             farglen > 0 ? l->fargs[0] : 0.0,
                             farglen > 1 ? l->fargs[1] : 0.0,
                             farglen > 2 ? l->fargs[2] : 0.0,
                             farglen > 3 ? l->fargs[3] : 0.0,
                             farglen > 4 ? l->fargs[4] : 0.0,
                             farglen > 5 ? l->fargs[5] : 0.0,
                             farglen > 6 ? l->fargs[6] : 0.0,
                             farglen > 7 ? l->fargs[7] : 0.0);
  } else
  if (l->rtype == __AVdouble) {
    *(double*)l->raddr =
      (*(double(*)())l->func)(l->iargs[0],
                              l->iargs[1],
                              l->iargs[2],
                              l->iargs[3],
                              l->iargs[4],
                              l->iargs[5],
                              farglen > 0 ? l->fargs[0] : 0.0,
                              farglen > 1 ? l->fargs[1] : 0.0,
                              farglen > 2 ? l->fargs[2] : 0.0,
                              farglen > 3 ? l->fargs[3] : 0.0,
                              farglen > 4 ? l->fargs[4] : 0.0,
                              farglen > 5 ? l->fargs[5] : 0.0,
                              farglen > 6 ? l->fargs[6] : 0.0,
                              farglen > 7 ? l->fargs[7] : 0.0);
  } else {
    iret = (*l->func)(l->iargs[0],
                      l->iargs[1],
                      l->iargs[2],
                      l->iargs[3],
                      l->iargs[4],
                      l->iargs[5],
                      farglen > 0 ? l->fargs[0] : 0.0,
                      farglen > 1 ? l->fargs[1] : 0.0,
                      farglen > 2 ? l->fargs[2] : 0.0,
                      farglen > 3 ? l->fargs[3] : 0.0,
                      farglen > 4 ? l->fargs[4] : 0.0,
                      farglen > 5 ? l->fargs[5] : 0.0,
                      farglen > 6 ? l->fargs[6] : 0.0,
                      farglen > 7 ? l->fargs[7] : 0.0);
    iret2 = iret2reg;

    /* save return value */
    if (l->rtype == __AVvoid) {
    } else
    if (l->rtype == __AVword) {
      RETURN(__avword, iret);
    } else
    if (l->rtype == __AVchar) {
      RETURN(char, iret);
    } else
    if (l->rtype == __AVschar) {
      RETURN(signed char, iret);
    } else
    if (l->rtype == __AVuchar) {
      RETURN(unsigned char, iret);
    } else
    if (l->rtype == __AVshort) {
      RETURN(short, iret);
    } else
    if (l->rtype == __AVushort) {
      RETURN(unsigned short, iret);
    } else
    if (l->rtype == __AVint) {
      RETURN(int, iret);
    } else
    if (l->rtype == __AVuint) {
      RETURN(unsigned int, iret);
    } else
    if (l->rtype == __AVlong) {
      RETURN(long, iret);
    } else
    if (l->rtype == __AVulong) {
      RETURN(unsigned long, iret);
    } else
    if (l->rtype == __AVlonglong) {
      RETURN(long long, iret);
    } else
    if (l->rtype == __AVulonglong) {
      RETURN(unsigned long long, iret);
    } else
  /* see above
    if (l->rtype == __AVfloat) {
    } else
    if (l->rtype == __AVdouble) {
    } else
  */
    if (l->rtype == __AVvoidp) {
      RETURN(void*, iret);
    } else
    if (l->rtype == __AVstruct) {
      if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
        /* Return structs of size <= 16 in registers. */
        if (l->rsize > 0 && l->rsize <= 16) {
          void* raddr = l->raddr;
          #if 0 /* Unoptimized */
          if (l->rsize == 1) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
          } else
          if (l->rsize == 2) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
          } else
          if (l->rsize == 3) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
          } else
          if (l->rsize == 4) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
          } else
          if (l->rsize == 5) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
          } else
          if (l->rsize == 6) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>40);
          } else
          if (l->rsize == 7) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>40);
            ((unsigned char *)raddr)[6] = (unsigned char)(iret>>48);
          } else
          if (l->rsize >= 8 && l->rsize <= 16) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>40);
            ((unsigned char *)raddr)[6] = (unsigned char)(iret>>48);
            ((unsigned char *)raddr)[7] = (unsigned char)(iret>>56);
            if (l->rsize == 8) {
            } else
            if (l->rsize == 9) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
            } else
            if (l->rsize == 10) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
            } else
            if (l->rsize == 11) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
            } else
            if (l->rsize == 12) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
            } else
            if (l->rsize == 13) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>32);
            } else
            if (l->rsize == 14) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>40);
            } else
            if (l->rsize == 15) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>40);
              ((unsigned char *)raddr)[8+6] = (unsigned char)(iret2>>48);
            } else
            if (l->rsize == 16) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>40);
              ((unsigned char *)raddr)[8+6] = (unsigned char)(iret2>>48);
              ((unsigned char *)raddr)[8+7] = (unsigned char)(iret2>>56);
            }
          }
          #else /* Optimized: fewer conditional jumps, fewer memory accesses */
          uintptr_t count = l->rsize; /* > 0, ≤ 2*sizeof(__avword) */
          __avword* wordaddr = (__avword*)((uintptr_t)raddr & ~(uintptr_t)(sizeof(__avword)-1));
          uintptr_t start_offset = (uintptr_t)raddr & (uintptr_t)(sizeof(__avword)-1); /* ≥ 0, < sizeof(__avword) */
          uintptr_t end_offset = start_offset + count; /* > 0, < 3*sizeof(__avword) */
          if (count <= sizeof(__avword)) {
            /* Use iret. */
            if (end_offset <= sizeof(__avword)) {
              /* 0 < end_offset ≤ sizeof(__avword) */
              __avword mask0 = ((__avword)2 << (end_offset*8-1)) - ((__avword)1 << (start_offset*8));
              wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
            } else {
              /* sizeof(__avword) < end_offset < 2*sizeof(__avword), start_offset > 0 */
              __avword mask0 = - ((__avword)1 << (start_offset*8));
              __avword mask1 = ((__avword)2 << (end_offset*8-sizeof(__avword)*8-1)) - 1;
              wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
              wordaddr[1] ^= (wordaddr[1] ^ (iret >> (sizeof(__avword)*8-start_offset*8))) & mask1;
            }
          } else {
            /* Use iret, iret2. */
            __avword mask0 = - ((__avword)1 << (start_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
            if (end_offset <= 2*sizeof(__avword)) {
              /* sizeof(__avword) < end_offset ≤ 2*sizeof(__avword) */
              __avword mask1 = ((__avword)2 << (end_offset*8-sizeof(__avword)*8-1)) - 1;
              wordaddr[1] ^= (wordaddr[1] ^ ((iret >> (sizeof(__avword)*4-start_offset*4) >> (sizeof(__avword)*4-start_offset*4)) | (iret2 << (start_offset*8)))) & mask1;
            } else {
              /* 2*sizeof(__avword) < end_offset < 3*sizeof(__avword), start_offset > 0 */
              __avword mask2 = ((__avword)2 << (end_offset*8-2*sizeof(__avword)*8-1)) - 1;
              wordaddr[1] = (iret >> (sizeof(__avword)*8-start_offset*8)) | (iret2 << (start_offset*8));
              wordaddr[2] ^= (wordaddr[2] ^ (iret2 >> (sizeof(__avword)*8-start_offset*8))) & mask2;
            }
          }
          #endif
        }
      }
    }
  }
  return 0;
}
