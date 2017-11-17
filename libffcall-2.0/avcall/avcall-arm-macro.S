#include "asm-arm.h"
	.text
	.align	2
	.global C(avcall_call)
	DECLARE_FUNCTION(avcall_call)
FUNBEGIN(avcall_call)
	// args = 0, pretend = 0, frame = 1024
	// frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	sub	fp, ip, $4
	sub	sp, sp, $1024
	add	r2, r0, $20
	ldmia	r2, {r2, r3}
	sub	r3, r2, r3
	mov	ip, $4
	mov	r1, r3, asr $2
	cmp	ip, r1
	mov	r5, r0
	bic	sp, sp, $7
	ldr	r4, [r0, $24]
	bge	L(47)
	add	r2, sp, $16
L(6):
	ldr	r3, [r4, ip, asl $2]
	add	ip, ip, $1
	cmp	ip, r1
	str	r3, [r2, $-16]
	add	r2, r2, $4
	blt	L(6)
L(47):
	ldmia	r4, {r0, r1, r2, r3}	// phole ldm
	mov	lr, pc
	ldr	pc, [r5, $4]
	ldr	r2, [r5, $12]
	cmp	r2, $1
	mov	ip, r0
	beq	L(8)
	cmp	r2, $0
	beq	L(57)
	cmp	r2, $2
	beq	L(50)
	cmp	r2, $3
	beq	L(50)
	cmp	r2, $4
	beq	L(50)
	cmp	r2, $5
	beq	L(49)
	cmp	r2, $6
	beq	L(49)
	cmp	r2, $7
	beq	L(57)
	cmp	r2, $8
	beq	L(57)
	cmp	r2, $9
	beq	L(57)
	cmp	r2, $10
	beq	L(57)
	sub	r3, r2, $11
	cmp	r3, $1
	bls	L(56)
	cmp	r2, $13
	ldreq	r3, [r5, $8]
	streq	r0, [r3, $0]	// float
	beq	L(8)
	cmp	r2, $14
	ldreq	r3, [r5, $8]
	stmeqia	r3, {r0-r1}	// double
	beq	L(8)
	cmp	r2, $15
	beq	L(57)
	cmp	r2, $16
	beq	L(58)
L(8):
	mov	r0, $0
	ldmea	fp, {r4, r5, fp, sp, pc}
L(58):
	ldr	r3, [r5, $0]
	tst	r3, $512
	beq	L(8)
	ldr	r3, [r5, $16]
	cmp	r3, $1
	beq	L(50)
	cmp	r3, $2
	beq	L(49)
	cmp	r3, $4
	bhi	L(43)
L(57):
	ldr	r3, [r5, $8]
L(48):
	str	ip, [r3, $0]
	b	L(8)
L(43):
	cmp	r3, $8
	bne	L(8)
L(56):
	ldr	r3, [r5, $8]
	str	r1, [r3, $4]
	b	L(48)
L(49):
	ldr	r3, [r5, $8]
	strh	ip, [r3, $0]	// movhi 
	b	L(8)
L(50):
	ldr	r3, [r5, $8]
	strb	ip, [r3, $0]
	b	L(8)
L(fe1):
	FUNEND(avcall_call)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",%progbits
#endif
