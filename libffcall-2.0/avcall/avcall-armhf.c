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

  Foreign function interface for an ARM with -mfloat-abi=hard with gcc.

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  ARM Argument Passing Conventions:

  All arguments, except the first 4 words which are passed in the registers
  r0, r1, r2, r3, are passed on the stack with word alignment. Doubles take
  two words.
  In ABIs where 'double' and 'long long' have alignment 4, they are passed
  entirely in registers or entirely on the stack (i.e. not the first half
  in r3 and the second half on the stack).
  In ABIs where 'double' and 'long long' have alignment 8, they are passed
  with 2-word alignment in this word sequence (e.g. a 'double' after an
  'int' in r0 gets passed in (r2,r3), not in (r1,r2)). This implies that
  they are passed entirely in registers or entirely on the stack.
  Structure args are passed as true structures embedded in the argument stack.
  A structure arg may be allocated partially in registers (r0,...,r3) and
  partially on the stack, if no previous args already consume stack space.
  To return a structure, the called function copies the return value to the
  address supplied in register r0.

  In hard-float configurations (armhf): Up to 16 floats get passed in the
  single-float registers s0, s1, ..., s15. A float gets returned in s0.
  Up to 8 doubles gets passed in the double-float registers d0, ..., d7
  (= {s0,s1}, {s2,s3}, ..., {s14,s15}). A double gets returned in d0.

  The 4 integer args registers and the 16 float args slots are allocated
  independently: 1) After more than 16 float args, integer args can still
  be allocated in registers. 2) After more than 4 integer args, float args
  can still be allocated in registers.

  Compile this routine with gcc -O (or -O2 or -g -O) to get the right
  register variables, or use the assembler version.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

