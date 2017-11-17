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
register void*	sp	__asm__("$sp");
register long	iarg0	__asm__("$4");
register long	iarg1	__asm__("$5");
register long	iarg2	__asm__("$6");
register long	iarg3	__asm__("$7");
register long	iarg4	__asm__("$8");
register long	iarg5	__asm__("$9");
register long	iarg6	__asm__("$10");
register long	iarg7	__asm__("$11");
register float	farg0	__asm__("$f12");
register float	farg1	__asm__("$f13");
register float	farg2	__asm__("$f14");
register float	farg3	__asm__("$f15");
register float	farg4	__asm__("$f16");
register float	farg5	__asm__("$f17");
register float	farg6	__asm__("$f18");
register float	farg7	__asm__("$f19");
register double	darg0	__asm__("$f12");
register double	darg1	__asm__("$f13");
register double	darg2	__asm__("$f14");
register double	darg3	__asm__("$f15");
register double	darg4	__asm__("$f16");
register double	darg5	__asm__("$f17");
register double	darg6	__asm__("$f18");
register double	darg7	__asm__("$f19");
register long	iret	__asm__("$2");
register long	iret2	__asm__("$3");
register float	fret	__asm__("$f0");
register float	fret2	__asm__("$f2");
register double	dret	__asm__("$f0");
register double	dret2	__asm__("$f2");

/* The ABI requires that the first 8 general-purpose argument words are
   being passed in registers, even if these words belong to a struct. No room
   is allocated for these register words on the stack by the caller, but the
   callee allocates room for them - at the right place in the stack frame,
   that is, above the usual {fp, retaddr} combo - if and only if they are part
   of a larger struct that extends to the stack and the address of this struct
   is taken. */
struct gpargsequence {
  __vaword word1; /* r4 */
  __vaword word2; /* r5 */
  __vaword word3; /* r6 */
  __vaword word4; /* r7 */
  __vaword word5; /* r8 */
  __vaword word6; /* r9 */
  __vaword word7; /* r10 */
  __vaword word8; /* r11 */
  __vaword firststackword;
};

