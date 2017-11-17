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

#ifndef _VACALL_INTERNAL_H
#define _VACALL_INTERNAL_H

/* Get intptr_t, uintptr_t. */
#include "ffcall-stdint.h"

/* Include the public definitions,  */
#ifndef REENTRANT
#include "vacall.h"
#else
#include "vacall_r.h"
#endif


/* The platform indicator symbols (__i386__, etc.) come from
   - "config.h" when compiling vacall-libapi.c,
   - the GCC command line options when compiling vacall-$(CPU).c.
 */

/* These two variants of powerpc ABIs are quite different. */
#if defined(__powerpc__) && !defined(__powerpc64__)
#if defined(_AIX) || (defined(__MACH__) && defined(__APPLE__))
#define __powerpc_aix__ 1
#else
#define __powerpc_sysv4__ 1
#endif
#endif

/* The Unix and Windows variants of x86_64 ABIs are quite different. */
#if defined(__x86_64__)
#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#define __x86_64_ms__ 1
#else
#define __x86_64_sysv__ 1
#endif
#endif


/* Max # words in temporary structure storage.
 */
#ifndef __VA_ALIST_WORDS
#define __VA_ALIST_WORDS  256
#endif

/*
 * Definition of the ‘__va_alist’ type.
 */
/* Note: This struct must not contain members of type 'long' or 'unsigned long',
   because in the mingw port we use precompiled code that assumes 'long' is
   64-bit whereas avcall-libapi.c is then compiled by a compiler that has a
   32-bit 'long' type. */
typedef struct vacall_alist
{
  /* some va_... macros need these flags */
  int            flags;
  /* temporary storage for return value */
#if defined(__i386__) || defined(__arm__) || defined(__armhf__) || (defined(__powerpc__) && !defined(__powerpc64__) && defined(__MACH__) && defined(__APPLE__))
  /* Filler word, needed if the numbers of words up to now in this structure */
  /* is odd.                                                                 */
  /* - On MSVC, alignof(double) = 8, but normally on i386 it is = 4.         */
  /* - On ARM, GCC 3.1 produces code for an ABI where alignof(double) = 4    */
  /*   and alignof(long long) = 4. But in the newer AAPCS ABI, these         */
  /*   alignments are 8.                                                     */
  /* - On Mac OS X, the Apple compiler has alignof(double) = 8 whereas the   */
  /*   standard GCC has alignof(double) = 4.                                 */
  __vaword       filler1;
#endif
  union {
    char                _char;
    signed char         _schar;
    unsigned char       _uchar;
    short               _short;
    unsigned short      _ushort;
    int                 _int;
    unsigned int        _uint;
    long                _long;
    unsigned long       _ulong;
#if !(defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__hppa64__) || defined(__arm64__) || defined(__powerpc64__) || defined(__ia64__))
    long long           _longlong;
    unsigned long long  _ulonglong;
#endif
    float               _float;
    double              _double;
    void*               _ptr;
    __vaword            _words[2];
  }              tmp;
  /* current pointer into the argument array */
  uintptr_t      aptr;
  /* structure return pointer, return type, return type size */
  void*          raddr;
  enum __VAtype  rtype;
  uintptr_t      rsize;
#if defined(__i386__) || defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__hppa__) || defined(__hppa64__) || defined(__arm64__) || defined(__ia64__)
  void*          structraddr;
#endif
#if (defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)) || defined(__alpha__) || defined(__hppa__) || defined(__hppa64__)
  uintptr_t      memargptr;
#endif
#if defined(__alpha__)
  long           farg_offset;
  double         farg[6];
#endif
#if defined(__hppa__) && !defined(__hppa64__)
  long           farg_offset;
  long           darg_offset;
  float          farg[4];
  double         darg[2];
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
  unsigned int   anum;
#define __VA_FARG_NUM 2
  unsigned int   fanum;
  float          farg[__VA_FARG_NUM];
  double         darg[__VA_FARG_NUM];
#endif
#if defined(__mipsn32__) || defined(__mips64__)
  int            anum;
#define __VA_FARG_NUM 8
  float          farg[__VA_FARG_NUM];
  double         darg[__VA_FARG_NUM];
#endif
#if defined(__sparc64__)
  int            anum;
  float          farg[16];
  double         darg[16];
#endif
#if defined(__hppa64__)
#define __VA_FARG_NUM 8
  float          farg[__VA_FARG_NUM];
  double         darg[__VA_FARG_NUM];
#endif
#if defined(__armhf__)
#define __VA_IARG_NUM 4
  /* The first __AV_IARG_NUM integer arguments are passed in registers, even if
     some floating-point arguments have already been allocated on the stack. */
  __vaword*      iarg;
  unsigned int   ianum;
  unsigned int   fanum;
  float          farg[16];
  double         darg[8];
#endif
#if defined(__arm64__)
#define __VA_IARG_NUM 8
  unsigned int   ianum;
  __vaword       iarg[__VA_IARG_NUM];
#define __VA_FARG_NUM 8
  unsigned int   fanum;
  float          farg[__VA_FARG_NUM];
  double         darg[__VA_FARG_NUM];
#endif
#if defined(__powerpc__) || defined(__powerpc64__)
#if defined(__powerpc_sysv4__)
#define __VA_IARG_NUM 8
  unsigned int   ianum;
  __vaword       iarg[__VA_IARG_NUM];
#define __VA_FARG_NUM 8
#else
#define __VA_FARG_NUM 13
#endif
  unsigned int   fanum;
  double         farg[__VA_FARG_NUM];
#endif
#if defined(__ia64__)
  __vaword*      saptr;
#define __VA_FARG_NUM 8
  unsigned int   fanum;
  double         farg[__VA_FARG_NUM];
#endif
#if defined(__x86_64_sysv__)
#define __VA_FARG_NUM 8
  unsigned int   fanum;
  double         farg[__VA_FARG_NUM];
#define __VA_IARG_NUM 6
  unsigned int   ianum;
  __vaword       iarg[__VA_IARG_NUM];
#endif
#if defined(__x86_64_ms__)
  int            anum;
#define __VA_FARG_NUM 4
  float          farg[__VA_FARG_NUM];
  double         darg[__VA_FARG_NUM];
#endif
#if defined(__s390__) && !defined(__s390x__)
#define __VA_IARG_NUM 5
  unsigned int   ianum;
  __vaword       iarg[5];
#define __VA_FARG_NUM 2
  unsigned int   fanum;
  float          farg[__VA_FARG_NUM];
  double         darg[__VA_FARG_NUM];
#endif
#if defined(__s390x__)
#define __VA_IARG_NUM 5
  unsigned int   ianum;
  __vaword       iarg[__VA_IARG_NUM];
#define __VA_FARG_NUM 4
  unsigned int   fanum;
  float          farg[__VA_FARG_NUM];
  double         darg[__VA_FARG_NUM];
#endif
} __va_alist;


