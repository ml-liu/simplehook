#include "asm-mips.h"
	.file	1 "avcall-mips64.c"
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
	daddiu	$sp,$sp,-64
	sd	$fp,40($sp)
	sd	$16,32($sp)
	sd	$31,48($sp)
	ld	$12,48($4)
	ld	$2,40($4)
	lw	$3,68($4)
	move	$fp,$sp
	dsubu	$2,$2,$12
	dsra	$2,$2,3
	daddiu	$sp,$sp,-2064
	sll	$2,$2,0
	move	$16,$4
	move	$6,$2
	.set	noreorder
	.set	nomacro
	beq	$3,$0,.L2
	move	$7,$sp
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
	lw	$3,72($16)
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
	bne	$2,$0,.L38
	li	$5,8			
	.set	macro
	.set	reorder

	.align	3
.L37:
	dsll	$2,$5,3
	daddu	$3,$12,$2
	ld	$4,0($3)
	daddu	$2,$7,$2
	addiu	$5,$5,1
	.set	noreorder
	.set	nomacro
	bne	$5,$6,.L37
	sd	$4,-64($2)
	.set	macro
	.set	reorder

.L38:

	ld $4,0($12)
	ld $5,8($12)
	ld $6,16($12)
	ld $7,24($12)
	ld $8,32($12)
	ld $9,40($12)
	ld $10,48($12)
	ld $11,56($12)

	ld	$25,8($16)
	jal	$25
	lw	$4,24($16)
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
	ld	$2,16($16)
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
	beq	$4,$2,.L98
	li	$2,10			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L98
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
	beq	$4,$2,.L98
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
	beq	$2,$0,.L39
	andi	$2,$4,0x4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beql	$2,$0,.L73
	ld	$7,32($16)
	.set	macro
	.set	reorder

	ld	$3,32($16)
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
	ld	$2,16($16)
	.set	macro
	.set	reorder

.L39:
	move	$sp,$fp
