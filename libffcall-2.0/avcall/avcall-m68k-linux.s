	.file	"avcall-m68k.c"
	.text
	.align	2
	.globl	avcall_call
	.type	avcall_call,@function
avcall_call:
	link.w %a6,#0
	movm.l #0x3820,-(%sp)
	move.l 8(%a6),%a2
	lea (-1024,%sp),%sp
	move.l 24(%a2),%d1
	move.l 20(%a2),%d0
	sub.l %d1,%d0
	asr.l #2,%d0
	jble .L54
	move.l %sp,%a1
	move.l %d1,%a0
	move.l %d0,%d2
	.align	2
.L6:
	move.l (%a0)+,(%a1)+
	subq.l #1,%d2
	jbne .L6
.L54:
	moveq.l #16,%d0
	cmp.l 12(%a2),%d0
	jbeq .L59
.L7:
	move.l 4(%a2),%a0
	jsr (%a0)
	move.l %d0,%d2
	move.l %d1,%d3
	move.l 12(%a2),%a1
	moveq.l #1,%d1
	cmp.l %a1,%d1
	jbeq .L9
	tst.l %a1
	jbeq .L55
	moveq.l #2,%d4
	cmp.l %a1,%d4
	jbeq .L58
	moveq.l #3,%d4
	cmp.l %a1,%d4
	jbeq .L58
	moveq.l #4,%d4
	cmp.l %a1,%d4
	jbeq .L58
	moveq.l #5,%d4
	cmp.l %a1,%d4
	jbeq .L57
	moveq.l #6,%d4
	cmp.l %a1,%d4
	jbeq .L57
	moveq.l #7,%d4
	cmp.l %a1,%d4
	jbeq .L55
	moveq.l #8,%d4
	cmp.l %a1,%d4
	jbeq .L55
	moveq.l #9,%d4
	cmp.l %a1,%d4
	jbeq .L55
	moveq.l #10,%d4
	cmp.l %a1,%d4
	jbeq .L55
	lea (-11,%a1),%a0
	moveq.l #1,%d4
	cmp.l %a0,%d4
	jbcc .L56
	moveq.l #13,%d4
	cmp.l %a1,%d4
	jbeq .L60
	moveq.l #14,%d4
	cmp.l %a1,%d4
	jbeq .L61
	moveq.l #15,%d0
	cmp.l %a1,%d0
	jbeq .L55
	moveq.l #16,%d1
	cmp.l %a1,%d1
	jbne .L9
	btst #1,2(%a2)
	jbeq .L9
	move.l 16(%a2),%d0
	moveq.l #1,%d4
	cmp.l %d0,%d4
	jbeq .L58
	moveq.l #2,%d1
	cmp.l %d0,%d1
	jbeq .L57
	moveq.l #4,%d4
	cmp.l %d0,%d4
	jbeq .L55
	moveq.l #8,%d1
	cmp.l %d0,%d1
	jbne .L9
.L56:
	move.l 8(%a2),%a0
	move.l %d2,(%a0)
	move.l %d3,4(%a0)
	jbra .L9
	.align	2
.L55:
	move.l 8(%a2),%a0
	move.l %d2,(%a0)
	jbra .L9
	.align	2
.L57:
	move.l 8(%a2),%a0
	move.w %d2,(%a0)
	jbra .L9
	.align	2
.L58:
	move.l 8(%a2),%a0
	move.b %d2,(%a0)
	jbra .L9
	.align	2
.L61:
	btst #6,3(%a2)
	jbeq .L39
	move.l 8(%a2),%a0
	fmove.d %fp0,(%a0)
	jbra .L9
	.align	2
.L39:
	move.l 8(%a2),%a0
	move.l %d0,(%a0)
	move.l %d1,4(%a0)
	jbra .L9
	.align	2
.L60:
	move.l (%a2),%d2
	btst #6,%d2
	jbeq .L33
	move.l 8(%a2),%a0
	fmove.s %fp0,(%a0)
	jbra .L9
	.align	2
.L33:
	btst #5,%d2
	jbeq .L35
	move.l 8(%a2),%a0
	move.l %d1,-(%sp)
	move.l %d0,-(%sp)
	fmove.d (%sp)+,%fp0
	fmove.s %fp0,(%a0)
	jbra .L9
	.align	2
.L35:
	move.l 8(%a2),%a0
	move.l %d0,(%a0)
	jbra .L9
	.align	2
.L59:
#APP
	move.l 8(%a2),%a1
#NO_APP
	jbra .L7
	.align	2
.L9:
	clr.l %d0
	movm.l -16(%a6),#0x41c
	unlk %a6
	rts
.Lfe1:
	.size	avcall_call,.Lfe1-avcall_call
	.ident	"GCC: (GNU) 3.1"
