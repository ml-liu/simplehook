#include "asm-m68k.h"
	.text
	.even
	.globl C(avcall_call)
	DECLARE_FUNCTION(avcall_call)
FUNBEGIN(avcall_call)
	link $a6,#0
	moveml #0x3820,$sp@-
	movel $a6@(8),$a2
	lea $sp@(-1024),$sp
	movel $a2@(24),$d1
	movel $a2@(20),$d0
	subl $d1,$d0
	asrl #2,$d0
	jle L(54)
	movel $sp,$a1
	movel $d1,$a0
	movel $d0,$d2
	.even
L(6):
	movel $a0@+,$a1@+
	subql #1,$d2
	jne L(6)
L(54):
	moveq #16,$d0
	cmpl $a2@(12),$d0
	jeq L(59)
L(7):
	movel $a2@(4),$a0
	jsr $a0@
	movel $d0,$d2
	movel $d1,$d3
	movel $a2@(12),$a1
	moveq #1,$d1
	cmpl $a1,$d1
	jeq L(9)
	tstl $a1
	jeq L(55)
	moveq #2,$d4
	cmpl $a1,$d4
	jeq L(58)
	moveq #3,$d4
	cmpl $a1,$d4
	jeq L(58)
	moveq #4,$d4
	cmpl $a1,$d4
	jeq L(58)
	moveq #5,$d4
	cmpl $a1,$d4
	jeq L(57)
	moveq #6,$d4
	cmpl $a1,$d4
	jeq L(57)
	moveq #7,$d4
	cmpl $a1,$d4
	jeq L(55)
	moveq #8,$d4
	cmpl $a1,$d4
	jeq L(55)
	moveq #9,$d4
	cmpl $a1,$d4
	jeq L(55)
	moveq #10,$d4
	cmpl $a1,$d4
	jeq L(55)
	lea $a1@(-11),$a0
	moveq #1,$d4
	cmpl $a0,$d4
	jcc L(56)
	moveq #13,$d4
	cmpl $a1,$d4
	jeq L(60)
	moveq #14,$d4
	cmpl $a1,$d4
	jeq L(61)
	moveq #15,$d0
	cmpl $a1,$d0
	jeq L(55)
	moveq #16,$d1
	cmpl $a1,$d1
	jne L(9)
	btst #1,$a2@(2)
	jeq L(9)
	movel $a2@(16),$d0
	moveq #1,$d4
	cmpl $d0,$d4
	jeq L(58)
	moveq #2,$d1
	cmpl $d0,$d1
	jeq L(57)
	moveq #4,$d4
	cmpl $d0,$d4
	jeq L(55)
	moveq #8,$d1
	cmpl $d0,$d1
	jne L(9)
L(56):
	movel $a2@(8),$a0
	movel $d2,$a0@
	movel $d3,$a0@(4)
	jra L(9)
	.even
L(55):
	movel $a2@(8),$a0
	movel $d2,$a0@
	jra L(9)
	.even
L(57):
	movel $a2@(8),$a0
	movew $d2,$a0@
	jra L(9)
	.even
L(58):
	movel $a2@(8),$a0
	moveb $d2,$a0@
	jra L(9)
	.even
L(61):
	btst #6,$a2@(3)
	jeq L(39)
	movel $a2@(8),$a0
	fmoved $fp0,$a0@
	jra L(9)
	.even
L(39):
	movel $a2@(8),$a0
	movel $d0,$a0@
	movel $d1,$a0@(4)
	jra L(9)
	.even
L(60):
	movel $a2@,$d2
	btst #6,$d2
	jeq L(33)
	movel $a2@(8),$a0
	fmoves $fp0,$a0@
	jra L(9)
	.even
L(33):
	btst #5,$d2
	jeq L(35)
	movel $a2@(8),$a0
	movel $d1,$sp@-
	movel $d0,$sp@-
	fmoved $sp@+,$fp0
	fmoves $fp0,$a0@
	jra L(9)
	.even
L(35):
	movel $a2@(8),$a0
	movel $d0,$a0@
	jra L(9)
	.even
L(59):
	movel $a2@(8),$a1
	jra L(7)
	.even
L(9):
	clrl $d0
	moveml $a6@(-16),#0x41c
	unlk $a6
	rts
FUNEND(avcall_call)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
