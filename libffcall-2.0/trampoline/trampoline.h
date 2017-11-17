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

#ifndef _TRAMPOLINE_H
#define _TRAMPOLINE_H

#include "ffcall-version.h"


#ifdef __cplusplus
extern "C" {
#endif

	
/* This type denotes an opaque function pointer.
   You need to cast it to an actual function pointer type (with correct return
   type) before you can actually invoke it. */
#ifdef __cplusplus
typedef int (*trampoline_function_t) (...);
#else
typedef int (*trampoline_function_t) ();
#endif


/* Allocates a trampoline.
   It returns a function pointer that takes the same parameters and returns the
   same type as ADDRESS.
   When invoked, it first stores DATA at the location pointed to by VARIABLE,
   then invokes ADDRESS with the same arguments. It returns the value returned
   by ADDRESS.
   The trampoline has indefinite extent. It can be accessed until a call to
   free_trampoline().
 */
extern trampoline_function_t alloc_trampoline (trampoline_function_t /* ADDRESS */, void** /* VARIABLE */, void* /* DATA */);

/* Frees the memory used by a trampoline.
   FUNCTION must be the result of an alloc_trampoline() invocation.
   After this call, FUNCTION must not be used any more - neither invoked,
   not used as an argument to other functions.
 */
extern void free_trampoline (trampoline_function_t /* FUNCTION */);


/* Tests whether a given pointer is a function pointer returned by
   alloc_trampoline(). Returns 1 for yes, 0 for no.
   If yes, it can be cast to trampoline_function_t.
 */
extern int is_trampoline (void* /* FUNCTION */);

/* Returns the ADDRESS argument passed to the alloc_trampoline() invocation.
   FUNCTION must be the result of an alloc_trampoline() invocation.
 */
extern trampoline_function_t trampoline_address (trampoline_function_t /* FUNCTION */);

/* Returns the VARIABLE argument passed to the alloc_trampoline() invocation.
   FUNCTION must be the result of an alloc_trampoline() invocation.
 */
extern void** trampoline_variable (trampoline_function_t /* FUNCTION */);

/* Returns the DATA argument passed to the alloc_trampoline() invocation.
   FUNCTION must be the result of an alloc_trampoline() invocation.
 */
extern void* trampoline_data (trampoline_function_t /* FUNCTION */);


#ifdef __cplusplus
}
#endif


#endif /* _TRAMPOLINE_H */
