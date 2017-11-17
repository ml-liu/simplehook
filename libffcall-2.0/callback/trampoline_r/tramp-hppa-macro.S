; Trampoline for hppa CPU

; Copyright 1997-2017 Bruno Haible <bruno@clisp.org>
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.

; Available registers: %r1, %r19, %r20, %r21, %r22, %r29, %r31.

	.code
	.IMPORT $global$,DATA
	.IMPORT $$dyncall,MILLICODE
	.code

	.align 4
	.EXPORT tramp_r,ENTRY,PRIV_LEV=3,ARGW0=GR,ARGW1=GR
	.label tramp_r
	.PROC
	.CALLINFO FRAME=0,NO_CALLS
	.ENTRY
; The closure pointer is already in register %r19.
; Move <data> into register %r29
	ldw 0(0,%r19),%r29
; Move <address> into register %r21.
	ldw 4(0,%r19),%r21
; Jump to it.
	bb,>=,n %r21,30,tramp_r_2
	depi 0,31,2,%r21
	ldw 4(0,%r21),%r19
	ldw 0(0,%r21),%r21
	.label tramp_r_2
	ldsid (0,%r21),%r1
	mtsp %r1,%sr0
	be,n 0(%sr0,%r21)
	nop
	.EXIT
	.PROCEND

#include "noexecstack.h"
