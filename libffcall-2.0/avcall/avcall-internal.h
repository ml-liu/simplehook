/*
 * Copyright 1993-1995 Bill Triggs <Bill.Triggs@inrialpes.fr>
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

#ifndef _AVCALL_INTERNAL_H
#define _AVCALL_INTERNAL_H

/* Get intptr_t, uintptr_t. */
#include "ffcall-stdint.h"

/* Include the public definitions and "avcall-alist.h",  */
#include "avcall.h"


/* Verify at compile time that sizeof(__av_alist) <= __AV_ALIST_SIZE_BOUND. */
typedef int __av_alist_verify[2*(__AV_ALIST_SIZE_BOUND - (int)sizeof(__av_alist))+1];

/* Conversion from the public, mostly opaque, 'av_alist*' to '__av_alist*'. */
#define AV_LIST_INNER(list) ((list)->_av_alist_head._av_m_alist)


/* Delayed overflow detection */
#if defined(__hppa__) && !defined(__hppa64__)
#define _av_overflown(LIST) ((LIST).aptr < (LIST).eptr)
#else
#define _av_overflown(LIST) ((LIST).aptr > (LIST).eptr)
#endif


/*
 * Initialization of an __av_alist
 */

#define __av_start(LIST,LIST_ARGS,LIST_ARGS_END,FUNC,RADDR,RETTYPE,FLAGS) \
  ((LIST).func = (FUNC),						\
   (LIST).raddr = (RADDR),						\
   (LIST).rtype = (RETTYPE),						\
   (LIST).args = (LIST_ARGS),						\
   __av_start1(LIST,LIST_ARGS_END)					\
   __av_start_init_eptr(LIST,LIST_ARGS_END)				\
   (LIST).flags = (FLAGS))

#if defined(__i386__) || defined(__m68k__) || defined(__alpha__) || (defined(__arm__) && !defined(__armhf__))
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = &(LIST).args[0],
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).anum = 0,							\
   (LIST).fanum = 0,							\
   (LIST).farg_mask = 0,						\
   (LIST).darg_mask = 0,						\
   (LIST).aptr = &(LIST).args[0],
#endif
#if defined(__mipsn32__) || defined(__mips64__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).anum = 0,							\
   (LIST).farg_mask = 0,						\
   (LIST).darg_mask = 0,						\
   (LIST).aptr = &(LIST).args[0],
#endif
#if defined(__sparc__) && !defined(__sparc64__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = &(LIST).args[0],
#endif
#if defined(__sparc64__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).anum = 0,							\
   (LIST).darg_mask = 0,						\
   (LIST).aptr = &(LIST).args[0],
#endif
#if defined(__hppa__) && !defined(__hppa64__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = (LIST).args_end = (LIST_ARGS_END),
#endif
#if defined(__hppa64__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).farg_mask = 0,						\
   (LIST).darg_mask = 0,						\
   (LIST).aptr = &(LIST).args[0],
#endif
#if defined(__armhf__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = &(LIST).args[__AV_IARG_NUM],				\
   (LIST).ianum = 0,							\
   (LIST).fanum = 0,							\
   (LIST).farg_mask = 0,						\
   (LIST).darg_mask = 0,
#endif
#if defined(__arm64__) || defined(__s390__) || defined(__s390x__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).ianum = 0,							\
   (LIST).fanum = 0,							\
   (LIST).farg_mask = 0,						\
   (LIST).darg_mask = 0,
#endif
#if defined(__powerpc_aix__) || defined(__powerpc64__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).faptr = &(LIST).fargs[0],
#endif
#if defined(__powerpc_sysv4__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).ianum = 0,							\
   (LIST).faptr = &(LIST).fargs[0],
#endif
#if defined(__ia64__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).faptr = &(LIST).fargs[0],
#endif
#if defined(__x86_64_sysv__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).ianum = 0,							\
   (LIST).faptr = &(LIST).fargs[0],
#endif
#if defined(__x86_64_ms__)
#define __av_start1(LIST,LIST_ARGS_END)					\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).anum = 0,							\
   (LIST).farg_mask = 0,						\
   (LIST).darg_mask = 0,
#endif

#if defined(__hppa__) && !defined(__hppa64__)
#define __av_start_init_eptr(LIST,LIST_ARGS_END)			\
   (LIST).eptr = &(LIST).args[0],
#else
#define __av_start_init_eptr(LIST,LIST_ARGS_END)			\
   (LIST).eptr = (LIST_ARGS_END),
#endif

#define __av_start_struct(LIST,LIST_ARGS,LIST_ARGS_END,FUNC,TYPE_SIZE,TYPE_SPLITTABLE,RADDR,FLAGS) \
  (__av_start(LIST,LIST_ARGS,LIST_ARGS_END,FUNC,RADDR,__AVstruct,FLAGS), \
   (LIST).rsize = (TYPE_SIZE),						\
   __av_start_struct2(LIST,TYPE_SIZE,TYPE_SPLITTABLE),			\
   0)

#if (defined(__sparc__) && !defined(__sparc64__))
/* Return structure pointer is passed in a special register.
 */
#define __av_start_struct2(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  0
#else
#define __av_start_struct2(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  (((LIST).flags & __AV_SMALL_STRUCT_RETURN)				\
   && __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)		\
   ? /* <= Word-sized structures are returned in a register. */		\
     __av_start_struct3(LIST)						\
   : __av_start_struct4(LIST,TYPE_SIZE)					\
  )
/* Determines whether a structure is returned in registers,
 * depending on its size and its word-splittable flag.
 */
#if (defined(__i386__) && defined(_WIN32))
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4		\
   || ((TYPE_SIZE) == 8							\
       && (((LIST).flags & __AV_MSVC_STRUCT_RETURN)			\
           || ((TYPE_SPLITTABLE)					\
               && ((LIST).flags & __AV_GCC_STRUCT_RETURN)		\
  )   )   )   )
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if (defined(__i386__) && !defined(_WIN32)) || defined(__m68k__) || (defined(__powerpc__) && !defined(__powerpc64__)) || (defined(__s390__) && !defined(__s390x__))
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4		\
   || ((TYPE_SIZE) == 8 && (TYPE_SPLITTABLE)				\
       && ((LIST).flags & __AV_GCC_STRUCT_RETURN)			\
  )   )
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__arm__) || defined(__armhf__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 4)
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__alpha__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8	\
   || ((TYPE_SIZE) == 16 && (TYPE_SPLITTABLE)				\
       && ((LIST).flags & __AV_GCC_STRUCT_RETURN)			\
  )   )
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__hppa__) && !defined(__hppa64__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 8)
/* Test __AV_SMALL_STRUCT_RETURN at run time. */
#define __av_start_struct3(LIST)  \
  0
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4)
/* Test __AV_SMALL_STRUCT_RETURN instead of __AV_REGISTER_STRUCT_RETURN. */
#define __av_start_struct3(LIST)  \
  0
