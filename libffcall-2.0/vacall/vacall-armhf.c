/* vacall function for arm CPU with -mfloat-abi=hard */

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
typedef struct { void (*vacall_function) (void*,va_alist); void* arg; } env_t;
#endif

/* armhf passes up to 16 float arguments and up to 8 double arguments
   in floating-point registers. */
register float  farg0   __asm__("s0");
register float  farg1   __asm__("s1");
register float  farg2   __asm__("s2");
register float  farg3   __asm__("s3");
register float  farg4   __asm__("s4");
register float  farg5   __asm__("s5");
register float  farg6   __asm__("s6");
register float  farg7   __asm__("s7");
register float  farg8   __asm__("s8");
register float  farg9   __asm__("s9");
register float  farg10  __asm__("s10");
register float  farg11  __asm__("s11");
register float  farg12  __asm__("s12");
register float  farg13  __asm__("s13");
register float  farg14  __asm__("s14");
register float  farg15  __asm__("s15");
register double darg0   __asm__("d0"); /* overlaps s0,s1 */
register double darg1   __asm__("d1"); /* overlaps s2,s3 */
register double darg2   __asm__("d2"); /* overlaps s4,s5 */
register double darg3   __asm__("d3"); /* overlaps s6,s7 */
register double darg4   __asm__("d4"); /* overlaps s8,s9 */
register double darg5   __asm__("d5"); /* overlaps s10,s11 */
register double darg6   __asm__("d6"); /* overlaps s12,s13 */
register double darg7   __asm__("d7"); /* overlaps s14,s15 */
register __vaword	iret	__asm__("r0");
register __vaword	iret2	__asm__("r1");
register float		fret	__asm__("s0");
register double		dret	__asm__("d0");

#ifndef REENTRANT
/* The ARM ABI requires that the first 4 general-purpose argument words are
   being passed in registers, even if these words belong to a struct. No room
   is allocated for these register words on the stack by the caller, but the
   callee allocates room for them - at the right place in the stack frame,
   that is, above the usual {fp, sp, retaddr, pc} combo - if and only if
   they are part of a larger struct that extends to the stack and the address
   of this struct is taken. */
struct gpargsequence {
  __vaword word1; /* r0 */
  __vaword word2; /* r1 */
  __vaword word3; /* r2 */
  __vaword word4; /* r3 */
  __vaword firststackword;
};

#ifdef REENTRANT
static
#endif
void /* the return type is variable, not void! */
vacall_receiver (struct gpargsequence gpargs)
#else /* REENTRANT */
/* The first 4 general-purpose argument words have already been pushed to the
   stack by the trampoline. We can ignore them here. */
void /* the return type is variable, not void! */
vacall_receiver (__vaword ignored1, __vaword ignored2, __vaword ignored3, __vaword ignored4,
                 env_t* env, __vaword filler, __vaword saved_fp, __vaword saved_sp, __vaword saved_lr, __vaword saved_pc,
                 __vaword firstword)
#endif
{
  __va_alist list;
  /* Save the floating point argument registers. */
  list.farg[0] = farg0;
  list.farg[1] = farg1;
  list.farg[2] = farg2;
  list.farg[3] = farg3;
  list.farg[4] = farg4;
  list.farg[5] = farg5;
  list.farg[6] = farg6;
  list.farg[7] = farg7;
  list.farg[8] = farg8;
  list.farg[9] = farg9;
  list.farg[10] = farg10;
  list.farg[11] = farg11;
  list.farg[12] = farg12;
  list.farg[13] = farg13;
  list.farg[14] = farg14;
  list.farg[15] = farg15;
  list.darg[0] = darg0;
  list.darg[1] = darg1;
  list.darg[2] = darg2;
  list.darg[3] = darg3;
  list.darg[4] = darg4;
  list.darg[5] = darg5;
  list.darg[6] = darg6;
  list.darg[7] = darg7;
  /* Prepare the va_alist. */
  list.flags = 0;
#ifndef REENTRANT
  list.iarg = (__vaword*)&gpargs;
#else /* REENTRANT */
  list.iarg = (__vaword*)&firstword;
#endif
  list.aptr = (long)(list.iarg + __VA_IARG_NUM);
  list.ianum = 0;
  list.fanum = 0;
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
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
    /* NB: On arm, all structure sizes are divisible by 4. */
    if (list.flags & __VA_REGISTER_STRUCT_RETURN) {
      if (list.rsize == sizeof(char)) { /* can't occur */
        iret = *(unsigned char *) list.raddr;
      } else
      if (list.rsize == sizeof(short)) { /* can't occur */
        iret = *(unsigned short *) list.raddr;
      } else
        iret = *(unsigned int *) list.raddr; /* struct of size 3 :) */
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