#ifdef REENTRANT
static
#endif
void /* the return type is variable, not void! */
vacall_receiver (struct gpargsequence gpargs)
{
  __va_alist list;
  list.darg[0] = darg0;
  list.darg[1] = darg1;
  list.darg[2] = darg2;
  list.darg[3] = darg3;
  list.darg[4] = darg4;
  list.darg[5] = darg5;
  list.darg[6] = darg6;
  list.darg[7] = darg7;
  list.farg[0] = farg0;
  list.farg[1] = farg1;
  list.farg[2] = farg2;
  list.farg[3] = farg3;
  list.farg[4] = farg4;
  list.farg[5] = farg5;
  list.farg[6] = farg6;
  list.farg[7] = farg7;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)&gpargs;
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.anum = 0;
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
      if (list.flags & __VA_GCC_STRUCT_RETURN) {
        /* gcc returns structs of size 1,2,4,8 in registers. */
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
        }
      } else {
        /* cc returns structs of size <= 16 in registers. */
        /* Maybe this big if cascade could be replaced with
         * if (list.rsize > 0 && list.rsize <= 16)
         *   __asm__ ("ldl $2,%0 ; ldr $2,%1"
         *            : : "m" (((unsigned char *) list.raddr)[0]),
         *                "m" (((unsigned char *) list.raddr)[7]));
         */
        if (list.rsize > 0 && list.rsize <= 16) {
          #if 0 /* Unoptimized */
          if (list.rsize == 1) {
            #if defined(_MIPSEL)
            iret =   (__vaword)((unsigned char *) list.raddr)[0];
            #else
            iret =   (__vaword)((unsigned char *) list.raddr)[0] << 56;
            #endif
          } else
          if (list.rsize == 2) {
            #if defined(_MIPSEL)
            iret =  ((__vaword)((unsigned char *) list.raddr)[0])
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 8);
            #else
            iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 48);
            #endif
          } else
          if (list.rsize == 3) {
            #if defined(_MIPSEL)
            iret =  ((__vaword)((unsigned char *) list.raddr)[0])
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 8)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 16);
            #else
            iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 40);
            #endif
          } else
          if (list.rsize == 4) {
            #if defined(_MIPSEL)
            iret =  ((__vaword)((unsigned char *) list.raddr)[0])
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 8)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 24);
            #else
            iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 32);
            #endif
          } else
          if (list.rsize == 5) {
            #if defined(_MIPSEL)
            iret =  ((__vaword)((unsigned char *) list.raddr)[0])
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 8)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[4] << 32);
            #else
            iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[4] << 24);
            #endif
          } else
          if (list.rsize == 6) {
            #if defined(_MIPSEL)
            iret =  ((__vaword)((unsigned char *) list.raddr)[0])
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 8)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[4] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[5] << 40);
            #else
            iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[5] << 16);
            #endif
          } else
          if (list.rsize == 7) {
            #if defined(_MIPSEL)
            iret =  ((__vaword)((unsigned char *) list.raddr)[0])
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 8)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[4] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[5] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[6] << 48);
            #else
            iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[5] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[6] << 8);
            #endif
          } else
          if (list.rsize >= 8 && list.rsize <= 16) {
            #if defined(_MIPSEL)
            iret =  ((__vaword)((unsigned char *) list.raddr)[0])
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 8)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[4] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[5] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[6] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[7] << 56);
            #else
            iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[5] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[6] << 8)
                  |  (__vaword)((unsigned char *) list.raddr)[7];
            #endif
            /* Maybe this big if cascade could be replaced with
             * if (list.rsize > 8 && list.rsize <= 16)
             *   __asm__ ("ldl $3,%0 ; ldr $3,%1"
             *            : : "m" (((unsigned char *) list.raddr)[8]),
             *                "m" (((unsigned char *) list.raddr)[15]));
             */
            if (list.rsize == 8) {
            } else
            if (list.rsize == 9) {
              #if defined(_MIPSEL)
              iret2 =   (__vaword)((unsigned char *) list.raddr)[8];
              #else
              iret2 =   (__vaword)((unsigned char *) list.raddr)[8] << 56;
              #endif
            } else
            if (list.rsize == 10) {
              #if defined(_MIPSEL)
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8])
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 8);
              #else
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 48);
              #endif
            } else
            if (list.rsize == 11) {
              #if defined(_MIPSEL)
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8])
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 8)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 16);
              #else
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 40);
              #endif
            } else
            if (list.rsize == 12) {
              #if defined(_MIPSEL)
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8])
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 8)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 16)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 24);
              #else
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 32);
              #endif
            } else
            if (list.rsize == 13) {
              #if defined(_MIPSEL)
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8])
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 8)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 16)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 24)
                     | ((__vaword)((unsigned char *) list.raddr)[12] << 32);
              #else
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                     | ((__vaword)((unsigned char *) list.raddr)[12] << 24);
              #endif
            } else
            if (list.rsize == 14) {
              #if defined(_MIPSEL)
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8])
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 8)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 16)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 24)
                     | ((__vaword)((unsigned char *) list.raddr)[12] << 32)
                     | ((__vaword)((unsigned char *) list.raddr)[13] << 40);
              #else
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                     | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                     | ((__vaword)((unsigned char *) list.raddr)[13] << 16);
              #endif
            } else
            if (list.rsize == 15) {
              #if defined(_MIPSEL)
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8])
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 8)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 16)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 24)
                     | ((__vaword)((unsigned char *) list.raddr)[12] << 32)
                     | ((__vaword)((unsigned char *) list.raddr)[13] << 40)
                     | ((__vaword)((unsigned char *) list.raddr)[14] << 48);
              #else
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                     | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                     | ((__vaword)((unsigned char *) list.raddr)[13] << 16)
                     | ((__vaword)((unsigned char *) list.raddr)[14] << 8);
              #endif
            } else
            if (list.rsize == 16) {
              #if defined(_MIPSEL)
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8])
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 8)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 16)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 24)
                     | ((__vaword)((unsigned char *) list.raddr)[12] << 32)
                     | ((__vaword)((unsigned char *) list.raddr)[13] << 40)
                     | ((__vaword)((unsigned char *) list.raddr)[14] << 48)
                     | ((__vaword)((unsigned char *) list.raddr)[15] << 56);
              #else
              iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                     | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                     | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                     | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                     | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                     | ((__vaword)((unsigned char *) list.raddr)[13] << 16)
                     | ((__vaword)((unsigned char *) list.raddr)[14] << 8)
                     |  (__vaword)((unsigned char *) list.raddr)[15];
              #endif
            }
          }
          #else /* Optimized: fewer conditional jumps, fewer memory accesses */
          uintptr_t count = list.rsize; /* > 0, ≤ 2*sizeof(__vaword) */
          __vaword* wordaddr = (__vaword*)((uintptr_t)list.raddr & ~(uintptr_t)(sizeof(__vaword)-1));
          uintptr_t start_offset = (uintptr_t)list.raddr & (uintptr_t)(sizeof(__vaword)-1); /* ≥ 0, < sizeof(__vaword) */
          uintptr_t end_offset = start_offset + count; /* > 0, < 3*sizeof(__vaword) */
          #if defined(_MIPSEL)
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
          #else
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
          #endif
        }
        if (list.flags & __VA_REGISTER_FLOATSTRUCT_RETURN) {
          if (list.rsize == sizeof(float)) {
            fret = *(float*)list.raddr;
          } else
          if (list.rsize == 2*sizeof(float)) {
            fret = *(float*)list.raddr;
            fret2 = *(float*)((char*)list.raddr + 4);
          }
        }
        if (list.flags & __VA_REGISTER_DOUBLESTRUCT_RETURN) {
          if (list.rsize == sizeof(double)) {
            dret = *(double*)list.raddr;
          } else
          if (list.rsize == 2*sizeof(double)) {
            dret = *(double*)list.raddr;
            dret2 = *(double*)((char*)list.raddr + 8);
          }
        }
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
