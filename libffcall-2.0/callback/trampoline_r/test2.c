/* Trampoline accessor test */

/*
 * Copyright 1995-2005 Bruno Haible <bruno@clisp.org>
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

#include <stdio.h>
#include <stdlib.h>

#include "trampoline_r.h"

#ifdef __cplusplus
typedef int (*function)(...);
#else
typedef int (*function)();
#endif

int f (int x)
{ return x; }

#define MAGIC1  0x9db9af42
#define MAGIC2  0x614a13c9

int main ()
{
  function cf = alloc_trampoline_r((function)&f, (void*)MAGIC1, (void*)MAGIC2);
  if (is_trampoline_r((void*)&main))
    { printf("is_trampoline_r(&main) returns true!\n"); exit(1); }
  if (!is_trampoline_r((void*)cf))
    { printf("is_trampoline_r() returns false!\n"); exit(1); }
  if (trampoline_r_address(cf) != (function)&f)
    { printf("trampoline_r_address() doesn't work!\n"); exit(1); }
  if (trampoline_r_data0(cf) != (void*)MAGIC1)
    { printf("trampoline_r_data0() doesn't work!\n"); exit(1); }
  if (trampoline_r_data1(cf) != (void*)MAGIC2)
    { printf("trampoline_r_data1() doesn't work!\n"); exit(1); }
  printf("test2 passed.\n");
  exit(0);
}
