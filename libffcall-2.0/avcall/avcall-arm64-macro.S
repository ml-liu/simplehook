#include "asm-arm.h"
	.cpu generic+fp+simd
	.text
	.align	2
	.p2align 3,,7
	.global C(avcall_call)
	.type	avcall_call, %function
FUNBEGIN(avcall_call)
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	ldp	x11, x12, [x0, 40]
	stp	x19, x20, [sp, 16]
	sub	x11, x11, x12
	ldr	w15, [x0, 64]
	asr	x10, x11, 3
	ldr	w14, [x0, 136]
	cmp	w10, wzr
	mov	x19, x0
	str	d8, [sp, 32]
	sub	sp, sp, $2064
	ble	L(6)
	mov	x13, sp
	mov	x9, 0
	mov	w11, w10
	.p2align 2
L(87):
	ldr	x10, [x12, x9, lsl 3]
	str	x10, [x13, x9, lsl 3]
	add	x9, x9, 1
	cmp	w11, w9
	bgt	L(87)
L(6):
	cbz	w15, L(7)
	cmp	w15, 1
	ldr	x0, [x19, 72]
	bls	L(7)
	cmp	w15, 2
	ldr	x1, [x19, 80]
	beq	L(7)
	cmp	w15, 3
	ldr	x2, [x19, 88]
	beq	L(7)
	cmp	w15, 4
	ldr	x3, [x19, 96]
	beq	L(7)
	cmp	w15, 5
	ldr	x4, [x19, 104]
	beq	L(7)
	cmp	w15, 6
	ldr	x5, [x19, 112]
	beq	L(7)
	cmp	w15, 7
	ldr	x6, [x19, 120]
	beq	L(7)
	ldr	x7, [x19, 128]
	.p2align 2
L(7):
	cbz	w14, L(9)
	ldr	w9, [x19, 144]
	tbz	x9, 0, L(10)
	ldr	d0, [x19, 184]
L(11):
	cmp	w14, 1
	bls	L(9)
	tbnz	x9, 1, L(121)
	ldr	w10, [x19, 140]
	tbz	x10, 1, L(14)
	ldr	s1, [x19, 152]
L(14):
	cmp	w14, 2
	beq	L(9)
	tbz	x9, 2, L(15)
	ldr	d2, [x19, 200]
L(16):
	cmp	w14, 3
	beq	L(9)
	tbnz	x9, 3, L(122)
	ldr	w10, [x19, 140]
	tbz	x10, 3, L(18)
	ldr	s3, [x19, 160]
L(18):
	cmp	w14, 4
	beq	L(9)
	tbz	x9, 4, L(19)
	ldr	d4, [x19, 216]
L(20):
	cmp	w14, 5
	beq	L(9)
	tbz	x9, 5, L(21)
	ldr	d5, [x19, 224]
L(22):
	cmp	w14, 6
	beq	L(9)
	tbz	x9, 6, L(23)
	ldr	d6, [x19, 232]
L(24):
	cmp	w14, 7
	beq	L(9)
	tbz	x9, 7, L(25)
	ldr	d7, [x19, 240]
	.p2align 2
L(9):
	ldr	w9, [x19, 24]
	cmp	w9, 13
	beq	L(123)
	cmp	w9, 14
	beq	L(124)
	ldr	x9, [x19, 8]
	blr	x9
	mov	x16, x0
	ldr	w9, [x19, 24]
	cmp	w9, 1
	beq	L(27)
	cbz	w9, L(119)
	cmp	w9, 2
	beq	L(115)
	cmp	w9, 3
	beq	L(115)
	cmp	w9, 4
	beq	L(115)
	cmp	w9, 5
	beq	L(116)
	cmp	w9, 6
	beq	L(116)
	cmp	w9, 7
	beq	L(117)
	cmp	w9, 8
	beq	L(117)
	and	w12, w9, -3
	cmp	w12, 9
	beq	L(119)
	sub	w12, w9, $10
	tst	w12, -3
	beq	L(119)
	cmp	w9, 15
	beq	L(119)
	cmp	w9, 16
	bne	L(27)
	ldr	w9, [x19]
	tbz	x9, 9, L(27)
	ldr	x12, [x19, 32]
	sub	x9, x12, $1
	cmp	x9, 15
	bhi	L(27)
	ldr	x13, [x19, 16]
	cmp	x12, 8
	and	x9, x13, 7
	and	x13, x13, -8
	add	x12, x12, x9
	bhi	L(40)
	cmp	x12, 8
	lsl	w11, w12, 3
	bhi	L(41)
	lsl	w9, w9, 3
	mov	x12, 2
	mov	x14, 1
	sub	w11, w11, $1
	lsl	x14, x14, x9
	lsl	x11, x12, x11
	lsl	x9, x0, x9
	sub	x10, x11, x14
	ldr	d17, [x13]
	fmov	d16, x10
	fmov	d8, x9
	bif	v8.8b, v17.8b, v16.8b
	str	d8, [x13]
