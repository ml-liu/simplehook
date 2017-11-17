	.file	"avcall-sparc.c"
	.section	".text"
	.align 4
	.global avcall_call
	.type	avcall_call,#function
	.proc	04
avcall_call:
	!#PROLOGUE# 0
	save	%sp, -1152, %sp
	ld	[%i0+20], %g3
	add	%sp, 68, %l1
	ld	[%i0+24], %o7
	ld	[%i0+12], %l0
	sub	%g3, %o7, %g3
	cmp	%l0, 16
	be	.LL54
	sra	%g3, 2, %g4
.LL2:
	mov	6, %l0
	cmp	%l0, %g4
	bge	.LL49
	ld	[%i0+24], %g1
.LL7:
	sll	%l0, 2, %g3
	ld	[%g1+%g3], %o7
	add	%l0, 1, %l0
	cmp	%l0, %g4
	bl	.LL7
	st	%o7, [%l1+%g3]
.LL49:
	ld	[%i0+12], %g3
	cmp	%g3, 16
	be,a	.LL55
	ld	[%i0], %g3
	ld	[%g1+20], %o5
.LL60:
	ld	[%i0+4], %g3
	ld	[%g1], %o0
	ld	[%g1+4], %o1
	ld	[%g1+8], %o2
	ld	[%g1+12], %o3
	call	%g3, 0
	ld	[%g1+16], %o4
	nop
	ld	[%i0+12], %o7
	cmp	%o7, 1
	be	.LL10
	mov	%o0, %l0
	cmp	%o7, 0
	be,a	.LL59
	ld	[%i0+8], %g3
	cmp	%o7, 2
	be	.LL53
	cmp	%o7, 3
	be	.LL53
	cmp	%o7, 4
	be	.LL53
	cmp	%o7, 5
	be	.LL52
	cmp	%o7, 6
	be	.LL52
	cmp	%o7, 7
	be	.LL51
	cmp	%o7, 8
	be	.LL51
	cmp	%o7, 9
	be	.LL51
	cmp	%o7, 10
	be	.LL51
	add	%o7, -11, %g3
	cmp	%g3, 1
	bgu	.LL31
	cmp	%o7, 13
	ld	[%i0+8], %g3
	st	%o0, [%g3]
	b	.LL10
	st	%o1, [%g3+4]
.LL31:
	be	.LL56
	cmp	%o7, 14
	be	.LL57
	cmp	%o7, 15
	be	.LL51
	cmp	%o7, 16
	bne	.LL10
	nop
	ld	[%i0], %g3
	andcc	%g3, 2, %g0
	be	.LL10
	nop
	ld	[%i0+16], %g3
	cmp	%g3, 1
	be	.LL53
	cmp	%g3, 2
	be	.LL52
	cmp	%g3, 4
	bne	.LL10
	nop
.LL51:
	ld	[%i0+8], %g3
.LL59:
	b	.LL10
	st	%l0, [%g3]
.LL52:
	ld	[%i0+8], %g3
	b	.LL10
	sth	%l0, [%g3]
.LL53:
	ld	[%i0+8], %g3
	b	.LL10
	stb	%l0, [%g3]
.LL57:
	ld	[%i0+8], %g3
	b	.LL10
	std	%f0, [%g3]
.LL56:
	ld	[%i0], %g3
	andcc	%g3, 32, %g0
	bne,a	.LL34
	fdtos	%f0, %f0
.LL34:
	ld	[%i0+8], %g3
	b	.LL10
	st	%f0, [%g3]
.LL55:
	andcc	%g3, 16, %g0
	be,a	.LL60
	ld	[%g1+20], %o5
	b	.LL58
	ld	[%i0+16], %l0
.LL54:
	ld	[%i0+8], %g3
	b	.LL2
	st	%g3, [%sp+64]
.LL58:
	sethi	%hi(-1614774272), %g3
	sethi	%hi(16777216), %o7
	st	%g3, [%fp-32]
	st	%o7, [%fp-28]
	sethi	%hi(-1341120512), %o7
	sethi	%hi(-2117607424), %g3
	st	%o7, [%fp-20]
	or	%g3, 8, %g3
	and	%l0, 4095, %l0
	st	%g3, [%fp-16]
	sethi	%hi(-2115502080), %o7
	st	%l0, [%fp-24]
	st	%o7, [%fp-12]
	add	%fp, -32, %g3
	iflush %g3
	add	%fp, -24, %o7
	iflush %o7
	add	%fp, -16, %g3
	iflush %g3
	add	%fp, -12, %o7
	iflush %o7
	ld	[%g1+20], %o5
	ld	[%i0+4], %g2
	ld	[%g1], %o0
	ld	[%g1+4], %o1
	ld	[%g1+8], %o2
	ld	[%g1+12], %o3
	jmp	%fp-32
	ld	[%g1+16], %o4
.LL10:
	ret
	restore %g0, 0, %o0
.LLfe1:
	.size	avcall_call,.LLfe1-avcall_call
	.ident	"GCC: (GNU) 3.1"
