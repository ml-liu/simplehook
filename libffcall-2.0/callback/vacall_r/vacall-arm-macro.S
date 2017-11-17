#include "asm-arm.h"
	.text
	.align	2
	DECLARE_FUNCTION(callback_receiver)
FUNBEGIN(callback_receiver)
	// args = 28, pretend = 0, frame = 32
	// frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	mov	r2, $0
	sub	fp, ip, $4
	sub	sp, sp, $32
	ldr	r4, [fp, $4]
	str	r2, [fp, $-28]
	add	r3, fp, $28
	str	r2, [fp, $-24]
	str	r2, [fp, $-48]
	str	r3, [fp, $-32]
	bic	sp, sp, $7
	ldr	r0, [r4, $4]
	sub	r1, fp, $48
	mov	lr, pc
	ldr	pc, [r4, $0]
	ldr	r2, [fp, $-24]
	cmp	r2, $0
	ldmeqea	fp, {r4, fp, sp, pc}
	cmp	r2, $1
	beq	L(36)
	cmp	r2, $2
	ldreqsb	r0, [fp, $-40]
	ldmeqea	fp, {r4, fp, sp, pc}
	cmp	r2, $3
	beq	L(36)
	cmp	r2, $4
	ldreqsh	r0, [fp, $-40]
	ldmeqea	fp, {r4, fp, sp, pc}
	cmp	r2, $5
	ldreqh	r0, [fp, $-40]
	ldmeqea	fp, {r4, fp, sp, pc}
	cmp	r2, $6
	beq	L(40)
	cmp	r2, $7
	beq	L(40)
	cmp	r2, $8
	beq	L(40)
	cmp	r2, $9
	beq	L(40)
	sub	r3, r2, $10
	cmp	r3, $1
	bls	L(41)
	cmp	r2, $12
	ldreq	r0, [fp, $-40]	// float
	ldmeqea	fp, {r4, fp, sp, pc}
	cmp	r2, $13
	beq	L(41)
	cmp	r2, $14
	beq	L(40)
	cmp	r2, $15
	ldmneea	fp, {r4, fp, sp, pc}
	ldr	r3, [fp, $-48]
	tst	r3, $1024
	ldmeqea	fp, {r4, fp, sp, pc}
	ldr	r3, [fp, $-20]
	cmp	r3, $1
	ldreq	r3, [fp, $-28]
	ldreqb	r0, [r3, $0]	// zero_extendqisi2
	ldmeqea	fp, {r4, fp, sp, pc}
	cmp	r3, $2
	ldreq	r3, [fp, $-28]
	ldrne	r3, [fp, $-28]
	ldreqh	r0, [r3, $0]
	ldrne	r0, [r3, $0]
	ldmea	fp, {r4, fp, sp, pc}
L(40):
	ldr	r0, [fp, $-40]
	ldmea	fp, {r4, fp, sp, pc}
L(41):
	sub	r0, fp, $40
	ldmia	r0, {r0, r1}	// phole ldm
	ldmea	fp, {r4, fp, sp, pc}
L(36):
	ldrb	r0, [fp, $-40]	// zero_extendqisi2
	ldmea	fp, {r4, fp, sp, pc}
L(fe1):
	FUNEND(callback_receiver)
	.align	2
	.global C(callback_get_receiver)
	DECLARE_FUNCTION(callback_get_receiver)
FUNBEGIN(callback_get_receiver)
	// args = 0, pretend = 0, frame = 0
	// frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {sl, fp, ip, lr, pc}
	ldr	sl, L(44)
	ldr	r3, L(44)+4
L(43):
	add	sl, pc, sl
	sub	fp, ip, $4
	add	r0, sl, r3
	ldmea	fp, {sl, fp, sp, pc}
L(45):
	.align	2
L(44):
	.word	_GLOBAL_OFFSET_TABLE_-(L(43)+8)
	.word	callback_receiver(GOTOFF)
L(fe2):
	FUNEND(callback_get_receiver)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",%progbits
#endif
