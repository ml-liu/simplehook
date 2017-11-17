#include "asm-mips.h"
	.file	1 "avcall-mipsn32.c"
	.text
	.align	2
	.align	3
	.globl	avcall_call
	.ent	avcall_call
	DECLARE_FUNCTION(avcall_call)
avcall_call:
	.frame	$fp,64,$31		
	.mask	0xc0010000,-16
	.fmask	0x00000000,0
	addiu	$sp,$sp,-64
	sd	$fp,40($sp)
	sd	$16,32($sp)
	sd	$31,48($sp)
	lw	$12,24($4)
	lw	$2,20($4)
	lw	$3,36($4)
	move	$fp,$sp
	subu	$2,$2,$12
	addiu	$sp,$sp,-2064
	move	$16,$4
	sra	$6,$2,3
	.set	noreorder
	.set	nomacro
	beq	$3,$0,.L2
	move	$4,$sp
	.set	macro
	.set	reorder

	andi	$2,$3,0x1
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L100
	andi	$2,$3,0x2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L101
	andi	$2,$3,0x4
	.set	macro
	.set	reorder

.L127:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L102
	andi	$2,$3,0x8
	.set	macro
	.set	reorder

.L126:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L103
	andi	$2,$3,0x10
	.set	macro
	.set	reorder

.L125:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L104
	andi	$2,$3,0x20
	.set	macro
	.set	reorder

.L124:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L105
	andi	$2,$3,0x40
	.set	macro
	.set	reorder

.L123:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L106
	andi	$2,$3,0x80
	.set	macro
	.set	reorder

.L122:
	bne	$2,$0,.L107
	.align	3
.L2:
	lw	$3,40($16)
.L119:
	.set	noreorder
	.set	nomacro
	beq	$3,$0,.L118
	slt	$2,$6,9
	.set	macro
	.set	reorder

	andi	$2,$3,0x1
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L108
	andi	$2,$3,0x2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L109
	andi	$2,$3,0x4
	.set	macro
	.set	reorder

.L131:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L110
	andi	$2,$3,0x8
	.set	macro
	.set	reorder

.L130:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L111
	andi	$2,$3,0x10
	.set	macro
	.set	reorder

.L129:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L112
	andi	$2,$3,0x20
	.set	macro
	.set	reorder

.L128:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L113
	andi	$2,$3,0x40
	.set	macro
	.set	reorder

.L133:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L114
	andi	$2,$3,0x80
	.set	macro
	.set	reorder

.L132:
	bne	$2,$0,.L115
	slt	$2,$6,9
.L118:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,.L37
	move	$5,$4
	.set	macro
	.set	reorder

	li	$4,8			
	.align	3
.L36:
	sll	$2,$4,3
	addu	$2,$2,$12
	ld	$3,0($2)
	addiu	$4,$4,1
	sd	$3,0($5)
	.set	noreorder
	.set	nomacro
	bne	$6,$4,.L36
	addiu	$5,$5,8
	.set	macro
	.set	reorder

.L37:

	ld $4,0($12)
	ld $5,8($12)
	ld $6,16($12)
	ld $7,24($12)
	ld $8,32($12)
	ld $9,40($12)
	ld $10,48($12)
	ld $11,56($12)

	lw	$25,4($16)
	jal	$25
	lw	$4,12($16)
	move	$9,$2
	li	$2,1			
	.set	noreorder
	.set	nomacro
	beql	$4,$2,.L120
	move	$sp,$fp
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beql	$4,$0,.L121
	lw	$2,8($16)
	.set	macro
	.set	reorder

	li	$2,2			
	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L94
	li	$2,3			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L94
	li	$2,4			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L94
	li	$2,5			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L96
	li	$2,6			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L96
	li	$2,7			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L97
	li	$2,8			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L97
	li	$2,9			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L97
	li	$2,10			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L97
	li	$2,11			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L98
	li	$2,12			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L98
	li	$2,13			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L116
	li	$2,14			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L117
	li	$2,15			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L97
	li	$2,16			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bnel	$4,$2,.L120
	move	$sp,$fp
	.set	macro
	.set	reorder

	lw	$4,0($16)
	andi	$2,$4,0x200
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L38
	andi	$2,$4,0x4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beql	$2,$0,.L72
	lw	$8,16($16)
	.set	macro
	.set	reorder

	lw	$3,16($16)
	li	$2,1			
	.set	noreorder
	.set	nomacro
	beq	$3,$2,.L94
	li	$2,2			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$3,$2,.L96
	li	$2,4			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$3,$2,.L97
	li	$2,8			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beql	$3,$2,.L121
	lw	$2,8($16)
	.set	macro
	.set	reorder