#endif
#if defined(__mipsn32__) || defined(__mips64__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((LIST).flags & __AV_GCC_STRUCT_RETURN				\
   ? ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8) \
   : ((TYPE_SIZE) <= 16)						\
  )
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if (defined(__powerpc64__) && !defined(__powerpc64_elfv2__)) || defined(__s390x__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  0
#define __av_start_struct3(LIST)  \
  0
#endif
#if defined(__sparc64__) || defined(__ia64__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 32)
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__hppa64__) || defined(__arm64__) || (defined(__powerpc64__) && defined(__powerpc64_elfv2__)) || defined(__x86_64_sysv__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 16)
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__x86_64_ms__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8)
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__m68k__) || defined(__hppa__) || defined(__hppa64__) || defined(__arm64__) || defined(__ia64__)
/* Return structure pointer is passed in a special register.
 */
#define __av_start_struct4(LIST,TYPE_SIZE)  0
#endif
/* Return structure pointer is passed as first arg.
 */
#if defined(__i386__) || defined(__alpha__) || (defined(__arm__) && !defined(__armhf__)) || defined(__powerpc_aix__) || defined(__powerpc64__)
#define __av_start_struct4(LIST,TYPE_SIZE)				\
   (*(LIST).aptr++ = (__avword)((LIST).raddr), 0)
#endif
#if defined(__armhf__)
#define __av_start_struct4(LIST,TYPE_SIZE)				\
   ((LIST).args[(LIST).ianum++] = (__avword)((LIST).raddr), 0)
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__) || defined(__x86_64_ms__)
#define __av_start_struct4(LIST,TYPE_SIZE)				\
   (*(LIST).aptr++ = (__avword)((LIST).raddr),				\
    (LIST).anum++,							\
    0									\
   )
#endif
#if defined(__powerpc_sysv4__) || defined(__x86_64_sysv__) || defined(__s390__) || defined(__s390x__)
#define __av_start_struct4(LIST,TYPE_SIZE)				\
   ((LIST).iargs[(LIST).ianum++] = (__avword)((LIST).raddr), 0)
#endif
#endif


/*
 * av_<type> macros which specify the argument and its type
 * In these macro definitions,
 * 1. check the new value of (LIST).aptr against (LIST).eptr, then
 * 2. modify (LIST).aptr (considering the alignment needed for the argument
 *    type), then store the argument. On little-endian machines and when
 *    there are no alignment considerations, it's also OK to store the
 *    argument and then modify (LIST).aptr.
 */

/*
 * scalar argument types
 */

#if defined(__i386__) || defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__alpha__) || defined(__hppa64__) || (defined(__arm__) && !defined(__armhf__)) || defined(__arm64__) || defined(__powerpc__) || defined(__powerpc64__) || defined(__ia64__) || defined(__x86_64_sysv__) || defined(__s390__) || defined(__s390x__)
/* Floats and all integer types are passed as words,
 * doubles as two words (on 32-bit platforms) or one word (on 64-bit platforms).
 */
#define __av_word(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((LIST).aptr)[-1] = (__avword)(VAL),				\
    0))
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__) || defined(__x86_64_ms__)
/* Most things are passed as integers:
 */
#define __av_word(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((LIST).aptr)[-1] = (__avword)(VAL),				\
    (LIST).anum++,							\
    0))
#endif
#if defined(__hppa__) && !defined(__hppa64__)
/* Floats and all integer types are passed as words,
 * doubles as two words.
 */
#define __av_word(LIST,VAL)						\
  ((LIST).aptr <= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr--,							\
    *(LIST).aptr = (__avword)(VAL),					\
    0))
#endif
#if defined(__armhf__)
#define __av_word(LIST,VAL)						\
  ((LIST).ianum < __AV_IARG_NUM						\
   ? ((LIST).args[(LIST).ianum++] = (__avword)(VAL), 0)			\
   : ((LIST).aptr >= (LIST).eptr					\
      ? -1 :								\
      ((LIST).aptr++,							\
       ((LIST).aptr)[-1] = (__avword)(VAL),				\
       0)))
#endif

/* integer argument types */

#if defined(__arm64__) || defined(__powerpc_sysv4__) || defined(__x86_64_sysv__) || defined(__s390__) || defined(__s390x__)
/* The first __AV_IARG_NUM integer arguments are passed in registers. */
#define __av_long(LIST,VAL)						\
  ((LIST).ianum < __AV_IARG_NUM						\
   ? ((LIST).iargs[(LIST).ianum++] = (long)(VAL), 0)			\
   : __av_word(LIST,(long)(VAL)))
#else
#define __av_long(LIST,VAL)	__av_word(LIST,(long)(VAL))
#endif

#if defined(__arm64__) || defined(__powerpc_sysv4__) || defined(__x86_64_sysv__) || defined(__s390__) || defined(__s390x__)
/* The first __AV_IARG_NUM integer arguments are passed in registers. */
#define __av_ulong(LIST,VAL)						\
  ((LIST).ianum < __AV_IARG_NUM						\
   ? ((LIST).iargs[(LIST).ianum++] = (unsigned long)(VAL), 0)		\
   : __av_word(LIST,(unsigned long)(VAL)))
#else
#define __av_ulong(LIST,VAL)	__av_word(LIST,(unsigned long)(VAL))
#endif

#if defined(__arm64__) || defined(__powerpc_sysv4__) || defined(__x86_64_sysv__) || defined(__s390__) || defined(__s390x__)
/* The first __AV_IARG_NUM integer arguments are passed in registers. */
#define __av_ptr(LIST,VAL)						\
  ((LIST).ianum < __AV_IARG_NUM						\
   ? ((LIST).iargs[(LIST).ianum++] = (__avword)(VAL), 0)		\
   : __av_word(LIST,VAL))
#else
#define __av_ptr(LIST,VAL)	__av_word(LIST,VAL)
#endif

