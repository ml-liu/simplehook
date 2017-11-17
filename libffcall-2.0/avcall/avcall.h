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

#ifndef _AVCALL_H
#define _AVCALL_H
/*----------------------------------------------------------------------
  av_call() foreign function interface.

  Varargs-style macros to build a C argument list incrementally
  and call a function on it.
 ----------------------------------------------------------------------*/

#include <stddef.h>

#include "ffcall-version.h"
#include "ffcall-abi.h"


/* Max # words in argument-list and temporary structure storage.
 */
#ifndef __AV_ALIST_WORDS
#define __AV_ALIST_WORDS  256
#endif

/* Determine whether the current ABI is LLP64
   ('long' = 32-bit, 'long long' = 'void*' = 64-bit). */
#if defined(__x86_64__) && (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)
#define __AV_LLP64 1
#endif

/* Determine the alignment of a type at compile time.
 */
#if defined(__GNUC__) || defined(__IBM__ALIGNOF__)
#define __AV_alignof __alignof__
#elif defined(__cplusplus)
template <class type> struct __AV_alignof_helper { char __slot1; type __slot2; };
#define __AV_alignof(type) offsetof (__AV_alignof_helper<type>, __slot2)
#elif defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) /* SGI compiler */
#define __AV_alignof __builtin_alignof
#else
#define __AV_offsetof(type,ident)  ((unsigned long)&(((type*)0)->ident))
#define __AV_alignof(type)  __AV_offsetof(struct { char __slot1; type __slot2; }, __slot2)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* C builtin types.
 */
#if defined(__mipsn32__) || defined(__x86_64_x32__) || defined(__AV_LLP64)
typedef long long __avword;
#else
typedef long __avword;
#endif

enum __AVtype
{
  __AVword,
  __AVvoid,
  __AVchar,
  __AVschar,
  __AVuchar,
  __AVshort,
  __AVushort,
  __AVint,
  __AVuint,
  __AVlong,
  __AVulong,
  __AVlonglong,
  __AVulonglong,
  __AVfloat,
  __AVdouble,
  __AVvoidp,
  __AVstruct
};

enum __AV_alist_flags
{

  /* how to return structs */
  /* There are basically 3 ways to return structs:
   * a. The called function returns a pointer to static data. Not reentrant.
   *    Not supported any more.
   * b. The caller passes the return structure address in a dedicated register
   *    or as a first (or last), invisible argument. The called function stores
   *    its result there.
   * c. Like b, and the called function also returns the return structure
   *    address in the return value register. (This is not very distinguishable
   *    from b.)
   * Independently of this,
   * r. small structures (<= 4 or <= 8 bytes) may be returned in the return
   *    value register(s), or
   * m. even small structures are passed in memory.
   */
  /* gcc-2.6.3 employs the following strategy:
   *   - If PCC_STATIC_STRUCT_RETURN is defined in the machine description
   *     it uses method a, else method c.
   *   - If flag_pcc_struct_return is set (either by -fpcc-struct-return or if
   *     DEFAULT_PCC_STRUCT_RETURN is defined to 1 in the machine description)
   *     it uses method m, else (either by -freg-struct-return or if
   *     DEFAULT_PCC_STRUCT_RETURN is defined to 0 in the machine description)
   *     method r.
   */
  __AV_SMALL_STRUCT_RETURN	= 1<<1,	/* r: special case for small structs */
  __AV_GCC_STRUCT_RETURN	= 1<<2,	/* consider 8 byte structs as small */
#if defined(__sparc__) && !defined(__sparc64__)
  __AV_SUNCC_STRUCT_RETURN	= 1<<3,
  __AV_SUNPROCC_STRUCT_RETURN	= 1<<4,
#endif
#if defined(__i386__)
  __AV_MSVC_STRUCT_RETURN	= 1<<4,
#endif
  /* the default way to return structs */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another struct returning convention,
   * just  #define __AV_STRUCT_RETURN ...
   * before or after #including <avcall.h>.
   */
#ifndef __AV_STRUCT_RETURN
  __AV_STRUCT_RETURN		=
#if defined(__sparc__) && !defined(__sparc64__) && defined(__sun) && (defined(__SUNPRO_C) || defined(__SUNPRO_CC)) /* SUNWspro cc or CC */
				  __AV_SUNPROCC_STRUCT_RETURN,
#else
#if (defined(__i386__) && (defined(_WIN32) || defined(__CYGWIN__) || (defined(__MACH__) && defined(__APPLE__)) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__OpenBSD__))) || defined(__m68k__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__) || defined(__hppa__) || defined(__hppa64__) || defined(__arm__) || defined(__armhf__) || defined(__arm64__) || defined(__powerpc64_elfv2__) || defined(__ia64__) || defined(__x86_64__)
				  __AV_SMALL_STRUCT_RETURN |
#endif
#if defined(__GNUC__) && !((defined(__mipsn32__) || defined(__mips64__)) && ((__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ > 3)))
				  __AV_GCC_STRUCT_RETURN |
#endif
#if defined(__i386__) && (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__) /* native Windows */
				  __AV_MSVC_STRUCT_RETURN |
#endif
				  0,
#endif
#endif

