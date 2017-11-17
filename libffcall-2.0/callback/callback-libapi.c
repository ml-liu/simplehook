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

#define __TR_function obsolete__TR_function
#include "callback.h"
#undef __TR_function
#include "trampoline_r.h"

/* This is the implementation of the library API.
   The symbols that the linker sees are all prefixed with 'callback_',
   to avoid potential collisions with other libraries. */

callback_t alloc_callback (callback_function_t address, void* data)
{
  return alloc_trampoline_r((__TR_function)callback_get_receiver(),(void*)address,data);
}

void free_callback (callback_t callback)
{
  free_trampoline_r (callback);
}

int is_callback (void* callback)
{
  return is_trampoline_r(callback)
         && trampoline_r_address((__TR_function)callback) == (__TR_function)callback_get_receiver();
}

callback_function_t callback_address (callback_t callback)
{
  return (callback_function_t)trampoline_r_data0(callback);
}

void* callback_data (callback_t callback)
{
  return trampoline_r_data1(callback);
}