int
avcall_call(av_alist* list)
{
  register unsigned long sp	__asm__("r13");  /* C names for registers */
/*register __avword	iret	__asm__("r0"); */
  register __avword	iret2	__asm__("r1");
  register float	fret	__asm__("s0");
  register double	dret	__asm__("d0");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */

  /* Enforce 8-bytes-alignment of the stack pointer.
     We need to do it this way because the old GCC that we use to compile
     this file does not support the option '-mabi=aapcs'. */
  sp &= -8;

  int arglen = l->aptr - l->args;
  __avword i;

  for (i = 4; i < arglen; i++)		/* push function args onto stack */
    argframe[i-4] = l->args[i];

  /* load float values into floating-point registers */
  if ((l->farg_mask >> 0) & 1)
    __asm__ __volatile__ ("vldr.32 s0,%0" : : "m" (l->fargs[0]));
  if ((l->farg_mask >> 1) & 1)
    __asm__ __volatile__ ("vldr.32 s1,%0" : : "m" (l->fargs[1]));
  if ((l->farg_mask >> 2) & 1)
    __asm__ __volatile__ ("vldr.32 s2,%0" : : "m" (l->fargs[2]));
  if ((l->farg_mask >> 3) & 1)
    __asm__ __volatile__ ("vldr.32 s3,%0" : : "m" (l->fargs[3]));
  if ((l->farg_mask >> 4) & 1)
    __asm__ __volatile__ ("vldr.32 s4,%0" : : "m" (l->fargs[4]));
  if ((l->farg_mask >> 5) & 1)
    __asm__ __volatile__ ("vldr.32 s5,%0" : : "m" (l->fargs[5]));
  if ((l->farg_mask >> 6) & 1)
    __asm__ __volatile__ ("vldr.32 s6,%0" : : "m" (l->fargs[6]));
  if ((l->farg_mask >> 7) & 1)
    __asm__ __volatile__ ("vldr.32 s7,%0" : : "m" (l->fargs[7]));
  if ((l->farg_mask >> 8) & 1)
    __asm__ __volatile__ ("vldr.32 s8,%0" : : "m" (l->fargs[8]));
  if ((l->farg_mask >> 9) & 1)
    __asm__ __volatile__ ("vldr.32 s9,%0" : : "m" (l->fargs[9]));
  if ((l->farg_mask >> 10) & 1)
    __asm__ __volatile__ ("vldr.32 s10,%0" : : "m" (l->fargs[10]));
  if ((l->farg_mask >> 11) & 1)
    __asm__ __volatile__ ("vldr.32 s11,%0" : : "m" (l->fargs[11]));
  if ((l->farg_mask >> 12) & 1)
    __asm__ __volatile__ ("vldr.32 s12,%0" : : "m" (l->fargs[12]));
  if ((l->farg_mask >> 13) & 1)
    __asm__ __volatile__ ("vldr.32 s13,%0" : : "m" (l->fargs[13]));
  if ((l->farg_mask >> 14) & 1)
    __asm__ __volatile__ ("vldr.32 s14,%0" : : "m" (l->fargs[14]));
  if ((l->farg_mask >> 15) & 1)
    __asm__ __volatile__ ("vldr.32 s15,%0" : : "m" (l->fargs[15]));

  /* load double values into floating-point registers */
  if ((l->darg_mask >> 0) & 1)
    __asm__ __volatile__ ("vldr.64 d0,%0" : : "m" (l->dargs[0]));
  if ((l->darg_mask >> 1) & 1)
    __asm__ __volatile__ ("vldr.64 d1,%0" : : "m" (l->dargs[1]));
  if ((l->darg_mask >> 2) & 1)
    __asm__ __volatile__ ("vldr.64 d2,%0" : : "m" (l->dargs[2]));
  if ((l->darg_mask >> 3) & 1)
    __asm__ __volatile__ ("vldr.64 d3,%0" : : "m" (l->dargs[3]));
  if ((l->darg_mask >> 4) & 1)
    __asm__ __volatile__ ("vldr.64 d4,%0" : : "m" (l->dargs[4]));
  if ((l->darg_mask >> 5) & 1)
    __asm__ __volatile__ ("vldr.64 d5,%0" : : "m" (l->dargs[5]));
  if ((l->darg_mask >> 6) & 1)
    __asm__ __volatile__ ("vldr.64 d6,%0" : : "m" (l->dargs[6]));
  if ((l->darg_mask >> 7) & 1)
    __asm__ __volatile__ ("vldr.64 d7,%0" : : "m" (l->dargs[7]));

				/* call function, pass 4 integer args in registers */
  i = (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3]);

  /* save return value */
  if (l->rtype == __AVvoid) {
  } else
  if (l->rtype == __AVword) {
    RETURN(__avword, i);
  } else
  if (l->rtype == __AVchar) {
    RETURN(char, i);
  } else
  if (l->rtype == __AVschar) {
    RETURN(signed char, i);
  } else
  if (l->rtype == __AVuchar) {
    RETURN(unsigned char, i);
  } else
  if (l->rtype == __AVshort) {
    RETURN(short, i);
  } else
  if (l->rtype == __AVushort) {
    RETURN(unsigned short, i);
  } else
  if (l->rtype == __AVint) {
    RETURN(int, i);
  } else
  if (l->rtype == __AVuint) {
    RETURN(unsigned int, i);
  } else
  if (l->rtype == __AVlong) {
    RETURN(long, i);
  } else
  if (l->rtype == __AVulong) {
    RETURN(unsigned long, i);
  } else
  if (l->rtype == __AVlonglong || l->rtype == __AVulonglong) {
    void* raddr = l->raddr;
    ((__avword*)raddr)[0] = i;
    ((__avword*)raddr)[1] = iret2;
  } else
  if (l->rtype == __AVfloat) {
    RETURN(float, fret);
  } else
  if (l->rtype == __AVdouble) {
    RETURN(double, dret);
  } else
  if (l->rtype == __AVvoidp) {
    RETURN(void*, i);
  } else
  if (l->rtype == __AVstruct) {
    /* PCS for ARM (http://infocenter.arm.com/help/topic/com.arm.doc.ihi0042b/IHI0042B_aapcs.pdf):
       page 19: "A Composite Type not larger than 4 bytes is returned in r0."
       sizeof({char a[3];}) = 3, so we have to use <= sizeof below */
    if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
      if (l->rsize == sizeof(char)) { /* can't occur */
        RETURN(char, i);
      } else
      if (l->rsize == sizeof(short)) { /* can't occur */
        RETURN(short, i);
      } else
      if (l->rsize <= sizeof(int)) {
        RETURN(int, i);
      } else
      if (l->rsize == 2*sizeof(__avword)) {
        void* raddr = l->raddr;
        ((__avword*)raddr)[0] = i;
        ((__avword*)raddr)[1] = iret2;
      }
    }
  }
  return 0;
}