  /* how to return floats */
#if defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__))
  __AV_SUNCC_FLOAT_RETURN	= 1<<5,
#endif
#if defined(__m68k__)
  __AV_FREG_FLOAT_RETURN	= 1<<6,
#endif
  /* the default way to return floats */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another float returning convention,
   * just  #define __AV_FLOAT_RETURN ...
   * before or after #including <avcall.h>.
   */
#ifndef __AV_FLOAT_RETURN
#if (defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__))) && !defined(__GNUC__) && defined(__sun) && !(defined(__SUNPRO_C) || defined(__SUNPRO_CC))  /* Sun cc or CC */
  __AV_FLOAT_RETURN		= __AV_SUNCC_FLOAT_RETURN,
#elif defined(__m68k__)
  __AV_FLOAT_RETURN		= __AV_FREG_FLOAT_RETURN,
#else
  __AV_FLOAT_RETURN		= 0,
#endif
#endif

  /* how to pass structs */
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
  __AV_SGICC_STRUCT_ARGS	= 1<<7,
#endif
#if defined(__powerpc__) || defined(__powerpc64__)
  __AV_AIXCC_STRUCT_ARGS	= 1<<7,
#endif
#if defined(__ia64__)
  __AV_OLDGCC_STRUCT_ARGS	= 1<<7,
#endif
  /* the default way to pass structs */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another struct passing convention,
   * just  #define __AV_STRUCT_ARGS ...
   * before or after #including <avcall.h>.
   */
#ifndef __AV_STRUCT_ARGS
#if (defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)) && !defined(__GNUC__) /* SGI mips cc */
  __AV_STRUCT_ARGS		= __AV_SGICC_STRUCT_ARGS,
#else
#if (defined(__mipsn32__) || defined(__mips64__)) && (!defined(__GNUC__) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ > 3)) /* SGI mips cc or gcc >= 3.4 */
  __AV_STRUCT_ARGS		= __AV_SGICC_STRUCT_ARGS,
#else
#if defined(__powerpc__) && !defined(__powerpc64__) && defined(_AIX) && !defined(__GNUC__) /* AIX 32-bit cc, xlc */
  __AV_STRUCT_ARGS		= __AV_AIXCC_STRUCT_ARGS,
#else
#if defined(__powerpc64__) && defined(_AIX) /* AIX 64-bit cc, xlc, gcc */
  __AV_STRUCT_ARGS		= __AV_AIXCC_STRUCT_ARGS,
#else
#if defined(__ia64__) && !(defined(__GNUC__) && (__GNUC__ >= 3))
  __AV_STRUCT_ARGS		= __AV_OLDGCC_STRUCT_ARGS,
#else
  __AV_STRUCT_ARGS		= 0,
#endif
#endif
#endif
#endif
#endif
#endif

