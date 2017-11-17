/* vacall function for hppa64 CPU */

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
         *	env	__asm__("%r31");
#endif

register __vaword arg1 __asm__("r26");
register __vaword arg2 __asm__("r25");
register __vaword arg3 __asm__("r24");
register __vaword arg4 __asm__("r23");
register __vaword arg5 __asm__("r22");
register __vaword arg6 __asm__("r21");
register __vaword arg7 __asm__("r20");
register __vaword arg8 __asm__("r19");

/*register float farg1 __asm__("fr4R");*/
/*register float farg2 __asm__("fr5R");*/
/*register float farg3 __asm__("fr6R");*/
/*register float farg4 __asm__("fr7R");*/
/*register float farg5 __asm__("fr8R");*/
/*register float farg6 __asm__("fr9R");*/
/*register float farg7 __asm__("fr10R");*/
/*register float farg8 __asm__("fr11R");*/

register double darg1 __asm__("fr4");
register double darg2 __asm__("fr5");
register double darg3 __asm__("fr6");
register double darg4 __asm__("fr7");
register double darg5 __asm__("fr8");
register double darg6 __asm__("fr9");
register double darg7 __asm__("fr10");
register double darg8 __asm__("fr11");

register __vaword iret __asm__("r28");
register __vaword iret2 __asm__("r29");

