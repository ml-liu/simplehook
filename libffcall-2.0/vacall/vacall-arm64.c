/* vacall function for arm64 (a.k.a. aarch64) CPU */

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
         *		env	__asm__("x18");
#endif

register __vaword* sret __asm__("x8");  /* structure return pointer */

register __vaword iarg1 __asm__("x0");
register __vaword iarg2 __asm__("x1");
register __vaword iarg3 __asm__("x2");
register __vaword iarg4 __asm__("x3");
register __vaword iarg5 __asm__("x4");
register __vaword iarg6 __asm__("x5");
register __vaword iarg7 __asm__("x6");
register __vaword iarg8 __asm__("x7");

register float farg1 __asm__("s0");
register float farg2 __asm__("s1");
register float farg3 __asm__("s2");
register float farg4 __asm__("s3");
register float farg5 __asm__("s4");
register float farg6 __asm__("s5");
register float farg7 __asm__("s6");
register float farg8 __asm__("s7");

register double darg1 __asm__("d0");
register double darg2 __asm__("d1");
register double darg3 __asm__("d2");
register double darg4 __asm__("d3");
register double darg5 __asm__("d4");
register double darg6 __asm__("d5");
register double darg7 __asm__("d6");
register double darg8 __asm__("d7");

register __vaword iret  __asm__("x0");
register __vaword iret2 __asm__("x1");
register float  fret __asm__("s0");
register double dret __asm__("d0");

#ifdef REENTRANT
static
#endif
void /* the return type is variable, not void! */
vacall_receiver (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
                 __vaword word5, __vaword word6, __vaword word7, __vaword word8,
                 __vaword firstword)
{
  __va_alist list;
  /* Move the arguments passed in registers to temp storage. */
  list.iarg[0] = iarg1;
  list.iarg[1] = iarg2;
  list.iarg[2] = iarg3;
  list.iarg[3] = iarg4;
  list.iarg[4] = iarg5;
  list.iarg[5] = iarg6;
  list.iarg[6] = iarg7;
  list.iarg[7] = iarg8;
  list.farg[0] = farg1;
  list.farg[1] = farg2;
  list.farg[2] = farg3;
  list.farg[3] = farg4;
  list.farg[4] = farg5;
  list.farg[5] = farg6;
  list.farg[6] = farg7;
  list.farg[7] = farg8;
  list.darg[0] = darg1;
  list.darg[1] = darg2;
  list.darg[2] = darg3;
  list.darg[3] = darg4;
  list.darg[4] = darg5;
  list.darg[5] = darg6;
  list.darg[6] = darg7;
  list.darg[7] = darg8;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)&firstword;
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.structraddr = sret;
  list.ianum = 0;
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
  if (list.rtype == __VAlong || list.rtype == __VAlonglong) {
    iret = list.tmp._long;
  } else
  if (list.rtype == __VAulong || list.rtype == __VAulonglong) {
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
    /* normal struct return convention */
    if (list.flags & __VA_REGISTER_STRUCT_RETURN) {
      /* Return structs of size <= 16 in registers. */
      if (list.rsize > 0 && list.rsize <= 16) {
        #if 0 /* Unoptimized */
        iret = (__vaword)((unsigned char *) list.raddr)[0];
        if (list.rsize >= 2)
          iret |= (__vaword)((unsigned char *) list.raddr)[1] << 8;
        if (list.rsize >= 3)
          iret |= (__vaword)((unsigned char *) list.raddr)[2] << 16;
        if (list.rsize >= 4)
          iret |= (__vaword)((unsigned char *) list.raddr)[3] << 24;
        if (list.rsize >= 5)
          iret |= (__vaword)((unsigned char *) list.raddr)[4] << 32;
        if (list.rsize >= 6)
          iret |= (__vaword)((unsigned char *) list.raddr)[5] << 40;
        if (list.rsize >= 7)
          iret |= (__vaword)((unsigned char *) list.raddr)[6] << 48;
        if (list.rsize >= 8)
          iret |= (__vaword)((unsigned char *) list.raddr)[7] << 56;
        if (list.rsize >= 9) {
          iret2 = (__vaword)((unsigned char *) list.raddr)[8];
          if (list.rsize >= 10)
            iret2 |= (__vaword)((unsigned char *) list.raddr)[9] << 8;
          if (list.rsize >= 11)
            iret2 |= (__vaword)((unsigned char *) list.raddr)[10] << 16;
          if (list.rsize >= 12)
            iret2 |= (__vaword)((unsigned char *) list.raddr)[11] << 24;
          if (list.rsize >= 13)
            iret2 |= (__vaword)((unsigned char *) list.raddr)[12] << 32;
          if (list.rsize >= 14)
            iret2 |= (__vaword)((unsigned char *) list.raddr)[13] << 40;
          if (list.rsize >= 15)
            iret2 |= (__vaword)((unsigned char *) list.raddr)[14] << 48;
          if (list.rsize >= 16)
            iret2 |= (__vaword)((unsigned char *) list.raddr)[15] << 56;
        }
        #else /* Optimized: fewer conditional jumps, fewer memory accesses */
        uintptr_t count = list.rsize; /* > 0, ≤ 2*sizeof(__vaword) */
        __vaword* wordaddr = (__vaword*)((uintptr_t)list.raddr & ~(uintptr_t)(sizeof(__vaword)-1));
        uintptr_t start_offset = (uintptr_t)list.raddr & (uintptr_t)(sizeof(__vaword)-1); /* ≥ 0, < sizeof(__vaword) */
        uintptr_t end_offset = start_offset + count; /* > 0, < 3*sizeof(__vaword) */
        if (count <= sizeof(__vaword)) {
          /* Assign iret. */
          if (end_offset <= sizeof(__vaword)) {
            /* 0 < end_offset ≤ sizeof(__vaword) */
            __vaword mask0 = ((__vaword)2 << (end_offset*8-1)) - 1;
            iret = (wordaddr[0] & mask0) >> (start_offset*8);
          } else {
            /* sizeof(__vaword) < end_offset < 2*sizeof(__vaword), start_offset > 0 */
            __vaword mask1 = ((__vaword)2 << (end_offset*8-sizeof(__vaword)*8-1)) - 1;
            iret = (wordaddr[0] >> (start_offset*8)) | ((wordaddr[1] & mask1) << (sizeof(__vaword)*8-start_offset*8));
          }
        } else {
          /* Assign iret, iret2. */
          if (end_offset <= 2*sizeof(__vaword)) {
            /* sizeof(__vaword) < end_offset ≤ 2*sizeof(__vaword) */
            __vaword mask1 = ((__vaword)2 << (end_offset*8-sizeof(__vaword)*8-1)) - 1;
            iret = (wordaddr[0] >> (start_offset*8)) | ((wordaddr[1] & mask1) << (sizeof(__vaword)*4-start_offset*4) << (sizeof(__vaword)*4-start_offset*4));
            iret2 = (wordaddr[1] & mask1) >> (start_offset*8);
          } else {
            /* 2*sizeof(__vaword) < end_offset < 3*sizeof(__vaword), start_offset > 0 */
            __vaword mask2 = ((__vaword)2 << (end_offset*8-2*sizeof(__vaword)*8-1)) - 1;
            iret = (wordaddr[0] >> (start_offset*8)) | (wordaddr[1] << (sizeof(__vaword)*8-start_offset*8));
            iret2 = (wordaddr[1] >> (start_offset*8)) | ((wordaddr[2] & mask2) << (sizeof(__vaword)*8-start_offset*8));
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