/* Avoid macro redefinition warnings on DragonFly BSD. */
#undef __va_start
#undef __va_arg


/*
 * Definition of the va_start_xxx macros.
 */

#define __va_start(LIST,RETTYPE,FLAGS)  \
  ((LIST)->flags = (FLAGS),						\
   (LIST)->rtype = (RETTYPE)						\
  )

/*
 * va_start_struct: Preparing structure return.
 */
#define __va_start_struct(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE,FLAGS)  \
  (__va_start(LIST,__VAstruct,FLAGS),					\
   (LIST)->rsize = (TYPE_SIZE),						\
   ((LIST)->flags & __VA_SUNPROCC_STRUCT_RETURN				\
    ? __va_start_struct2(LIST)						\
    : ((LIST)->flags & __VA_SUNCC_STRUCT_RETURN				\
       ? ((TYPE_SIZE) <= sizeof(vacall_struct_buffer) || (vacall_error_struct_too_large(TYPE_SIZE), 0), \
          (LIST)->raddr = &vacall_struct_buffer,			\
          0								\
         )								\
       : (((LIST)->flags & __VA_SMALL_STRUCT_RETURN)			\
          && __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)	\
          ? ((LIST)->raddr = &(LIST)->tmp,				\
             __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE) \
            )								\
          : __va_start_struct2(LIST)					\
  ))  )  )
/* Determines whether a structure is returned in registers,
 * depending on its size and its word-splittable flag.
 */
#if (defined(__i386__) && defined(_WIN32))
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4		\
   || ((TYPE_SIZE) == 8							\
       && (((LIST)->flags & __VA_MSVC_STRUCT_RETURN)			\
           || ((TYPE_SPLITTABLE)					\
               && ((LIST)->flags & __VA_GCC_STRUCT_RETURN)		\
  )   )   )   )
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN, 0)
#endif
#if (defined(__i386__) && !defined(_WIN32)) || defined(__m68k__) || (defined(__powerpc__) && !defined(__powerpc64__)) || (defined(__s390__) && !defined(__s390x__))
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4		\
   || ((TYPE_SIZE) == 8 && (TYPE_SPLITTABLE)				\
       && ((LIST)->flags & __VA_GCC_STRUCT_RETURN)			\
  )   )
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__arm__) || defined(__armhf__)
/* structs of size 3 also will be returned in register */
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 4)
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__alpha__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8	\
   || ((TYPE_SIZE) == 16 && (TYPE_SPLITTABLE)				\
       && ((LIST)->flags & __VA_GCC_STRUCT_RETURN)			\
  )   )
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__hppa__) && !defined(__hppa64__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 8)
/* Test __VA_SMALL_STRUCT_RETURN at run time. */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  0
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__) || (defined(__sparc__) && !defined(__sparc64__))
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4)
/* Test __VA_SMALL_STRUCT_RETURN instead of __VA_REGISTER_STRUCT_RETURN. */
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->anum++,							\
   0									\
  )
#else
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  0
#endif
#endif
#if defined(__mipsn32__) || defined(__mips64__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((LIST)->flags & __VA_GCC_STRUCT_RETURN				\
   ? ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8) \
   : ((TYPE_SIZE) <= 16)						\
  )
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers. Also turn on
 * __VA_REGISTER_FLOATSTRUCT_RETURN or __VA_REGISTER_DOUBLESTRUCT_RETURN if
 * the struct will be returned in floating-point registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN,				\
   (TYPE_ALIGN) == sizeof(float) && (TYPE_SPLITTABLE)				\
    && ((TYPE_SIZE) == sizeof(float) || (TYPE_SIZE) == 2*sizeof(float))		\
    && ((LIST)->flags |= __VA_REGISTER_FLOATSTRUCT_RETURN),			\
   (TYPE_ALIGN) == sizeof(double) && (TYPE_SPLITTABLE)				\
    && ((TYPE_SIZE) == sizeof(double) || (TYPE_SIZE) == 2*sizeof(double))	\
    && ((LIST)->flags |= __VA_REGISTER_DOUBLESTRUCT_RETURN),			\
   0)
#endif
#if (defined(__powerpc64__) && !defined(__powerpc64_elfv2__)) || defined(__s390x__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  0
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  0
#endif
#if defined(__sparc64__) || defined(__ia64__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 32)
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN,			\
   0)
#endif
#if defined(__hppa64__) || defined(__arm64__) || (defined(__powerpc64__) && defined(__powerpc64_elfv2__)) || defined(__x86_64_sysv__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 16)
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN,			\
   0)
#endif
#if defined(__x86_64_ms__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8)
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN,			\
   0)
#endif
/*
 * Preparing structure return in memory.
 */