#if defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__hppa64__) || defined(__arm64__) || defined(__powerpc64__) || defined(__ia64__) || (defined(__x86_64__) && !defined(__x86_64_x32__) && !defined(__AV_LLP64)) || defined(__s390x__)
/* ‘long long’ and ‘long’ are identical. */
#define __av_longlong		__av_long
#define __av_ulonglong		__av_ulong
#elif defined(__mipsn32__) || (defined(__x86_64__) && defined(__AV_LLP64))
/* ‘long long’ fits in __avword. */
#define __av_longlong			__av_word
#define __av_ulonglong(LIST,VAL)	__av_word(LIST,(unsigned long long)(VAL))
#elif defined(__i386__) || defined(__m68k__) || (defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)) || (defined(__sparc__) && !defined(__sparc64__)) || (defined(__hppa__) && !defined(__hppa64__)) || defined(__arm__) || defined(__armhf__) || defined(__powerpc__) || defined(__x86_64_x32__) || (defined(__s390__) && !defined(__s390x__))
/* ‘long long’s are passed embedded on the arg stack. */
#define __av_longlong(LIST,VAL)		__av_arg_longlong(LIST,long long,VAL)
#define __av_ulonglong(LIST,VAL)	__av_arg_longlong(LIST,unsigned long long,VAL)
#if defined(__i386__) || defined(__m68k__) || defined(__powerpc_aix__)
/* ‘long long’s are (at most) word-aligned. */
#define __av_arg_longlong(LIST,TYPE,VAL)				\
  ((LIST).aptr + sizeof(TYPE)/sizeof(__avword) > (LIST).eptr		\
   ? -1 :								\
   ((LIST).aptr += sizeof(TYPE)/sizeof(__avword),			\
    ((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL),				\
    0))
#endif
#if defined(__mips__) || (defined(__sparc__) && !defined(__sparc64__)) || (defined(__hppa__) && !defined(__hppa64__)) || defined(__arm__) || defined(__armhf__) || defined(__powerpc_sysv4__) || defined(__x86_64_x32__) || (defined(__s390__) && !defined(__s390x__))
/* ‘long long’s have alignment 4 or 8. */
#if defined(__mips__)
#define __av_arg_longlong(LIST,TYPE,VAL)				\
  ((__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE)) > (LIST).eptr \
   ? -1 :								\
   (((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE))), \
    ((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL),				\
    (LIST).anum++,							\
    0))
#endif
#if defined(__sparc__) && !defined(__sparc64__)
/* Within the arg stack, the alignment is only 4, not 8. */
/* This assumes sizeof(long long) == 2*sizeof(__avword). */
#define __av_arg_longlong(LIST,TYPE,VAL)				\
  ((LIST).aptr + sizeof(TYPE)/sizeof(__avword) > (LIST).eptr		\
   ? -1 :								\
   ((LIST).aptr += sizeof(TYPE)/sizeof(__avword),			\
    (LIST).tmp._longlong = (TYPE)(VAL),					\
    (LIST).aptr[-2] = (LIST).tmp.words[0],				\
    (LIST).aptr[-1] = (LIST).tmp.words[1],				\
    0))
#endif
#if (defined(__hppa__) && !defined(__hppa64__))
#define __av_arg_longlong(LIST,TYPE,VAL)				\
  ((__avword*)(((uintptr_t)(LIST).aptr & -(intptr_t)__AV_alignof(TYPE)) - sizeof(TYPE)) < (LIST).eptr \
   ? -1 :								\
   ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr & -(intptr_t)__AV_alignof(TYPE)) - sizeof(TYPE)), \
    *(TYPE*)(LIST).aptr = (TYPE)(VAL),					\
    0))
#endif
#if defined(__arm__) && !defined(__armhf__)
#define __av_arg_longlong(LIST,TYPE,VAL)				\
  ((__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE)) > (LIST).eptr \
   ? -1 :								\
   ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE)), \
    ((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL),				\
    0))
#endif
#if defined(__armhf__)
#define __av_arg_longlong(LIST,TYPE,VAL)				\
  ((((LIST).ianum + sizeof(TYPE)/sizeof(__avword)+__AV_alignof(TYPE)/sizeof(__avword)-1) & -(intptr_t)(__AV_alignof(TYPE)/sizeof(__avword))) <= __AV_IARG_NUM \
   ? ((LIST).ianum = (((LIST).ianum + sizeof(TYPE)/sizeof(__avword)+__AV_alignof(TYPE)/sizeof(__avword)-1) & -(intptr_t)(__AV_alignof(TYPE)/sizeof(__avword))), \
      ((TYPE*)&(LIST).args[(LIST).ianum])[-1] = (TYPE)(VAL),		\
      0)								\
   : ((LIST).aptr == &(LIST).args[__AV_IARG_NUM]			\
      ? /* split case */						\
        ((__avword*)(((uintptr_t)&(LIST).args[(LIST).ianum]+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE)) > (LIST).eptr \
         ? -1 :								\
         ((LIST).aptr = (__avword*)(((uintptr_t)&(LIST).args[(LIST).ianum]+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE)), \
          ((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL),			\
          (LIST).ianum = __AV_IARG_NUM,					\
          0))								\
      : ((__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE)) > (LIST).eptr \
         ? -1 :								\
         ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE)), \
          ((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL),			\
          (LIST).ianum = __AV_IARG_NUM,					\
          0))))
#endif
#if defined(__powerpc_sysv4__)
#define __av_arg_longlong(LIST,TYPE,VAL)				\
  ((((LIST).ianum + sizeof(TYPE)/sizeof(__avword)+__AV_alignof(TYPE)/sizeof(__avword)-1) & -(intptr_t)(__AV_alignof(TYPE)/sizeof(__avword))) <= __AV_IARG_NUM \
   ? ((LIST).ianum = (((LIST).ianum + sizeof(TYPE)/sizeof(__avword)+__AV_alignof(TYPE)/sizeof(__avword)-1) & -(intptr_t)(__AV_alignof(TYPE)/sizeof(__avword))), \
      ((TYPE*)&(LIST).iargs[(LIST).ianum])[-1] = (TYPE)(VAL),		\
      0)								\
   : ((LIST).ianum = __AV_IARG_NUM,					\
      ((__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE)) > (LIST).eptr \
       ? -1 :								\
       ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(intptr_t)__AV_alignof(TYPE)), \
        ((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL),				\
        0))))
#endif
#if defined(__x86_64_x32__)
#define __av_arg_longlong(LIST,TYPE,VAL)				\
  ((LIST).ianum < __AV_IARG_NUM						\
   ? ((LIST).iargs[(LIST).ianum++] = (__avword)(TYPE)(VAL), 0)		\
   : __av_word(LIST,(TYPE)(VAL)))
#endif
#if (defined(__s390__) && !defined(__s390x__))
/* Within the arg stack, the alignment is only 4, not 8. */
#define __av_arg_longlong(LIST,TYPE,VAL)				\
  ((LIST).ianum + (sizeof(TYPE)+sizeof(__avword)-1)/sizeof(__avword) <= __AV_IARG_NUM \
   ? ((LIST).ianum += (sizeof(TYPE)+sizeof(__avword)-1)/sizeof(__avword), \
      ((TYPE*)&(LIST).iargs[(LIST).ianum])[-1] = (TYPE)(VAL),		\
      0)								\
   : ((LIST).ianum = __AV_IARG_NUM,					\
      ((__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
       ? -1 :								\
       ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr+sizeof(TYPE)+sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
        ((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL),				\
        0))))
#endif
#endif
#endif

/* floating-point argument types */

#if defined(__i386__) || defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__))

#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((float*)(LIST).aptr)[-1] = (float)(VAL),				\
    0))

/* This assumes sizeof(double) == 2*sizeof(__avword). */
#define _av_double(LIST,VAL)						\
  ((LIST).aptr + 2 > (LIST).eptr					\
   ? -1 :								\
   ((LIST).aptr += 2,							\
    (LIST).tmp._double = (double)(VAL),					\
    (LIST).aptr[-2] = (LIST).tmp.words[0],				\
    (LIST).aptr[-1] = (LIST).tmp.words[1],				\
    0))

