/* vacall function for arm CPU */

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

/* armel have only softvfp which uses generic registers */
register __vaword	iret	__asm__("r0");
register __vaword	iret2	__asm__("r1");
register float		fret	__asm__("r0");
register __vaword	dret1	__asm__("r0");
register __vaword	dret2	__asm__("r1");

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

void /* the return type is variable, not void! */
vacall_receiver (struct gpargsequence gpargs)
#else /* REENTRANT */
/* The first 4 general-purpose argument words have already been pushed to the
   stack by the trampoline. We can ignore them here. */
static
void /* the return type is variable, not void! */
vacall_receiver (__vaword ignored1, __vaword ignored2, __vaword ignored3, __vaword ignored4,
                 env_t* env, __vaword filler, __vaword saved_fp, __vaword saved_sp, __vaword saved_lr, __vaword saved_pc,
                 __vaword firstword)
#endif
{
  __va_alist list;

  /* Enforce 8-bytes-alignment of the stack pointer.
     We need to do it this way because the old GCC that we use to compile
     this file does not support the option '-mabi=aapcs'. */
  register unsigned long sp __asm__("r13");  /* C names for registers */
  sp &= -8;

  /* Prepare the va_alist. */
  list.flags = 0;
#ifndef REENTRANT
  list.aptr = (long)&gpargs;
#else /* REENTRANT */
  list.aptr = (long)&firstword;
#endif
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
    dret1 = ((__vaword *) &list.tmp._double)[0];
    dret2 = ((__vaword *) &list.tmp._double)[1];
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
