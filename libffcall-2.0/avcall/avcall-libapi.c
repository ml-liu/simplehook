/*
 * Copyright 2017 Bruno Haible <bruno@clisp.org>
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

#include "avcall-internal.h"

/* This is the implementation of the library API.
   The symbols that the linker sees are all prefixed with 'avcall_',
   to avoid potential collisions with other libraries. */

int avcall_overflown (av_alist* list)
{
  return _av_overflown(AV_LIST_INNER(list));
}

void avcall_start (av_alist* list, __avword* list_args, __avword* list_args_end, __avword(*func)(), void* raddr, int rettype, int flags)
{
  __av_start(AV_LIST_INNER(list),list_args,list_args_end,func,raddr,rettype,flags);
}

void avcall_start_struct (av_alist* list, __avword* list_args, __avword* list_args_end, __avword(*func)(), size_t type_size, int type_splittable, void* raddr, int flags)
{
  __av_start_struct(AV_LIST_INNER(list),list_args,list_args_end,func,type_size,type_splittable,raddr,flags);
}

int avcall_arg_long (av_alist* list, long val)
{
  return __av_long(AV_LIST_INNER(list),val);
}

int avcall_arg_ulong (av_alist* list, unsigned long val)
{
  return __av_ulong(AV_LIST_INNER(list),val);
}

int avcall_arg_ptr (av_alist* list, void* val)
{
  return __av_ptr(AV_LIST_INNER(list),val);
}

int avcall_arg_longlong (av_alist* list, long long val)
{
  return __av_longlong(AV_LIST_INNER(list),val);
}

int avcall_arg_ulonglong (av_alist* list, unsigned long long val)
{
  return __av_ulonglong(AV_LIST_INNER(list),val);
}

int avcall_arg_float (av_alist* list, float val)
{
  return _av_float(AV_LIST_INNER(list),val);
}

int avcall_arg_double (av_alist* list, double val)
{
  return _av_double(AV_LIST_INNER(list),val);
}

int avcall_arg_struct (av_alist* list, size_t type_size, size_t type_align, const void* val_addr)
{
  return __av_struct(AV_LIST_INNER(list),type_size,type_align,val_addr);
}
