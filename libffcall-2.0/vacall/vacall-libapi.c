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

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

#include "vacall-internal.h"

/* This is the implementation of the library API.
   The symbols that the linker sees are all prefixed with 'vacall',
   to avoid potential collisions with other libraries. */

#ifndef REENTRANT

/* This is the function pointer vacall(). A function pointer indirection is
   needed because gcc-3.4 generates invalid code when the address of a symbol
   is casted to a function pointer with different return type.
   (http://gcc.gnu.org/ml/gcc-patches/2003-12/msg01767.html) */
#ifdef __cplusplus
extern "C" void vacall_receiver (); /* the return type is variable, not void! */
#else
extern void vacall_receiver (); /* the return type is variable, not void! */
#endif
void (*vacall) () = vacall_receiver;

/* This is the function called by vacall(). */
void (* vacall_function) (va_alist);

#endif

/* Room for returning structs according to the Sun C non-reentrant struct return convention. */
typedef union { __vaword room[__VA_ALIST_WORDS]; double align; } __va_struct_buffer_t;
static __va_struct_buffer_t vacall_struct_buffer;

static _Noreturn void
vacall_error_type_mismatch (enum __VAtype start_type, enum __VAtype return_type)
{
  /* If you see this, fix your code. */
  fprintf (stderr, "vacall: va_start type %d and va_return type %d disagree.\n",
                   (int)start_type, (int)return_type);
  abort();
}

static _Noreturn void
vacall_error_struct_too_large (unsigned int size)
{
  /* If you see this, increase __VA_ALIST_WORDS: */
  fprintf (stderr, "vacall: struct of size %u too large for Sun C struct return.\n",
                   size);
  abort();
}

void vacall_start (va_alist list, int rettype, int flags)
{
  __va_start(list,rettype,flags);
}

void vacall_start_struct (va_alist list, size_t type_size, size_t type_align, int type_splittable, int flags)
{
  __va_start_struct(list,type_size,type_align,type_splittable,flags);
}

char vacall_arg_char (va_alist list)
{
  return _va_arg_char(list);
}

signed char vacall_arg_schar (va_alist list)
{
  return _va_arg_schar(list);
}

unsigned char vacall_arg_uchar (va_alist list)
{
  return _va_arg_uchar(list);
}

short vacall_arg_short (va_alist list)
{
  return _va_arg_short(list);
}

unsigned short vacall_arg_ushort (va_alist list)
{
  return _va_arg_ushort(list);
}

int vacall_arg_int (va_alist list)
{
  return _va_arg_int(list);
}

unsigned int vacall_arg_uint (va_alist list)
{
  return _va_arg_uint(list);
}

long vacall_arg_long (va_alist list)
{
  return _va_arg_long(list);
}

unsigned long vacall_arg_ulong (va_alist list)
{
  return _va_arg_ulong(list);
}

long long vacall_arg_longlong (va_alist list)
{
  return _va_arg_longlong(list);
}

unsigned long long vacall_arg_ulonglong (va_alist list)
{
  return _va_arg_ulonglong(list);
}

float vacall_arg_float (va_alist list)
{
  return _va_arg_float(list);
}

double vacall_arg_double (va_alist list)
{
  return _va_arg_double(list);
}

void* vacall_arg_ptr (va_alist list)
{
  return _va_arg_ptr(list);
}

void* vacall_arg_struct (va_alist list, size_t type_size, size_t type_align)
{
  return __va_arg_struct(list,type_size,type_align);
}

void vacall_return_void (va_alist list)
{
  _va_return_void(list);
}

void vacall_return_char (va_alist list, char val)
{
  _va_return_char(list,val);
}

void vacall_return_schar (va_alist list, signed char val)
{
  _va_return_schar(list,val);
}

void vacall_return_uchar (va_alist list, unsigned char val)
{
  _va_return_uchar(list,val);
}

void vacall_return_short (va_alist list, short val)
{
  _va_return_short(list,val);
}

void vacall_return_ushort (va_alist list, unsigned short val)
{
  _va_return_ushort(list,val);
}

void vacall_return_int (va_alist list, int val)
{
  _va_return_int(list,val);
}

void vacall_return_uint (va_alist list, unsigned int val)
{
  _va_return_uint(list,val);
}

void vacall_return_long (va_alist list, long val)
{
  _va_return_long(list,val);
}

void vacall_return_ulong (va_alist list, unsigned long val)
{
  _va_return_ulong(list,val);
}

void vacall_return_longlong (va_alist list, long long val)
{
  _va_return_longlong(list,val);
}

void vacall_return_ulonglong (va_alist list, unsigned long long val)
{
  _va_return_ulonglong(list,val);
}

void vacall_return_float (va_alist list, float val)
{
  _va_return_float(list,val);
}

void vacall_return_double (va_alist list, double val)
{
  _va_return_double(list,val);
}

void vacall_return_ptr (va_alist list, void* val)
{
  _va_return_ptr(list,val);
}

void vacall_return_struct (va_alist list, size_t type_size, size_t type_align, const void* val_addr)
{
  __va_return_struct(list,type_size,type_align,val_addr);
}
