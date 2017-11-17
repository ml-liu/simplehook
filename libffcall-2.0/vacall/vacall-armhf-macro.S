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
	.global C(vacall_receiver)
	.syntax unified
	.arm
	.fpu vfpv3-d16
	.type	vacall_receiver, %function
FUNBEGIN(vacall_receiver)
	// args = 20, pretend = 16, frame = 176
	// frame_needed = 1, uses_anonymous_args = 0
	sub	sp, sp, $16
	mov	ip, $0
	push	{r4, r5, fp, lr}
	add	fp, sp, $12
	add	lr, fp, $4
	movw	r4, $:lower16:C(vacall_function)
	movt	r4, $:upper16:C(vacall_function)
	sub	sp, sp, $176
	add	r5, fp, $20
	stm	lr, {r0, r1, r2, r3}
	sub	r0, fp, $188
	vstr.32	s0, [fp, $-144]
	str	lr, [fp, $-156]
	str	ip, [fp, $-188]
	vstr.32	s1, [fp, $-140]
	str	ip, [fp, $-152]
	str	r5, [fp, $-172]
	vstr.32	s2, [fp, $-136]
	vstr.32	s3, [fp, $-132]
	vstr.32	s4, [fp, $-128]
	vstr.32	s5, [fp, $-124]
	vstr.32	s6, [fp, $-120]
	vstr.32	s7, [fp, $-116]
	vstr.32	s8, [fp, $-112]
	vstr.32	s9, [fp, $-108]
	vstr.32	s10, [fp, $-104]
	vstr.32	s11, [fp, $-100]
	vstr.32	s12, [fp, $-96]
	vstr.32	s13, [fp, $-92]
	vstr.32	s14, [fp, $-88]
	vstr.32	s15, [fp, $-84]
	vstr.64	d0, [fp, $-76]
	vstr.64	d1, [fp, $-68]
	vstr.64	d2, [fp, $-60]
	vstr.64	d3, [fp, $-52]
	vstr.64	d4, [fp, $-44]
	vstr.64	d5, [fp, $-36]
	vstr.64	d6, [fp, $-28]
	ldr	r3, [r4]
	str	ip, [fp, $-148]
	vstr.64	d7, [fp, $-20]
	str	ip, [fp, $-168]
	strb	ip, [fp, $-164]
	blx	r3
	ldrb	r3, [fp, $-164]	// zero_extendqisi2
	cmp	r3, $0
	beq	L(1)
	cmp	r3, $1
	beq	L(25)
	cmp	r3, $2
	ldrsbeq	r0, [fp, $-180]
	beq	L(1)
	cmp	r3, $3
	beq	L(25)
	cmp	r3, $4
	ldrsheq	r0, [fp, $-180]
	beq	L(1)
	cmp	r3, $5
	ldrheq	r0, [fp, $-180]
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
	vldreq.32	s0, [fp, $-180]
	beq	L(1)
	cmp	r3, $13
	vldreq.64	d0, [fp, $-180]
	beq	L(1)
	cmp	r3, $14
	beq	L(27)
	cmp	r3, $15
	bne	L(1)
	ldr	r3, [fp, $-188]
	tst	r3, $1024
	beq	L(1)
	ldr	r3, [fp, $-160]
	cmp	r3, $1
	beq	L(30)
	cmp	r3, $2
	ldr	r3, [fp, $-168]
	ldrheq	r0, [r3]
	ldrne	r0, [r3]
L(1):
	sub	sp, fp, $12
	// sp needed
	pop	{r4, r5, fp, lr}
	add	sp, sp, $16
	bx	lr
L(25):
	ldrb	r0, [fp, $-180]	// zero_extendqisi2
	sub	sp, fp, $12
	// sp needed
	pop	{r4, r5, fp, lr}
	add	sp, sp, $16
	bx	lr
L(27):
	ldr	r0, [fp, $-180]
	sub	sp, fp, $12
	// sp needed
	pop	{r4, r5, fp, lr}
	add	sp, sp, $16
	bx	lr
L(29):
	ldr	r0, [fp, $-180]
	ldr	r1, [fp, $-176]
	b	L(1)
L(30):
	ldr	r3, [fp, $-168]
	ldrb	r0, [r3]	// zero_extendqisi2
	b	L(1)
	FUNEND(vacall_receiver)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",%progbits
#endif