#endif

#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)

/* Up to 2 leading float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs. For doubles we need to align the aptr
 * to an even boundary.
 */
#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((LIST).anum == (LIST).fanum && (LIST).fanum < __AV_FARG_NUM	\
     ? /* only floating-point arguments so far */			\
       ((LIST).farg_mask |= (unsigned int) 1 << (LIST).fanum,		\
        (LIST).fargs[(LIST).fanum] = ((float*)(LIST).aptr)[-1] = (float)(VAL), \
        (LIST).fanum++,							\
        0)								\
     : (((float*)(LIST).aptr)[-1] = (float)(VAL),			\
        0)),								\
    (LIST).anum++,							\
    0))

#define _av_double(LIST,VAL)						\
  ((__avword*)(((uintptr_t)(LIST).aptr+15)&-8) > (LIST).eptr		\
   ? -1 :								\
   ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr+15)&-8),		\
    ((LIST).anum == (LIST).fanum && (LIST).fanum < __AV_FARG_NUM	\
     ? /* only floating-point arguments so far */			\
       ((LIST).darg_mask |= (unsigned int) 1 << (LIST).fanum,		\
        (LIST).dargs[(LIST).fanum] = ((double*)(LIST).aptr)[-1] = (double)(VAL), \
        (LIST).fanum++,							\
        0)								\
     : (((double*)(LIST).aptr)[-1] = (double)(VAL),			\
        0)),								\
    (LIST).anum++,							\
    0))

#endif

#if defined(__mipsn32__) || defined(__mips64__)

/* Up to 8 leading float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs.
 */
#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   (((LIST).anum < 8							\
     ? ((LIST).farg_mask |= (1 << (LIST).anum),				\
        (LIST).fargs[(LIST).anum] = *(float*)(LIST).aptr = (float)(VAL)) \
     : (*(float*)(LIST).aptr = (float)(VAL))),				\
    (LIST).anum++,							\
    (LIST).aptr++,							\
    0))

#define _av_double(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   (((LIST).anum < 8 && ((LIST).darg_mask |= (1 << (LIST).anum))),	\
    *(double*)(LIST).aptr = (double)(VAL),				\
    (LIST).anum++,							\
    (LIST).aptr++,							\
    0))

#endif

#if defined(__sparc64__)

/* Up to 16 leading float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs.
 */
#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((LIST).anum < 16 && ((LIST).darg_mask |= (1 << (LIST).anum))),	\
    (((float*)(LIST).aptr)[-1] = (float)(VAL)),				\
    (LIST).anum++,							\
    0))

#define _av_double(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((LIST).anum < 16 && ((LIST).darg_mask |= (1 << (LIST).anum))),	\
    ((double*)(LIST).aptr)[-1] = (double)(VAL),				\
    (LIST).anum++,							\
    0))

#endif

#if defined(__alpha__)

#define _av_double(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((double*)(LIST).aptr)[-1] = (double)(VAL),				\
    0))

#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1									\
   : ((LIST).aptr++,							\
      ((LIST).aptr > &(LIST).args[6]					\
       ? /* These args will be fetched from memory using "lds" instructions */ \
         /* therefore store them as floats */				\
         (*(float*)((LIST).aptr-1) = (float)(VAL))			\
       : /* The first 6 args will be put into registers by "ldt" instructions */ \
         /* (see avcall-alpha.c!). Therefore store them as doubles. */	\
         /* When viewed as floats, the value will be the correct one. */\
         (*(double*)((LIST).aptr-1) = (double)(float)(VAL))),		\
      0))

#endif

#if defined(__hppa__) && !defined(__hppa64__)

#define _av_float(LIST,VAL)						\
  ((LIST).aptr <= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr--,							\
    *(float*)(LIST).aptr = (float)(VAL),				\
    0))

#define _av_double(LIST,VAL)						\
  ((__avword*)(((uintptr_t)(LIST).aptr-sizeof(double)) & -(intptr_t)sizeof(double)) < (LIST).eptr \
    ? -1 :								\
    ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr-sizeof(double)) & -(intptr_t)sizeof(double)), \
     *(double*)(LIST).aptr = (double)(VAL),				\
     0))

#endif

#if defined(__hppa64__)

#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   (((LIST).aptr < &(LIST).args[8]					\
     ? ((LIST).farg_mask |= (unsigned int)1 << ((LIST).aptr - (LIST).args), 0) \
     : 0),								\
    (LIST).aptr++,							\
    ((float*)(LIST).aptr)[-1] = (float)(VAL),				\
    0))

#define _av_double(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   (((LIST).aptr < &(LIST).args[8]					\
     ? ((LIST).darg_mask |= (unsigned int)1 << ((LIST).aptr - (LIST).args), 0) \
     : 0),								\
    (LIST).aptr++,							\
    ((double*)(LIST).aptr)[-1] = (double)(VAL),				\
    0))

#endif

#if defined(__arm__) && !defined(__armhf__)

#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((float*)(LIST).aptr)[-1] = (float)(VAL),				\
    0))

#define _av_double(LIST,VAL)						\
  ((__avword*)(((uintptr_t)(LIST).aptr + 15) & -8) > (LIST).eptr	\
   ? -1 :								\
   ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr + 15) & -8),	\
    (LIST).tmp._double = (double)(VAL),					\
    (LIST).aptr[-2] = (LIST).tmp.words[0],				\
    (LIST).aptr[-1] = (LIST).tmp.words[1],				\
    0))

#endif

#if defined(__armhf__)

/* Up to 16 float or up to 8 double args can be passed in float registers.
 * But they overlap: {s0,s1} = d0, {s2,s3} = d1, and so on.
 */
#define _av_float(LIST,VAL)						\
  ((LIST).fanum <= 15							\
   ? ((LIST).fargs[(LIST).fanum] = (float)(VAL),			\
      (LIST).farg_mask |= ((unsigned int) 1) << (LIST).fanum,		\
      (LIST).fanum++,							\
      0)								\
   : ((LIST).aptr >= (LIST).eptr					\
      ? -1 :								\
      ((*(float*)(LIST).aptr = (float)(VAL)),				\
       (LIST).aptr++,							\
       0)))

#define _av_double(LIST,VAL)						\
  (((LIST).fanum % 2 ? ((LIST).fanum++, 0) : 0),			\
   ((LIST).fanum <= 14							\
    ? ((LIST).dargs[(LIST).fanum / 2] = (double)(VAL),			\
       (LIST).darg_mask |= ((unsigned int) 1) << ((LIST).fanum / 2),	\
       (LIST).fanum += 2,						\
       0)								\
    : ((LIST).aptr + 2 > (LIST).eptr					\
       ? -1 :								\
       ((*(double*)(LIST).aptr = (double)(VAL)),			\
        (LIST).aptr += 2,						\
        0))))