  /* how to pass floats */
  /* ANSI C compilers and GNU gcc pass floats as floats.
   * K&R C compilers pass floats as doubles. We don't support them any more.
   */
#if defined(__powerpc64__)
  __AV_AIXCC_FLOAT_ARGS         = 1<<8,      /* pass floats in the low 4 bytes of an 8-bytes word */
#endif
  /* the default way to pass floats */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another float passing convention,
   * just  #define __AV_FLOAT_ARGS ...
   * before or after #including <avcall.h>.
   */
#ifndef __AV_FLOAT_ARGS
#if defined(__powerpc64__) && defined(_AIX) && !defined(__GNUC__) /* AIX 64-bit xlc */
  __AV_FLOAT_ARGS		= __AV_AIXCC_FLOAT_ARGS,
#else
  __AV_FLOAT_ARGS		= 0,
#endif
#endif

  /* how to pass and return small integer arguments */
  __AV_ANSI_INTEGERS		= 0, /* no promotions */
  __AV_TRADITIONAL_INTEGERS	= 0, /* promote [u]char, [u]short to [u]int */
  /* Fortunately these two methods are compatible. Our macros work with both. */

  /* stack cleanup policy */
  __AV_CDECL_CLEANUP		= 0, /* caller pops args after return */
  __AV_STDCALL_CLEANUP		= 0, /* callee pops args before return */
				     /* currently only supported on __i386__ */
#ifndef __AV_CLEANUP
  __AV_CLEANUP			= __AV_CDECL_CLEANUP,
#endif

  /* These are for internal use only */
#if defined(__i386__) || defined(__m68k__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__hppa64__) || defined(__arm__) || defined(__armhf__) || defined(__arm64__) || defined(__powerpc__) || defined(__powerpc64__) || defined(__ia64__) || defined(__x86_64__) || (defined(__s390__) && !defined(__s390x__))
  __AV_REGISTER_STRUCT_RETURN	= 1<<9,
#endif

  __AV_flag_for_broken_compilers_that_dont_like_trailing_commas
};

#ifdef _AVCALL_INTERNAL_H
#include "avcall-alist.h"
#endif

/* An upper bound for sizeof(__av_alist).
   The total size of the __av_alist fields, ignoring alignment of fields,
   varies from
     40 bytes (for __i386__, __m68k__, __sparc__, __hppa__, __arm__)
   to
     232 bytes (for __arm64__). */
#define __AV_ALIST_SIZE_BOUND 256

typedef struct
{
  /* First part: Fixed size __av_alist. */
  union {
    char _av_m_room[__AV_ALIST_SIZE_BOUND];
#ifdef _AVCALL_INTERNAL_H
    __av_alist _av_m_alist;
#endif
/* GNU clisp pokes in internals of the alist!
   When used by GNU clisp, assume a C compiler that supports anonymous unions
   (GCC or an ISO C 11 compiler). */
#ifdef LISPFUN
    int flags;
#endif
    /* For alignment. */
    long align1;
    double align2;
    long long align3;
    long double align4;
  }
#ifndef LISPFUN
  _av_alist_head
#endif
  ;
  /* Second part: An array whose size depends on __AV_ALIST_WORDS. */
  union {
    __avword _av_m_args[__AV_ALIST_WORDS];
    /* For alignment. */
    long align1;
    double align2;
    long long align3;
    long double align4;
  } _av_alist_flexarray;
} av_alist;


/* Delayed overflow detection */
extern int avcall_overflown (av_alist* /* LIST */);
#define av_overflown(LIST) avcall_overflown(&(LIST))


/*
 *  av_start_<type> macros which specify the return type
 */

#define __AV_START_FLAGS  \
  __AV_STRUCT_RETURN | __AV_FLOAT_RETURN | __AV_STRUCT_ARGS | __AV_FLOAT_ARGS | __AV_CLEANUP

extern void avcall_start (av_alist* /* LIST */, __avword* /* LIST_ARGS */, __avword* /* LIST_ARGS_END */, __avword(* /* FUNC */)(), void* /* RADDR */, int /* RETTYPE */, int /* FLAGS */);

