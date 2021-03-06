dnl -*- Autoconf -*-
dnl Copyright (C) 1993-2017 Free Software Foundation, Inc.
dnl This file is free software, distributed under the terms of the GNU
dnl General Public License as published by the Free Software Foundation;
dnl either version 2 of the License, or (at your option) any later version.
dnl As a special exception to the GNU General Public License, this file
dnl may be distributed as part of a program that contains a configuration
dnl script generated by Autoconf, under the same distribution terms as
dnl the rest of that program.

dnl From Bruno Haible, Marcus Daniels, Sam Steingold.

AC_PREREQ([2.57])

AC_DEFUN([CL_GETPAGESIZE],
[
  CL_LINK_CHECK([getpagesize], [cl_cv_func_getpagesize],
    [#ifdef HAVE_UNISTD_H
      #include <sys/types.h>
      #include <unistd.h>
     #endif
    ],
    [getpagesize();],
    [
      AC_DEFINE([HAVE_GETPAGESIZE], [], [have getpagesize()])
      have_getpagesize=1
    ])
  if test -n "$have_getpagesize"; then
    CL_PROTO([getpagesize],
      [CL_PROTO_RET(
         [#include <stdlib.h>
          #ifdef HAVE_UNISTD_H
           #include <unistd.h>
          #endif
         ],
         [int getpagesize();],
         [cl_cv_proto_getpagesize_ret], [int], [size_t])
      ],
      [extern $cl_cv_proto_getpagesize_ret getpagesize (void);])
    AC_DEFINE_UNQUOTED([RETGETPAGESIZETYPE], [$cl_cv_proto_getpagesize_ret],
      [return type of getpagesize()])
  else
    dnl Otherwise we use PAGESIZE defined in <sys/param.h>.
    dnl But mingw32 doesn't have <sys/param.h>.
    AC_CHECK_HEADERS([sys/param.h])
  fi
])