#if defined(__i386__) || defined(__alpha__) || (defined(__arm__) && !defined(__armhf__)) || defined(__powerpc_aix__) || defined(__powerpc64__)
/* Return structure pointer is passed as first arg. */
#define __va_start_struct2(LIST)  \
  ((LIST)->raddr = *(void* *)((LIST)->aptr),				\
   (LIST)->aptr += sizeof(void*),					\
   0									\
  )
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__) || defined(__x86_64_ms__)
/* Return structure pointer is passed as first arg. */
#define __va_start_struct2(LIST)  \
  ((LIST)->raddr = *(void* *)((LIST)->aptr),				\
   (LIST)->aptr += sizeof(void*),					\
   (LIST)->anum++,							\
   0									\
  )
#endif
#if defined(__armhf__)
/* Return structure pointer is passed as first arg. */
#define __va_start_struct2(LIST)  \
  ((LIST)->raddr = (void*)(LIST)->iarg[(LIST)->ianum],			\
   (LIST)->ianum++,							\
   0									\
  )
#endif
#if defined(__powerpc_sysv4__) || defined(__x86_64_sysv__) || defined(__s390__) || defined(__s390x__)
/* Return structure pointer is passed as first arg. */
#define __va_start_struct2(LIST)  \
  ((LIST)->raddr = (void*)((LIST)->iarg[(LIST)->ianum++]),		\
   0									\
  )
#endif
#if defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__hppa__) || defined(__hppa64__) || defined(__arm64__) || defined(__ia64__)
/* Return structure pointer is passed in a special register. */
#define __va_start_struct2(LIST)  \
  ((LIST)->raddr = (LIST)->structraddr, 0)
#endif


/*
 * Definition of the va_arg_xxx macros.
 */

/* Padding of non-struct arguments. */
#define __va_argsize(TYPE_SIZE)  \
  (((TYPE_SIZE) + sizeof(__vaword)-1) & -(intptr_t)sizeof(__vaword))
#if defined(__i386__) || defined(__m68k__) || (defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__alpha__) || (defined(__arm__) && !defined(__armhf__)) || defined(__arm64__) || defined(__powerpc_aix__) || defined(__powerpc64__) || defined(__ia64__) || defined(__x86_64_sysv__) || defined(__s390__) || defined(__s390x__)
/* args grow up */
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - __va_argsize(TYPE_SIZE)				\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - ((TYPE_SIZE) < sizeof(__vaword)			\
		   ? (TYPE_SIZE)					\
		   : __va_argsize(TYPE_SIZE)				\
		  )							\
  )
#endif
#if defined(__armhf__)
/* args grow up */
/* small structures < 1 word are adjusted depending on compiler */
/* the first __VA_IARG_NUM argument words are passed in registers */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (((LIST)->ianum + ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword) <= __VA_IARG_NUM \
    ? ((LIST)->ianum += __va_argsize(TYPE_SIZE) / sizeof(__vaword),	\
       (char*)&(LIST)->iarg[(LIST)->ianum]				\
      )									\
    : (((LIST)->aptr == (uintptr_t)&(LIST)->iarg[__VA_IARG_NUM]		\
        ? /* split case */						\
          ((LIST)->aptr = (uintptr_t)&(LIST)->iarg[(LIST)->ianum] + __va_argsize(TYPE_SIZE), \
           0)								\
        : ((LIST)->aptr += __va_argsize(TYPE_SIZE),			\
           0)),								\
       (LIST)->ianum = __VA_IARG_NUM,					\
       (char*)(LIST)->aptr						\
   )  )									\
   - __va_argsize(TYPE_SIZE)						\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (((LIST)->ianum + ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword) <= __VA_IARG_NUM \
    ? ((LIST)->ianum += __va_argsize(TYPE_SIZE) / sizeof(__vaword),	\
       (char*)&(LIST)->iarg[(LIST)->ianum]				\
      )									\
    : (((LIST)->aptr == (uintptr_t)&(LIST)->iarg[__VA_IARG_NUM]		\
        ? /* split case */						\
          ((LIST)->aptr = (uintptr_t)&(LIST)->iarg[(LIST)->ianum] + __va_argsize(TYPE_SIZE), \
           0)								\
        : ((LIST)->aptr += __va_argsize(TYPE_SIZE),			\
           0)),								\
       (LIST)->ianum = __VA_IARG_NUM,					\
       (char*)(LIST)->aptr						\
   )  )									\
   - ((TYPE_SIZE) < sizeof(__vaword)					\
      ? (TYPE_SIZE)							\
      : __va_argsize(TYPE_SIZE)						\
     )									\
  )
#endif
#if defined(__powerpc_sysv4__)
/* args grow up */
/* small structures < 1 word are adjusted depending on compiler */
/* the first __VA_IARG_NUM argument words are passed in registers */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (((LIST)->ianum + ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword) <= __VA_IARG_NUM \
    ? ((LIST)->ianum += __va_argsize(TYPE_SIZE) / sizeof(__vaword),	\
       (char*)&(LIST)->iarg[(LIST)->ianum]				\
      )									\
    : ((LIST)->aptr += __va_argsize(TYPE_SIZE),				\
       (char*)(LIST)->aptr						\
   )  )									\
   - __va_argsize(TYPE_SIZE)						\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (((LIST)->ianum + ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword) <= __VA_IARG_NUM \
    ? ((LIST)->ianum += __va_argsize(TYPE_SIZE) / sizeof(__vaword),	\
       (char*)&(LIST)->iarg[(LIST)->ianum]				\
      )									\
    : ((LIST)->aptr += __va_argsize(TYPE_SIZE),				\
       (char*)(LIST)->aptr						\
   )  )									\
   - ((TYPE_SIZE) < sizeof(__vaword)					\
      ? (TYPE_SIZE)							\
      : __va_argsize(TYPE_SIZE)						\
     )									\
  )