#define av_start_void(LIST,FUNC)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),0,    __AVvoid,     __AV_START_FLAGS)
#define av_start_char(LIST,FUNC,RADDR)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVchar,     __AV_START_FLAGS)
#define av_start_schar(LIST,FUNC,RADDR)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVschar,    __AV_START_FLAGS)
#define av_start_uchar(LIST,FUNC,RADDR)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVuchar,    __AV_START_FLAGS)
#define av_start_short(LIST,FUNC,RADDR)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVshort,    __AV_START_FLAGS)
#define av_start_ushort(LIST,FUNC,RADDR)				\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVushort,   __AV_START_FLAGS)
#define av_start_int(LIST,FUNC,RADDR)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVint,      __AV_START_FLAGS)
#define av_start_uint(LIST,FUNC,RADDR)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVuint,     __AV_START_FLAGS)
#define av_start_long(LIST,FUNC,RADDR)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVlong,     __AV_START_FLAGS)
#define av_start_ulong(LIST,FUNC,RADDR)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVulong,    __AV_START_FLAGS)
#define av_start_longlong(LIST,FUNC,RADDR)				\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVlonglong, __AV_START_FLAGS)
#define av_start_ulonglong(LIST,FUNC,RADDR)				\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVulonglong,__AV_START_FLAGS)
#define av_start_float(LIST,FUNC,RADDR)					\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVfloat,    __AV_START_FLAGS)
#define av_start_double(LIST,FUNC,RADDR)				\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVdouble,   __AV_START_FLAGS)
#define av_start_ptr(LIST,FUNC,TYPE,RADDR)				\
  avcall_start(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),RADDR,__AVvoidp,    __AV_START_FLAGS)

extern void avcall_start_struct (av_alist* /* LIST */, __avword* /* LIST_ARGS */, __avword* /* LIST_ARGS_END */, __avword(* /* FUNC */)(), size_t /* TYPE_SIZE */, int /* TYPE_SPLITTABLE */, void* /* RADDR */, int /* FLAGS */);

#define av_start_struct(LIST,FUNC,TYPE,TYPE_SPLITTABLE,RADDR)		\
  _av_start_struct(LIST,FUNC,sizeof(TYPE),TYPE_SPLITTABLE,RADDR)
/* Undocumented, but used by GNU clisp. */
#define _av_start_struct(LIST,FUNC,TYPE_SIZE,TYPE_SPLITTABLE,RADDR)	\
  avcall_start_struct(&(LIST),(LIST)._av_alist_flexarray._av_m_args,&(LIST)._av_alist_flexarray._av_m_args[__AV_ALIST_WORDS],(__avword(*)())(FUNC),TYPE_SIZE,TYPE_SPLITTABLE,RADDR,__AV_START_FLAGS)


/*
 * av_<type> macros which specify the argument and its type
 */

/* integer argument types */

extern int avcall_arg_long (av_alist* /* LIST */, long /* VAL */);
extern int avcall_arg_ulong (av_alist* /* LIST */, unsigned long /* VAL */);

#define av_char(LIST,VAL)	avcall_arg_long(&(LIST),(char)(VAL))
#define av_schar(LIST,VAL)	avcall_arg_long(&(LIST),(signed char)(VAL))
#define av_short(LIST,VAL)	avcall_arg_long(&(LIST),(short)(VAL))
#define av_int(LIST,VAL)	avcall_arg_long(&(LIST),(int)(VAL))
#define av_long(LIST,VAL)	avcall_arg_long(&(LIST),(long)(VAL))
#define av_uchar(LIST,VAL)	avcall_arg_ulong(&(LIST),(unsigned char)(VAL))
#define av_ushort(LIST,VAL)	avcall_arg_ulong(&(LIST),(unsigned short)(VAL))
#define av_uint(LIST,VAL)	avcall_arg_ulong(&(LIST),(unsigned int)(VAL))
#define av_ulong(LIST,VAL)	avcall_arg_ulong(&(LIST),(unsigned long)(VAL))

extern int avcall_arg_ptr (av_alist* /* LIST */, void* /* VAL */);

#define av_ptr(LIST,TYPE,VAL)	avcall_arg_ptr(&(LIST),(TYPE)(VAL))

extern int avcall_arg_longlong (av_alist* /* LIST */, long long /* VAL */);
extern int avcall_arg_ulonglong (av_alist* /* LIST */, unsigned long long /* VAL */);

#define av_longlong(LIST,VAL)	avcall_arg_longlong(&(LIST),VAL)
#define av_ulonglong(LIST,VAL)	avcall_arg_ulonglong(&(LIST),VAL)

/* floating-point argument types */

