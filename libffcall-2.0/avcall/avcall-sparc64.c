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

  Foreign function interface for a Sparc v9 in 64-bit mode with gcc.

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  Sparc 64-bit Argument Passing Conventions

  The argument registers are laid out as an array of 16 elements
  and arguments are added sequentially.  The first 6 int args and up to the
  first 16 fp args (depending on size) are passed in regs.

  Slot    Stack   Integral   Float   Float in structure   Double   Long Double
  ----    -----   --------   -----   ------------------   ------   -----------
   15   [SP+248]              %f31       %f30,%f31         %d30
   14   [SP+240]              %f29       %f28,%f29         %d28       %q28
   13   [SP+232]              %f27       %f26,%f27         %d26
   12   [SP+224]              %f25       %f24,%f25         %d24       %q24
   11   [SP+216]              %f23       %f22,%f23         %d22
   10   [SP+208]              %f21       %f20,%f21         %d20       %q20
    9   [SP+200]              %f19       %f18,%f19         %d18
    8   [SP+192]              %f17       %f16,%f17         %d16       %q16
    7   [SP+184]              %f15       %f14,%f15         %d14
    6   [SP+176]              %f13       %f12,%f13         %d12       %q12
    5   [SP+168]     %o5      %f11       %f10,%f11         %d10
    4   [SP+160]     %o4       %f9        %f8,%f9           %d8        %q8
    3   [SP+152]     %o3       %f7        %f6,%f7           %d6
    2   [SP+144]     %o2       %f5        %f4,%f5           %d4        %q4
    1   [SP+136]     %o1       %f3        %f2,%f3           %d2
    0   [SP+128]     %o0       %f1        %f0,%f1           %d0        %q0

  Here SP = %sp if -mno-stack-bias or %sp+stack_bias otherwise.

  Integral arguments are always passed as 64 bit quantities appropriately
  extended.

  Passing of floating point values is handled as follows.
  If a prototype is in scope:
    If the value is in a named argument (i.e. not a stdarg function or a
    value not part of the ‘...’) then the value is passed in the appropriate
    fp reg.
    If the value is part of the ‘...’ and is passed in one of the first 6
    slots then the value is passed in the appropriate int reg.
    If the value is part of the ‘...’ and is not passed in one of the first 6
    slots then the value is passed in memory.
  If a prototype is not in scope:
    If the value is one of the first 6 arguments the value is passed in the
    appropriate integer reg and the appropriate fp reg.
    If the value is not one of the first 6 arguments the value is passed in
    the appropriate fp reg and in memory.

  Remaining arguments are pushed onto the stack starting at a fixed offset
  Space is left on the stack frame for temporary storage of the register
  arguments as well.

  Integers shorter than ‘long’ are always promoted to word-length
  (zero-extended or sign-extended, according to their type). Structures
  <= 16 bytes are passed embedded in the argument sequence; bigger structures
  are passed by reference.

  Integers and pointers are returned in o0, floats in f0, doubles in
  f0/f1.  If the function returns a structure a pointer to space
  allocated by the caller is pushed onto the stack immediately
  before the function arguments. Structures <= 32 bytes are returned in
  registers (integer/float/double registers, as appropriate).

  Long doubles are 16-byte aligned, but we don't deal with this here, so
  we assume 8-byte alignment for everything.

  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))
#define OFFSETOF(struct,member) ((int)&(((struct*)0)->member))

register __avword o0	__asm__("%o0");
register __avword o1	__asm__("%o1");
register __avword o2	__asm__("%o2");
register __avword o3	__asm__("%o3");
register __avword o4	__asm__("%o4");
register __avword o5	__asm__("%o5");