#endif
#if defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__) || defined(__x86_64_ms__)
/* args grow up */
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->anum += __va_argsize(TYPE_SIZE)/sizeof(__vaword),		\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - __va_argsize(TYPE_SIZE)				\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->anum += __va_argsize(TYPE_SIZE)/sizeof(__vaword),		\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - ((TYPE_SIZE) < sizeof(__vaword)			\
		   ? (TYPE_SIZE)					\
		   : __va_argsize(TYPE_SIZE)				\
		  )							\
  )
#endif
#if defined(__hppa__) && !defined(__hppa64__)
/* args grow down */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->aptr = (LIST)->aptr - __va_argsize(TYPE_SIZE),		\
   ((TYPE_SIZE) > 4 && ((LIST)->aptr &= -8)),				\
   (LIST)->aptr								\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->aptr = (LIST)->aptr - __va_argsize(TYPE_SIZE),		\
   ((TYPE_SIZE) > 4 && ((LIST)->aptr &= -8)),				\
   (LIST)->aptr + ((-(TYPE_SIZE)) & 3)					\
  )
#endif
#if defined(__hppa64__)
/* args grow up */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (((TYPE_SIZE) > 8 && ((LIST)->aptr = (((LIST)->aptr +15) & -16))),	\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - __va_argsize(TYPE_SIZE)				\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (((TYPE_SIZE) > 8 && ((LIST)->aptr = (((LIST)->aptr +15) & -16))),	\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - ((TYPE_SIZE) < sizeof(__vaword)			\
		   ? (TYPE_SIZE)					\
		   : __va_argsize(TYPE_SIZE)				\
		  )							\
  )
#endif
#if defined(__i386__) || ((defined(__mipsn32__) || defined(__mips64__)) && defined(_MIPSEL)) || defined(__alpha__) || ((defined(__arm__) || defined(__armhf__)) && defined(__ARMEL__)) || defined(__ia64__) || (defined(__powerpc64__) && defined(_LITTLE_ENDIAN)) || defined(__x86_64_ms__)
/* little endian -> small args < 1 word are adjusted to the left */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)
#endif
#if defined(__m68k__) || ((defined(__mipsn32__) || defined(__mips64__)) && defined(_MIPSEB)) || defined(__sparc__) || defined(__sparc64__) || defined(__hppa__) || defined(__hppa64__) || ((defined(__arm__) || defined(__armhf__)) && !defined(__ARMEL__)) || (defined(__powerpc__) && !defined(__powerpc64__)) || (defined(__powerpc64__) && defined(_BIG_ENDIAN))
/* big endian -> small args < 1 word are adjusted to the right */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (void*)__va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
#ifdef _MIPSEB
/* big endian -> small args < 1 word are adjusted to the right */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->anum++,							\
   (void*)__va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN))
#else /* _MIPSEL */
/* little endian -> small args < 1 word are adjusted to the left */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->anum++,							\
   (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN))
#endif
#endif
#if defined(__arm64__)
/* the first __VA_IARG_NUM argument words are passed in registers */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->ianum + ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword) <= __VA_IARG_NUM \
   ? ((LIST)->ianum += ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword), \
      &(LIST)->iarg[(LIST)->ianum - ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword)] \
     )									\
   : (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  )
#endif
#if defined(__x86_64_sysv__)
/* the first __VA_IARG_NUM argument words are passed in registers */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (((TYPE_SIZE) <= 2*sizeof(__vaword)					\
    && (LIST)->ianum + ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword) <= __VA_IARG_NUM) \
   ? ((LIST)->ianum += ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword), \
      &(LIST)->iarg[(LIST)->ianum - ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword)] \
     )									\
   : (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  )
#endif
#if defined(__s390__) || defined(__s390x__)
/* the first __VA_IARG_NUM argument words are passed in registers */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->ianum + ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword) <= __VA_IARG_NUM \
   ? ((LIST)->ianum += ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword), \
      (void*)((uintptr_t)&(LIST)->iarg[(LIST)->ianum] - (TYPE_SIZE))	\
     )									\
   : ((LIST)->ianum = __VA_IARG_NUM,					\
      (void*)__va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  )  )
#endif
#define __va_arg(LIST,TYPE)  \
  *(TYPE*)__va_arg_adjusted(LIST,sizeof(TYPE),__VA_alignof(TYPE))

/* Integer arguments. */

#define _va_arg_char(LIST)	__va_arg(LIST,char)
#define _va_arg_schar(LIST)	__va_arg(LIST,signed char)
#define _va_arg_uchar(LIST)	__va_arg(LIST,unsigned char)
#define _va_arg_short(LIST)	__va_arg(LIST,short)
#define _va_arg_ushort(LIST)	__va_arg(LIST,unsigned short)
#define _va_arg_int(LIST)	__va_arg(LIST,int)
#define _va_arg_uint(LIST)	__va_arg(LIST,unsigned int)
#define _va_arg_long(LIST)	__va_arg(LIST,long)
#define _va_arg_ulong(LIST)	__va_arg(LIST,unsigned long)