#endif

#if defined(__arm64__)

/* Up to __AV_FARG_NUM float or double args can be passed in float registers. */
#define _av_float(LIST,VAL)						\
  ((LIST).fanum < __AV_FARG_NUM						\
   ? ((LIST).fargs[(LIST).fanum] = (float)(VAL),			\
      (LIST).farg_mask |= ((unsigned int) 1) << (LIST).fanum,		\
      (LIST).fanum++,							\
      0)								\
   : ((LIST).aptr >= (LIST).eptr					\
      ? -1 :								\
      ((*(float*)(LIST).aptr = (float)(VAL)),				\
       (LIST).aptr++,							\
       0)))

#define _av_double(LIST,VAL)						\
  (((LIST).fanum < __AV_FARG_NUM					\
    ? ((LIST).dargs[(LIST).fanum] = (double)(VAL),			\
       (LIST).darg_mask |= ((unsigned int) 1) << (LIST).fanum,		\
       (LIST).fanum++,							\
       0)								\
    : ((LIST).aptr >= (LIST).eptr					\
       ? -1 :								\
       ((*(double*)(LIST).aptr = (double)(VAL)),			\
        (LIST).aptr++,							\
        0))))

#endif

#if defined(__powerpc_aix__)

/* Up to __AV_FARG_NUM float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs.
 */

#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((float*)(LIST).aptr)[-1] = (float)(VAL),				\
    (LIST).faptr < &(LIST).fargs[__AV_FARG_NUM] && (*(LIST).faptr++ = (double)(float)(VAL)), \
    0))

#define _av_double(LIST,VAL)						\
  ((LIST).aptr + 2 > (LIST).eptr					\
   ? -1 :								\
   ((LIST).aptr += 2,							\
    (LIST).tmp._double = (double)(VAL),					\
    (LIST).aptr[-2] = (LIST).tmp.words[0],				\
    (LIST).aptr[-1] = (LIST).tmp.words[1],				\
    (LIST).faptr < &(LIST).fargs[__AV_FARG_NUM] && (*(LIST).faptr++ = (LIST).tmp._double), \
    0))

#endif

#if defined(__powerpc_sysv4__)

/* Up to __AV_FARG_NUM float or double non-varargs args can be passed in
 * float registers, without occupying space in the general registers.
 */

#define _av_float(LIST,VAL)						\
  ((LIST).faptr < &(LIST).fargs[__AV_FARG_NUM]				\
   ? ((*(LIST).faptr++ = (double)(float)(VAL)), 0)			\
   : ((LIST).aptr >= (LIST).eptr					\
      ? -1 :								\
      ((LIST).aptr++,							\
       ((float*)(LIST).aptr)[-1] = (float)(VAL),			\
       0)))

#define _av_double(LIST,VAL)						\
  ((LIST).faptr < &(LIST).fargs[__AV_FARG_NUM]				\
   ? ((*(LIST).faptr++ = (double)(VAL)), 0)				\
   : ((LIST).aptr + 2 > (LIST).eptr					\
      ? -1 :								\
      ((LIST).aptr += 2,						\
       (LIST).tmp._double = (double)(VAL),				\
       (LIST).aptr[-2] = (LIST).tmp.words[0],				\
       (LIST).aptr[-1] = (LIST).tmp.words[1],				\
       0)))

#endif

#if defined(__powerpc64__)

/* Up to __AV_FARG_NUM float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs.
 */

#if defined(_AIX)
#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((float*)(LIST).aptr)[(LIST).flags & __AV_AIXCC_FLOAT_ARGS ? -2 : -1] = (float)(VAL), \
    (LIST).faptr < &(LIST).fargs[__AV_FARG_NUM] && (*(LIST).faptr++ = (double)(float)(VAL)), \
    0))
#elif defined(_LITTLE_ENDIAN)
#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((float*)(LIST).aptr)[-2] = (float)(VAL),				\
    (LIST).faptr < &(LIST).fargs[__AV_FARG_NUM] && (*(LIST).faptr++ = (double)(float)(VAL)), \
    0))
#else /* _BIG_ENDIAN */
#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((float*)(LIST).aptr)[-1] = (float)(VAL),				\
    (LIST).faptr < &(LIST).fargs[__AV_FARG_NUM] && (*(LIST).faptr++ = (double)(float)(VAL)), \
    0))
#endif

#define _av_double(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((LIST).aptr++,							\
    ((double*)(LIST).aptr)[-1] = (double)(VAL),				\
    (LIST).faptr < &(LIST).fargs[__AV_FARG_NUM] && (*(LIST).faptr++ = (double)(VAL)), \
    0))

#endif

#if defined(__ia64__)

/* Up to 8 leading float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs.
 */
#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   ((*(float*)(LIST).aptr = (float)(VAL)),				\
    ((LIST).faptr < &(LIST).fargs[__AV_FARG_NUM] && (*(LIST).faptr = *(float*)(LIST).aptr, (LIST).faptr++)), \
    (LIST).aptr++,							\
    0))

#define _av_double(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   (*(double*)(LIST).aptr = (double)(VAL),				\
    ((LIST).faptr < &(LIST).fargs[__AV_FARG_NUM] && (*(LIST).faptr = *(double*)(LIST).aptr, (LIST).faptr++)), \
    (LIST).aptr++,							\
    0))

#endif

#if defined(__x86_64_sysv__)

/* Up to 8 leading float or double args can be passed in float registers.
 */
#define _av_float(LIST,VAL)						\
  ((LIST).faptr < &(LIST).fargs[__AV_FARG_NUM]				\
   ? (*(LIST).faptr = 0.0, *(float*)(LIST).faptr = (float)(VAL),	\
      (LIST).faptr++,							\
      0)								\
   : ((LIST).aptr >= (LIST).eptr					\
      ? -1 :								\
      ((*(float*)(LIST).aptr = (float)(VAL)),				\
       (LIST).aptr++,							\
       0)))

#define _av_double(LIST,VAL)						\
  ((LIST).faptr < &(LIST).fargs[__AV_FARG_NUM]				\
   ? (*(LIST).faptr = (double)(VAL),					\
      (LIST).faptr++,							\
      0)								\
   : ((LIST).aptr >= (LIST).eptr					\
      ? -1 :								\
      ((*(double*)(LIST).aptr = (double)(VAL)),				\
       (LIST).aptr++,							\
       0)))

#endif

#if defined(__x86_64_ms__)

/* The float or double args among the first 4 argument words are passed
 * in floating-point registers, but we also push them into the
 * corresponding integer registers in case of varargs.
 */
#define _av_float(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   (((LIST).anum < 4							\
     ? ((LIST).farg_mask |= (1 << (LIST).anum),				\
        (LIST).fargs[(LIST).anum] = *(float*)(LIST).aptr = (float)(VAL)) \
     : (*(float*)(LIST).aptr = (float)(VAL))),				\
    (LIST).anum++,							\
    (LIST).aptr++,							\
    0))

