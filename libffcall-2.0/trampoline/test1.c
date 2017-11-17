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

#include <stdio.h>
#include <stdlib.h>

#include "trampoline.h"

#define MAGIC1  0x9db9af42
#define MAGIC2  0x614a13c9

static int magic = MAGIC1;

void* function_data;

int f (int x)
{ return *(int*)function_data + x; }

int main ()
{
  trampoline_function_t cf = alloc_trampoline((trampoline_function_t)&f, &function_data, &magic);
  /* calling cf shall set  function_data = &magic  and then call f(x),
   * thus returning  magic + x.
   */
  if (((*cf)(MAGIC2) == MAGIC1+MAGIC2) && (function_data == &magic))
    { free_trampoline(cf); printf("Works, test1 passed.\n"); exit(0); }
  else
    { printf("Doesn't work!\n"); exit(1); }
}