#if defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__hppa64__) || defined(__arm64__) || defined(__powerpc64__) || defined(__ia64__) || (defined(__x86_64__) && !defined(__x86_64_x32__) && !defined(__VA_LLP64)) || defined(__s390x__)
/* ‘long long’ and ‘long’ are identical. */
#define _va_arg_longlong	_va_arg_long
#define _va_arg_ulonglong	_va_arg_ulong
#elif defined(__mipsn32__) || defined(__x86_64_x32__) || (defined(__x86_64__) && defined(__VA_LLP64))
/* ‘long long’ fits in __vaword. */
#define _va_arg_longlong(LIST)	__va_arg(LIST,long long)
#define _va_arg_ulonglong(LIST)	__va_arg(LIST,unsigned long long)
#elif defined(__i386__) || defined(__m68k__) || defined(__mips__) || (defined(__sparc__) && !defined(__sparc64__)) || (defined(__hppa__) && !defined(__hppa64__)) || defined(__arm__) || defined(__armhf__) || defined(__powerpc__) || (defined(__s390__) && !defined(__s390x__))
/* ‘long long’s are passed embedded on the arg stack. */
#define _va_arg_longlong(LIST)	__va_arg_longlong(LIST,long long)
#define _va_arg_ulonglong(LIST)	__va_arg_longlong(LIST,unsigned long long)
#if defined(__i386__) || defined(__m68k__) || defined(__powerpc_aix__)
/* ‘long long’s are (at most) word-aligned. */
#define __va_arg_longlong(LIST,TYPE)	__va_arg(LIST,TYPE)
#endif
#if defined(__mips__) || defined(__arm__)
/* ‘long long’s have alignment 8. */
#define __va_arg_longlong(LIST,TYPE)					\
  ((LIST)->aptr = (((LIST)->aptr+__VA_alignof(TYPE)-1) & -(intptr_t)__VA_alignof(TYPE)), \
   __va_arg(LIST,TYPE))
#endif
#if defined(__armhf__) || defined(__powerpc_sysv4__)
/* ‘long long’s have alignment 8. */
#define __va_arg_longlong(LIST,TYPE)					\
  (((LIST)->ianum < __VA_IARG_NUM					\
    ? ((LIST)->ianum = (((LIST)->ianum+__VA_alignof(TYPE)/sizeof(__vaword)-1) & -(intptr_t)(__VA_alignof(TYPE)/sizeof(__vaword))), 0) \
    : ((LIST)->aptr = (((LIST)->aptr+__VA_alignof(TYPE)-1) & -(intptr_t)__VA_alignof(TYPE)), 0) \
   ),									\
   __va_arg(LIST,TYPE))
#endif
#if defined(__s390__) && !defined(__s390x__)
/* Within the arg stack, the alignment is only 4, not 8. */
#define __va_arg_longlong(LIST,TYPE)	__va_arg(LIST,TYPE)
#endif
#if (defined(__sparc__) && !defined(__sparc64__))
/* Within the arg stack, the alignment is only 4, not 8. */
/* Beware against unaligned accesses! */
#define __va_arg_longlong(LIST,TYPE)					\
  ((LIST)->tmp._words[0] = ((__vaword*)((LIST)->aptr))[0],		\
   (LIST)->tmp._words[1] = ((__vaword*)((LIST)->aptr))[1],		\
   (LIST)->aptr += sizeof(TYPE),					\
   (TYPE)((LIST)->tmp._longlong)					\
  )
#endif
#if defined(__hppa__) && !defined(__hppa64__)
/* ‘long long’s have alignment 8. */
#define __va_arg_longlong(LIST,TYPE)					\
  ((LIST)->aptr = ((LIST)->aptr & -(intptr_t)__VA_alignof(TYPE)),	\
   __va_arg(LIST,TYPE))
#endif
#endif

/* Floating point arguments. */

#if defined(__i386__) || defined(__m68k__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc__) || defined(__sparc64__) || defined(__alpha__) || defined(__hppa64__) || defined(__arm64__) || defined(__powerpc__) || defined(__powerpc64__) || defined(__ia64__) || defined(__x86_64__) || defined(__s390__) || defined(__s390x__)
#define __va_align_double(LIST)
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__) || defined(__arm__) || defined(__armhf__)
/* __VA_alignof(double) > sizeof(__vaword) */
#define __va_align_double(LIST)  \
  (LIST)->aptr = ((LIST)->aptr + sizeof(double)-1) & -(intptr_t)sizeof(double),
#endif
#if defined(__hppa__) && !defined(__hppa64__)
#define __va_align_double(LIST)  \
  (LIST)->aptr = (LIST)->aptr & -(intptr_t)sizeof(double),
#endif

#if defined(__sparc__) && !defined(__sparc64__)
/* Beware against unaligned ‘double’ accesses! */
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->tmp._words[0] = ((__vaword*)((LIST)->aptr))[0],		\
   (LIST)->tmp._words[1] = ((__vaword*)((LIST)->aptr))[1],		\
   (LIST)->aptr += sizeof(double),					\
   (LIST)->tmp._double							\
  )
#endif
#if defined(__alpha__)
/* The first 6 floating point registers have been stored in another place. */
#define _va_arg_double(LIST)  \
  (((LIST)->aptr += sizeof(double)) <= (LIST)->memargptr		\
   ? *(double*)((LIST)->aptr - sizeof(double) + (LIST)->farg_offset)	\
   : *(double*)((LIST)->aptr - sizeof(double))				\
  )
#define _va_arg_float(LIST)  \
  (((LIST)->aptr += sizeof(double)) <= (LIST)->memargptr		\
   ? /* The first 6 args have been put into memory by "stt" instructions */\
     /* (see vacall-alpha.s!). Therefore load them as doubles. */	\
     /* When viewed as floats, the value will be the correct one. */	\
     (float)*(double*)((LIST)->aptr - sizeof(double) + (LIST)->farg_offset) \
   : /* These args have been put into memory by "sts" instructions, */	\
     /* therefore load them as floats. */				\
     *(float*)((LIST)->aptr - sizeof(double))				\
  )
#endif
#if defined(__hppa__) && !defined(__hppa64__)
/* The first 4 float registers and the first 2 double registers are stored
 * elsewhere.
 */
#if 1 /* gcc-2.5.2 passes these args in general registers! A bug, I think. */
#define _va_arg_float(LIST)  \
  (*(float*)((LIST)->aptr -= sizeof(float)))
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   *(double*)((LIST)->aptr -= sizeof(double))				\
  )
