/**
  Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
  Copyright 2001 Gerhard Tonn <gt@debian.org>

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

  Foreign function interface for an IBM S/390 with gcc

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  S390 Argument Passing Conventions:

  All arguments, except the first 5 words, are passed on the stack with
  word alignment. Doubles take two words. The first 2 doubles and floats
  are also passed in floating-point-registers.
  To return a structure, the called function copies the value to space
  pointed to by its first argument, and all other arguments are shifted
  down by one.

  Compile this routine with gcc -O2 to get the right register variables.
  For other compilers use the pre-compiled assembler version.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

register float  farg1	__asm__("f0");
register float  farg2	__asm__("f2");
register double darg1	__asm__("f0");
register double darg2	__asm__("f2");

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("r15");  /* C names for registers */
/*register __avword	iret	__asm__("r2"); */
  register __avword	iret2	__asm__("r3");
  register float	fret	__asm__("f0");
  register double	dret	__asm__("f0");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = l->aptr - l->args;
  unsigned int fanum = l->fanum;
  __avword i;

  for (i = 0; i < arglen; i++)		/* push function args onto stack */
   argframe[i] = l->args[i];

  /* Put upto 2 floating-point args into registers. */
  if (fanum >= 1) {
    if (l->darg_mask & (1 << 0)) darg1 = l->dargs[0];
    else if (l->farg_mask & (1 << 0)) farg1 = l->fargs[0];
    if (fanum >= 2) {
      if (l->darg_mask & (1 << 1)) darg2 = l->dargs[1];
      else if (l->farg_mask & (1 << 1)) farg2 = l->fargs[1];
    }
  }

				/* call function, pass 5 args in registers */
  i = (*l->func)(l->iargs[0], l->iargs[1], l->iargs[2], l->iargs[3],
		 l->iargs[4]);

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
    if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
      if (l->rsize == sizeof(char)) {
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
        ((__avword*)raddr)[1] = iret2;
      }
    }
  }
  return 0;
}
