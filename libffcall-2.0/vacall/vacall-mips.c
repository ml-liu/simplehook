/* vacall function for mips CPU */

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

#ifndef REENTRANT
typedef void (*func_pointer)(va_alist);
#else /* REENTRANT */
#define vacall_receiver callback_receiver
typedef void (*func_pointer)(void*,va_alist);
register struct { func_pointer vacall_function; void* arg; }
         *	env	__asm__("$2");
#endif
register float	farg1	__asm__("$f12");
register float	farg2	__asm__("$f14");
register double	darg1	__asm__("$f12");
register double	darg2	__asm__("$f14");
register int	iret	__asm__("$2");
register int	iret2	__asm__("$3");
register float	fret	__asm__("$f0");
register double	dret	__asm__("$f0");

#ifdef REENTRANT
static
#endif
void /* the return type is variable, not void! */
vacall_receiver (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
                 __vaword firstword)
{
  __va_alist list;
  /* gcc-2.6.3 source says: When a parameter is passed in a register,
   * stack space is still allocated for it.
   */
  /* Move the arguments passed in registers to their stack locations. */
  (&firstword)[-4] = word1;
  (&firstword)[-3] = word2;
  (&firstword)[-2] = word3;
  (&firstword)[-1] = word4;
  list.darg[0] = darg1;
  list.darg[1] = darg2;
  list.farg[0] = farg1;
  list.farg[1] = farg2;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)(&firstword - 4);
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.memargptr = (long)&firstword;
  list.anum = 0;
  list.fanum = 0;
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
  if (list.rtype == __VAlonglong || list.rtype == __VAulonglong) {
    iret  = ((__vaword *) &list.tmp._longlong)[0];
    iret2 = ((__vaword *) &list.tmp._longlong)[1];
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
    if (list.flags & __VA_SMALL_STRUCT_RETURN) {
      if (list.rsize == sizeof(char)) {
        iret = *(unsigned char *) list.raddr;
      } else
      if (list.rsize == sizeof(short)) {
        iret = *(unsigned short *) list.raddr;
      } else
      if (list.rsize == sizeof(int)) {
        iret = *(unsigned int *) list.raddr;
      }
    } else {
      iret = (long)list.raddr;
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