#else /* this would be correct if the args were passed in float registers. */
#define _va_arg_float(LIST)  \
  (((LIST)->aptr -= sizeof(float)) >= (LIST)->memargptr			\
   ? /* The first 4 float args are stored separately. */		\
     *(float*)((LIST)->aptr + (LIST)->farg_offset)			\
   : *(float*)((LIST)->aptr)						\
  )
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (((LIST)->aptr -= sizeof(double)) >= (LIST)->memargptr		\
    ? /* The first 2 double args are stored separately. */		\
      *(double*)((LIST)->aptr + (LIST)->darg_offset)			\
    : *(double*)((LIST)->aptr)						\
  ))
#endif
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
/* The first 0,1,2 registers are stored elsewhere if they are floating-point
 * parameters.
 */
#define _va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(float),					\
   (LIST)->anum++,							\
   (LIST)->fanum++,							\
   ((LIST)->anum == (LIST)->fanum && (LIST)->fanum <= __VA_FARG_NUM	\
    ? /* only floating-point arguments so far */			\
      (LIST)->farg[(LIST)->fanum - 1]					\
    : *(float*)((LIST)->aptr - sizeof(float))				\
  ))
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (LIST)->anum++,							\
   (LIST)->fanum++,							\
   ((LIST)->anum == (LIST)->fanum && (LIST)->fanum <= __VA_FARG_NUM	\
    ? /* only floating-point arguments so far */			\
      (LIST)->darg[(LIST)->fanum - 1]					\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__mipsn32__) || defined(__mips64__) || defined(__x86_64_ms__)
/* The first 0,..,8 registers are stored elsewhere if they are floating-point
 * parameters.
 */
#define _va_arg_float(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (++(LIST)->anum <= __VA_FARG_NUM					\
    ? (LIST)->farg[(LIST)->anum - 1]					\
    : *(float*)((LIST)->aptr - sizeof(double))				\
  ))
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (++(LIST)->anum <= __VA_FARG_NUM					\
    ? (LIST)->darg[(LIST)->anum - 1]					\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__sparc64__)
/* The first 0,..,16 registers are stored elsewhere if they are floating-point
 * parameters.
 */
#define _va_arg_float(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (++(LIST)->anum <= 16						\
    ? (LIST)->farg[(LIST)->anum - 1]					\
    : *(float*)((LIST)->aptr - sizeof(float))				\
  ))
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (++(LIST)->anum <= 16						\
    ? (LIST)->darg[(LIST)->anum - 1]					\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__hppa64__)
/* The floating-point arguments among the first 8 argument words have been
   stored elsewhere. */
#define _va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(double),					\
   ((LIST)->aptr <= (LIST)->memargptr					\
    ? (LIST)->farg[__VA_FARG_NUM-1-((LIST)->memargptr - (LIST)->aptr)/sizeof(__vaword)] \
    : ((float*)(LIST)->aptr)[-1]					\
  ))
#define _va_arg_double(LIST)  \
  ((LIST)->aptr += sizeof(double),					\
   ((LIST)->aptr <= (LIST)->memargptr					\
    ? (LIST)->darg[__VA_FARG_NUM-1-((LIST)->memargptr - (LIST)->aptr)/sizeof(__vaword)] \
    : ((double*)(LIST)->aptr)[-1]					\
  ))
#endif
#if defined(__armhf__)
#define _va_arg_float(LIST)  \
  ((LIST)->fanum <= 15							\
   ? (LIST)->farg[(LIST)->fanum++]					\
   : ((LIST)->aptr += sizeof(float),					\
      *(float*)((LIST)->aptr - sizeof(float))				\
  )  )
#define _va_arg_double(LIST)  \
  (((LIST)->fanum % 2 ? (LIST)->fanum++ : 0),				\
   ((LIST)->fanum <= 14							\
    ? ((LIST)->fanum += 2, (LIST)->darg[(LIST)->fanum / 2 - 1])		\
    : ((LIST)->aptr += sizeof(double),					\
       *(double*)((LIST)->aptr - sizeof(double))			\
  ))  )
#endif
#if defined(__arm64__)
/* The first __VA_FARG_NUM floating-point args have been stored elsewhere. */
#define _va_arg_float(LIST)  \
  ((LIST)->fanum < __VA_FARG_NUM					\
   ? (LIST)->farg[(LIST)->fanum++]					\
   : ((LIST)->aptr += sizeof(__vaword),					\
      *(float*)((LIST)->aptr - sizeof(__vaword))			\
  )  )
#define _va_arg_double(LIST)  \
  ((LIST)->fanum < __VA_FARG_NUM					\
   ? (LIST)->darg[(LIST)->fanum++]					\
   : ((LIST)->aptr += sizeof(__vaword),					\
      *(double*)((LIST)->aptr - sizeof(__vaword))			\
  )  )
#endif
#if defined(__powerpc_aix__)
/* The first __VA_FARG_NUM floating-point args have been stored elsewhere. */
#define _va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(float),					\
   ((LIST)->fanum < __VA_FARG_NUM					\
    ? (float) (LIST)->farg[(LIST)->fanum++]				\
    : *(float*)((LIST)->aptr - sizeof(float))				\
  ))
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   ((LIST)->fanum < __VA_FARG_NUM					\
    ? (LIST)->farg[(LIST)->fanum++]					\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__powerpc_sysv4__)
/* The first __VA_FARG_NUM floating-point args have been stored elsewhere. */
#define _va_arg_float(LIST)  \
  ((LIST)->fanum < __VA_FARG_NUM					\
   ? (float) (LIST)->farg[(LIST)->fanum++]				\
   : ((LIST)->aptr += sizeof(float),					\
      *(float*)((LIST)->aptr - sizeof(float))				\
  )  )
#define _va_arg_double(LIST)  \
  ((LIST)->fanum < __VA_FARG_NUM					\
   ? (LIST)->farg[(LIST)->fanum++]					\
   : (__va_align_double(LIST)						\
      (LIST)->aptr += sizeof(double),					\
      *(double*)((LIST)->aptr - sizeof(double))				\
  )  )
