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
	.global C(avcall_call)
	.syntax unified
	.arm
	.fpu vfpv3-d16
	.type	avcall_call, %function
FUNBEGIN(avcall_call)
	// args = 0, pretend = 0, frame = 0
	// frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, fp, lr}
	mov	r4, r0
	ldr	ip, [r4, $24]
	add	fp, sp, $12
	ldr	r0, [r0, $20]
	sub	sp, sp, $1024
	sub	sp, sp, $8
	sub	r3, r0, ip
	cmp	r3, $19
	addgt	r3, ip, $16
	movgt	r2, sp
	subgt	r2, r2, $4
	ble	L(6)
L(5):
	ldr	r1, [r3], $4
	cmp	r0, r3
	str	r1, [r2, $4]!
	bne	L(5)
L(6):
	ldr	r3, [r4, $48]
	tst	r3, $1
	beq	L(4)
	.syntax divided
// 87 "avcall-armhf.c" 1
	vldr.32 s0,[r4, $56]
// 0 "" 2
	.arm
	.syntax unified
L(4):
	tst	r3, $2
	beq	L(7)
	.syntax divided
// 89 "avcall-armhf.c" 1
	vldr.32 s1,[r4, $60]
// 0 "" 2
	.arm
	.syntax unified
L(7):
	tst	r3, $4
	beq	L(8)
	.syntax divided
// 91 "avcall-armhf.c" 1
	vldr.32 s2,[r4, $64]
// 0 "" 2
	.arm
	.syntax unified
L(8):
	tst	r3, $8
	beq	L(9)
	.syntax divided
// 93 "avcall-armhf.c" 1
	vldr.32 s3,[r4, $68]
// 0 "" 2
	.arm
	.syntax unified
L(9):
	tst	r3, $16
	beq	L(10)
	.syntax divided
// 95 "avcall-armhf.c" 1
	vldr.32 s4,[r4, $72]
// 0 "" 2
	.arm
	.syntax unified
L(10):
	tst	r3, $32
	beq	L(11)
	.syntax divided
// 97 "avcall-armhf.c" 1
	vldr.32 s5,[r4, $76]
// 0 "" 2
	.arm
	.syntax unified
L(11):
	tst	r3, $64
	beq	L(12)
	.syntax divided
// 99 "avcall-armhf.c" 1
	vldr.32 s6,[r4, $80]
// 0 "" 2
	.arm
	.syntax unified
L(12):
	tst	r3, $128
	beq	L(13)
	.syntax divided
// 101 "avcall-armhf.c" 1
	vldr.32 s7,[r4, $84]
// 0 "" 2
	.arm
	.syntax unified
L(13):
	tst	r3, $256
	beq	L(14)
	.syntax divided
// 103 "avcall-armhf.c" 1
	vldr.32 s8,[r4, $88]
// 0 "" 2
	.arm
	.syntax unified
L(14):
	tst	r3, $512
	beq	L(15)
	.syntax divided
// 105 "avcall-armhf.c" 1
	vldr.32 s9,[r4, $92]
// 0 "" 2
	.arm
	.syntax unified
L(15):
	tst	r3, $1024
	beq	L(16)
	.syntax divided
// 107 "avcall-armhf.c" 1
	vldr.32 s10,[r4, $96]
// 0 "" 2
	.arm
	.syntax unified
L(16):
	tst	r3, $2048
	beq	L(17)
	.syntax divided
// 109 "avcall-armhf.c" 1
	vldr.32 s11,[r4, $100]
// 0 "" 2
	.arm
	.syntax unified
L(17):
	tst	r3, $4096
	beq	L(18)
	.syntax divided
// 111 "avcall-armhf.c" 1
	vldr.32 s12,[r4, $104]
// 0 "" 2
	.arm
	.syntax unified
L(18):
	tst	r3, $8192
	beq	L(19)
	.syntax divided
// 113 "avcall-armhf.c" 1
	vldr.32 s13,[r4, $108]
// 0 "" 2
	.arm
	.syntax unified
L(19):
	tst	r3, $16384
	beq	L(20)
	.syntax divided
// 115 "avcall-armhf.c" 1
	vldr.32 s14,[r4, $112]
// 0 "" 2
	.arm
	.syntax unified
L(20):
	tst	r3, $32768
	beq	L(21)
	.syntax divided
