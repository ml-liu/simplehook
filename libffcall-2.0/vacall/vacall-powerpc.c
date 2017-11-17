/* vacall function for powerpc CPU */

/*
 * Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
 * Copyright 2000 Adam Fedor <fedor@gnu.org>
 * Copyright 2004 Paul Guyot <pguyot@kallisys.net>
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
         *		env	__asm__("r11");
#endif
register double		farg1	__asm__("fr1");
register double		farg2	__asm__("fr2");
register double		farg3	__asm__("fr3");
register double		farg4	__asm__("fr4");
register double		farg5	__asm__("fr5");
register double		farg6	__asm__("fr6");
register double		farg7	__asm__("fr7");
register double		farg8	__asm__("fr8");
register double		farg9	__asm__("fr9");
register double		farg10	__asm__("fr10");
register double		farg11	__asm__("fr11");
register double		farg12	__asm__("fr12");
register double		farg13	__asm__("fr13");
register __vaword	iret	__asm__("r3");
register __vaword	iret2	__asm__("r4");
register float		fret	__asm__("fr1");
register double		dret	__asm__("fr1");

#ifdef REENTRANT
static
#endif
void /* the return type is variable, not void! */
vacall_receiver (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
                 __vaword word5, __vaword word6, __vaword word7, __vaword word8,
                 __vaword firstword)
{
  __va_alist list;
#if defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)) /* __powerpc_aix__ */
  /* gcc-2.6.3 source says: When a parameter is passed in a register,
   * stack space is still allocated for it.
   */
  /* Move the arguments passed in registers to their stack locations. */
  (&firstword)[-8] = word1;
  (&firstword)[-7] = word2;
  (&firstword)[-6] = word3;
  (&firstword)[-5] = word4;
  (&firstword)[-4] = word5;
  (&firstword)[-3] = word6;
  (&firstword)[-2] = word7;
  (&firstword)[-1] = word8;
#else /* __powerpc_sysv4__ */
  /* Move the arguments passed in registers to temp storage, since
     moving them to the stack would mess up the stack */
  list.iarg[0] = word1;
  list.iarg[1] = word2;
  list.iarg[2] = word3;
  list.iarg[3] = word4;
  list.iarg[4] = word5;
  list.iarg[5] = word6;
  list.iarg[6] = word7;
  list.iarg[7] = word8;
#endif
  list.farg[0] = farg1;
  list.farg[1] = farg2;
  list.farg[2] = farg3;
  list.farg[3] = farg4;
  list.farg[4] = farg5;
  list.farg[5] = farg6;
  list.farg[6] = farg7;
  list.farg[7] = farg8;
#if defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)) /* __powerpc_aix__ */
  list.farg[8] = farg9;
  list.farg[9] = farg10;
  list.farg[10] = farg11;
  list.farg[11] = farg12;
  list.farg[12] = farg13;
#endif
  /* Prepare the va_alist. */
  list.flags = 0;
#if defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)) /* __powerpc_aix__ */
  list.aptr = (long)(&firstword - 8);
#else /* __powerpc_sysv4__ */
  list.aptr = (long)(&firstword);
  list.ianum = 0;
#endif
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
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
