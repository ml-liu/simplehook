/**
  Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
  Copyright 2000 Adam Fedor <fedor@gnu.org>
  Copyright 2004 Paul Guyot <pguyot@kallisys.net>

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

  Foreign function interface for a 64-bit PowerPC with gcc

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  PowerPC64 Argument Passing Conventions:

  All arguments, except the first 8 words, are passed on the stack with
  word alignment. The first 13 doubles and floats are also passed in
  floating-point-registers.
  To return a structure, the called function copies the value to space
  pointed to by its first argument, and all other arguments are shifted
  down by one.

  The AIX argument passing conventions are used:
  - the first 13 doubles and floats are passed in FP registers,
    and when they do, there is still room allocated for them in the
    argument sequence (integer regs or stack).
  - Structures are passed in the argument sequence. But structures
    containing floats or doubles are passed in FP registers?!

  Compile this routine with gcc -O (or -O2 -fno-omit-frame-pointer or -g -O)
  to get the right register variables. For other compilers use the
  pre-compiled assembler version.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

register double farg1	__asm__("fr1");
register double farg2	__asm__("fr2");
register double farg3	__asm__("fr3");
register double farg4	__asm__("fr4");
register double farg5	__asm__("fr5");
register double farg6	__asm__("fr6");
register double farg7	__asm__("fr7");
register double farg8	__asm__("fr8");
register double farg9	__asm__("fr9");
register double farg10	__asm__("fr10");
register double farg11	__asm__("fr11");
register double farg12	__asm__("fr12");
register double farg13	__asm__("fr13");

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("r1");  /* C names for registers */
/*register __avword	iret	__asm__("r3"); */
  register __avword	iret2	__asm__("r4");
  register float	fret	__asm__("fr1");
  register double	dret	__asm__("fr1");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = l->aptr - l->args;
  __avword iret;
  int i;

  for (i = 8; i < arglen; i++) /* push function args onto stack */
    argframe[i-8] = l->args[i];

  /* pass first 13 floating-point args in registers */
  arglen = l->faptr - l->fargs;
  if (arglen > 0) {
    if (arglen > 1) {
      if (arglen > 2) {
        if (arglen > 3) {
          if (arglen > 4) {
            if (arglen > 5) {
              if (arglen > 6) {
                if (arglen > 7) {
                  if (arglen > 8) {
                    if (arglen > 9) {
                      if (arglen > 10) {
                        if (arglen > 11) {
                          if (arglen > 12) {
                            farg13 = l->fargs[12];
                          }
                          farg12 = l->fargs[11];
                        }
                        farg11 = l->fargs[10];
                      }
                      farg10 = l->fargs[9];
                    }
                    farg9 = l->fargs[8];
                  }
                  farg8 = l->fargs[7];
                }
                farg7 = l->fargs[6];
              }
              farg6 = l->fargs[5];
            }
            farg5 = l->fargs[4];
          }
          farg4 = l->fargs[3];
        }
        farg3 = l->fargs[2];
      }
      farg2 = l->fargs[1];
    }
    farg1 = l->fargs[0];
  }
				/* call function, pass 8 args in registers */
  iret = (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
		    l->args[4], l->args[5], l->args[6], l->args[7]);

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
#ifdef __powerpc64_elfv2__
    if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
      /* In the ELFv2 ABI, gcc returns structs of size <= 16 in registers. */
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
#endif
  }
  return 0;
}
