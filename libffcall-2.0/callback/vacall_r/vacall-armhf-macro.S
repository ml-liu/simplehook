#include "asm-arm.h"
	.arch armv7-a
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.text
	.align	2
	.global C(callback_receiver)
	.syntax unified
	.arm
	.fpu vfpv3-d16
	.type	callback_receiver, %function
FUNBEGIN(callback_receiver)
	// args = 28, pretend = 0, frame = 176
	// frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, $4
	sub	sp, sp, $176
	ldr	r2, [fp, $4]
	mov	r3, $0
	vstr.32	s0, [fp, $-136]
	sub	r1, fp, $180
	str	r3, [fp, $-180]
	str	r3, [fp, $-144]
	vstr.32	s1, [fp, $-132]
	str	r3, [fp, $-140]
	str	r3, [fp, $-160]
	vstr.32	s2, [fp, $-128]
	strb	r3, [fp, $-156]
	add	r3, fp, $28
	str	r3, [fp, $-148]
	add	r3, fp, $44
	vstr.32	s3, [fp, $-124]
	str	r3, [fp, $-164]
	vstr.32	s4, [fp, $-120]
	vstr.32	s5, [fp, $-116]
	vstr.32	s6, [fp, $-112]
	vstr.32	s7, [fp, $-108]
	vstr.32	s8, [fp, $-104]
	vstr.32	s9, [fp, $-100]
	vstr.32	s10, [fp, $-96]
	vstr.32	s11, [fp, $-92]
	vstr.32	s12, [fp, $-88]
	vstr.32	s13, [fp, $-84]
	vstr.32	s14, [fp, $-80]
	vstr.32	s15, [fp, $-76]
	vstr.64	d0, [fp, $-68]
	vstr.64	d1, [fp, $-60]
	vstr.64	d2, [fp, $-52]
	vstr.64	d3, [fp, $-44]
	vstr.64	d4, [fp, $-36]
	vstr.64	d5, [fp, $-28]
	vstr.64	d6, [fp, $-20]
	ldr	r3, [r2]
	ldr	r0, [r2, $4]
	vstr.64	d7, [fp, $-12]
	blx	r3
	ldrb	r3, [fp, $-156]	// zero_extendqisi2
	cmp	r3, $0
	beq	L(1)
	cmp	r3, $1
	beq	L(25)
	cmp	r3, $2
	ldrsbeq	r0, [fp, $-172]
	beq	L(1)
	cmp	r3, $3
	beq	L(25)
	cmp	r3, $4
	ldrsheq	r0, [fp, $-172]
	beq	L(1)
	cmp	r3, $5
	ldrheq	r0, [fp, $-172]
	beq	L(1)
	cmp	r3, $6
	beq	L(27)
	cmp	r3, $7
	beq	L(27)
	cmp	r3, $8
	beq	L(27)
	cmp	r3, $9
	beq	L(27)
	sub	r2, r3, $10
	cmp	r2, $1
	bls	L(29)
	cmp	r3, $12
	vldreq.32	s0, [fp, $-172]
	beq	L(1)
	cmp	r3, $13
	vldreq.64	d0, [fp, $-172]
	beq	L(1)
	cmp	r3, $14
	beq	L(27)
	cmp	r3, $15
	bne	L(1)
	ldr	r3, [fp, $-180]
	tst	r3, $1024
	beq	L(1)
	ldr	r3, [fp, $-152]
	cmp	r3, $1
	beq	L(30)
	cmp	r3, $2
	ldr	r3, [fp, $-160]
	ldrheq	r0, [r3]
	ldrne	r0, [r3]
L(1):
	sub	sp, fp, $4
	// sp needed
	pop	{fp, pc}
L(25):
	ldrb	r0, [fp, $-172]	// zero_extendqisi2
	sub	sp, fp, $4
	// sp needed
	pop	{fp, pc}
L(27):
	ldr	r0, [fp, $-172]
	sub	sp, fp, $4
	// sp needed
	pop	{fp, pc}
L(29):
	ldr	r0, [fp, $-172]
	ldr	r1, [fp, $-168]
	b	L(1)
L(30):
	ldr	r3, [fp, $-160]
	ldrb	r0, [r3]	// zero_extendqisi2
	b	L(1)
	FUNEND(callback_receiver)
	.align	2
	.global C(callback_get_receiver)
	.syntax unified
	.arm
	.fpu vfpv3-d16
	.type	callback_get_receiver, %function
FUNBEGIN(callback_get_receiver)
	// args = 0, pretend = 0, frame = 0
	// frame_needed = 1, uses_anonymous_args = 0
	// link register save eliminated.
	ldr	r3, L(33)
	ldr	r2, L(33)+4
L(PIC0):
	add	r3, pc, r3
	str	fp, [sp, $-4]!
	add	fp, sp, $0
	ldr	r3, [r3, r2]
	mov	r0, r3
	add	sp, fp, $0
	// sp needed
	ldr	fp, [sp], $4
	bx	lr
L(34):
	.align	2
L(33):
	.word	_GLOBAL_OFFSET_TABLE_-(L(PIC0)+8)
	.word	callback_receiver(GOT)
	FUNEND(callback_get_receiver)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",%progbits
#endif
