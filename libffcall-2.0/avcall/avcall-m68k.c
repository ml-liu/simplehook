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

  Foreign function interface for a m68k Sun3 with gcc/sun-cc.

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  M68k Argument Passing Conventions:

  All arguments are passed on the stack with word alignment. Doubles take
  two words. Structure args are passed as true structures embedded in the
  argument stack. To return a structure, the called function copies the
  return value to the address supplied in register "a1". Gcc without
  -fpcc-struct-return returns <= 4 byte structures as integers.

  Compile this routine with gcc -O (or -O2 or -g -O) to get the right
  register variables, or use the assembler version.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("sp");  /* C names for registers */
  register __avword*	sret	__asm__("a1");	/* structure return pointer */
/*register __avword	iret	__asm__("d0"); */
  register __avword	iret2	__asm__("d1");
  register float	fret	__asm__("d0");	/* d0 */
  register double	dret	__asm__("d0");	/* d0,d1 */
  register float	fp_fret	__asm__("fp0");
  register double	fp_dret	__asm__("fp0");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = l->aptr - l->args;
  __avword i;
  __avword i2;

  for (i = 0; i < arglen; i++)		/* push function args onto stack */
    argframe[i] = l->args[i];

  if (l->rtype == __AVstruct)		/* push struct return address */
    __asm__("move%.l %0,%/a1" : : "g" (l->raddr));

  i = (*l->func)();			/* call function */
  i2 = iret2;

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
    ((__avword*)raddr)[1] = i2;
  } else
  if (l->rtype == __AVfloat) {
    if (l->flags & __AV_FREG_FLOAT_RETURN) {
      RETURN(float, fp_fret);
    } else {
      if (l->flags & __AV_SUNCC_FLOAT_RETURN) {
        RETURN(float, (float)dret);
      } else {
        RETURN(float, fret);
      }
    }
  } else
  if (l->rtype == __AVdouble) {
    if (l->flags & __AV_FREG_FLOAT_RETURN) {
      RETURN(double, fp_dret);
    } else {
      RETURN(double, dret);
    }
  } else
  if (l->rtype == __AVvoidp) {
    RETURN(void*, i);
  } else
  if (l->rtype == __AVstruct) {
    /* NB: On m68k, all structure sizes are divisible by 2. */
    if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
      if (l->rsize == sizeof(char)) { /* can't occur */
        RETURN(char, i);
      } else
      if (l->rsize == sizeof(short)) {
        RETURN(short, i);
      } else
      if (l->rsize == sizeof(int)) {
        RETURN(int, i);
      } else
      if (l->rsize == 2*sizeof(__avword)) {
        void* raddr = l->raddr;
        ((__avword*)raddr)[0] = i;
        ((__avword*)raddr)[1] = i2;
      }
    }
  }
  return 0;
}
