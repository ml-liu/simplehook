#include "asm-m68k.h"
	.text
	.align	2
	.globl C(vacall_receiver)
	DECLARE_FUNCTION(vacall_receiver)
FUNBEGIN(vacall_receiver)
	link.w %a6,#-32
	movm.l #0x3030,-(%sp)
	clr.l -32(%a6)
	lea (8,%a6),%a2
	move.l %a2,-20(%a6)
	clr.l -16(%a6)
	clr.l -12(%a6)
	move.l %a1,-4(%a6)
	pea -32(%a6)
	move.l C(vacall_function),%a2
	jbsr (%a2)
	addq.l #4,%sp
	move.l -12(%a6),%a3
	tst.l %a3
	jbeq L(1)
	moveq.l #1,%d2
	cmp.l %a3,%d2
	jbeq L(46)
	moveq.l #2,%d3
	cmp.l %a3,%d3
	jbeq L(46)
	moveq.l #3,%d2
	cmp.l %a3,%d2
	jbeq L(47)
	moveq.l #4,%d3
	cmp.l %a3,%d3
	jbeq L(48)
	moveq.l #5,%d2
	cmp.l %a3,%d2
	jbeq L(49)
	moveq.l #6,%d3
	cmp.l %a3,%d3
	jbeq L(45)
	moveq.l #7,%d2
	cmp.l %a3,%d2
	jbeq L(45)
	moveq.l #8,%d3
	cmp.l %a3,%d3
	jbeq L(45)
	moveq.l #9,%d2
	cmp.l %a3,%d2
	jbeq L(45)
	lea (-10,%a3),%a2
	moveq.l #1,%d3
	cmp.l %a2,%d3
	jbcs L(22)
	move.l -28(%a6),%d0
	move.l -24(%a6),%d1
	jbra L(1)
	.align	2
L(22):
	moveq.l #12,%d2
	cmp.l %a3,%d2
	jbeq L(50)
	moveq.l #13,%d2
	cmp.l %a3,%d2
	jbeq L(51)
	moveq.l #14,%d3
	cmp.l %a3,%d3
	jbeq L(52)
	moveq.l #15,%d2
	cmp.l %a3,%d2
	jbne L(1)
	btst #2,-30(%a6)
	jbeq L(1)
	move.l -8(%a6),%d2
	moveq.l #1,%d3
	cmp.l %d2,%d3
	jbeq L(53)
	moveq.l #2,%d3
	cmp.l %d2,%d3
	jbeq L(54)
	moveq.l #4,%d3
	cmp.l %d2,%d3
	jbeq L(55)
	moveq.l #8,%d3
	cmp.l %d2,%d3
	jbne L(1)
	move.l -16(%a6),%a2
	move.l (%a2),%d0
	move.l 4(%a2),%d1
	jbra L(1)
	.align	2
L(55):
	move.l -16(%a6),%a2
	move.l (%a2),%d0
	jbra L(1)
	.align	2
L(54):
	move.l -16(%a6),%a2
	clr.l %d0
	move.w (%a2),%d0
	jbra L(1)
	.align	2
L(53):
	move.l -16(%a6),%a2
	clr.l %d0
	move.b (%a2),%d0
	jbra L(1)
	.align	2
L(52):
	move.l -28(%a6),%d0
	move.l %d0,%a0
	jbra L(1)
	.align	2
L(51):
	btst #6,-29(%a6)
	jbeq L(31)
	fmove.d -28(%a6),%fp0
	jbra L(1)
	.align	2
L(31):
	move.l -28(%a6),%d0
	move.l -24(%a6),%d1
	jbra L(1)
	.align	2
L(50):
	move.l -32(%a6),%d2
	btst #6,%d2
	jbeq L(25)
	fmove.s -28(%a6),%fp0
	jbra L(1)
	.align	2
L(25):
	btst #5,%d2
	jbeq L(27)
	fmove.s -28(%a6),%fp1
	fmove.d %fp1,-(%sp)
	move.l (%sp)+,%d0
	move.l (%sp)+,%d1
	jbra L(1)
	.align	2
L(27):
	move.l -28(%a6),%d0
	jbra L(1)
	.align	2
L(45):
	move.l -28(%a6),%d0
	jbra L(1)
	.align	2
L(49):
	clr.l %d0
	move.w -28(%a6),%d0
	jbra L(1)
	.align	2
L(48):
	move.w -28(%a6),%d0
	ext.l %d0
	jbra L(1)
	.align	2
L(47):
	clr.l %d0
	move.b -28(%a6),%d0
	jbra L(1)
	.align	2
L(46):
	move.b -28(%a6),%d0
	extb.l %d0
L(1):
	movm.l -48(%a6),#0xc0c
	unlk %a6
	rts
L(fe1):
	FUNEND(vacall_receiver)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
