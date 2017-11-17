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
  !!! THIS ROUTINE MUST BE COMPILED gcc -O -fno-omit-frame-pointer !!!

  Foreign function interface for a Linux arm64 (a.k.a. aarch64) with gcc.

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  ARM64 Argument Passing Conventions are documented in
  http://infocenter.arm.com/help/topic/com.arm.doc.ihi0055b/IHI0055B_aapcs64.pdf.

  Up to 8 words are passed in integer registers (x0, ..., x7).
  Up to 8 float/double arguments are passed in floating point / SIMD
  registers (v0/q0/d0/s0, ..., v7/q7/d7/s7).
  Arguments passed on the stack have word alignment.
  Structure args larger than 16 bytes are passed as pointers to caller-made
  local copies. (§ 5.4.2 rule B.3)
  Structure args <= 16 bytes are passed as up to two words in registers
  (§ 5.4.2 rule C.10) or otherwise on the stack (§ 5.4.2 rule C.13).

  Integers are returned in x0, x1.
  Float/double values are returned in d0/s0, d1/s1.
  Structures <= 16 bytes are returned in registers. To return a structure
  larger than 16 bytes, the called function copies the value to space
  pointed to by x8.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

register __avword* sret __asm__("x8");  /* structure return pointer */

register __avword iarg1 __asm__("x0");
register __avword iarg2 __asm__("x1");
register __avword iarg3 __asm__("x2");
register __avword iarg4 __asm__("x3");
register __avword iarg5 __asm__("x4");
register __avword iarg6 __asm__("x5");
register __avword iarg7 __asm__("x6");
register __avword iarg8 __asm__("x7");

register float farg1 __asm__("s0");
register float farg2 __asm__("s1");
register float farg3 __asm__("s2");
register float farg4 __asm__("s3");
register float farg5 __asm__("s4");
register float farg6 __asm__("s5");
register float farg7 __asm__("s6");
register float farg8 __asm__("s7");

register double darg1 __asm__("d0");
register double darg2 __asm__("d1");
register double darg3 __asm__("d2");
register double darg4 __asm__("d3");
register double darg5 __asm__("d4");
register double darg6 __asm__("d5");
register double darg7 __asm__("d6");
register double darg8 __asm__("d7");

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("sp");	/* C names for registers */
  register __avword	iretreg	 __asm__("x0");
  register __avword	iret2reg __asm__("x1");
  register double	dret	__asm__("d0");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = l->aptr - l->args;
  unsigned int ianum = l->ianum;
  unsigned int fanum = l->fanum;
  __avword iret, iret2;

  {
    int i;
    for (i = 0; i < arglen; i++)	/* push function args onto stack */
      argframe[i] = l->args[i];
  }

  /* Put up to 8 integer args into registers. */
  if (ianum >= 1) {
    iarg1 = l->iargs[0];
    if (ianum >= 2) {
      iarg2 = l->iargs[1];
      if (ianum >= 3) {
        iarg3 = l->iargs[2];
        if (ianum >= 4) {
          iarg4 = l->iargs[3];
          if (ianum >= 5) {
            iarg5 = l->iargs[4];
            if (ianum >= 6) {
              iarg6 = l->iargs[5];
              if (ianum >= 7) {
                iarg7 = l->iargs[6];
                if (ianum >= 8) {
                  iarg8 = l->iargs[7];
                }
              }
            }
          }
        }
      }
    }
  }

  /* Put upto 8 floating-point args into registers. */
  if (fanum >= 1) {
    if (l->darg_mask & (1 << 0)) darg1 = l->dargs[0];
    else if (l->farg_mask & (1 << 0)) farg1 = l->fargs[0];
    if (fanum >= 2) {
      if (l->darg_mask & (1 << 1)) darg2 = l->dargs[1];
      else if (l->farg_mask & (1 << 1)) farg2 = l->fargs[1];
      if (fanum >= 3) {
        if (l->darg_mask & (1 << 2)) darg3 = l->dargs[2];
        else if (l->farg_mask & (1 << 2)) farg3 = l->fargs[2];
        if (fanum >= 4) {
          if (l->darg_mask & (1 << 3)) darg4 = l->dargs[3];
          else if (l->farg_mask & (1 << 3)) farg4 = l->fargs[3];
          if (fanum >= 5) {
            if (l->darg_mask & (1 << 4)) darg5 = l->dargs[4];
            else if (l->farg_mask & (1 << 4)) farg5 = l->fargs[4];
            if (fanum >= 6) {
              if (l->darg_mask & (1 << 5)) darg6 = l->dargs[5];
              else if (l->farg_mask & (1 << 5)) farg6 = l->fargs[5];
              if (fanum >= 7) {
                if (l->darg_mask & (1 << 6)) darg7 = l->dargs[6];
                else if (l->farg_mask & (1 << 6)) farg7 = l->fargs[6];
                if (fanum >= 8) {
                  if (l->darg_mask & (1 << 7)) darg8 = l->dargs[7];
                  else if (l->farg_mask & (1 << 7)) farg8 = l->fargs[7];
                }
              }
            }
          }
        }
      }
    }
  }
        
  /* Call function. */
  if (l->rtype == __AVfloat) {
    *(float*)l->raddr = (*(float(*)())l->func)();
  } else
  if (l->rtype == __AVdouble) {
    *(double*)l->raddr = (*(double(*)())l->func)();
  } else {
    iret = (*l->func)();
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
    if (l->rtype == __AVlong || l->rtype == __AVlonglong) {
      RETURN(long, iret);
    } else
    if (l->rtype == __AVulong || l->rtype == __AVulonglong) {
      RETURN(unsigned long, iret);
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
