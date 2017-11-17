/* Instruction cache flushing for sparc */

/*
 * Copyright 1996-1999 Bruno Haible <bruno@clisp.org>
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

/*
 * This assumes that the range [first_addr..last_addr] lies in at most two
 * cache lines.
 */
void __TR_clear_cache_2 (char* first_addr, char* last_addr)
{
  asm volatile ("iflush %0+0;" /* the +0 is needed by gas, says gforth-0.3.0 */
                "iflush %0+8"
                : : "r" (first_addr));
}