L(27):
	add	sp, x29, 0
	ldr	d8, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
L(10):
	ldr	w10, [x19, 140]
	tbz	x10, 0, L(11)
	ldr	s0, [x19, 148]
	b	L(11)
	.p2align 3
L(119):
	ldr	x9, [x19, 16]
	mov	w0, 0
	str	x16, [x9]
	ldr	d8, [x29, 32]
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
L(121):
	ldr	d1, [x19, 192]
	b	L(14)
	.p2align 3
L(115):
	ldr	x9, [x19, 16]
	mov	w0, 0
	strb	w16, [x9]
	ldr	d8, [x29, 32]
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
L(124):
	ldp	x9, x20, [x19, 8]
	blr	x9
	str	d0, [x20]
	mov	w0, 0
	ldr	d8, [x29, 32]
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
L(123):
	ldp	x9, x20, [x19, 8]
	blr	x9
	str	s0, [x20]
	b	L(27)
L(15):
	ldr	w10, [x19, 140]
	tbz	x10, 2, L(16)
	ldr	s2, [x19, 156]
	b	L(16)
L(116):
	ldr	x9, [x19, 16]
	strh	w16, [x9]
	b	L(27)
L(122):
	ldr	d3, [x19, 208]
	b	L(18)
L(117):
	ldr	x9, [x19, 16]
	str	w16, [x9]
	b	L(27)
L(19):
	ldr	w10, [x19, 140]
	tbz	x10, 4, L(20)
	ldr	s4, [x19, 164]
	b	L(20)
L(21):
	ldr	w10, [x19, 140]
	tbz	x10, 5, L(22)
	ldr	s5, [x19, 168]
	b	L(22)
L(23):
	ldr	w10, [x19, 140]
	tbz	x10, 6, L(24)
	ldr	s6, [x19, 172]
	b	L(24)
L(25):
	ldr	w9, [x19, 140]
	tbz	x9, 7, L(9)
	ldr	s7, [x19, 176]
	b	L(9)
L(41):
	lsl	w14, w9, 3
	neg	w9, w9, lsl 3
	movi	d16, -1
	add	w10, w9, 64
	dup	v8.8b, w14
	lsl	x9, x0, x14
	ldp	d17, d18, [x13]
	mov	x12, 2
	sub	w11, w11, $65
	lsl	x11, x12, x11
	ushl	d16, d16, d8
	fmov	d8, x9
	asr	x9, x0, x10
	sub	x10, x11, $1
	bsl	v16.8b, v8.8b, v17.8b
	fmov	d8, x10
	fmov	d17, x9
	str	d16, [x13]
	bif	v17.8b, v18.8b, v8.8b
	str	d17, [x13, 8]
	b	L(27)
L(40):
	lsl	w14, w9, 3
	cmp	x12, 16
	movi	d16, -1
	lsl	x15, x0, x14
	dup	v8.8b, w14
	fmov	d17, x15
	ushl	d16, d16, d8
	ldr	d8, [x13]
	bsl	v16.8b, v17.8b, v8.8b
	str	d16, [x13]
	bls	L(125)
	lsl	w12, w12, 3
	mov	x15, 2
	neg	w9, w9, lsl 3
	sub	w12, w12, $129
	add	w9, w9, 64
	lsl	x12, x15, x12
	asr	x11, x1, x9
	asr	x10, x0, x9
	sub	x9, x12, $1
	ldr	d17, [x13, 16]
	fmov	d16, x11
	lsl	x14, x1, x14
	fmov	d8, x9
	orr	x10, x10, x14
	bif	v16.8b, v17.8b, v8.8b
	fmov	x11, d16
	stp	x10, x11, [x13, 8]
	b	L(27)
L(125):
	neg	w9, w9, lsl 2
	lsl	w12, w12, 3
	add	w9, w9, 32
	mov	x15, 2
	sub	w12, w12, $65
	lsl	x11, x1, x14
	lsl	x12, x15, x12
	asr	x14, x0, x9
	asr	x10, x14, x9
	sub	x9, x12, $1
	ldr	d17, [x13, 8]
	fmov	d8, x9
	orr	x9, x10, x11
	fmov	d16, x9
	bif	v16.8b, v17.8b, v8.8b
	str	d16, [x13, 8]
	b	L(27)
	FUNEND(avcall_call)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",%progbits
#endif