.L38:
	move	$sp,$fp
.L120:
	ld	$31,48($sp)
	ld	$fp,40($sp)
	ld	$16,32($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,64
	.set	macro
	.set	reorder

.L98:
	lw	$2,8($16)
.L121:
	move	$sp,$fp
	sd	$9,0($2)
	ld	$31,48($sp)
	ld	$fp,40($sp)
	ld	$16,32($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,64
	.set	macro
	.set	reorder

.L115:

	ldc1 $f19,56($12)

	.set	noreorder
	.set	nomacro
	b	.L118
	slt	$2,$6,9
	.set	macro
	.set	reorder

.L107:

	lwc1 $f19,72($16)

	.set	noreorder
	.set	nomacro
	b	.L119
	lw	$3,40($16)
	.set	macro
	.set	reorder

.L106:

	lwc1 $f18,68($16)

	andi	$2,$3,0x80
	.set	noreorder
	.set	nomacro
	beql	$2,$0,.L119
	lw	$3,40($16)
	.set	macro
	.set	reorder

	b	.L107
.L105:

	lwc1 $f17,64($16)

	andi	$2,$3,0x40
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L122
	andi	$2,$3,0x80
	.set	macro
	.set	reorder

	b	.L106
.L104:

	lwc1 $f16,60($16)

	andi	$2,$3,0x20
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L123
	andi	$2,$3,0x40
	.set	macro
	.set	reorder

	b	.L105
.L103:

	lwc1 $f15,56($16)

	andi	$2,$3,0x10
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L124
	andi	$2,$3,0x20
	.set	macro
	.set	reorder

	b	.L104
.L102:

	lwc1 $f14,52($16)

	andi	$2,$3,0x8
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L125
	andi	$2,$3,0x10
	.set	macro
	.set	reorder

	b	.L103
.L101:

	lwc1 $f13,48($16)

	andi	$2,$3,0x4
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L126
	andi	$2,$3,0x8
	.set	macro
	.set	reorder

	b	.L102
.L100:

	lwc1 $f12,44($16)

	andi	$2,$3,0x2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L127
	andi	$2,$3,0x4
	.set	macro
	.set	reorder

	b	.L101
.L111:

	ldc1 $f15,24($12)

	andi	$2,$3,0x10
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L128
	andi	$2,$3,0x20
	.set	macro
	.set	reorder

	b	.L112
.L110:

	ldc1 $f14,16($12)

	andi	$2,$3,0x8
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L129
	andi	$2,$3,0x10
	.set	macro
	.set	reorder

	b	.L111
.L109:

	ldc1 $f13,8($12)

	andi	$2,$3,0x4
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L130
	andi	$2,$3,0x8
	.set	macro
	.set	reorder

	b	.L110
.L108:

	ldc1 $f12,0($12)

	andi	$2,$3,0x2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L131
	andi	$2,$3,0x4
	.set	macro
	.set	reorder

	b	.L109
.L113:

	ldc1 $f17,40($12)

	andi	$2,$3,0x40
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L132
	andi	$2,$3,0x80
	.set	macro
	.set	reorder

	b	.L114
.L112:

	ldc1 $f16,32($12)

	andi	$2,$3,0x20
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L133
	andi	$2,$3,0x40
	.set	macro
	.set	reorder

	b	.L113
.L114:

	ldc1 $f18,48($12)

	andi	$2,$3,0x80
	.set	noreorder
	.set	nomacro
	beql	$2,$0,.L118
	slt	$2,$6,9
	.set	macro
	.set	reorder

	b	.L115
.L94:
	lw	$2,8($16)
	move	$sp,$fp
	sb	$9,0($2)
	ld	$31,48($sp)
	ld	$fp,40($sp)
	ld	$16,32($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,64
	.set	macro
	.set	reorder

.L97:
	lw	$2,8($16)
	.set	noreorder
	.set	nomacro
	b	.L38
	sw	$9,0($2)
	.set	macro
	.set	reorder

.L96:
	lw	$2,8($16)
	.set	noreorder
	.set	nomacro
	b	.L38
	sh	$9,0($2)
	.set	macro
	.set	reorder

.L116:
	lw	$2,8($16)
	.set	noreorder
	.set	nomacro
	b	.L38
	swc1	$f0,0($2)
	.set	macro
	.set	reorder

.L117:
	lw	$2,8($16)
	.set	noreorder
	.set	nomacro
	b	.L38
	sdc1	$f0,0($2)
	.set	macro
	.set	reorder

.L72:
	addiu	$2,$8,-1
	sltu	$2,$2,16
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L38
	sltu	$5,$8,9
	.set	macro
	.set	reorder

	lw	$2,8($16)
	li	$4,-8			
	andi	$7,$2,0x7
	and	$10,$2,$4
	.set	noreorder
	.set	nomacro
	beq	$5,$0,.L82
	addu	$11,$8,$7
	.set	macro
	.set	reorder

	sltu	$2,$11,9
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L84
	sll	$3,$7,3
	.set	macro
	.set	reorder

	sll	$4,$7,3
	sll	$5,$11,3
	ld	$7,0($10)
	nor	$6,$0,$4
	subu	$5,$0,$5
	li	$2,2			
	li	$3,1			
	dsll	$2,$2,$6
	dsll	$3,$3,$5
	dsra	$4,$9,$4
	xor	$4,$7,$4
	dsubu	$2,$2,$3
	and	$2,$2,$4
	xor	$7,$7,$2
	.set	noreorder
	.set	nomacro
	b	.L38
	sd	$7,0($10)
	.set	macro
	.set	reorder

.L82:
	ld	$6,0($10)
	sll	$8,$7,3
	nor	$5,$0,$8
	li	$2,2			
	dsll	$2,$2,$5
	dsra	$4,$9,$8
	xor	$4,$6,$4
	daddiu	$2,$2,-1
	and	$2,$2,$4
	xor	$6,$6,$2
	sltu	$4,$11,17
	.set	noreorder
	.set	nomacro
	beq	$4,$0,.L86
	sd	$6,0($10)
	.set	macro
	.set	reorder

	sll	$5,$7,2
	li	$2,32			
	subu	$2,$2,$5
	ld	$6,8($10)
	dsll	$4,$9,$2
	dsll	$4,$4,$2
	dsra	$3,$3,$8
	sll	$5,$11,3
	or	$4,$4,$3
	subu	$5,$0,$5
	li	$2,-1			
	xor	$4,$6,$4
	dsll	$2,$2,$5
	and	$2,$2,$4
	xor	$6,$6,$2
	.set	noreorder
	.set	nomacro
	b	.L38
	sd	$6,8($10)
	.set	macro
	.set	reorder

.L84:
	ld	$8,8($10)
	ld	$7,0($10)
	nor	$4,$0,$3
	subu	$6,$0,$3
	sll	$5,$11,3
	li	$2,2			
	dsll	$2,$2,$4
	dsll	$6,$9,$6
	subu	$5,$0,$5
	dsra	$3,$9,$3
	li	$4,-1			
	xor	$3,$7,$3
	xor	$6,$8,$6
	dsll	$4,$4,$5
	daddiu	$2,$2,-1
	and	$2,$2,$3
	and	$4,$4,$6
	xor	$7,$7,$2
	xor	$8,$8,$4
	sd	$8,8($10)
	.set	noreorder
	.set	nomacro
	b	.L38
	sd	$7,0($10)
	.set	macro
	.set	reorder

.L86:
	ld	$7,16($10)
	li	$4,64			
	subu	$4,$4,$8
	sll	$2,$11,3
	dsll	$5,$3,$4
	subu	$2,$0,$2
	li	$6,-1			
	xor	$5,$7,$5
	dsll	$6,$6,$2
	and	$6,$6,$5
	dsll	$4,$9,$4
	dsra	$3,$3,$8
	or	$4,$4,$3
	xor	$7,$7,$6
	sd	$7,16($10)
	.set	noreorder
	.set	nomacro
	b	.L38
	sd	$4,8($10)
	.set	macro
	.set	reorder

	.end	avcall_call
