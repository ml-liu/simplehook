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
  !!! THIS ROUTINE MUST BE COMPILED gcc -O !!!

  Foreign function interface for a HP Precision Architecture 1.0 with gcc

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  HPPA Argument Passing Conventions:

  All arguments, except the first 4 words, are passed on the stack
  - growing down! - with word alignment. Doubles take two words and force
  double alignment. Small structures args are passed as true structures
  embedded in the argument stack. They force double alignment and - if they
  don't fit entirely in the 4 register words - are passed in memory.
  The first 2 words are passed like this:
    %r26 = first integer arg, %r25 = second integer arg, or
    %r26 = high word of double arg, %r25 = low word of double arg.
  Similarly for the next 2 words, passed in %r24 and %r23.
  Note that other calling conventions would be in effect if we would call
  an explicitly named function!

  To return a structure of more than 8 bytes, the called function copies
  the return value to the address supplied in register "%r28". Smaller
  structures are returned in the registers %r28 (first 4 bytes) and %r29
  (next 4 bytes, if present).

  It is forbidden to modify the stack pointer.

  Compile this routine with gcc -O2 -fomit-frame-pointer to get the right
  register variables.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

/* This declaration tells gcc not to modify %r28. */
register __avword*	sret	__asm__("%r28");  /* structure return pointer */

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("%r30");  /* C names for registers */
  register float	fret	__asm__("%fr4");
  register double	dret	__asm__("%fr4");
/*register __avword	iret1	__asm__("%r28"); */
  register __avword	iret2	__asm__("%r29");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword space[__AV_ALIST_WORDS];	/* space for callee's stack frame */
  __avword* argframe = sp - 8;		/* stack offset for argument list */
  int arglen = l->args_end - l->aptr;
  __avword iret;

  {
    int i;
    for (i = -arglen; i < -4; i++)	/* push function args onto stack */
      argframe[i] = l->args_end[i];
  }

  if (l->rtype == __AVstruct)		/* push struct return address */
    sret = l->raddr;

				/* call function, pass 4 args in registers */
  iret = (*l->func)(l->args_end[-1], l->args_end[-2],
		    l->args_end[-3], l->args_end[-4]);

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
  if (l->rtype == __AVlonglong || l->rtype == __AVulonglong) {
    void* raddr = l->raddr;
    ((__avword*)raddr)[0] = iret;
    ((__avword*)raddr)[1] = iret2;
  } else
  if (l->rtype == __AVfloat) {
    RETURN(float, fret);
  } else
  if (l->rtype == __AVdouble) {
    RETURN(double, dret);
  } else
  if (l->rtype == __AVvoidp) {
    RETURN(void*, iret);
  } else
  if (l->rtype == __AVstruct) {
    if (l->flags & __AV_SMALL_STRUCT_RETURN) {
      /* cc, c89 and gcc >= 2.7 return structs of size <= 8 in registers. */
      if (l->rsize > 0 && l->rsize <= 8) {
        /* This is really weird code, unlike all other big-endian platforms. */
        void* raddr = l->raddr;
        #if 0 /* Unoptimized */
        if (l->rsize == 1) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret);
        } else
        if (l->rsize == 2) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret);
        } else
        if (l->rsize == 3) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret);
        } else
        if (l->rsize == 4) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>24);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret);
        } else
        if (l->rsize == 5) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret2>>24);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret2>>16);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret2>>8);
          ((unsigned char *)raddr)[4] = (unsigned char)(iret2);
        } else
        if (l->rsize == 6) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret2>>24);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret2>>16);
          ((unsigned char *)raddr)[4] = (unsigned char)(iret2>>8);
          ((unsigned char *)raddr)[5] = (unsigned char)(iret2);
        } else
        if (l->rsize == 7) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret2>>24);
          ((unsigned char *)raddr)[4] = (unsigned char)(iret2>>16);
          ((unsigned char *)raddr)[5] = (unsigned char)(iret2>>8);
          ((unsigned char *)raddr)[6] = (unsigned char)(iret2);
        } else
        if (l->rsize == 8) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>24);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret);
          ((unsigned char *)raddr)[4] = (unsigned char)(iret2>>24);
          ((unsigned char *)raddr)[5] = (unsigned char)(iret2>>16);
          ((unsigned char *)raddr)[6] = (unsigned char)(iret2>>8);
          ((unsigned char *)raddr)[7] = (unsigned char)(iret2);
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
            __avword mask0 = ((__avword)2 << (sizeof(__avword)*8-start_offset*8-1)) - ((__avword)1 << (sizeof(__avword)*8-end_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret << (sizeof(__avword)*8-end_offset*8))) & mask0;
          } else {
            /* sizeof(__avword) < end_offset < 2*sizeof(__avword), start_offset > 0 */
            __avword mask0 = ((__avword)2 << (sizeof(__avword)*8-start_offset*8-1)) - 1;
            __avword mask1 = - ((__avword)1 << (2*sizeof(__avword)*8-end_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret >> (end_offset*8-sizeof(__avword)*8))) & mask0;
            wordaddr[1] ^= (wordaddr[1] ^ (iret << (2*sizeof(__avword)*8-end_offset*8))) & mask1;
          }
        } else {
          /* Use iret, iret2. */
          __avword mask0 = ((__avword)2 << (sizeof(__avword)*8-start_offset*8-1)) - 1;
          if (end_offset <= 2*sizeof(__avword)) {
            /* sizeof(__avword) < end_offset ≤ 2*sizeof(__avword) */
            __avword mask1 = - ((__avword)1 << (2*sizeof(__avword)*8-end_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ ((iret << (2*sizeof(__avword)*8-end_offset*8)) | (iret2 >> (end_offset*4-sizeof(__avword)*4) >> (end_offset*4-sizeof(__avword)*4)))) & mask0;
            wordaddr[1] ^= (wordaddr[1] ^ (iret2 << (2*sizeof(__avword)*8-end_offset*8))) & mask1;
          } else {
            /* 2*sizeof(__avword) < end_offset < 3*sizeof(__avword), start_offset > 0 */
            __avword mask2 = - ((__avword)1 << (3*sizeof(__avword)*8-end_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret >> (end_offset*8-2*sizeof(__avword)*8))) & mask0;
            wordaddr[1] = (iret << (3*sizeof(__avword)*8-end_offset*8)) | (iret2 >> (end_offset*8-2*sizeof(__avword)*8));
            wordaddr[2] ^= (wordaddr[2] ^ (iret2 << (3*sizeof(__avword)*8-end_offset*8))) & mask2;
          }
        }
        #endif
      }
    }
  }
  return 0;
}
