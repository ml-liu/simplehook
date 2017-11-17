# endianness.m4 serial 1
dnl Copyright (C) 2017 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl From Bruno Haible.

dnl For specific bi-endian CPUs, sets the ENDIANNESS variable to either
dnl 'eb' (means big endian) or 'el' (means little endian).
dnl
dnl This variable can be used to select a particular assembly language
dnl source file that will interoperate with C code on the given host.
AC_DEFUN([FFCALL_ENDIANNESS],
[
  AC_REQUIRE([AC_CANONICAL_HOST])
  case "$host_cpu" in
    arm* )
      AC_CACHE_CHECK([endianness], [ffcall_cv_endianness],
        [AC_EGREP_CPP([yes],
           [#if defined __ARMEL__
            yes
            #endif],
           [ffcall_cv_endianness=little],
           [ffcall_cv_endianness=big])])
      ;;
    mips* )
      AC_CACHE_CHECK([endianness], [ffcall_cv_endianness],
        [# Compilers on IRIX define only _MIPSEB as indicator.
         # Compilers on Linux define _MIPSEB, __MIPSEB__, __MIPSEB or - in
         # the opposite case - _MIPSEL, __MIPSEL__, __MIPSEL.
         AC_EGREP_CPP([yes],
           [#if defined _MIPSEB
            yes
            #endif],
           [ffcall_cv_endianness=big],
           [AC_EGREP_CPP([yes],
              [#if defined _MIPSEL
               yes
               #endif],
              [ffcall_cv_endianness=little],
              [ffcall_cv_endianness=unknown])])
         ])
      ;;
    powerpc*)
      AC_CACHE_CHECK([endianness], [ffcall_cv_endianness],
        [# Compilers on AIX and Linux define _BIG_ENDIAN, __BIG_ENDIAN__ or
         # - in the opposite case - _LITTLE_ENDIAN, __LITTLE_ENDIAN__.
         AC_EGREP_CPP([yes],
           [#if defined _BIG_ENDIAN
            yes
            #endif],
           [ffcall_cv_endianness=big],
           [AC_EGREP_CPP([yes],
              [#if defined _LITTLE_ENDIAN
               yes
               #endif],
              [ffcall_cv_endianness=little],
              [ffcall_cv_endianness=unknown])])
         ])
      ;;
    *) ffcall_cv_endianness=known ;;
  esac
  case "$ffcall_cv_endianness" in
    big)    ENDIANNESS='eb' ;;
    little) ENDIANNESS='el' ;;
    *)      ENDIANNESS='' ;;
  esac
  AC_SUBST([ENDIANNESS])
])
