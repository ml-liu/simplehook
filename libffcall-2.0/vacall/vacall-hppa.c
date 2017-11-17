/* vacall function for hppa CPU */

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

/*---------------------------------------------------------------------------
  HPPA Argument Passing Conventions:

  The calling conventions for anonymous functions and for explicitly named
  functions are different. Only the convention for explicitly named functions
  matters here.

  All arguments, except the first 4 words, are passed on the stack
  - growing down! - with word alignment. Doubles take two words and force
  double alignment. Structures args are passed as true structures embedded
  in the argument stack. They force double alignment and - if they don't
  fit entirely in the 4 register words - are passed in memory.
  The first 2 words are passed like this:
    %r26 = first integer arg, %r25 = second integer arg, or
    %fr4L = first float arg, %fr5L = second float arg, or
    %fr5 = double arg.
  Similarly for the next 2 words, passed in %r24 and %r23, or
                                            %fr6L and %fr7L, or
                                            %fr7.

  To return a structure, the called function copies the return value to
  the address supplied in register "%r28".
---------------------------------------------------------------------------*/

#include "vacall-internal.h"

#ifdef REENTRANT
#define vacall_receiver callback_receiver
register struct { void (*vacall_function) (void*,va_alist); void* arg; }
         *	env	__asm__("%r29");
#endif
register void*	sret	__asm__("%r28");
register long   arg1	__asm__("%r26");
register long   arg2	__asm__("%r25");
register long   arg3	__asm__("%r24");
register long   arg4	__asm__("%r23");
register float  farg1	__asm__("%fr4"); /* fr4L */
register float  farg2	__asm__("%fr5"); /* fr5L */
register float  farg3	__asm__("%fr6"); /* fr6L */
register float  farg4	__asm__("%fr7"); /* fr7L */
register double darg1	__asm__("%fr5");
register double darg2	__asm__("%fr7");
register int	iret	__asm__("%r28");
register float	fret	__asm__("%fr4"); /* fr4L */
register double	dret	__asm__("%fr4");
register __vaword iret1	__asm__("%r28");
register __vaword iret2	__asm__("%r29");