extern int avcall_arg_float (av_alist* /* LIST */, float /* VAL */);
#define av_float(LIST,VAL)	avcall_arg_float(&(LIST),VAL)

extern int avcall_arg_double (av_alist* /* LIST */, double /* VAL */);
#define av_double(LIST,VAL)	avcall_arg_double(&(LIST),VAL)

/*
 * structure argument types
 */

extern int avcall_arg_struct (av_alist* /* LIST */, size_t /* TYPE_SIZE */, size_t /* TYPE_ALIGN */, const void* /* VAL_ADDR */);

#define av_struct(LIST,TYPE,VAL)					\
  avcall_arg_struct(&(LIST),sizeof(TYPE),__AV_alignof(TYPE),&(VAL))
/* _av_struct() is like av_struct(), except that you pass the type's size and alignment
 * and the value's address instead of the type and the value themselves.
 * Undocumented, but used by GNU clisp.
 */
#define _av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL_ADDR)			\
  avcall_arg_struct(&(LIST),TYPE_SIZE,TYPE_ALIGN,VAL_ADDR)

/*
 * calling the function
 */

extern int avcall_call (av_alist* /* LIST */);
#define av_call(LIST) avcall_call(&(LIST))

/* Determine whether a struct type is word-splittable, i.e. whether each of
 * its components fit into a register.
 * The entire computation is done at compile time.
 */
#define av_word_splittable_1(slot1)  \
  (__av_offset1(slot1)/sizeof(__avword) == (__av_offset1(slot1)+sizeof(slot1)-1)/sizeof(__avword))
#define av_word_splittable_2(slot1,slot2)  \
  ((__av_offset1(slot1)/sizeof(__avword) == (__av_offset1(slot1)+sizeof(slot1)-1)/sizeof(__avword)) \
   && (__av_offset2(slot1,slot2)/sizeof(__avword) == (__av_offset2(slot1,slot2)+sizeof(slot2)-1)/sizeof(__avword)) \
  )
#define av_word_splittable_3(slot1,slot2,slot3)  \
  ((__av_offset1(slot1)/sizeof(__avword) == (__av_offset1(slot1)+sizeof(slot1)-1)/sizeof(__avword)) \
   && (__av_offset2(slot1,slot2)/sizeof(__avword) == (__av_offset2(slot1,slot2)+sizeof(slot2)-1)/sizeof(__avword)) \
   && (__av_offset3(slot1,slot2,slot3)/sizeof(__avword) == (__av_offset3(slot1,slot2,slot3)+sizeof(slot3)-1)/sizeof(__avword)) \
  )
#define av_word_splittable_4(slot1,slot2,slot3,slot4)  \
  ((__av_offset1(slot1)/sizeof(__avword) == (__av_offset1(slot1)+sizeof(slot1)-1)/sizeof(__avword)) \
   && (__av_offset2(slot1,slot2)/sizeof(__avword) == (__av_offset2(slot1,slot2)+sizeof(slot2)-1)/sizeof(__avword)) \
   && (__av_offset3(slot1,slot2,slot3)/sizeof(__avword) == (__av_offset3(slot1,slot2,slot3)+sizeof(slot3)-1)/sizeof(__avword)) \
   && (__av_offset4(slot1,slot2,slot3,slot4)/sizeof(__avword) == (__av_offset4(slot1,slot2,slot3,slot4)+sizeof(slot4)-1)/sizeof(__avword)) \
  )
#define __av_offset1(slot1)  \
  0
#define __av_offset2(slot1,slot2)  \
  ((__av_offset1(slot1)+sizeof(slot1)+__AV_alignof(slot2)-1) & -(long)__AV_alignof(slot2))
#define __av_offset3(slot1,slot2,slot3)  \
  ((__av_offset2(slot1,slot2)+sizeof(slot2)+__AV_alignof(slot3)-1) & -(long)__AV_alignof(slot3))
#define __av_offset4(slot1,slot2,slot3,slot4)  \
  ((__av_offset3(slot1,slot2,slot3)+sizeof(slot3)+__AV_alignof(slot4)-1) & -(long)__AV_alignof(slot4))

#ifdef __cplusplus
}
#endif

#endif /* _AVCALL_H */
