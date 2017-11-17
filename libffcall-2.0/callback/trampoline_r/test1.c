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

#include "trampoline_r.h"
#include "ffcall-abi.h"  /* Define __${host_cpu}__ */

/* Set when we can check that the env register is being passed correctly. */
#if defined __GNUC__ && !defined __clang__ && !defined(__arm__)
#define CHECK_ENV_REGISTER
#endif

#define MAGIC1  0x9db9af42
#define MAGIC2  0x614a13c9
#define MAGIC3  0x7aff3cb4
#define MAGIC4  0xa2f9d045

#ifdef __cplusplus
typedef int (*function)(...);
#else
typedef int (*function)();
#endif

int f (int x)
{
#ifdef CHECK_ENV_REGISTER
#ifdef __i386__
register void* env __asm__("%ecx");
#endif
#ifdef __m68k__
register void* env __asm__("a0");
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
register void* env __asm__("$2");
#endif
#if defined(__sparc__) && !defined(__sparc64__)
register void* env __asm__("%g2");
#endif
#ifdef __sparc64__
register void* env __asm__("%g5");
#endif
#ifdef __alpha__
register void* env __asm__("$1");
#endif
#if defined(__hppa__) && !defined(__hppa64__)
register void* env __asm__("%r29");
#endif
#ifdef __hppa64__
register void* env __asm__("%r31");
#endif
#ifdef __arm64__
register void* env __asm__("x18");
#endif
#ifdef __powerpc__
register void* env __asm__("r11");
#endif
#ifdef __ia64__
register void* env __asm__("r15");
#endif
#ifdef __x86_64__
register void* env __asm__("r10");
#endif
#if defined(__s390__) || defined(__s390x__)
register void* env __asm__("r0");
#endif

  return x + (int)(long)((void**)env)[0] + (int)(long)((void**)env)[1] + MAGIC3;
#else
  return x + MAGIC3;
#endif
}

int main ()
{
  function cf = alloc_trampoline_r((function)&f, (void*)MAGIC1, (void*)MAGIC2);
#ifdef CHECK_ENV_REGISTER
  if ((*cf)(MAGIC4) == MAGIC1+MAGIC2+MAGIC3+MAGIC4)
#else
  if ((*cf)(MAGIC4) == MAGIC3+MAGIC4)
#endif
    { free_trampoline_r(cf); printf("Works, test1 passed.\n"); exit(0); }
  else
    { printf("Doesn't work!\n"); exit(1); }
}
