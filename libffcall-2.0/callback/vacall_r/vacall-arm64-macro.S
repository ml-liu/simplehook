#include "asm-arm.h"
	.cpu generic+fp+simd
	.text
	.align	2
	.p2align 3,,7
	.type	callback_receiver, %function
FUNBEGIN(callback_receiver)
	stp	x29, x30, [sp, -256]!
	add	x29, sp, 0
	ldr	x10, [x18]
	add	x11, x29, 256
	stp	s0, s1, [x29, 156]
	stp	s2, s3, [x29, 164]
	stp	x0, x1, [x29, 88]
	stp	s4, s5, [x29, 172]
	stp	x11, xzr, [x29, 40]
	stp	s6, s7, [x29, 180]
	str	x8, [x29, 72]
	stp	d0, d1, [x29, 192]
	stp	x2, x3, [x29, 104]
	stp	d2, d3, [x29, 208]
	stp	x4, x5, [x29, 120]
	stp	d4, d5, [x29, 224]
	stp	x6, x7, [x29, 136]
	stp	d6, d7, [x29, 240]
	str	wzr, [x29, 16]
	add	x1, x29, 16
	str	wzr, [x29, 56]
	ldr	x0, [x18, 8]
	str	wzr, [x29, 80]
	str	wzr, [x29, 152]
	blr	x10
	ldr	w9, [x29, 56]
	cbz	w9, L(1)
	cmp	w9, 1
	beq	L(25)
	cmp	w9, 2
	beq	L(29)
	cmp	w9, 3
	beq	L(25)
	cmp	w9, 4
	beq	L(30)
	cmp	w9, 5
	beq	L(31)
	cmp	w9, 6
	beq	L(32)
	cmp	w9, 7
	beq	L(33)
	and	w10, w9, -3
	cmp	w10, 8
	beq	L(27)
	cmp	w10, 9
	beq	L(27)
	cmp	w9, 12
	beq	L(34)
	cmp	w9, 13
	beq	L(35)
	cmp	w9, 14
	beq	L(27)
	cmp	w9, 15
	bne	L(1)
	ldr	w9, [x29, 16]
	tbz	x9, 10, L(1)
	ldr	x9, [x29, 64]
	sub	x10, x9, $1
	cmp	x10, 15
	bhi	L(1)
	ldr	x11, [x29, 48]
	cmp	x9, 8
	and	x10, x11, 7
	and	x11, x11, -8
	add	x9, x9, x10
	bhi	L(15)
	cmp	x9, 8
	lsl	w9, w9, 3
	bhi	L(16)
	mov	x12, 2
	sub	w9, w9, $1
	lsl	x9, x12, x9
	ldr	x11, [x11]
	sub	x9, x9, $1
	lsl	w10, w10, 3
	and	x9, x9, x11
	asr	x0, x9, x10
L(1):
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
L(25):
	ldrb	w0, [x29, 24]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
L(27):
	ldr	x0, [x29, 24]
	b	L(1)
	.p2align 3
L(29):
	ldrsb	x0, [x29, 24]
	b	L(1)
	.p2align 3
L(30):
	ldrsh	x0, [x29, 24]
	b	L(1)
	.p2align 3
L(31):
	ldrh	w0, [x29, 24]
	b	L(1)
	.p2align 3
L(32):
	ldrsw	x0, [x29, 24]
	b	L(1)
	.p2align 3
L(33):
	ldr	w0, [x29, 24]
	b	L(1)
L(34):
	ldr	s0, [x29, 24]
	b	L(1)
L(35):
	ldr	d0, [x29, 24]
	b	L(1)
L(15):
	cmp	x9, 16
	lsl	w9, w9, 3
	bls	L(36)
	mov	x13, 2
	sub	w9, w9, $129
	ldp	x14, x12, [x11, 8]
	lsl	x9, x13, x9
	lsl	w15, w10, 3
	sub	x9, x9, $1
	neg	w10, w10, lsl 3
	ldr	x11, [x11]
	add	w10, w10, 64
	and	x9, x9, x12
	lsl	x16, x14, x10
	asr	x11, x11, x15
	asr	x14, x14, x15
	lsl	x10, x9, x10
	orr	x0, x11, x16
	orr	x1, x10, x14
	b	L(1)
L(16):
	mov	w13, -8
	mov	x14, 2
	sub	w9, w9, $65
	lsl	w15, w10, 3
	ldr	x12, [x11, 8]
	lsl	x9, x14, x9
	mul	w10, w13, w10
	sub	x9, x9, $1
	ldr	x11, [x11]
	add	w10, w10, 64
	and	x9, x9, x12
	asr	x11, x11, x15
	lsl	x9, x9, x10
	orr	x0, x9, x11
	b	L(1)
L(36):
	mov	w13, -4
	mov	x14, 2
	sub	w9, w9, $65
	lsl	w15, w10, 3
	ldr	x12, [x11, 8]
	lsl	x9, x14, x9
	mul	w10, w13, w10
	sub	x9, x9, $1
	ldr	x11, [x11]
	add	w10, w10, 32
	and	x9, x9, x12
	asr	x1, x9, x15
	lsl	x9, x9, x10
	asr	x11, x11, x15
	lsl	x9, x9, x10
	orr	x0, x11, x9
	b	L(1)
	FUNEND(callback_receiver)
	.align	2
	.p2align 3,,7
	.global C(callback_get_receiver)
	.type	callback_get_receiver, %function
FUNBEGIN(callback_get_receiver)
	adrp	x9, callback_receiver
	add	x0, x9, :lo12:callback_receiver
	ret
	FUNEND(callback_get_receiver)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",%progbits
#endif