#define _av_double(LIST,VAL)						\
  ((LIST).aptr >= (LIST).eptr						\
   ? -1 :								\
   (((LIST).anum < 4							\
     ? ((LIST).darg_mask |= (1 << (LIST).anum),				\
        (LIST).dargs[(LIST).anum] = *(double*)(LIST).aptr = (double)(VAL)) \
     : (*(double*)(LIST).aptr = (double)(VAL))),			\
    (LIST).anum++,							\
    (LIST).aptr++,							\
    0))

#endif

#if defined(__s390__) && !defined(__s390x__)

/* Up to 2 float or double non-varargs args can be passed in
 * float registers, without occupying space in the general registers.
 */

#define _av_float(LIST,VAL)						\
  ((LIST).fanum < __AV_FARG_NUM						\
   ? ((LIST).fargs[(LIST).fanum] = (float)(VAL),			\
      (LIST).farg_mask |= ((unsigned int) 1) << (LIST).fanum,		\
      (LIST).fanum++,							\
      0)								\
   : ((LIST).aptr >= (LIST).eptr					\
      ? -1 :								\
      ((LIST).aptr++,							\
       ((float*)(LIST).aptr)[-1] = (float)(VAL),			\
       0)))

#define _av_double(LIST,VAL)						\
  ((LIST).fanum < __AV_FARG_NUM						\
   ? ((LIST).dargs[(LIST).fanum] = (double)(VAL),			\
       (LIST).darg_mask |= ((unsigned int) 1) << (LIST).fanum,		\
       (LIST).fanum++,							\
       0)								\
   : ((LIST).aptr + 2 > (LIST).eptr					\
      ? -1 :								\
      ((LIST).aptr += 2,						\
       (LIST).tmp._double = (double)(VAL),				\
       (LIST).aptr[-2] = (LIST).tmp.words[0],				\
       (LIST).aptr[-1] = (LIST).tmp.words[1],				\
       0)))

#endif

#if defined(__s390x__)

/* Up to __AV_FARG_NUM float or double args can be passed in float registers. */
#define _av_float(LIST,VAL)						\
  ((LIST).fanum < __AV_FARG_NUM						\
   ? ((LIST).fargs[(LIST).fanum] = (float)(VAL),			\
      (LIST).farg_mask |= ((unsigned int) 1) << (LIST).fanum,		\
      (LIST).fanum++,							\
      0)								\
   : ((LIST).aptr >= (LIST).eptr					\
      ? -1 :								\
      ((LIST).aptr++,							\
       ((float*)(LIST).aptr)[-1] = (float)(VAL),			\
       0)))

#define _av_double(LIST,VAL)						\
  (((LIST).fanum < __AV_FARG_NUM					\
    ? ((LIST).dargs[(LIST).fanum] = (double)(VAL),			\
       (LIST).darg_mask |= ((unsigned int) 1) << (LIST).fanum,		\
       (LIST).fanum++,							\
       0)								\
    : ((LIST).aptr >= (LIST).eptr					\
       ? -1 :								\
       ((*(double*)(LIST).aptr = (double)(VAL)),			\
        (LIST).aptr++,							\
        0))))

#endif

/*
 * structure argument types
 */

extern void avcall_structcpy (void* dest, const void* src, unsigned long size, unsigned long alignment);

#define __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,PLACE,VAL_ADDR)		\
  avcall_structcpy(PLACE,VAL_ADDR,TYPE_SIZE,TYPE_ALIGN)

/* Structure argument alignment. */
#if defined(__i386__) && defined(_MSC_VER)
/* In MSVC, doubles inside structures have alignment 8, i.e.
 * __AV_alignof(double) = 8, but doubles (and also structures containing
 * doubles) are passed on the stack with alignment 4. Looks really weird.
 */
#define __av_struct_alignment(TYPE_ALIGN)  \
  ((TYPE_ALIGN) <= 4 ? (TYPE_ALIGN) : 4)
#else
#define __av_struct_alignment(TYPE_ALIGN)  \
  (TYPE_ALIGN)
#endif
#if defined(__i386__) || defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) || defined(__alpha__) || defined(__hppa64__) || defined(__arm__) || defined(__armhf__) || defined(__powerpc_aix__) || defined(__powerpc64__) || defined(__ia64__)
/* Structures are passed as fully aligned structures on the arg stack.
 * We align the aptr, store the structure, then fill to word alignment.
 * Single-small-integer structures are NOT promoted to integers and have
 * different alignment.
 */
/* little endian -> small structures < 1 word are adjusted to the left (i.e. occupy the low bits of the word) */
#if defined(__i386__) || defined(__alpha__) || (defined(__arm__) && !defined(__armhf__) && defined(__ARMEL__))
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN)) > (LIST).eptr \
   ? -1 :								\
   (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
    (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN)) +sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
    0))
#endif
#if defined(__ia64__)
/* With GCC < 3, types larger than a word have 2-word alignment. */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  (((LIST).flags & __AV_OLDGCC_STRUCT_ARGS)				\
   ? ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN)), \
      ((TYPE_SIZE) > sizeof(__avword) && (((LIST).aptr - &(LIST).args[0]) & 1) ? ++(LIST).aptr : 0), \
      ((LIST).aptr > (LIST).eptr					\
       ? -1 :								\
       (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr-(TYPE_SIZE)),VAL), \
        (LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr+sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
        0)))								\
   : ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN)) > (LIST).eptr \
      ? -1 :								\
      (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
       (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN)) +sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
       0)))
#endif
/* small structures < 1 word are adjusted depending on compiler */
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
#define __av_struct_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)		\
  ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) > (LIST).eptr \
   ? -1 :								\
   (++(LIST).anum,							\
    __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
    (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) +sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
    0))
#define __av_struct_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)	\
  ((__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
   ? -1 :								\
   ((LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
    ++(LIST).anum,						\
    __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr-(TYPE_SIZE)),VAL),\
    0))
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((LIST).flags & __AV_SGICC_STRUCT_ARGS				\
   ? /* SGI MIPS cc passes small structures left-adjusted, although big-endian! */\
     __av_struct_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)		\
   : /* SGI MIPS gcc passes small structures within the first four words left-	  \
      * adjusted, for compatibility with cc. But structures in memory are passed  \
      * right-adjusted!! See gcc-2.6.3/config/mips/mips.c:function_arg().	  \
      */									  \
     ((LIST).aptr < &(LIST).args[4]					\
      ? __av_struct_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)		\
      : __av_struct_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)))
#endif
#if defined(__mipsn32__) || defined(__mips64__)
/* When a structure is passed (partially) in registers, it is passed in the
 * integer registers, except that doubles within the structure are passed in
 * the floating point registers. Instead of distinguishing these cases, we
 * always pass the structure in both the integer and the floating point
 * registers.
 */
