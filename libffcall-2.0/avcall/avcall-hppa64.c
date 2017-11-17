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

  Foreign function interface for a HP-PA 2.0w in 64-bit mode with cc
  (NB: gcc-7.1.0/gcc/config/pa/pa64-regs.h is quite incorrect. Ignore it.)

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  hppa64 Argument Passing Conventions:

  Up to 8 words are passed in registers:
            integer/pointer    float      double
     1.          %r26          %fr4R       %fr4
     2.          %r25          %fr5R       %fr5
     3.          %r24          %fr6R       %fr6
     4.          %r23          %fr7R       %fr7
     5.          %r22          %fr8R       %fr8
     6.          %r21          %fr9R       %fr9
     7.          %r20          %fr10R      %fr10
     8.          %r19          %fr11R      %fr11
  The remaining arguments are passed on the stack - growing up, unlike
  in 32-bit mode! -, and %r29 is the base address of this stack area.
  Room is preallocated for 8 words, i.e. from address %r29-64 to %r29-1.
  Among these stack arguments:
    - integer/pointer occupies 1 word (right-adjusted, since big-endian),
    - float occupies 1 word and is stored in the upper 4 bytes of the word,
    - double occupies 1 word.

  Structs of any size are passed in the argument sequence, e.g. in integer
  registers (first byte being at bits 63..56). Note that a {long,long}
  struct has 2*(8 bytes) alignment.

  The return value is returned in register %r28.
  Float return values are also returned in %fr4R.
  Double return values are also returned in %fr4.
  (How silly! Who designed this ABI?!)

  To return a structure of more than 16 bytes, the called function copies
  the return value to the address supplied in register %r28. The function
  also returns the pointer.
  Smaller structures are returned in the registers %r28 (first 8 bytes)
  and %r29 (next 8 bytes, if present).

  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

/* This declaration tells gcc not to modify %r28. */
register __avword*	sret	__asm__("%r28");  /* structure return pointer */

register __avword arg1 __asm__("r26");
register __avword arg2 __asm__("r25");
register __avword arg3 __asm__("r24");
register __avword arg4 __asm__("r23");
register __avword arg5 __asm__("r22");
register __avword arg6 __asm__("r21");
register __avword arg7 __asm__("r20");
register __avword arg8 __asm__("r19");

/*register float farg1 __asm__("fr4R");*/
/*register float farg2 __asm__("fr5R");*/
/*register float farg3 __asm__("fr6R");*/
/*register float farg4 __asm__("fr7R");*/
/*register float farg5 __asm__("fr8R");*/
/*register float farg6 __asm__("fr9R");*/
/*register float farg7 __asm__("fr10R");*/
/*register float farg8 __asm__("fr11R");*/