// 117 "avcall-armhf.c" 1
	vldr.32 s15,[r4, $116]
// 0 "" 2
	.arm
	.syntax unified
L(21):
	ldr	r3, [r4, $52]
	tst	r3, $1
	beq	L(22)
	.syntax divided
// 121 "avcall-armhf.c" 1
	vldr.64 d0,[r4, $120]
// 0 "" 2
	.arm
	.syntax unified
L(22):
	tst	r3, $2
	beq	L(23)
	.syntax divided
// 123 "avcall-armhf.c" 1
	vldr.64 d1,[r4, $128]
// 0 "" 2
	.arm
	.syntax unified
L(23):
	tst	r3, $4
	beq	L(24)
	.syntax divided
// 125 "avcall-armhf.c" 1
	vldr.64 d2,[r4, $136]
// 0 "" 2
	.arm
	.syntax unified
L(24):
	tst	r3, $8
	beq	L(25)
	.syntax divided
// 127 "avcall-armhf.c" 1
	vldr.64 d3,[r4, $144]
// 0 "" 2
	.arm
	.syntax unified
L(25):
	tst	r3, $16
	beq	L(26)
	.syntax divided
// 129 "avcall-armhf.c" 1
	vldr.64 d4,[r4, $152]
// 0 "" 2
	.arm
	.syntax unified
L(26):
	tst	r3, $32
	beq	L(27)
	.syntax divided
// 131 "avcall-armhf.c" 1
	vldr.64 d5,[r4, $160]
// 0 "" 2
	.arm
	.syntax unified
L(27):
	tst	r3, $64
	beq	L(28)
	.syntax divided
// 133 "avcall-armhf.c" 1
	vldr.64 d6,[r4, $168]
// 0 "" 2
	.arm
	.syntax unified
L(28):
	tst	r3, $128
	beq	L(29)
	.syntax divided
// 135 "avcall-armhf.c" 1
	vldr.64 d7,[r4, $176]
// 0 "" 2
	.arm
	.syntax unified
L(29):
	ldm	ip, {r0, r1, r2, r3}
	ldr	r5, [r4, $4]
	blx	r5
	ldrb	r3, [r4, $12]	// zero_extendqisi2
	cmp	r3, $1
	beq	L(30)
	cmp	r3, $0
	beq	L(130)
	cmp	r3, $2
	beq	L(128)
	cmp	r3, $3
	beq	L(128)
	cmp	r3, $4
	beq	L(128)
	cmp	r3, $5
	beq	L(131)
	cmp	r3, $6
	beq	L(131)
	cmp	r3, $7
	beq	L(130)
	cmp	r3, $8
	beq	L(130)
	cmp	r3, $9
	beq	L(130)
	cmp	r3, $10
	beq	L(130)
	sub	r2, r3, $11
	cmp	r2, $1
	bls	L(132)
	cmp	r3, $13
	ldreq	r3, [r4, $8]
	vstreq.32	s0, [r3]
	beq	L(30)
	cmp	r3, $14
	ldreq	r3, [r4, $8]
	vstreq.64	d0, [r3]
	beq	L(30)
	cmp	r3, $15
	beq	L(130)
	cmp	r3, $16
	bne	L(30)
	ldr	r3, [r4]
	tst	r3, $512
	beq	L(30)
	ldr	r3, [r4, $16]
	cmp	r3, $1
	beq	L(128)
	cmp	r3, $2
	beq	L(131)
	cmp	r3, $4
	bls	L(130)
	cmp	r3, $8
	bne	L(30)
L(132):
	ldr	r3, [r4, $8]
	stm	r3, {r0, r1}
L(30):
	mov	r0, $0
	sub	sp, fp, $12
	// sp needed
	pop	{r4, r5, fp, pc}
L(130):
	ldr	r3, [r4, $8]
	str	r0, [r3]
	mov	r0, $0
	sub	sp, fp, $12
	// sp needed
	pop	{r4, r5, fp, pc}
L(128):
	ldr	r3, [r4, $8]
	strb	r0, [r3]
	mov	r0, $0
	sub	sp, fp, $12
	// sp needed
	pop	{r4, r5, fp, pc}
L(131):
	ldr	r3, [r4, $8]
	strh	r0, [r3]	// movhi
	b	L(30)
	FUNEND(avcall_call)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",%progbits
#endif
