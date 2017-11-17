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
#error "Never use <avcall-alist.h> directly; include <avcall-internal.h> instead."
#endif

/* The platform indicator symbols (__i386__, etc.) come from
   - "config.h" when compiling avcall-libapi.c,
   - the GCC command line options when compiling avcall-$(CPU).c.
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

/*
 * Definition of the ‘__av_alist’ type.
 */
/* Note: This struct must not contain members of type 'long' or 'unsigned long',
   because in the mingw port we use precompiled code that assumes 'long' is
   64-bit whereas avcall-libapi.c is then compiled by a compiler that has a
   32-bit 'long' type. */
typedef struct
{
  /* some av_... macros need these flags */
  int			flags;
  /* function to be called */
  __avword		(*func)();
  /* return type, address for the result */
  void*			raddr;
  enum __AVtype		rtype;
  uintptr_t		rsize;
  /* current pointer into the args[] array */
  __avword*		aptr;
  /* beginning of the args[] array */
  __avword*		args;
#if defined(__hppa__) && !defined(__hppa64__)
  /* end of the args[] array */
  __avword*		args_end;
#endif
  /* limit pointer into the args[] array */
  __avword*		eptr;
#if defined(__i386__) && 0
  /* Filler word, needed if the numbers of words up to now in this structure */
  /* is odd (because on MSVC, alignof(double) = 8, normally = 4).            */
  __avword		filler1;
#endif
#if defined(__i386__) || defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__)) || (defined(__hppa__) && !defined(__hppa64__)) || defined(__arm__) || defined(__armhf__) || (defined(__powerpc__) && !defined(__powerpc64__)) || (defined(__s390__) && !defined(__s390x__))
  /* temporary storage, used to split doubles into two words */
  union {
    double	_double;
#if defined(__sparc__) && !defined(__sparc64__)
    long long	_longlong;
#endif
    __avword	words[2];
  }			tmp;
#endif
#if defined(__x86_64_sysv__)
#define __AV_IARG_NUM 6
  /* store the integer arguments in an extra array */
  unsigned int		ianum;
  __avword		iargs[__AV_IARG_NUM];
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
#define __AV_FARG_NUM 2
  /* store the floating-point arguments in an extra array */
  unsigned int		anum;
  unsigned int		fanum;
  unsigned int		farg_mask;	/* bitmask of those entries in fargs[] which have a float value */
  unsigned int		darg_mask;	/* bitmask of those entries in dargs[] which have a double value */
  float			fargs[__AV_FARG_NUM];
  double		dargs[__AV_FARG_NUM];
#endif
#if defined(__mipsn32__) || defined(__mips64__)
  /* store the floating-point arguments in an extra array */
  int			anum;		/* redundant: (LIST).aptr = &(LIST).args[(LIST).anum] */
  unsigned int		farg_mask;	/* bitmask of those entries in farg[] which have a value */
  unsigned int		darg_mask;	/* bitmask of those entries in args[] which have a double value */
  float			fargs[8];
#endif
#if defined(__sparc64__)
  /* store the floating-point arguments in an extra array */
  int			anum;		/* redundant: (LIST).aptr = &(LIST).args[(LIST).anum] */
  unsigned int		darg_mask;	/* bitmask of those entries in args[] which have a float or double value */
#endif
#if defined(__hppa64__)
  unsigned int		farg_mask;	/* bitmask of those entries in args[] which have a float value */
  unsigned int		darg_mask;	/* bitmask of those entries in args[] which have a double value */
#endif
#if defined(__armhf__)
#define __AV_IARG_NUM 4
  /* The first __AV_IARG_NUM integer arguments are passed in registers, even if
     some floating-point arguments have already been allocated on the stack. */
  unsigned int		ianum;
  /* store the floating-point arguments in an extra array */
  unsigned int		fanum;		/* number of fargs[] words that are occupied so far */
  unsigned int		farg_mask;	/* bitmask of those entries in fargs[] which have a float value */
  unsigned int		darg_mask;	/* bitmask of those entries in dargs[] which have a double value */
  float			fargs[16];
  double		dargs[8];
#endif
#if defined(__arm64__)
#define __AV_IARG_NUM 8
  /* store the integer arguments in an extra array */
  unsigned int		ianum;
  __avword		iargs[__AV_IARG_NUM];
#define __AV_FARG_NUM 8
  /* store the floating-point arguments in an extra array */
  unsigned int		fanum;		/* number of fargs[] words that are occupied so far */
  unsigned int		farg_mask;	/* bitmask of those entries in fargs[] which have a float value */
  unsigned int		darg_mask;	/* bitmask of those entries in dargs[] which have a double value */
  float			fargs[__AV_FARG_NUM];
  double		dargs[__AV_FARG_NUM];
#endif
#if defined(__ia64__) || defined(__x86_64_sysv__)
  /* store the floating-point arguments in an extra array */
#define __AV_FARG_NUM 8
  double*		faptr;
  double		fargs[__AV_FARG_NUM];
#endif
#if defined(__powerpc__) || defined(__powerpc64__)
#if defined(__powerpc_sysv4__)
#define __AV_IARG_NUM 8
  /* store the integer arguments in an extra array */
  unsigned int		ianum;
  __avword		iargs[__AV_IARG_NUM];
#define __AV_FARG_NUM 8
#else
#define __AV_FARG_NUM 13
#endif
  /* store the floating-point arguments in an extra array */
  double*		faptr;
  double		fargs[__AV_FARG_NUM];
#endif
#if defined(__x86_64_ms__)
  /* store the floating-point arguments in an extra array */
  int			anum;		/* redundant: (LIST).aptr = &(LIST).args[(LIST).anum] */
#define __AV_FARG_NUM 4
  unsigned int		farg_mask;	/* bitmask of those entries in fargs[] which have a float value */
  unsigned int		darg_mask;	/* bitmask of those entries in dargs[] which have a double value */
  float			fargs[__AV_FARG_NUM];
  double		dargs[__AV_FARG_NUM];
#endif
#if (defined(__s390__) && !defined(__s390x__))
#define __AV_IARG_NUM 5
  /* store the integer arguments in an extra array */
  unsigned int		ianum;
  __avword		iargs[__AV_IARG_NUM];
  /* store the floating-point arguments in an extra array */
#define __AV_FARG_NUM 2
  unsigned int		fanum;		/* number of fargs[] words that are occupied so far */
  unsigned int		farg_mask;	/* bitmask of those entries in fargs[] which have a float value */
  unsigned int		darg_mask;	/* bitmask of those entries in dargs[] which have a double value */
  float			fargs[__AV_FARG_NUM];
  double		dargs[__AV_FARG_NUM];
#endif
#if defined(__s390x__)
#define __AV_IARG_NUM 5
  /* store the integer arguments in an extra array */
  unsigned int		ianum;
  __avword		iargs[__AV_IARG_NUM];
#define __AV_FARG_NUM 4
  /* store the floating-point arguments in an extra array */
  unsigned int		fanum;		/* number of fargs[] words that are occupied so far */
  unsigned int		farg_mask;	/* bitmask of those entries in fargs[] which have a float value */
  unsigned int		darg_mask;	/* bitmask of those entries in dargs[] which have a double value */
  float			fargs[__AV_FARG_NUM];
  double		dargs[__AV_FARG_NUM];
#endif
} __av_alist;
