/* Trampoline test */

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

#include "config.h"  /* Define __${host_cpu}__ */

#include <stdio.h>
#include <stdlib.h>

#include "callback.h"

#define MAGIC1  0x9db9af42
#define MAGIC2  0xa2f9d045
#define MAGIC3  0x7aff3cb4

int f (int x)
{
  return x + MAGIC3;
}

void vf (void* data, va_alist alist)
{
  if (data != (void*)MAGIC1) { printf("wrong data\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int r = f(a);
  va_return_int(alist, r);
}}

int main ()
{
  callback_t cf = alloc_callback(&vf, (void*)MAGIC1);
  if ((*cf)(MAGIC2) == MAGIC2+MAGIC3)
    { free_callback(cf); printf("Works, test1 passed.\n"); exit(0); }
  else
    { printf("Doesn't work!\n"); exit(1); }
}
