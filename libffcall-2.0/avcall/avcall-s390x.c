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

  Foreign function interface for an s390x 64-bit CPU.

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  s390x 64-bit Argument Passing Conventions

  * Arguments:
    - The first 5 integer or pointer arguments get passed in
      r2, r3, r4, r5, r6; the remaining ones (as an entire word each)
      on the stack.
    - The first 4 float or double arguments get passed in
      f0, f2, f4, f6; the remaining ones on the stack (as an entire
      word each, floats in the upper half of a word).
    - Structures of sizes 1, 2, 4, 8 are passed as follows:
      - Structures consisting only of a float or double are passed
        like an immediate float or double, that is, in f0, f2, f4, f6
        and on the stack (floats in the upper half of their respective
        word). But we don't support this kind of structure.
      - Other structures get passed as an entire word, like integers
        and pointers.
        When in r2, ..., r6: as the 8*sizeof(S) low bits of the register
        (a.k.a. "right-adjusted").
        When on the stack: they occupy an entire word and are adjusted
        on the high end of the word:
          - sizeof(S) == 1: at an address == 7 mod 8,
          - sizeof(S) == 2: at an address == 6 mod 8,
          - sizeof(S) == 4: at an address == 4 mod 8,
    - Structures of other sizes are passed as references.
  * Return value:
    - An integer or pointer is returned in r2.
    - A float or double is returned in f0.
    - Structure return convention: The caller passes a pointer to the
      destination area (quasi as an additional first pointer argument)
      in r2. The callee fills it and returns the same pointer in r2.

  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

register __avword iarg1 __asm__("r2");
register __avword iarg2 __asm__("r3");
register __avword iarg3 __asm__("r4");
register __avword iarg4 __asm__("r5");
register __avword iarg5 __asm__("r6");

register float farg1 __asm__("f0");
register float farg2 __asm__("f2");
register float farg3 __asm__("f4");
register float farg4 __asm__("f6");

register double darg1 __asm__("f0");
register double darg2 __asm__("f2");
register double darg3 __asm__("f4");
register double darg4 __asm__("f6");

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("r15");	/* C names for registers */
  register __avword	iret	__asm__("r2");
  register double	dret	__asm__("f0");

  /* We need to put a value in r6, but it's a call-saved register. */
  __avword saved_iarg5 = iarg5;

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = l->aptr - l->args;
  unsigned int ianum = l->ianum;
  unsigned int fanum = l->fanum;
  __avword i;

  for (i = 0; i < arglen; i++)		/* push function args onto stack */
    argframe[i] = l->args[i];

  /* Put up to 5 integer args into registers. */
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
          }
        }
      }
    }
  }

  /* Put upto 4 floating-point args into registers. */
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
    i = (*l->func)();

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
    if (l->rtype == __AVlong || l->rtype == __AVlonglong) {
      RETURN(long, i);
    } else
    if (l->rtype == __AVulong || l->rtype == __AVulonglong) {
      RETURN(unsigned long, i);
    } else
  /* see above
    if (l->rtype == __AVfloat) {
    } else
    if (l->rtype == __AVdouble) {
    } else
  */
    if (l->rtype == __AVvoidp) {
      RETURN(void*, i);
    } else
    if (l->rtype == __AVstruct) {
      /* normal struct return convention */
    }
  }
  iarg5 = saved_iarg5;
  return 0;
}