.L120:
	ld	$31,48($sp)
	ld	$fp,40($sp)
	ld	$16,32($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	daddiu	$sp,$sp,64
	.set	macro
	.set	reorder

.L98:
	ld	$2,16($16)
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
	daddiu	$sp,$sp,64
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

	lwc1 $f19,104($16)

	.set	noreorder
	.set	nomacro
	b	.L119
	lw	$3,72($16)
	.set	macro
	.set	reorder

.L106:

	lwc1 $f18,100($16)

	andi	$2,$3,0x80
	.set	noreorder
	.set	nomacro
	beql	$2,$0,.L119
	lw	$3,72($16)
	.set	macro
	.set	reorder

	b	.L107
.L105:

	lwc1 $f17,96($16)

	andi	$2,$3,0x40
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L122
	andi	$2,$3,0x80
	.set	macro
	.set	reorder

	b	.L106
.L104:

	lwc1 $f16,92($16)

	andi	$2,$3,0x20
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L123
	andi	$2,$3,0x40
	.set	macro
	.set	reorder

	b	.L105
.L103:

	lwc1 $f15,88($16)

	andi	$2,$3,0x10
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L124
	andi	$2,$3,0x20
	.set	macro
	.set	reorder

	b	.L104
.L102:

	lwc1 $f14,84($16)

	andi	$2,$3,0x8
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L125
	andi	$2,$3,0x10
	.set	macro
	.set	reorder

	b	.L103
.L101:

	lwc1 $f13,80($16)

	andi	$2,$3,0x4
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L126
	andi	$2,$3,0x8
	.set	macro
	.set	reorder

	b	.L102
.L100:

	lwc1 $f12,76($4)

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
	ld	$2,16($16)
	move	$sp,$fp
	sb	$9,0($2)
	ld	$31,48($sp)
	ld	$fp,40($sp)
	ld	$16,32($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	daddiu	$sp,$sp,64
	.set	macro
	.set	reorder

.L96:
	ld	$2,16($16)
	.set	noreorder
	.set	nomacro
	b	.L39
	sh	$9,0($2)
	.set	macro
	.set	reorder

.L97:
	ld	$2,16($16)
	.set	noreorder
	.set	nomacro
	b	.L39
	sw	$9,0($2)
	.set	macro
	.set	reorder

.L116:
	ld	$2,16($16)
	.set	noreorder
	.set	nomacro
	b	.L39
	swc1	$f0,0($2)
	.set	macro
	.set	reorder

.L117:
	ld	$2,16($16)
	.set	noreorder
	.set	nomacro
	b	.L39
	sdc1	$f0,0($2)
	.set	macro
	.set	reorder

.L73:
	daddiu	$2,$7,-1
	sltu	$2,$2,16
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L39
	sltu	$5,$7,9
	.set	macro
	.set	reorder

	ld	$2,16($16)
	li	$4,-8			
	andi	$8,$2,0x7
	and	$11,$2,$4
	.set	noreorder
	.set	nomacro
	beq	$5,$0,.L83
	daddu	$7,$7,$8
	.set	macro
	.set	reorder

	sltu	$2,$7,9
	.set	noreorder
	.set	nomacro
	beql	$2,$0,.L85
	dsll	$4,$8,3
	.set	macro
	.set	reorder

	dsll	$2,$7,3
	dsll	$5,$8,3
	li	$6,64			
	li	$4,63			
	ld	$7,0($11)
	dsubu	$6,$6,$2
	dsubu	$4,$4,$5
	sll	$4,$4,0
	sll	$6,$6,0
	sll	$5,$5,0
	li	$2,2			
	li	$3,1			
	dsll	$2,$2,$4
	dsll	$3,$3,$6
	dsra	$5,$9,$5
	xor	$5,$7,$5
	dsubu	$2,$2,$3
	and	$2,$2,$5
	xor	$7,$7,$2
	.set	noreorder
	.set	nomacro
	b	.L39
	sd	$7,0($11)
	.set	macro
	.set	reorder

.L83:
	dsll	$10,$8,3
	li	$5,63			
	ld	$6,0($11)
	dsubu	$5,$5,$10
	sll	$5,$5,0
	sll	$12,$10,0
	li	$2,2			
	dsll	$2,$2,$5
	dsra	$4,$9,$12
	xor	$4,$6,$4
	daddiu	$2,$2,-1
	and	$2,$2,$4
	xor	$6,$6,$2
	sltu	$4,$7,17
	.set	noreorder
	.set	nomacro
	beq	$4,$0,.L87
	sd	$6,0($11)
	.set	macro
	.set	reorder

	dsll	$4,$8,2
	li	$2,32			
	dsubu	$2,$2,$4
	sll	$2,$2,0
	ld	$6,8($11)
	dsll	$4,$9,$2
	dsll	$7,$7,3
	li	$5,128			
	dsll	$4,$4,$2
	dsubu	$5,$5,$7
	dsra	$3,$3,$12
	or	$4,$4,$3
	sll	$5,$5,0
	li	$2,-1			
	xor	$4,$6,$4
	dsll	$2,$2,$5
	and	$2,$2,$4
	xor	$6,$6,$2
	.set	noreorder
	.set	nomacro
	b	.L39
	sd	$6,8($11)
	.set	macro
	.set	reorder

.L85:
	li	$5,64			
	li	$3,63			
	dsll	$2,$7,3
	ld	$8,8($11)
	ld	$7,0($11)
	dsubu	$5,$5,$4
	dsubu	$3,$3,$4
	li	$6,128			
	dsubu	$6,$6,$2
	sll	$3,$3,0
	sll	$5,$5,0
	sll	$4,$4,0
	li	$2,2			
	dsll	$2,$2,$3
	dsll	$5,$9,$5
	dsra	$4,$9,$4
	sll	$6,$6,0
	li	$3,-1			
	xor	$4,$7,$4
	xor	$5,$8,$5
	dsll	$3,$3,$6
	daddiu	$2,$2,-1
	and	$2,$2,$4
	and	$3,$3,$5
	xor	$7,$7,$2
	xor	$8,$8,$3
	sd	$8,8($11)
	.set	noreorder
	.set	nomacro
	b	.L39
	sd	$7,0($11)
	.set	macro
	.set	reorder

.L87:
	li	$2,64			
	dsll	$5,$7,3
	dsubu	$2,$2,$10
	ld	$7,16($11)
	li	$4,192			
	dsubu	$4,$4,$5
	sll	$2,$2,0
	dsll	$5,$3,$2
	sll	$4,$4,0
	li	$6,-1			
	xor	$5,$7,$5
	dsll	$6,$6,$4
	and	$6,$6,$5
	dsll	$2,$9,$2
	dsra	$3,$3,$12
	or	$2,$2,$3
	xor	$7,$7,$6
	sd	$7,16($11)
	.set	noreorder
	.set	nomacro
	b	.L39
	sd	$2,8($11)
	.set	macro
	.set	reorder

	.end	avcall_call