#endif
#if defined(__powerpc64__)
/* The first __VA_FARG_NUM floating-point args have been stored elsewhere. */
#if defined(_AIX)
#define _va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(__vaword),					\
   ((LIST)->fanum < __VA_FARG_NUM					\
    ? (float) (LIST)->farg[(LIST)->fanum++]				\
    : ((float*)(LIST)->aptr)[(LIST)->flags & __VA_AIXCC_FLOAT_ARGS ? -2 : -1] \
  ))
#elif defined(_LITTLE_ENDIAN)
#define _va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(__vaword),					\
   ((LIST)->fanum < __VA_FARG_NUM					\
    ? (float) (LIST)->farg[(LIST)->fanum++]				\
    : ((float*)(LIST)->aptr)[-2]					\
  ))
#else /* _BIG_ENDIAN */
#define _va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(__vaword),					\
   ((LIST)->fanum < __VA_FARG_NUM					\
    ? (float) (LIST)->farg[(LIST)->fanum++]				\
    : ((float*)(LIST)->aptr)[-1]					\
  ))
#endif
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   ((LIST)->fanum < __VA_FARG_NUM					\
    ? (LIST)->farg[(LIST)->fanum++]					\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__ia64__)
/* The first 8 floating-point args have been stored elsewhere. */
#define _va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(__vaword),					\
   ((LIST)->fanum < __VA_FARG_NUM					\
    ? (float) (LIST)->farg[(LIST)->fanum++]				\
    : *(float*)((LIST)->aptr - sizeof(__vaword))			\
  ))
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   ((LIST)->fanum < __VA_FARG_NUM					\
    ? (LIST)->farg[(LIST)->fanum++]					\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__x86_64_sysv__)
/* The first 8 floating-point args have been stored elsewhere. */
#define _va_arg_float(LIST)  \
  ((LIST)->fanum < __VA_FARG_NUM					\
   ? *(float*)&(LIST)->farg[(LIST)->fanum++]				\
   : ((LIST)->aptr += sizeof(__vaword),					\
      *(float*)((LIST)->aptr - sizeof(__vaword))			\
  )  )
#define _va_arg_double(LIST)  \
  ((LIST)->fanum < __VA_FARG_NUM					\
   ? (LIST)->farg[(LIST)->fanum++]					\
   : ((LIST)->aptr += sizeof(__vaword),					\
      *(double*)((LIST)->aptr - sizeof(__vaword))			\
  )  )
#endif
#if defined(__s390__) || defined(__s390x__)
/* The first __VA_FARG_NUM floating-point args have been stored elsewhere. */
#define _va_arg_float(LIST)  \
  ((LIST)->fanum < __VA_FARG_NUM					\
   ? (LIST)->farg[(LIST)->fanum++]					\
   : ((LIST)->aptr += sizeof(__vaword),					\
      ((float*)(LIST)->aptr)[-1]					\
  )  )
#define _va_arg_double(LIST)  \
  ((LIST)->fanum < __VA_FARG_NUM					\
   ? (LIST)->darg[(LIST)->fanum++]					\
   : ((LIST)->aptr += sizeof(double),					\
      *(double*)((LIST)->aptr - sizeof(double))				\
  )  )
#endif
#ifndef _va_arg_float
#define _va_arg_float(LIST)	__va_arg(LIST,float)
#endif
#ifndef _va_arg_double
#define _va_arg_double(LIST)  \
  (__va_align_double(LIST) __va_arg(LIST,double))
#endif

/* Pointer arguments. */
#define _va_arg_ptr(LIST)	__va_arg(LIST,void*)

/* Structure arguments. */
/* Structure argument alignment. */
#if defined(__i386__) && defined(_MSC_VER)
/* In MSVC, doubles inside structures have alignment 8, i.e.
 * __VA_alignof(double) = 8, but doubles (and also structures containing
 * doubles) are passed on the stack with alignment 4. Looks really weird.
 */
#define __va_struct_alignment(TYPE_ALIGN)  \
  ((TYPE_ALIGN) <= 4 ? (TYPE_ALIGN) : 4)
#else
#define __va_struct_alignment(TYPE_ALIGN)  \
  (TYPE_ALIGN)
#endif
#define __va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (LIST)->aptr = ((LIST)->aptr + __va_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__va_struct_alignment(TYPE_ALIGN),
#if defined(__i386__) || defined(__m68k__) || defined(__alpha__) || defined(__arm__) || defined(__armhf__) || (defined(__powerpc64__) && !defined(_AIX)) || defined(__x86_64_sysv__)
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)				\
  )
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   ((LIST)->flags & __VA_SGICC_STRUCT_ARGS				\
    ? /* SGI MIPS cc passes small structures left-adjusted, although big-endian! */\
      (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
    : /* SGI MIPS gcc passes small structures within the first four words left-	   \
       * adjusted, for compatibility with cc. But structures in memory are passed  \
       * right-adjusted!! See gcc-2.6.3/config/mips/mips.c:function_arg().	   \
       */									   \
      ((LIST)->aptr < (LIST)->memargptr					\
       ? (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)	\
       : (void*)__va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)	\
  ))  )
#endif
#if defined(__mipsn32__) || defined(__mips64__)
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   ((LIST)->flags & __VA_SGICC_STRUCT_ARGS				\
    ? /* SGI MIPS cc and gcc >= 3.4 passes small structures left-adjusted, although big-endian! */\
      (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
    : /* SGI MIPS gcc < 3.4 passes small structures right-adjusted. */	\
      (void*)__va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  ))
