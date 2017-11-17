/* vacall function for alpha CPU */

/*
 * Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "vacall-internal.h"

#ifdef REENTRANT
#define vacall_receiver callback_receiver
register struct { void (*vacall_function) (void*,va_alist); void* arg; }
         *		env	__asm__("$1");
#endif
register long		arg1	__asm__("$16");
register long		arg2	__asm__("$17");
register long		arg3	__asm__("$18");
register long		arg4	__asm__("$19");
register long		arg5	__asm__("$20");
register long		arg6	__asm__("$21");
register double		farg1	__asm__("$f16");
register double		farg2	__asm__("$f17");
register double		farg3	__asm__("$f18");
register double		farg4	__asm__("$f19");
register double		farg5	__asm__("$f20");
register double		farg6	__asm__("$f21");
register __vaword	iret	__asm__("$0");
register __vaword	iret2	__asm__("$1");
register float		fret	__asm__("$f0");
register double		dret	__asm__("$f0");

/* The ABI requires that the first 6 general-purpose argument words are
   being passed in registers, even if these words belong to a struct. No room
   is allocated for these register words on the stack by the caller, but the
   callee allocates room for them - at the right place in the stack frame,
   that is, above the usual {fp, retaddr} combo - if and only if they are part
   of a larger struct that extends to the stack and the address of this struct
   is taken. */
struct gpargsequence {
  __vaword word1; /* $16 */
  __vaword word2; /* $17 */
  __vaword word3; /* $18 */
  __vaword word4; /* $19 */
  __vaword word5; /* $20 */
  __vaword word6; /* $21 */
  __vaword firststackword;
};

#ifdef REENTRANT
static
#endif
void /* the return type is variable, not void! */
vacall_receiver (struct gpargsequence gpargs)
{
  __va_alist list;
  /* Move the arguments passed in registers to their stack locations. */
  list.farg[0] = farg1;
  list.farg[1] = farg2;
  list.farg[2] = farg3;
  list.farg[3] = farg4;
  list.farg[4] = farg5;
  list.farg[5] = farg6;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)&gpargs;
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.memargptr = (long)&gpargs.firststackword;
  list.farg_offset = (long)&list.farg[0] - list.aptr;
  /* Call vacall_function. The macros do all the rest. */
#ifndef REENTRANT
  (*vacall_function) (&list);
#else /* REENTRANT */
  (*env->vacall_function) (env->arg,&list);
#endif
  /* Put return value into proper register. */
  if (list.rtype == __VAvoid) {
  } else
  if (list.rtype == __VAchar) {
    iret = list.tmp._char;
  } else
  if (list.rtype == __VAschar) {
    iret = list.tmp._schar;
  } else
  if (list.rtype == __VAuchar) {
    iret = list.tmp._uchar;
  } else
  if (list.rtype == __VAshort) {
    iret = list.tmp._short;
  } else
  if (list.rtype == __VAushort) {
    iret = list.tmp._ushort;
  } else
  if (list.rtype == __VAint) {
    iret = list.tmp._int;
  } else
  if (list.rtype == __VAuint) {
    iret = list.tmp._uint;
  } else
  if (list.rtype == __VAlong) {
    iret = list.tmp._long;
  } else
  if (list.rtype == __VAulong) {
    iret = list.tmp._ulong;
  } else
  if (list.rtype == __VAlonglong) {
    iret = list.tmp._long;
  } else
  if (list.rtype == __VAulonglong) {
    iret = list.tmp._ulong;
  } else
  if (list.rtype == __VAfloat) {
    fret = list.tmp._float;
  } else
  if (list.rtype == __VAdouble) {
    dret = list.tmp._double;
  } else
  if (list.rtype == __VAvoidp) {
    iret = (long)list.tmp._ptr;
  } else
  if (list.rtype == __VAstruct) {
    if (list.flags & __VA_REGISTER_STRUCT_RETURN) {
      if (list.rsize == sizeof(char)) {
        iret = *(unsigned char *) list.raddr;
      } else
      if (list.rsize == sizeof(short)) {
        iret = *(unsigned short *) list.raddr;
      } else
      if (list.rsize == sizeof(int)) {
        iret = *(unsigned int *) list.raddr;
      } else
      if (list.rsize == sizeof(long)) {
        iret = *(unsigned long *) list.raddr;
      } else
      if (list.rsize == 2*sizeof(__vaword)) {
        iret  = ((__vaword *) list.raddr)[0];
        iret2 = ((__vaword *) list.raddr)[1];
      }
    }
  }
}

#ifdef REENTRANT
__vacall_r_t
callback_get_receiver (void)
{
  return (__vacall_r_t)(void*)&callback_receiver;
}
#endif