#ifdef REENTRANT
static
#endif
void /* the return type is variable, not void! */
vacall_receiver (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
                 __vaword firstword)
{
  /* gcc-2.6.3 source says: When a parameter is passed in a register,
   * stack space is still allocated for it.
   */
  /* Note about stack offsets (see vacall-hppa.s):
   * &firstword = %r30 - 244, &word4 = %r30 - 240, ..., &word1 = %r30 - 228,
   */
  __va_alist list;
  /* Move the arguments passed in registers to their stack locations. */
  (&firstword)[4] = word1;
  (&firstword)[3] = word2;
  (&firstword)[2] = word3;
  (&firstword)[1] = word4;
  list.darg[1] = darg1;
  list.darg[0] = darg2;
  list.farg[3] = farg1;
  list.farg[2] = farg2;
  list.farg[1] = farg3;
  list.farg[0] = farg4;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)(&firstword + 5);
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.structraddr = sret;
  list.memargptr = (long)(&firstword + 1);
  list.farg_offset = (long)&list.farg[4] - list.aptr;
  list.darg_offset = (long)&list.darg[2] - list.aptr;
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
    iret1 = ((__vaword *) &list.tmp._longlong)[0];
    iret2 = ((__vaword *) &list.tmp._longlong)[1];
  } else
  if (list.rtype == __VAfloat) {
    fret = list.tmp._float;
    iret1 = list.tmp._words[0]; /* HP cc generates a RTNVAL=GR call */
  } else
  if (list.rtype == __VAdouble) {
    dret = list.tmp._double;
    iret1 = list.tmp._words[0]; /* HP cc generates a RTNVAL=GR call */
    iret2 = list.tmp._words[1]; /* i.e. result is expected in r28,r29 */
  } else
  if (list.rtype == __VAvoidp) {
    iret = (long)list.tmp._ptr;
  } else
  if (list.rtype == __VAstruct) {
    if (list.flags & __VA_SMALL_STRUCT_RETURN) {
      /* cc, c89 and gcc >= 2.7 return structs of size <= 8 in registers. */
      /* This is really weird code, unlike all other big-endian platforms. */
      if (list.rsize > 0 && list.rsize <= 8) {
        #if 0 /* Unoptimized */
        if (list.rsize == 1) {
          iret =   ((unsigned char *) list.raddr)[0];
        } else
        if (list.rsize == 2) {
          iret =  (((unsigned char *) list.raddr)[0] << 8)
                |  ((unsigned char *) list.raddr)[1];
        } else
        if (list.rsize == 3) {
          iret =  (((unsigned char *) list.raddr)[0] << 16)
                | (((unsigned char *) list.raddr)[1] << 8)
                |  ((unsigned char *) list.raddr)[2];
        } else
        if (list.rsize == 4) {
          iret =  (((unsigned char *) list.raddr)[0] << 24)
                | (((unsigned char *) list.raddr)[1] << 16)
                | (((unsigned char *) list.raddr)[2] << 8)
                |  ((unsigned char *) list.raddr)[3];
        } else
        if (list.rsize == 5) {
          iret1 =   ((unsigned char *) list.raddr)[0];
          iret2 =  (((unsigned char *) list.raddr)[1] << 24)
                 | (((unsigned char *) list.raddr)[2] << 16)
                 | (((unsigned char *) list.raddr)[3] << 8)
                 |  ((unsigned char *) list.raddr)[4];
        } else
        if (list.rsize == 6) {
          iret1 =  (((unsigned char *) list.raddr)[0] << 8)
                 |  ((unsigned char *) list.raddr)[1];
          iret2 =  (((unsigned char *) list.raddr)[2] << 24)
                 | (((unsigned char *) list.raddr)[3] << 16)
                 | (((unsigned char *) list.raddr)[4] << 8)
                 |  ((unsigned char *) list.raddr)[5];
        } else
        if (list.rsize == 7) {
          iret1 =  (((unsigned char *) list.raddr)[0] << 16)
                 | (((unsigned char *) list.raddr)[1] << 8)
                 |  ((unsigned char *) list.raddr)[2];
          iret2 =  (((unsigned char *) list.raddr)[3] << 24)
                 | (((unsigned char *) list.raddr)[4] << 16)
                 | (((unsigned char *) list.raddr)[5] << 8)
                 |  ((unsigned char *) list.raddr)[6];
        } else
        if (list.rsize == 8) {
          iret1 =  (((unsigned char *) list.raddr)[0] << 24)
                 | (((unsigned char *) list.raddr)[1] << 16)
                 | (((unsigned char *) list.raddr)[2] << 8)
                 |  ((unsigned char *) list.raddr)[3];
          iret2 =  (((unsigned char *) list.raddr)[4] << 24)
                 | (((unsigned char *) list.raddr)[5] << 16)
                 | (((unsigned char *) list.raddr)[6] << 8)
                 |  ((unsigned char *) list.raddr)[7];
        }
        #else /* Optimized: fewer conditional jumps, fewer memory accesses */
        uintptr_t count = list.rsize; /* > 0, ≤ 2*sizeof(__vaword) */
        __vaword* wordaddr = (__vaword*)((uintptr_t)list.raddr & ~(uintptr_t)(sizeof(__vaword)-1));
        uintptr_t start_offset = (uintptr_t)list.raddr & (uintptr_t)(sizeof(__vaword)-1); /* ≥ 0, < sizeof(__vaword) */
        uintptr_t end_offset = start_offset + count; /* > 0, < 3*sizeof(__vaword) */
        if (count <= sizeof(__vaword)) {
          /* Assign iret. */
          __vaword mask0 = ((__vaword)2 << (sizeof(__vaword)*8-start_offset*8-1)) - 1;
          if (end_offset <= sizeof(__vaword)) {
            /* 0 < end_offset ≤ sizeof(__vaword) */
            iret = (wordaddr[0] & mask0) >> (sizeof(__vaword)*8-end_offset*8);
          } else {
            /* sizeof(__vaword) < end_offset < 2*sizeof(__vaword), start_offset > 0 */
            iret = ((wordaddr[0] & mask0) << (end_offset*8-sizeof(__vaword)*8))
                   | (wordaddr[1] >> (2*sizeof(__vaword)*8-end_offset*8));
          }
        } else {
          /* Assign iret, iret2. */
          __vaword mask0 = ((__vaword)2 << (sizeof(__vaword)*8-start_offset*8-1)) - 1;
          if (end_offset <= 2*sizeof(__vaword)) {
            /* sizeof(__vaword) < end_offset ≤ 2*sizeof(__vaword) */
            iret = (wordaddr[0] & mask0) >> (2*sizeof(__vaword)*8-end_offset*8);
            iret2 = ((wordaddr[0] & mask0) << (end_offset*4-sizeof(__vaword)*4) << (end_offset*4-sizeof(__vaword)*4))
                    | (wordaddr[1] >> (2*sizeof(__vaword)*8-end_offset*8));
          } else {
            /* 2*sizeof(__vaword) < end_offset < 3*sizeof(__vaword), start_offset > 0 */
            iret = ((wordaddr[0] & mask0) << (end_offset*8-2*sizeof(__vaword)*8))
                   | (wordaddr[1] >> (3*sizeof(__vaword)*8-end_offset*8));
            iret2 = (wordaddr[1] << (end_offset*8-2*sizeof(__vaword)*8))
                    | (wordaddr[2] >> (3*sizeof(__vaword)*8-end_offset*8));
          }
        }
        #endif
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
