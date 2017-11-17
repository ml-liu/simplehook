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
  using the Windows ABI ('gcc -mabi=ms').

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  x86_64 Argument Passing Conventions on Windows:

  Documentation is at https://docs.microsoft.com/en-us/cpp/build/calling-convention
  A summary is at https://en.wikipedia.org/wiki/X86_calling_conventions#x86-64_calling_conventions

  * Arguments:
    - Up to 4 words are passed in registers:
             integer/pointer  float/double
        1.        %rcx           %xmm0
        2.        %rdx           %xmm1
        3.        %r8            %xmm2
        4.        %r9            %xmm3
    - Integer or pointer arguments:
      The first 4 integer or pointer arguments get passed in integer
      registers (%rcx, %rdx, %r8, %r9).
      The remaining ones (as an entire word each) on the stack.
    - Floating-point arguments:
      The float/double arguments among the first 4 words are passed in
      SSE registers (%xmm0..%xmm3), as shown above.
      The remaining ones (as an entire word each) on the stack.
    - Structure arguments:
      Structure args of size 1, 2, 4, 8 bytes are passed like integers.
      Structure args of other sizes are passed as pointers to caller-allocated
      temporary locations.
  * Return value:
    Types of size 1, 2, 4, 8 bytes are returned in %rax or (for float/double
    values) in %xmm0.
    To return a structure of another size, the called function copies the
    value to space pointed to by its first argument, and all other arguments
    are shifted down by one. The function also returns the pointer.
  * Call-used registers: rax,rdx,rcx,r8-r11

  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

/*register __avword iarg1 __asm__("rcx");*/
/*register __avword iarg2 __asm__("rdx");*/
/*register __avword iarg3 __asm__("r8");*/
/*register __avword iarg4 __asm__("r9");*/

register float farg1 __asm__("xmm0");
register float farg2 __asm__("xmm1");
register float farg3 __asm__("xmm2");
register float farg4 __asm__("xmm3");

register double darg1 __asm__("xmm0");
register double darg2 __asm__("xmm1");
register double darg3 __asm__("xmm2");
register double darg4 __asm__("xmm3");

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("rsp");	/* C names for registers */
  register __avword	iret	__asm__("rax");
  register float	fret	__asm__("xmm0");
  register double	dret	__asm__("xmm0");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = l->aptr - l->args;
  int i;

  for (i = 4; i < arglen; i++)		/* push function args onto stack */
    argframe[i-4] = l->args[i];

  /* put up to 4 float args into registers */
  if (l->farg_mask) {
    if (l->farg_mask & (1<<0))
      farg1 = l->fargs[0];
    if (l->farg_mask & (1<<1))
      farg2 = l->fargs[1];
    if (l->farg_mask & (1<<2))
      farg3 = l->fargs[2];
    if (l->farg_mask & (1<<3))
      farg4 = l->fargs[3];
  }

  /* put up to 4 double args into registers */
  if (l->darg_mask) {
    if (l->darg_mask & (1<<0))
      darg1 = l->dargs[0];
    if (l->darg_mask & (1<<1))
      darg2 = l->dargs[1];
    if (l->darg_mask & (1<<2))
      darg3 = l->dargs[2];
    if (l->darg_mask & (1<<3))
      darg4 = l->dargs[3];
  }

  /* Call function. */
  if (l->rtype == __AVfloat) {
    *(float*)l->raddr = (*(float(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3]);
  } else
  if (l->rtype == __AVdouble) {
    *(double*)l->raddr = (*(double(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3]);
  } else {
    __avword iret;
    iret = (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3]);

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
        /* Return structs of size 1, 2, 4, 8 in registers. */
        void* raddr = l->raddr;
        #if 0 /* Unoptimized */
        if (l->rsize == 1) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret);
        } else
        if (l->rsize == 2) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
        } else
        if (l->rsize == 4) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
        } else
        if (l->rsize == 8) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
          ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
          ((unsigned char *)raddr)[5] = (unsigned char)(iret>>40);
          ((unsigned char *)raddr)[6] = (unsigned char)(iret>>48);
          ((unsigned char *)raddr)[7] = (unsigned char)(iret>>56);
        }
        #else /* Optimized: fewer conditional jumps, fewer memory accesses */
        uintptr_t count = l->rsize;
        if (count == 1 || count == 2 || count == 4 || count == 8) {
          /* 0 < count ≤ sizeof(__avword) */
          __avword* wordaddr = (__avword*)((uintptr_t)raddr & ~(uintptr_t)(sizeof(__avword)-1));
          uintptr_t start_offset = (uintptr_t)raddr & (uintptr_t)(sizeof(__avword)-1); /* ≥ 0, < sizeof(__avword) */
          uintptr_t end_offset = start_offset + count; /* > 0, < 2*sizeof(__avword) */
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
        }
        #endif
      }
    }
  }
  return 0;
}
