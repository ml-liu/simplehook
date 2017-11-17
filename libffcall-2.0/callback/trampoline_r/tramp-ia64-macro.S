/* Trampoline for ia64 CPU */

/*
 * Copyright 2001-2017 Bruno Haible <bruno@clisp.org>
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

/* Available registers: r14 ... r31, r9 ... r11, r2 ... r3. */

	.text
	.align 16
	.global tramp_r#
	.proc tramp_r#
tramp_r:
	/* The closure pointer is already in register r1. */
	ld8 r14 = [r1]		/* Move <address> into register r14. */
	adds r15 = 8, r1
	;;
	ld8 r15 = [r15]		/* Move <data> into register r15. */
	/* Jump to r14. */
	ld8 r17 = [r14]
	adds r16 = 8, r14
	;;
	ld8 r1 = [r16]
	mov b6 = r17
	;;
	br b6
	;;
	.endp tramp_r#

#include "noexecstack.h"
