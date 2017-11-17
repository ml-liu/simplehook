	.file	"vacall-m68k.c"
	.text
	.align	2
	.type	callback_receiver,@function
callback_receiver:
	link.w %a6,#-32
	movm.l #0x3030,-(%sp)
	clr.l -32(%a6)
	lea (8,%a6),%a2
	move.l %a2,-20(%a6)
	clr.l -16(%a6)
	clr.l -12(%a6)
	move.l %a1,-4(%a6)
	pea -32(%a6)
	move.l 4(%a0),-(%sp)
	move.l (%a0),%a2
	jsr (%a2)
	addq.l #8,%sp
	move.l -12(%a6),%a3
	tst.l %a3
	jbeq .L1
	moveq.l #1,%d2
	cmp.l %a3,%d2
	jbeq .L46
	moveq.l #2,%d3
	cmp.l %a3,%d3
	jbeq .L46
	moveq.l #3,%d2
	cmp.l %a3,%d2
	jbeq .L47
	moveq.l #4,%d3
	cmp.l %a3,%d3
	jbeq .L48
	moveq.l #5,%d2
	cmp.l %a3,%d2
	jbeq .L49
	moveq.l #6,%d3
	cmp.l %a3,%d3
	jbeq .L45
	moveq.l #7,%d2
	cmp.l %a3,%d2
	jbeq .L45
	moveq.l #8,%d3
	cmp.l %a3,%d3
	jbeq .L45
	moveq.l #9,%d2
	cmp.l %a3,%d2
	jbeq .L45
	lea (-10,%a3),%a2
	moveq.l #1,%d3
	cmp.l %a2,%d3
	jbcs .L22
	move.l -28(%a6),%d0
	move.l -24(%a6),%d1
	jbra .L1
	.align	2
.L22:
	moveq.l #12,%d2
	cmp.l %a3,%d2
	jbeq .L50
	moveq.l #13,%d2
	cmp.l %a3,%d2
	jbeq .L51
	moveq.l #14,%d3
	cmp.l %a3,%d3
	jbeq .L52
	moveq.l #15,%d2
	cmp.l %a3,%d2
	jbne .L1
	btst #2,-30(%a6)
	jbeq .L1
	move.l -8(%a6),%d2
	moveq.l #1,%d3
	cmp.l %d2,%d3
	jbeq .L53
	moveq.l #2,%d3
	cmp.l %d2,%d3
	jbeq .L54
	moveq.l #4,%d3
	cmp.l %d2,%d3
	jbeq .L55
	moveq.l #8,%d3
	cmp.l %d2,%d3
	jbne .L1
	move.l -16(%a6),%a2
	move.l (%a2),%d0
	move.l 4(%a2),%d1
	jbra .L1
	.align	2
.L55:
	move.l -16(%a6),%a2
	move.l (%a2),%d0
	jbra .L1
	.align	2
.L54:
	move.l -16(%a6),%a2
	clr.l %d0
	move.w (%a2),%d0
	jbra .L1
	.align	2
.L53:
	move.l -16(%a6),%a2
	clr.l %d0
	move.b (%a2),%d0
	jbra .L1
	.align	2
.L52:
	move.l -28(%a6),%d0
	move.l %d0,%a0
	jbra .L1
	.align	2
.L51:
	btst #6,-29(%a6)
	jbeq .L31
	fmove.d -28(%a6),%fp0
	jbra .L1
	.align	2
.L31:
	move.l -28(%a6),%d0
	move.l -24(%a6),%d1
	jbra .L1
	.align	2
.L50:
	move.l -32(%a6),%d2
	btst #6,%d2
	jbeq .L25
	fmove.s -28(%a6),%fp0
	jbra .L1
	.align	2
.L25:
	btst #5,%d2
	jbeq .L27
	fmove.s -28(%a6),%fp1
	fmove.d %fp1,-(%sp)
	move.l (%sp)+,%d0
	move.l (%sp)+,%d1
	jbra .L1
	.align	2
.L27:
	move.l -28(%a6),%d0
	jbra .L1
	.align	2
.L45:
	move.l -28(%a6),%d0
	jbra .L1
	.align	2
.L49:
	clr.l %d0
	move.w -28(%a6),%d0
	jbra .L1
	.align	2
.L48:
	move.w -28(%a6),%d0
	ext.l %d0
	jbra .L1
	.align	2
.L47:
	clr.l %d0
	move.b -28(%a6),%d0
	jbra .L1
	.align	2
.L46:
	move.b -28(%a6),%d0
	extb.l %d0
.L1:
	movm.l -48(%a6),#0xc0c
	unlk %a6
	rts
.Lfe1:
	.size	callback_receiver,.Lfe1-callback_receiver
	.align	2
	.globl	callback_get_receiver
	.type	callback_get_receiver,@function
callback_get_receiver:
	link.w %a6,#0
	move.l %a5,-(%sp)
	lea (%pc, _GLOBAL_OFFSET_TABLE_@GOTPC), %a5
	move.l callback_receiver@GOT(%a5),%a0
	move.l %a0,%d0
	move.l (%sp)+,%a5
	unlk %a6
	rts
.Lfe2:
	.size	callback_get_receiver,.Lfe2-callback_get_receiver
	.ident	"GCC: (GNU) 3.1"