register double darg1 __asm__("fr4");
register double darg2 __asm__("fr5");
register double darg3 __asm__("fr6");
register double darg4 __asm__("fr7");
register double darg5 __asm__("fr8");
register double darg6 __asm__("fr9");
register double darg7 __asm__("fr10");
register double darg8 __asm__("fr11");

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("%r30");  /* C names for registers */
/*register __avword	iret1	__asm__("%r28"); */
  register __avword	iret2	__asm__("%r29");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  __avword* memargptr;
  int arglen = l->aptr - l->args;
  __avword iret;

  {
    int i;
    for (i = 8; i < arglen; i++)	/* push function args onto stack */
      argframe[i] = l->args[i];
  }

  if (l->rtype == __AVstruct)		/* push struct return address */
    sret = l->raddr;

  /* Put args in registers */
  if (arglen >= 1) {
    if (l->darg_mask & (1 << 0))
      darg1 = ((double*)&l->args[1])[-1];
    else if (l->farg_mask & (1 << 0))
      __asm__ __volatile__ ("fldw %0,%%fr4R" : : "m" (((float*)&l->args[1])[-1])); /* farg1 = ((float*)&l->args[1])[-1]; */
    else
      arg1 = l->args[0];
    if (arglen >= 2) {
      if (l->darg_mask & (1 << 1))
        darg2 = ((double*)&l->args[2])[-1];
      else if (l->farg_mask & (1 << 1))
        __asm__ __volatile__ ("fldw %0,%%fr5R" : : "m" (((float*)&l->args[2])[-1])); /* farg2 = ((float*)&l->args[2])[-1];; */
      else
        arg2 = l->args[1];
      if (arglen >= 3) {
        if (l->darg_mask & (1 << 2))
          darg3 = ((double*)&l->args[3])[-1];
        else if (l->farg_mask & (1 << 2))
          __asm__ __volatile__ ("fldw %0,%%fr6R" : : "m" (((float*)&l->args[3])[-1])); /* farg3 = ((float*)&l->args[3])[-1];; */
        else
          arg3 = l->args[2];
        if (arglen >= 4) {
          if (l->darg_mask & (1 << 3))
            darg4 = ((double*)&l->args[4])[-1];
          else if (l->farg_mask & (1 << 3))
            __asm__ __volatile__ ("fldw %0,%%fr7R" : : "m" (((float*)&l->args[4])[-1])); /* farg4 = ((float*)&l->args[4])[-1];; */
          else
            arg4 = l->args[3];
          if (arglen >= 5) {
            if (l->darg_mask & (1 << 4))
              darg5 = ((double*)&l->args[5])[-1];
            else if (l->farg_mask & (1 << 4))
              __asm__ __volatile__ ("fldw %0,%%fr8R" : : "m" (((float*)&l->args[5])[-1])); /* farg5 = ((float*)&l->args[5])[-1];; */
            else
              arg5 = l->args[4];
            if (arglen >= 6) {
              if (l->darg_mask & (1 << 5))
                darg6 = ((double*)&l->args[6])[-1];
              else if (l->farg_mask & (1 << 5))
                __asm__ __volatile__ ("fldw %0,%%fr9R" : : "m" (((float*)&l->args[6])[-1])); /* farg6 = ((float*)&l->args[6])[-1];; */
              else
                arg6 = l->args[5];
              if (arglen >= 7) {
                if (l->darg_mask & (1 << 6))
                  darg7 = ((double*)&l->args[7])[-1];
                else if (l->farg_mask & (1 << 6))
                  __asm__ __volatile__ ("fldw %0,%%fr10R" : : "m" (((float*)&l->args[7])[-1])); /* farg7 = ((float*)&l->args[7])[-1];; */
                else
                  arg7 = l->args[6];
                if (arglen >= 8) {
                  if (l->darg_mask & (1 << 7))
                    darg8 = ((double*)&l->args[8])[-1];
                  else if (l->farg_mask & (1 << 7))
                    __asm__ __volatile__ ("fldw %0,%%fr11R" : : "m" (((float*)&l->args[8])[-1])); /* farg8 = ((float*)&l->args[8])[-1];; */
                  else
                    arg8 = l->args[7];
                  if (arglen > 8) {
                    memargptr = &argframe[8];
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (l->rtype == __AVfloat) {
    __asm__ __volatile__ ("copy %0,%%r29" : : "r" (memargptr));
    /* GCC generates an 'ldo -16(%r30),%r29' instruction as part of this
       function call. We eliminate it through post-processing. */
    *(float*)l->raddr = (*(float(*)())l->func)();
  } else
  if (l->rtype == __AVdouble) {
    __asm__ __volatile__ ("copy %0,%%r29" : : "r" (memargptr));
    /* GCC generates an 'ldo -16(%r30),%r29' instruction as part of this
       function call. We eliminate it through post-processing. */
    *(double*)l->raddr = (*(double(*)())l->func)();
  } else {
    __asm__ __volatile__ ("copy %0,%%r29" : : "r" (memargptr));
    /* GCC generates an 'ldo -16(%r30),%r29' instruction as part of this
       function call. We eliminate it through post-processing. */
    iret = (*l->func)();

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
        /* cc returns structs of size <= 16 in registers. */
        if (l->rsize > 0 && l->rsize <= 16) {
          #if 0
          void* raddr = l->raddr;
          #else
          #define raddr l->raddr
          #endif
          #if 1 /* Unoptimized */
          if (l->rsize == 1) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret>>56);
          } else
          if (l->rsize == 2) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret>>56);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>48);
          } else
          if (l->rsize == 3) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret>>56);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>48);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>40);
          } else
          if (l->rsize == 4) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret>>56);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>48);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>40);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>32);
          } else
          if (l->rsize == 5) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret>>56);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>48);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>40);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>24);
          } else
          if (l->rsize == 6) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret>>56);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>48);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>40);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>16);
          } else
          if (l->rsize == 7) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret>>56);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>48);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>40);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[6] = (unsigned char)(iret>>8);
          } else
          if (l->rsize >= 8 && l->rsize <= 16) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret>>56);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>48);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>40);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[6] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[7] = (unsigned char)(iret);
            if (l->rsize == 8) {
            } else
            if (l->rsize == 9) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2>>56);
            } else
            if (l->rsize == 10) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2>>56);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>48);
            } else
            if (l->rsize == 11) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2>>56);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>48);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>40);
            } else
            if (l->rsize == 12) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2>>56);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>48);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>40);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>32);
            } else
            if (l->rsize == 13) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2>>56);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>48);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>40);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>24);
            } else
            if (l->rsize == 14) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2>>56);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>48);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>40);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>16);
            } else
            if (l->rsize == 15) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2>>56);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>48);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>40);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+6] = (unsigned char)(iret2>>8);
            } else
            if (l->rsize == 16) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2>>56);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>48);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>40);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+6] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+7] = (unsigned char)(iret2);
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
              __avword mask0 = ((__avword)2 << (sizeof(__avword)*8-start_offset*8-1)) - ((__avword)1 << (sizeof(__avword)*8-end_offset*8));
              wordaddr[0] ^= (wordaddr[0] ^ (iret >> (start_offset*8))) & mask0;
            } else {
              /* sizeof(__avword) < end_offset < 2*sizeof(__avword), start_offset > 0 */
              __avword mask0 = ((__avword)2 << (sizeof(__avword)*8-start_offset*8-1)) - 1;
              __avword mask1 = - ((__avword)1 << (2*sizeof(__avword)*8-end_offset*8));
              wordaddr[0] ^= (wordaddr[0] ^ (iret >> (start_offset*8))) & mask0;
              wordaddr[1] ^= (wordaddr[1] ^ (iret << (sizeof(__avword)*8-start_offset*8))) & mask1;
            }
          } else {
            /* Use iret, iret2. */
            __avword mask0 = ((__avword)2 << (sizeof(__avword)*8-start_offset*8-1)) - 1;
            wordaddr[0] ^= (wordaddr[0] ^ (iret >> (start_offset*8))) & mask0;
            if (end_offset <= 2*sizeof(__avword)) {
              /* sizeof(__avword) < end_offset ≤ 2*sizeof(__avword) */
              __avword mask1 = - ((__avword)1 << (2*sizeof(__avword)*8-end_offset*8));
              wordaddr[1] ^= (wordaddr[1] ^ ((iret << (sizeof(__avword)*4-start_offset*4) << (sizeof(__avword)*4-start_offset*4)) | (iret2 >> (start_offset*8)))) & mask1;
            } else {
              /* 2*sizeof(__avword) < end_offset < 3*sizeof(__avword), start_offset > 0 */
              __avword mask2 = - ((__avword)1 << (3*sizeof(__avword)*8-end_offset*8));
              wordaddr[1] = (iret << (sizeof(__avword)*8-start_offset*8)) | (iret2 >> (start_offset*8));
              wordaddr[2] ^= (wordaddr[2] ^ (iret2 << (sizeof(__avword)*8-start_offset*8))) & mask2;
            }
          }
          #endif
        }
      }
    }
  }
  return 0;
}
