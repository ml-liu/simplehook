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

/* Replacement for a subset of <stdint.h>.
   We cannot use gnulib's portable <stdint.h> replacement, because when
   cross-compiling the various avcall-$(CPU).c and vacall-$(CPU).c files,
   gnulib-generated files are not available. And the cross-compilers of
   GCC version < 4.5 don't provide <stdint.h>. */

/* Define integer types that are as large as a pointer, */

#if defined(__x86_64__) && (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)
/* An LLP64 platform. */
typedef long long ff_intptr_t;
typedef unsigned long long ff_uintptr_t;
#else
/* An ILP32 or LP64 platform. */
typedef long ff_intptr_t;
typedef unsigned long ff_uintptr_t;
#endif
#define intptr_t ff_intptr_t
#define uintptr_t ff_uintptr_t

/* Verify at compile time that sizeof([u]intptr_t) == sizeof(void*). */
typedef int intptr_verify[2*(sizeof(intptr_t) == sizeof(void*))-1];
typedef int uintptr_verify[2*(sizeof(uintptr_t) == sizeof(void*))-1];