void /* the return type is variable, not void! */
vacall_receiver (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
                 __vaword word5, __vaword word6, __vaword word7, __vaword word8,
                 __vaword firstword)
{
  __va_alist list;
  /* Move the arguments passed in registers to their stack locations. */
  (&firstword)[-8] = word1;
  (&firstword)[-7] = word2;
  (&firstword)[-6] = word3;
  (&firstword)[-5] = word4;
  (&firstword)[-4] = word5;
  (&firstword)[-3] = word6;
  (&firstword)[-2] = word7;
  (&firstword)[-1] = word8;
  __asm__ __volatile__ ("fstw %%fr4R,%0" : : "m" (list.farg[0])); /* list.farg[0] = farg1; */
  __asm__ __volatile__ ("fstw %%fr5R,%0" : : "m" (list.farg[1])); /* list.farg[1] = farg2; */
  __asm__ __volatile__ ("fstw %%fr6R,%0" : : "m" (list.farg[2])); /* list.farg[2] = farg3; */
  __asm__ __volatile__ ("fstw %%fr7R,%0" : : "m" (list.farg[3])); /* list.farg[3] = farg4; */
  __asm__ __volatile__ ("fstw %%fr8R,%0" : : "m" (list.farg[4])); /* list.farg[4] = farg5; */
  __asm__ __volatile__ ("fstw %%fr9R,%0" : : "m" (list.farg[5])); /* list.farg[5] = farg6; */
  __asm__ __volatile__ ("fstw %%fr10R,%0" : : "m" (list.farg[6])); /* list.farg[6] = farg7; */
  __asm__ __volatile__ ("fstw %%fr11R,%0" : : "m" (list.farg[7])); /* list.farg[7] = farg8; */
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
  list.aptr = (long)(&firstword - 8);
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.memargptr = (long)&firstword;
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
    __asm__ __volatile__ ("fldw %0,%%fr4R" : : "m" (list.tmp._float)); /* farg1 = list.tmp._float; */
    iret = *(unsigned int *)&list.tmp._float;
  } else
  if (list.rtype == __VAdouble) {
    darg1 = list.tmp._double;
    iret = *(unsigned long*)&list.tmp._double;
  } else
  if (list.rtype == __VAvoidp) {
    iret = (long)list.tmp._ptr;
  } else
  if (list.rtype == __VAstruct) {
    if (list.flags & __VA_REGISTER_STRUCT_RETURN) {
      #if 0 /* Unoptimized */
      if (list.rsize == 1) {
        iret =   (__vaword)((unsigned char *) list.raddr)[0] << 56;
      } else
      if (list.rsize == 2) {
        iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
              | ((__vaword)((unsigned char *) list.raddr)[1] << 48);
      } else
      if (list.rsize == 3) {
        iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
              | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
              | ((__vaword)((unsigned char *) list.raddr)[2] << 40);
      } else
      if (list.rsize == 4) {
        iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
              | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
              | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
              | ((__vaword)((unsigned char *) list.raddr)[3] << 32);
      } else
      if (list.rsize == 5) {
        iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
              | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
              | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
              | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
              | ((__vaword)((unsigned char *) list.raddr)[4] << 24);
      } else
      if (list.rsize == 6) {
        iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
              | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
              | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
              | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
              | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
              | ((__vaword)((unsigned char *) list.raddr)[5] << 16);
      } else
      if (list.rsize == 7) {
        iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
              | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
              | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
              | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
              | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
              | ((__vaword)((unsigned char *) list.raddr)[5] << 16)
              | ((__vaword)((unsigned char *) list.raddr)[6] << 8);
      } else
      if (list.rsize >= 8 && list.rsize <= 16) {
        iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
              | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
              | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
              | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
              | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
              | ((__vaword)((unsigned char *) list.raddr)[5] << 16)
              | ((__vaword)((unsigned char *) list.raddr)[6] << 8)
              |  (__vaword)((unsigned char *) list.raddr)[7];
        if (list.rsize == 8) {
        } else
        if (list.rsize == 9) {
          iret2 =   (__vaword)((unsigned char *) list.raddr)[8] << 56;
        } else
        if (list.rsize == 10) {
          iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                 | ((__vaword)((unsigned char *) list.raddr)[9] << 48);
        } else
        if (list.rsize == 11) {
          iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                 | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                 | ((__vaword)((unsigned char *) list.raddr)[10] << 40);
        } else
        if (list.rsize == 12) {
          iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                 | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                 | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                 | ((__vaword)((unsigned char *) list.raddr)[11] << 32);
        } else
        if (list.rsize == 13) {
          iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                 | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                 | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                 | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                 | ((__vaword)((unsigned char *) list.raddr)[12] << 24);
        } else
        if (list.rsize == 14) {
          iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                 | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                 | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                 | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                 | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                 | ((__vaword)((unsigned char *) list.raddr)[13] << 16);
        } else
        if (list.rsize == 15) {
          iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                 | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                 | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                 | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                 | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                 | ((__vaword)((unsigned char *) list.raddr)[13] << 16)
                 | ((__vaword)((unsigned char *) list.raddr)[14] << 8);
        } else
        if (list.rsize == 16) {
          iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                 | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                 | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                 | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                 | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                 | ((__vaword)((unsigned char *) list.raddr)[13] << 16)
                 | ((__vaword)((unsigned char *) list.raddr)[14] << 8)
                 |  (__vaword)((unsigned char *) list.raddr)[15];
        }
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
          __vaword mask0 = - ((__vaword)1 << (sizeof(__vaword)*8-end_offset*8));
          iret = (wordaddr[0] & mask0) << (start_offset*8);
        } else {
          /* sizeof(__vaword) < end_offset < 2*sizeof(__vaword), start_offset > 0 */
          __vaword mask1 = - ((__vaword)1 << (2*sizeof(__vaword)*8-end_offset*8));
          iret = (wordaddr[0] << (start_offset*8)) | ((wordaddr[1] & mask1) >> (sizeof(__vaword)*8-start_offset*8));
        }
      } else {
        /* Assign iret, iret2. */
        if (end_offset <= 2*sizeof(__vaword)) {
          /* sizeof(__vaword) < end_offset ≤ 2*sizeof(__vaword) */
          __vaword mask1 = - ((__vaword)1 << (2*sizeof(__vaword)*8-end_offset*8));
          iret = (wordaddr[0] << (start_offset*8)) | ((wordaddr[1] & mask1) >> (sizeof(__vaword)*4-start_offset*4) >> (sizeof(__vaword)*4-start_offset*4));
          iret2 = (wordaddr[1] & mask1) << (start_offset*8);
        } else {
          /* 2*sizeof(__vaword) < end_offset < 3*sizeof(__vaword), start_offset > 0 */
          __vaword mask2 = - ((__vaword)1 << (3*sizeof(__vaword)*8-end_offset*8));
          iret = (wordaddr[0] << (start_offset*8)) | (wordaddr[1] >> (sizeof(__vaword)*8-start_offset*8));
          iret2 = (wordaddr[1] << (start_offset*8)) | ((wordaddr[2] & mask2) >> (sizeof(__vaword)*8-start_offset*8));
        }
      }
      #endif
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