#endif
#if defined(__powerpc_aix__) || (defined(__powerpc64__) && defined(_AIX))
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   ((LIST)->flags & __VA_AIXCC_STRUCT_ARGS				\
    ? /* AIX cc and xlc pass small structures left-adjusted, although big-endian! */\
      (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
    : /* gcc passes small structures right-adjusted. */			\
      (void*)__va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  ))
#endif
#if defined(__powerpc_sysv4__)
/* Structures are passed as pointers to caller-made local copies. */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  va_arg_ptr(LIST,void*)
#endif
#if defined(__sparc__) && !defined(__sparc64__)
/* Structures are passed as pointers to caller-made local copies. */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  va_arg_ptr(LIST,void*)
#endif
#if defined(__sparc64__)
/* Small structures are passed left-adjusted, although big-endian! */
/* Big structures are passed as pointers to caller-made local copies. */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((TYPE_SIZE) <= 16							\
   ? (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)			\
      (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN))		\
   : va_arg_ptr(LIST,void*)						\
  )
#endif
#if defined(__hppa64__)
/* Structures are passed left-adjusted (although big-endian!). */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  )
#endif
#if defined(__arm64__)
/* Small structures are passed in registers or on the stack. */
/* Big structures are passed as pointers to caller-made local copies. */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((TYPE_SIZE) <= 16							\
   ? (void*)__va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
   : va_arg_ptr(LIST,void*)						\
  )
#endif
#if defined(__x86_64_ms__) || defined(__s390__) || defined(__s390x__)
/* Structures of 1, 2, 4, 8 bytes are passed as embedded copies on the arg stack.
 * Big structures are passed as pointers to caller-made local copies.
 */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8 \
   ? (void*)__va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
   : va_arg_ptr(LIST,void*)						\
  )
#endif
#if defined(__hppa__) && !defined(__hppa64__)
/* Structures <= 8 bytes are passed as embedded copies on the arg stack.
 * Big structures are passed as pointers to caller-made local copies.
 */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((TYPE_SIZE) > 8							\
   ? va_arg_ptr(LIST,void*)						\
   : /* FIXME: gcc-2.6.3 passes structures <= 4 bytes in memory left-adjusted! ?? */\
     (void*)__va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  )
#endif
#if defined(__ia64__)
/* With GCC < 3, types larger than a word have 2-word alignment. */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   (((LIST)->flags & __VA_OLDGCC_STRUCT_ARGS) && (TYPE_SIZE) > sizeof(__vaword) && (((__vaword*)(LIST)->aptr - (LIST)->saptr) & 1) ? (LIST)->aptr += sizeof(__vaword) : 0), \
   __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)				\
  )
#endif


/*
 * Definition of the va_return_xxx macros.
 */
#define __va_return(LIST,RETTYPE)  \
  (((LIST)->rtype == (RETTYPE)) || (vacall_error_type_mismatch((LIST)->rtype,RETTYPE), 0))
#define _va_return_void(LIST)  \
  __va_return(LIST,__VAvoid)
#define _va_return_char(LIST,VAL)  \
  (__va_return(LIST,__VAchar), (LIST)->tmp._char = (VAL))
#define _va_return_schar(LIST,VAL)  \
  (__va_return(LIST,__VAschar), (LIST)->tmp._schar = (VAL))
#define _va_return_uchar(LIST,VAL)  \
  (__va_return(LIST,__VAuchar), (LIST)->tmp._uchar = (VAL))
#define _va_return_short(LIST,VAL)  \
  (__va_return(LIST,__VAshort), (LIST)->tmp._short = (VAL))
#define _va_return_ushort(LIST,VAL)  \
  (__va_return(LIST,__VAushort), (LIST)->tmp._ushort = (VAL))
#define _va_return_int(LIST,VAL)  \
  (__va_return(LIST,__VAint), (LIST)->tmp._int = (VAL))
#define _va_return_uint(LIST,VAL)  \
  (__va_return(LIST,__VAuint), (LIST)->tmp._uint = (VAL))
#define _va_return_long(LIST,VAL)  \
  (__va_return(LIST,__VAlong), (LIST)->tmp._long = (VAL))
#define _va_return_ulong(LIST,VAL)  \
  (__va_return(LIST,__VAulong), (LIST)->tmp._ulong = (VAL))
#if defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__hppa64__) || defined(__arm64__) || defined(__powerpc64__) || defined(__ia64__) || (defined(__x86_64__) && !defined(__x86_64_x32__) && !defined(__VA_LLP64))
#define _va_return_longlong(LIST,VAL)  \
  (__va_return(LIST,__VAlonglong), (LIST)->tmp._long = (VAL))
#define _va_return_ulonglong(LIST,VAL)  \
  (__va_return(LIST,__VAulonglong), (LIST)->tmp._ulong = (VAL))
#else
#define _va_return_longlong(LIST,VAL)  \
  (__va_return(LIST,__VAlonglong), (LIST)->tmp._longlong = (VAL))
#define _va_return_ulonglong(LIST,VAL)  \
  (__va_return(LIST,__VAulonglong), (LIST)->tmp._ulonglong = (VAL))
#endif
#define _va_return_float(LIST,VAL)  \
  (__va_return(LIST,__VAfloat), (LIST)->tmp._float = (VAL))
#define _va_return_double(LIST,VAL)  \
  (__va_return(LIST,__VAdouble), (LIST)->tmp._double = (VAL))
#define _va_return_ptr(LIST,VAL)  \
  (__va_return(LIST,__VAvoidp), (LIST)->tmp._ptr = (VAL))
#define __va_return_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL_ADDR)  \
  (__va_return(LIST,__VAstruct),					\
   vacall_structcpy((void*)((LIST)->raddr),VAL_ADDR,TYPE_SIZE,TYPE_ALIGN) \
  )


/*
 * Miscellaneous declarations.
 */
extern void vacall_structcpy (void* dest, const void* src, unsigned long size, unsigned long alignment);


#endif /* _VACALL_INTERNAL_H */