#define __av_struct_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)		\
  ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) > (LIST).eptr \
   ? -1 :								\
   (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
    (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) +sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
    ((LIST).anum < 8 && ((LIST).darg_mask |= (-1 << (LIST).anum))),	\
    (LIST).anum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))/sizeof(__avword), \
    (LIST).darg_mask &= (1 << ((LIST).anum < 8 ? (LIST).anum : 8)) - 1, \
    0))
#define __av_struct_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)	\
  ((__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
   ? -1 :								\
   ((LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
    __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr-(TYPE_SIZE)),VAL), \
    ((LIST).anum < 8 && ((LIST).darg_mask |= (-1 << (LIST).anum))),	\
    (LIST).anum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))/sizeof(__avword), \
    (LIST).darg_mask &= (1 << ((LIST).anum < 8 ? (LIST).anum : 8)) - 1, \
    0))
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((LIST).flags & __AV_SGICC_STRUCT_ARGS				\
   ? /* SGI MIPS cc and gcc >= 3.4 passes small structures left-adjusted, although big-endian! */\
     __av_struct_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)		\
   : /* SGI MIPS gcc < 3.4 passes small structures right-adjusted. */	\
     __av_struct_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL))
#endif
#if (defined(__armhf__) && defined(__ARMEL__))
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((((LIST).ianum*sizeof(__avword)+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) <= __AV_IARG_NUM*sizeof(__avword) \
   ? ((LIST).ianum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))/sizeof(__avword), \
      __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)&(LIST).args[(LIST).ianum]-(TYPE_SIZE)),VAL), \
      0)								\
   : ((LIST).aptr == &(LIST).args[__AV_IARG_NUM]			\
      ? /* split case */						\
        ((__avword*)(((((uintptr_t)&(LIST).args[(LIST).ianum]+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
         ? -1 :								\
         (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)&(LIST).args[(LIST).ianum]+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
          (LIST).aptr = (__avword*)(((((uintptr_t)&(LIST).args[(LIST).ianum]+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
          (LIST).ianum = __AV_IARG_NUM,					\
          0))								\
      : ((__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
         ? -1 :								\
         (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
          (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
          (LIST).ianum = __AV_IARG_NUM,					\
          0))))
#endif
#if defined(__powerpc__) || defined(__powerpc64__)
#define __av_struct_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)		\
  ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) > (LIST).eptr \
   ? -1 :								\
   (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
    (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) +sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
    0))
#define __av_struct_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)	\
  ((__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
   ? -1 :								\
   ((LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
    __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr-(TYPE_SIZE)),VAL), \
    0))
#if (defined(__powerpc__) && !defined(__powerpc64__)) || (defined(__powerpc64__) && defined(_BIG_ENDIAN))
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((LIST).flags & __AV_AIXCC_STRUCT_ARGS				\
   ? /* AIX cc and xlc pass small structures left-adjusted, although big-endian! */\
     __av_struct_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)		\
   : /* gcc passes small structures right-adjusted. */			\
     __av_struct_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL))
#endif
#if (defined(__powerpc64__) && defined(_LITTLE_ENDIAN))
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  __av_struct_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)
#endif
#endif
/* big endian -> small structures < 1 word are adjusted to the right (i.e. occupy the high bits of the word) */
#if (defined(__arm__) && !defined(__armhf__) && !defined(__ARMEL__))
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
   ? -1 :								\
   ((LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
    __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr-(TYPE_SIZE)),VAL), \
    0))
#endif
#if (defined(__armhf__) && !defined(__ARMEL__))
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((((LIST).ianum*sizeof(__avword)+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) <= __AV_IARG_NUM*sizeof(__avword) \
   ? ((LIST).ianum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))/sizeof(__avword), \
      __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)&(LIST).args[(LIST).ianum]-(TYPE_SIZE)),VAL), \
      0)								\
   : ((LIST).aptr == &(LIST).args[__AV_IARG_NUM]			\
      ? /* split case */						\
        ((__avword*)(((((uintptr_t)&(LIST).args[(LIST).ianum]+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
         ? -1 :								\
         ((LIST).aptr = (__avword*)(((((uintptr_t)&(LIST).args[(LIST).ianum]+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
          __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr-(TYPE_SIZE)),VAL), \
          (LIST).ianum = __AV_IARG_NUM,					\
          0))								\
      : ((__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
         ? -1 :								\
         ((LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
          __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr-(TYPE_SIZE)),VAL), \
          (LIST).ianum = __AV_IARG_NUM,					\
          0))))
#endif
#if defined(__hppa64__)
/* Structures are passed left-adjusted (although big-endian!). */
#define __av_struct_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)		\
  ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) > (LIST).eptr \
   ? -1 :								\
   (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
    (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) +sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
    0))
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  __av_struct_leftadjusted(LIST,TYPE_SIZE,(TYPE_SIZE)>sizeof(__avword)?2*sizeof(__avword):(TYPE_ALIGN),VAL)
#endif
#endif
#if defined(__m68k__)
/* Structures are passed as embedded copies on the arg stack.
 */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)) > (LIST).eptr \
    ? -1 :								\
    ((LIST).aptr = (__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
     __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr-(TYPE_SIZE)),VAL),\
     0))
#endif
#if (defined(__sparc__) && !defined(__sparc64__))
/* Structures are passed as pointers to caller-made local copies. We
 * grab space for the copies from the end of the argument list space
 * and always use maximal (double) alignment.
 */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
   (++(LIST).aptr							\
    > ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
    ? -1 :								\
    (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL),	\
     (LIST).aptr[-1] = (__avword)(LIST).eptr,				\
     0))
#endif
#if defined(__sparc64__)
/* Structures <= 16 bytes are passed as embedded copies on the arg stack,
 * left-adjusted (although big-endian!).
 * When a structure is passed (partially) in registers, it is passed in the
 * integer registers, except that floats and doubles within the structure
 * are passed in the floating point registers. Instead of distinguishing
 * these cases, we always pass the structure in both the integer and the
 * floating point registers.
 * Big structures are passed as pointers to caller-made local copies.
 * FIXME: Shouldn't (LIST).anum be incremented in sync with (LIST).aptr ?
 */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((TYPE_SIZE) > 16							\
   ? (++(LIST).aptr							\
      > ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
      ? -1 :								\
      (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL),	\
       (LIST).aptr[-1] = (__avword)(LIST).eptr,				\
       0))								\
   : ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) > (LIST).eptr \
      ? -1 :								\
      (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
       (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) +sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
       ((LIST).anum < 16 && ((LIST).darg_mask |= (-1 << (LIST).anum))),	\
       (LIST).anum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))/sizeof(__avword), \
       (LIST).darg_mask &= (1 << ((LIST).anum < 16 ? (LIST).anum : 16)) - 1, \
       0)))
