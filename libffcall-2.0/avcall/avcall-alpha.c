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

  Foreign function interface for a DEC Alpha with gcc.

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  Alpha Argument Passing Conventions

  The first 6 arguments are passed in registers $16-$21 for integers,
  in registers $f16-$f21 for floats. From then on, everything is passed
  on the stack.

  Everything on the stack is word-aligned.

  Integers and pointers are returned in $0, floats and doubles in $f0.
  To return a structure, the called function copies the value to space
  pointed to by its first argument, and all other arguments are shifted
  down by one.

  Compile this routine with gcc for the __asm__ extensions and with
  optimisation on (-O or -O2 or -g -O) so that argframe is set to the
  correct offset.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

int
avcall_call(av_alist* list)
{
  register __avword*	sp	__asm__("$30");  /* C names for registers */
  register long		arg1	__asm__("$16");
  register long		arg2	__asm__("$17");
  register long		arg3	__asm__("$18");
  register long		arg4	__asm__("$19");
  register long		arg5	__asm__("$20");
  register long		arg6	__asm__("$21");
  register double	fret	__asm__("$f0");
  register double	farg1	__asm__("$f16");
  register double	farg2	__asm__("$f17");
  register double	farg3	__asm__("$f18");
  register double	farg4	__asm__("$f19");
  register double	farg5	__asm__("$f20");
  register double	farg6	__asm__("$f21");
/*register __avword	iret	__asm__("$0"); */
  register __avword	iret2	__asm__("$1");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = ((unsigned long) l->aptr - (unsigned long) l->args) / sizeof (__avword);
  __avword i, i2;

  for (i = 6; i < arglen; i++)		/* push excess function args */
    argframe[i-6] = l->args[i];

					/* call function with 1st 6 args */
  /* we pass the args both in the integer registers and the floating point
     registers, so we don't have to store the argument types. */
  __asm__ __volatile__ ("ldq $16,%0" : : "m" (l->args[0])); /* arg1 = l->args[0]; */
  __asm__ __volatile__ ("ldt $f16,%0" : : "m" (l->args[0])); /* farg1 = *(double*) &l->args[0]; */
  __asm__ __volatile__ ("ldq $17,%0" : : "m" (l->args[1])); /* arg2 = l->args[1]; */
  __asm__ __volatile__ ("ldt $f17,%0" : : "m" (l->args[1])); /* farg2 = *(double*) &l->args[1]; */
  __asm__ __volatile__ ("ldq $18,%0" : : "m" (l->args[2])); /* arg3 = l->args[2]; */
  __asm__ __volatile__ ("ldt $f18,%0" : : "m" (l->args[2])); /* farg3 = *(double*) &l->args[2]; */
  __asm__ __volatile__ ("ldq $19,%0" : : "m" (l->args[3])); /* arg4 = l->args[3]; */
  __asm__ __volatile__ ("ldt $f19,%0" : : "m" (l->args[3])); /* farg4 = *(double*) &l->args[3]; */
  __asm__ __volatile__ ("ldq $20,%0" : : "m" (l->args[4])); /* arg5 = l->args[4]; */
  __asm__ __volatile__ ("ldt $f20,%0" : : "m" (l->args[4])); /* farg5 = *(double*) &l->args[4]; */
  __asm__ __volatile__ ("ldq $21,%0" : : "m" (l->args[5])); /* arg6 = l->args[5]; */
  __asm__ __volatile__ ("ldt $f21,%0" : : "m" (l->args[5])); /* farg6 = *(double*) &l->args[5]; */
  i = (*l->func)();
  i2 = iret2;
  /* this is apparently not needed, but better safe than sorry... */
  __asm__ __volatile__ ("" : : :
			/* clobber */ "$16", "$17", "$18", "$19", "$20", "$21",
				     "$f16","$f17","$f18","$f19","$f20","$f21");

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
  if (l->rtype == __AVlonglong) {
    RETURN(long long, i);
  } else
  if (l->rtype == __AVulonglong) {
    RETURN(unsigned long long, i);
  } else
  if (l->rtype == __AVfloat) {
    RETURN(float, fret);
  } else
  if (l->rtype == __AVdouble) {
    RETURN(double, fret);
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
      if (l->rsize == sizeof(long)) {
        RETURN(long, i);
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