int
avcall_call(av_alist* list)
{
  register __avword* sp	__asm__("%sp");  /* C names for registers */
  register float fret	__asm__("%f0");  /* %f0 */
  register double dret	__asm__("%f0");  /* %f0,%f1 */

  __av_alist* l = &AV_LIST_INNER(list);

  __avword trampoline[6];		/* room for a trampoline */
  int arglen = l->aptr - l->args;
  __avword iret;

  if (l->darg_mask) {
    /* push leading float/double args */
      __avword* a = l->args;
    if (l->darg_mask & (1<<0))
      __asm__("ldd [%0+%1],%%f0" : : "p" (a), "i" (0 * sizeof (__avword)));
    if (l->darg_mask & (1<<1))
      __asm__("ldd [%0+%1],%%f2" : : "p" (a), "i" (1 * sizeof (__avword)));
    if (l->darg_mask & (1<<2))
      __asm__("ldd [%0+%1],%%f4" : : "p" (a), "i" (2 * sizeof (__avword)));
    if (l->darg_mask & (1<<3))
      __asm__("ldd [%0+%1],%%f6" : : "p" (a), "i" (3 * sizeof (__avword)));
    if (l->darg_mask & (1<<4))
      __asm__("ldd [%0+%1],%%f8" : : "p" (a), "i" (4 * sizeof (__avword)));
    if (l->darg_mask & (1<<5))
      __asm__("ldd [%0+%1],%%f10" : : "p" (a), "i" (5 * sizeof (__avword)));
    if (l->darg_mask & (1<<6))
      __asm__("ldd [%0+%1],%%f12" : : "p" (a), "i" (6 * sizeof (__avword)));
    if (l->darg_mask & (1<<7))
      __asm__("ldd [%0+%1],%%f14" : : "p" (a), "i" (7 * sizeof (__avword)));
    if (l->darg_mask & (1<<8))
      __asm__("ldd [%0+%1],%%f16" : : "p" (a), "i" (8 * sizeof (__avword)));
    if (l->darg_mask & (1<<9))
      __asm__("ldd [%0+%1],%%f18" : : "p" (a), "i" (9 * sizeof (__avword)));
    if (l->darg_mask & (1<<10))
      __asm__("ldd [%0+%1],%%f20" : : "p" (a), "i" (10 * sizeof (__avword)));
    if (l->darg_mask & (1<<11))
      __asm__("ldd [%0+%1],%%f22" : : "p" (a), "i" (11 * sizeof (__avword)));
    if (l->darg_mask & (1<<12))
      __asm__("ldd [%0+%1],%%f24" : : "p" (a), "i" (12 * sizeof (__avword)));
    if (l->darg_mask & (1<<13))
      __asm__("ldd [%0+%1],%%f26" : : "p" (a), "i" (13 * sizeof (__avword)));
    if (l->darg_mask & (1<<14))
      __asm__("ldd [%0+%1],%%f28" : : "p" (a), "i" (14 * sizeof (__avword)));
    if (l->darg_mask & (1<<15))
      __asm__("ldd [%0+%1],%%f30" : : "p" (a), "i" (15 * sizeof (__avword)));
  }

  if (arglen > 6) {
    /* alloca space is separated from the extra outgoing args area by
     * the area for compiler temps (addressable with postive offsets from sp)
     * but they shouldn't be needed for this function, so, effectively,
     * space returned by alloca is safe to use as the area for extra args.
     */
    void *extra_args_area = __builtin_alloca(sizeof(__avword) * (arglen - 6));
    __avword *argframe = (__avword *)extra_args_area - 6;
#if 0
    /* "by construction" */
    assert(argframe == (void *)((unsigned long)(sp + 16)+2047));
#endif

    int i;
    for (i = 6; i < arglen; i++)	/* push excess function args */
      argframe[i] = l->args[i];
  }

					/* call function with 1st 6 args */
  iret = ({ register __avword iretreg __asm__ ("%o0");
            iretreg = (*l->func)(l->args[0], l->args[1], l->args[2],
                                 l->args[3], l->args[4], l->args[5]);
            asm __volatile__("nop");	/* struct returning functions skip this instruction */
            iretreg;
          });

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
    if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
      /* Return structs of size <= 32 in registers. */
      #define iret2 o1
      #define iret3 o2
      #define iret4 o3
      if (l->rsize > 0 && l->rsize <= 32) {
        void* raddr = l->raddr;
        #if 0 /* Unoptimized */
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
        if (l->rsize >= 8 && l->rsize <= 32) {
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
          if (l->rsize >= 16 && l->rsize <= 32) {
            ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2>>56);
            ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>48);
            ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>40);
            ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>32);
            ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>24);
            ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>16);
            ((unsigned char *)raddr)[8+6] = (unsigned char)(iret2>>8);
            ((unsigned char *)raddr)[8+7] = (unsigned char)(iret2);
            if (l->rsize == 16) {
            } else
            if (l->rsize == 17) {
              ((unsigned char *)raddr)[16+0] = (unsigned char)(iret3>>56);
            } else
            if (l->rsize == 18) {
              ((unsigned char *)raddr)[16+0] = (unsigned char)(iret3>>56);
              ((unsigned char *)raddr)[16+1] = (unsigned char)(iret3>>48);
            } else
            if (l->rsize == 19) {
              ((unsigned char *)raddr)[16+0] = (unsigned char)(iret3>>56);
              ((unsigned char *)raddr)[16+1] = (unsigned char)(iret3>>48);
              ((unsigned char *)raddr)[16+2] = (unsigned char)(iret3>>40);
            } else
            if (l->rsize == 20) {
              ((unsigned char *)raddr)[16+0] = (unsigned char)(iret3>>56);
              ((unsigned char *)raddr)[16+1] = (unsigned char)(iret3>>48);
              ((unsigned char *)raddr)[16+2] = (unsigned char)(iret3>>40);
              ((unsigned char *)raddr)[16+3] = (unsigned char)(iret3>>32);
            } else
            if (l->rsize == 21) {
              ((unsigned char *)raddr)[16+0] = (unsigned char)(iret3>>56);
              ((unsigned char *)raddr)[16+1] = (unsigned char)(iret3>>48);
              ((unsigned char *)raddr)[16+2] = (unsigned char)(iret3>>40);
              ((unsigned char *)raddr)[16+3] = (unsigned char)(iret3>>32);
              ((unsigned char *)raddr)[16+4] = (unsigned char)(iret3>>24);
            } else
            if (l->rsize == 22) {
              ((unsigned char *)raddr)[16+0] = (unsigned char)(iret3>>56);
              ((unsigned char *)raddr)[16+1] = (unsigned char)(iret3>>48);
              ((unsigned char *)raddr)[16+2] = (unsigned char)(iret3>>40);
              ((unsigned char *)raddr)[16+3] = (unsigned char)(iret3>>32);
              ((unsigned char *)raddr)[16+4] = (unsigned char)(iret3>>24);
              ((unsigned char *)raddr)[16+5] = (unsigned char)(iret3>>16);
            } else
            if (l->rsize == 23) {
              ((unsigned char *)raddr)[16+0] = (unsigned char)(iret3>>56);
              ((unsigned char *)raddr)[16+1] = (unsigned char)(iret3>>48);
              ((unsigned char *)raddr)[16+2] = (unsigned char)(iret3>>40);
              ((unsigned char *)raddr)[16+3] = (unsigned char)(iret3>>32);
              ((unsigned char *)raddr)[16+4] = (unsigned char)(iret3>>24);
              ((unsigned char *)raddr)[16+5] = (unsigned char)(iret3>>16);
              ((unsigned char *)raddr)[16+6] = (unsigned char)(iret3>>8);
            } else
            if (l->rsize >= 24 && l->rsize <= 32) {
              ((unsigned char *)raddr)[16+0] = (unsigned char)(iret3>>56);
              ((unsigned char *)raddr)[16+1] = (unsigned char)(iret3>>48);
              ((unsigned char *)raddr)[16+2] = (unsigned char)(iret3>>40);
              ((unsigned char *)raddr)[16+3] = (unsigned char)(iret3>>32);
              ((unsigned char *)raddr)[16+4] = (unsigned char)(iret3>>24);
              ((unsigned char *)raddr)[16+5] = (unsigned char)(iret3>>16);
              ((unsigned char *)raddr)[16+6] = (unsigned char)(iret3>>8);
              ((unsigned char *)raddr)[16+7] = (unsigned char)(iret3);
              if (l->rsize == 24) {
              } else
              if (l->rsize == 25) {
                ((unsigned char *)raddr)[24+0] = (unsigned char)(iret4>>56);
              } else
              if (l->rsize == 26) {
                ((unsigned char *)raddr)[24+0] = (unsigned char)(iret4>>56);
                ((unsigned char *)raddr)[24+1] = (unsigned char)(iret4>>48);
              } else
              if (l->rsize == 27) {
                ((unsigned char *)raddr)[24+0] = (unsigned char)(iret4>>56);
                ((unsigned char *)raddr)[24+1] = (unsigned char)(iret4>>48);
                ((unsigned char *)raddr)[24+2] = (unsigned char)(iret4>>40);
              } else
              if (l->rsize == 28) {
                ((unsigned char *)raddr)[24+0] = (unsigned char)(iret4>>56);
                ((unsigned char *)raddr)[24+1] = (unsigned char)(iret4>>48);
                ((unsigned char *)raddr)[24+2] = (unsigned char)(iret4>>40);
                ((unsigned char *)raddr)[24+3] = (unsigned char)(iret4>>32);
              } else
              if (l->rsize == 29) {
                ((unsigned char *)raddr)[24+0] = (unsigned char)(iret4>>56);
                ((unsigned char *)raddr)[24+1] = (unsigned char)(iret4>>48);
                ((unsigned char *)raddr)[24+2] = (unsigned char)(iret4>>40);
                ((unsigned char *)raddr)[24+3] = (unsigned char)(iret4>>32);
                ((unsigned char *)raddr)[24+4] = (unsigned char)(iret4>>24);
              } else
              if (l->rsize == 30) {
                ((unsigned char *)raddr)[24+0] = (unsigned char)(iret4>>56);
                ((unsigned char *)raddr)[24+1] = (unsigned char)(iret4>>48);
                ((unsigned char *)raddr)[24+2] = (unsigned char)(iret4>>40);
                ((unsigned char *)raddr)[24+3] = (unsigned char)(iret4>>32);
                ((unsigned char *)raddr)[24+4] = (unsigned char)(iret4>>24);
                ((unsigned char *)raddr)[24+5] = (unsigned char)(iret4>>16);
              } else
              if (l->rsize == 31) {
                ((unsigned char *)raddr)[24+0] = (unsigned char)(iret4>>56);
                ((unsigned char *)raddr)[24+1] = (unsigned char)(iret4>>48);
                ((unsigned char *)raddr)[24+2] = (unsigned char)(iret4>>40);
                ((unsigned char *)raddr)[24+3] = (unsigned char)(iret4>>32);
                ((unsigned char *)raddr)[24+4] = (unsigned char)(iret4>>24);
                ((unsigned char *)raddr)[24+5] = (unsigned char)(iret4>>16);
                ((unsigned char *)raddr)[24+6] = (unsigned char)(iret4>>8);
              } else
              if (l->rsize == 32) {
                ((unsigned char *)raddr)[24+0] = (unsigned char)(iret4>>56);
                ((unsigned char *)raddr)[24+1] = (unsigned char)(iret4>>48);
                ((unsigned char *)raddr)[24+2] = (unsigned char)(iret4>>40);
                ((unsigned char *)raddr)[24+3] = (unsigned char)(iret4>>32);
                ((unsigned char *)raddr)[24+4] = (unsigned char)(iret4>>24);
                ((unsigned char *)raddr)[24+5] = (unsigned char)(iret4>>16);
                ((unsigned char *)raddr)[24+6] = (unsigned char)(iret4>>8);
                ((unsigned char *)raddr)[24+7] = (unsigned char)(iret4);
              }
            }
          }
        }
        #else /* Optimized: fewer conditional jumps, fewer memory accesses */
        uintptr_t count = l->rsize; /* > 0, ≤ 4*sizeof(__avword) */
        __avword* wordaddr = (__avword*)((uintptr_t)raddr & ~(uintptr_t)(sizeof(__avword)-1));
        uintptr_t start_offset = (uintptr_t)raddr & (uintptr_t)(sizeof(__avword)-1); /* ≥ 0, < sizeof(__avword) */
        uintptr_t end_offset = start_offset + count; /* > 0, < 5*sizeof(__avword) */
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
        } else if (count <= 2*sizeof(__avword)) {
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
        } else if (count <= 3*sizeof(__avword)) {
          /* Use iret, iret2, iret3. */
          __avword mask0 = ((__avword)2 << (sizeof(__avword)*8-start_offset*8-1)) - 1;
          wordaddr[0] ^= (wordaddr[0] ^ (iret >> (start_offset*8))) & mask0;
          if (end_offset <= 3*sizeof(__avword)) {
            /* 2*sizeof(__avword) < end_offset ≤ 3*sizeof(__avword) */
            __avword mask2 = - ((__avword)1 << (3*sizeof(__avword)*8-end_offset*8));
            wordaddr[1] = (iret << (sizeof(__avword)*4-start_offset*4) << (sizeof(__avword)*4-start_offset*4)) | (iret2 >> (start_offset*8));
            wordaddr[2] ^= (wordaddr[2] ^ ((iret2 << (sizeof(__avword)*4-start_offset*4) << (sizeof(__avword)*4-start_offset*4)) | (iret3 >> (start_offset*8)))) & mask2;
          } else {
            /* 3*sizeof(__avword) < end_offset < 4*sizeof(__avword), start_offset > 0 */
            __avword mask3 = - ((__avword)1 << (4*sizeof(__avword)*8-end_offset*8));
            wordaddr[1] = (iret << (sizeof(__avword)*8-start_offset*8)) | (iret2 >> (start_offset*8));
            wordaddr[2] = (iret2 << (sizeof(__avword)*8-start_offset*8)) | (iret3 >> (start_offset*8));
            wordaddr[3] ^= (wordaddr[3] ^ (iret3 << (sizeof(__avword)*8-start_offset*8))) & mask3;
          }
        } else {
          /* Use iret, iret2, iret3, iret4. */
          __avword mask0 = ((__avword)2 << (sizeof(__avword)*8-start_offset*8-1)) - 1;
          wordaddr[0] ^= (wordaddr[0] ^ (iret >> (start_offset*8))) & mask0;
          if (end_offset <= 4*sizeof(__avword)) {
            /* 3*sizeof(__avword) < end_offset ≤ 4*sizeof(__avword) */
            __avword mask3 = - ((__avword)1 << (4*sizeof(__avword)*8-end_offset*8));
            wordaddr[1] = (iret << (sizeof(__avword)*4-start_offset*4) << (sizeof(__avword)*4-start_offset*4)) | (iret2 >> (start_offset*8));
            wordaddr[2] = (iret2 << (sizeof(__avword)*4-start_offset*4) << (sizeof(__avword)*4-start_offset*4)) | (iret3 >> (start_offset*8));
            wordaddr[3] ^= (wordaddr[3] ^ ((iret3 << (sizeof(__avword)*4-start_offset*4) << (sizeof(__avword)*4-start_offset*4)) | (iret4 >> (start_offset*8)))) & mask3;
          } else {
            /* 4*sizeof(__avword) < end_offset < 5*sizeof(__avword), start_offset > 0 */
            __avword mask4 = - ((__avword)1 << (5*sizeof(__avword)*8-end_offset*8));
            wordaddr[1] = (iret << (sizeof(__avword)*8-start_offset*8)) | (iret2 >> (start_offset*8));
            wordaddr[2] = (iret2 << (sizeof(__avword)*8-start_offset*8)) | (iret3 >> (start_offset*8));
            wordaddr[3] = (iret3 << (sizeof(__avword)*8-start_offset*8)) | (iret4 >> (start_offset*8));
            wordaddr[4] ^= (wordaddr[4] ^ (iret4 << (sizeof(__avword)*8-start_offset*8))) & mask4;
          }
        }
        #endif
      }
    }
  }
  return 0;
}