#endif
#if defined(__hppa__) && !defined(__hppa64__)
/* Structures <= 8 bytes are passed as embedded copies on the arg stack.
 * Big structures are passed as pointers to caller-made local copies.
 */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((TYPE_SIZE) > 8							\
   ? (--(LIST).aptr							\
      < ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr + (((TYPE_SIZE) + 7) & -8))) \
      ? -1								\
      : (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE) + 7) & -8)), VAL), \
         *(LIST).aptr = (__avword)((uintptr_t)(LIST).eptr - (((TYPE_SIZE) + 7) & -8)), \
         0))								\
   : ((TYPE_SIZE) > 4							\
      ? ((__avword*)((((uintptr_t)(LIST).aptr & -8) - (intptr_t)(TYPE_SIZE)) & -8) < (LIST).eptr \
         ? -1 :								\
         ((LIST).aptr = (__avword*)((((uintptr_t)(LIST).aptr & -8) - (intptr_t)(TYPE_SIZE)) & -8), \
          __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).aptr,VAL), \
          0))								\
      : /* FIXME: gcc-2.6.3 passes structures <= 4 bytes in memory left-adjusted! ?? */\
        ((__avword*)(((uintptr_t)(LIST).aptr & -4) - (intptr_t)(TYPE_SIZE)) < (LIST).eptr \
         ? -1 :								\
         (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(((uintptr_t)(LIST).aptr & -4) - (intptr_t)(TYPE_SIZE)),VAL), \
          (LIST).aptr = (__avword*)((((uintptr_t)(LIST).aptr & -4) - (intptr_t)(TYPE_SIZE)) & -4),	\
          0))))
#endif
#if defined(__arm64__)
/* Structures <= 16 bytes are passed as embedded copies on the arg stack.
 * Big structures are passed as pointers to caller-made local copies.
 */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((TYPE_SIZE) <= 16							\
   ? ((((LIST).ianum*sizeof(__avword)+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) <= __AV_IARG_NUM*sizeof(__avword) \
      ? (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)&(LIST).iargs[(LIST).ianum],VAL), \
         (LIST).ianum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))/sizeof(__avword), \
         0)								\
      : ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) > (LIST).eptr \
         ? -1 :								\
         ((LIST).ianum = __AV_IARG_NUM,					\
          __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
          (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) +sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
          0)))								\
   : ((LIST).ianum < __AV_IARG_NUM					\
      ? ((LIST).aptr							\
         > ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
         ? -1 :								\
         (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL), \
          (LIST).iargs[(LIST).ianum++] = (__avword)(LIST).eptr,		\
          0))								\
      : (++(LIST).aptr							\
         > ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
         ? -1 :								\
         (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL), \
          (LIST).aptr[-1] = (__avword)(LIST).eptr,			\
          0))))
#endif
#if defined(__powerpc_sysv4__)
/* Structures are passed as pointers to caller-made local copies. We
 * grab space for the copies from the end of the argument list space
 * and always use maximal (double) alignment.
 */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
   ((LIST).ianum < __AV_IARG_NUM					\
    ? ((LIST).aptr							\
       > ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
       ? -1 :								\
       (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL),	\
        (LIST).iargs[(LIST).ianum++] = (__avword)(LIST).eptr,		\
        0))								\
    : (++(LIST).aptr							\
       > ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
       ? -1 :								\
       (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL),	\
        (LIST).aptr[-1] = (__avword)(LIST).eptr,			\
        0)))
#endif
#if defined(__x86_64_sysv__)
/* Structures <= 16 bytes can be passed in integer or floating-point registers
   if there is enough room for the whole number of words needed by the structure
   in the corresponding iargs/fargs block. We can't distinguish the two cases
   and support only passing in integer registers. Other structures are passed
   on the arg stack. */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)				\
  (((TYPE_SIZE) <= 2*sizeof(__avword)						\
    && (LIST).ianum + ((TYPE_SIZE) + sizeof(__avword)-1) / sizeof(__avword) <= __AV_IARG_NUM) \
   ? (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)&(LIST).iargs[(LIST).ianum],VAL), \
      (LIST).ianum += ((TYPE_SIZE) + sizeof(__avword)-1) / sizeof(__avword),	\
      0)									\
   : ((__avword*)((uintptr_t)(LIST).aptr + (((TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN))) > (LIST).eptr \
      ? -1 :									\
      ((LIST).aptr = (__avword*)((uintptr_t)(LIST).aptr + (((TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN))), \
       __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr - (((TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(intptr_t)__av_struct_alignment(TYPE_ALIGN))),VAL), \
       0)))
#endif
#if defined(__x86_64_ms__)
/* Structures of 1, 2, 4, 8 bytes are passed as embedded copies on the arg stack.
 * Big structures are passed as pointers to caller-made local copies.
 */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8	\
   ? ((__avword*)((uintptr_t)(LIST).aptr + (((TYPE_SIZE)+sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))) > (LIST).eptr \
      ? -1 :								\
      ((LIST).aptr = (__avword*)((uintptr_t)(LIST).aptr + (((TYPE_SIZE)+sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))), \
       __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)(LIST).aptr - (((TYPE_SIZE)+sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))),VAL), \
       0))								\
   : (++(LIST).aptr							\
      > ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
      ? -1 :								\
      (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL),	\
       (LIST).aptr[-1] = (__avword)(LIST).eptr,				\
       0)))
#endif
#if defined(__s390__) || defined(__s390x__)
/* Structures of 1, 2, 4, 8 bytes are passed as embedded copies on the arg stack.
 * Big structures are passed as pointers to caller-made local copies.
 */
#define __av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL)			\
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8	\
   ? ((((LIST).ianum*sizeof(__avword)+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) <= __AV_IARG_NUM*sizeof(__avword) \
      ? ((LIST).ianum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(intptr_t)sizeof(__avword))/sizeof(__avword), \
         __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((uintptr_t)&(LIST).iargs[(LIST).ianum]-(TYPE_SIZE)),VAL), \
         0)								\
      : ((__avword*)(((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) > (LIST).eptr \
         ? -1 :								\
         ((LIST).ianum = __AV_IARG_NUM,					\
          __av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) - (TYPE_SIZE)),VAL), \
          (LIST).aptr = (__avword*)(((((uintptr_t)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(intptr_t)(TYPE_ALIGN)) +sizeof(__avword)-1) & -(intptr_t)sizeof(__avword)), \
          0)))								\
   : ((LIST).ianum < __AV_IARG_NUM					\
      ? ((LIST).aptr							\
         > ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
         ? -1 :								\
         (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL), \
          (LIST).iargs[(LIST).ianum++] = (__avword)(LIST).eptr,		\
          0))								\
      : (++(LIST).aptr							\
         > ((LIST).eptr = (__avword*)((uintptr_t)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
         ? -1 :								\
         (__av_struct_copy(TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL), \
          (LIST).aptr[-1] = (__avword)(LIST).eptr,			\
          0))))
#endif


#endif /* _AVCALL_INTERNAL_H */
