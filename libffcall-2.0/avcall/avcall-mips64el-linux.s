	.file	1 "avcall-mips64.c"
	.section .mdebug.abi64
	.previous
	.abicalls
	.text
	.align	2
	.align	3
	.globl	avcall_call
	.ent	avcall_call
	.type	avcall_call, @function
avcall_call:
	.frame	$fp,64,$31		# vars= 0, regs= 3/0, args= 32, gp= 0
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
	li	$5,8			# 0x8
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
#APP
	ld $4,0($12)
	ld $5,8($12)
	ld $6,16($12)
	ld $7,24($12)
	ld $8,32($12)
	ld $9,40($12)
	ld $10,48($12)
	ld $11,56($12)
#NO_APP
	ld	$25,8($16)
	jal	$25
	lw	$4,24($16)
	move	$9,$2
	li	$2,1			# 0x1
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

	li	$2,2			# 0x2
	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L94
	li	$2,3			# 0x3
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L94
	li	$2,4			# 0x4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L94
	li	$2,5			# 0x5
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L96
	li	$2,6			# 0x6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L96
	li	$2,7			# 0x7
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L97
	li	$2,8			# 0x8
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L97
	li	$2,9			# 0x9
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L98
	li	$2,10			# 0xa
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L98
	li	$2,11			# 0xb
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L98
	li	$2,12			# 0xc
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L98
	li	$2,13			# 0xd
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L116
	li	$2,14			# 0xe
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L117
	li	$2,15			# 0xf
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,.L98
	li	$2,16			# 0x10
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
	ld	$6,32($16)
	.set	macro
	.set	reorder

	ld	$3,32($16)
	li	$2,1			# 0x1
	.set	noreorder
	.set	nomacro
	beq	$3,$2,.L94
	li	$2,2			# 0x2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$3,$2,.L96
	li	$2,4			# 0x4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$3,$2,.L97
	li	$2,8			# 0x8
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
#APP
	ldc1 $f19,56($12)
#NO_APP
	.set	noreorder
	.set	nomacro
	b	.L118
	slt	$2,$6,9
	.set	macro
	.set	reorder

.L107:
#APP
	lwc1 $f19,104($16)
#NO_APP
	.set	noreorder
	.set	nomacro
	b	.L119
	lw	$3,72($16)
	.set	macro
	.set	reorder

.L106:
#APP
	lwc1 $f18,100($16)
#NO_APP
	andi	$2,$3,0x80
	.set	noreorder
	.set	nomacro
	beql	$2,$0,.L119
	lw	$3,72($16)
	.set	macro
	.set	reorder

	b	.L107
.L105:
#APP
	lwc1 $f17,96($16)
#NO_APP
	andi	$2,$3,0x40
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L122
	andi	$2,$3,0x80
	.set	macro
	.set	reorder

	b	.L106
.L104:
#APP
	lwc1 $f16,92($16)
#NO_APP
	andi	$2,$3,0x20
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L123
	andi	$2,$3,0x40
	.set	macro
	.set	reorder

	b	.L105
.L103:
#APP
	lwc1 $f15,88($16)
#NO_APP
	andi	$2,$3,0x10
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L124
	andi	$2,$3,0x20
	.set	macro
	.set	reorder

	b	.L104
.L102:
#APP
	lwc1 $f14,84($16)
#NO_APP
	andi	$2,$3,0x8
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L125
	andi	$2,$3,0x10
	.set	macro
	.set	reorder

	b	.L103
.L101:
#APP
	lwc1 $f13,80($16)
#NO_APP
	andi	$2,$3,0x4
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L126
	andi	$2,$3,0x8
	.set	macro
	.set	reorder

	b	.L102
.L100:
#APP
	lwc1 $f12,76($4)
#NO_APP
	andi	$2,$3,0x2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L127
	andi	$2,$3,0x4
	.set	macro
	.set	reorder

	b	.L101
.L111:
#APP
	ldc1 $f15,24($12)
#NO_APP
	andi	$2,$3,0x10
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L128
	andi	$2,$3,0x20
	.set	macro
	.set	reorder

	b	.L112
.L110:
#APP
	ldc1 $f14,16($12)
#NO_APP
	andi	$2,$3,0x8
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L129
	andi	$2,$3,0x10
	.set	macro
	.set	reorder

	b	.L111
.L109:
#APP
	ldc1 $f13,8($12)
#NO_APP
	andi	$2,$3,0x4
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L130
	andi	$2,$3,0x8
	.set	macro
	.set	reorder

	b	.L110
.L108:
#APP
	ldc1 $f12,0($12)
#NO_APP
	andi	$2,$3,0x2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L131
	andi	$2,$3,0x4
	.set	macro
	.set	reorder

	b	.L109
.L113:
#APP
	ldc1 $f17,40($12)
#NO_APP
	andi	$2,$3,0x40
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L132
	andi	$2,$3,0x80
	.set	macro
	.set	reorder

	b	.L114
.L112:
#APP
	ldc1 $f16,32($12)
#NO_APP
	andi	$2,$3,0x20
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L133
	andi	$2,$3,0x40
	.set	macro
	.set	reorder

	b	.L113
.L114:
#APP
	ldc1 $f18,48($12)
#NO_APP
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
	daddiu	$2,$6,-1
	sltu	$2,$2,16
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L39
	sltu	$5,$6,9
	.set	macro
	.set	reorder

	ld	$2,16($16)
	li	$4,-8			# 0xfffffffffffffff8
	andi	$8,$2,0x7
	and	$10,$2,$4
	.set	noreorder
	.set	nomacro
	beq	$5,$0,.L83
	daddu	$7,$6,$8
	.set	macro
	.set	reorder

	sltu	$2,$7,9
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L85
	dsll	$6,$8,3
	.set	macro
	.set	reorder

	dsll	$2,$7,3
	daddiu	$2,$2,-1
	ld	$6,0($10)
	sll	$2,$2,0
	dsll	$5,$8,3
	li	$3,2			# 0x2
	sll	$5,$5,0
	dsll	$3,$3,$2
	li	$2,1			# 0x1
	dsll	$4,$9,$5
	dsll	$2,$2,$5
	xor	$4,$6,$4
	dsubu	$3,$3,$2
	and	$3,$3,$4
	xor	$6,$6,$3
	.set	noreorder
	.set	nomacro
	b	.L39
	sd	$6,0($10)
	.set	macro
	.set	reorder

.L83:
	ld	$5,0($10)
	dsll	$11,$8,3
	sll	$12,$11,0
	dsll	$4,$9,$12
	li	$2,-1			# 0xffffffffffffffff
	xor	$4,$5,$4
	dsll	$2,$2,$12
	and	$2,$2,$4
	xor	$5,$5,$2
	sltu	$4,$7,17
	.set	noreorder
	.set	nomacro
	beq	$4,$0,.L87
	sd	$5,0($10)
	.set	macro
	.set	reorder

	dsll	$4,$8,2
	li	$2,32			# 0x20
	dsubu	$2,$2,$4
	sll	$2,$2,0
	dsll	$5,$7,3
	ld	$6,8($10)
	dsra	$4,$9,$2
	daddiu	$5,$5,-65
	dsra	$4,$4,$2
	dsll	$3,$3,$12
	sll	$5,$5,0
	li	$2,2			# 0x2
	dsll	$2,$2,$5
	or	$4,$4,$3
	xor	$4,$6,$4
	daddiu	$2,$2,-1
	and	$2,$2,$4
	xor	$6,$6,$2
	.set	noreorder
	.set	nomacro
	b	.L39
	sd	$6,8($10)
	.set	macro
	.set	reorder

.L85:
	dsll	$4,$7,3
	li	$3,64			# 0x40
	ld	$7,0($10)
	ld	$8,8($10)
	dsubu	$3,$3,$6
	daddiu	$4,$4,-65
	sll	$4,$4,0
	sll	$6,$6,0
	sll	$3,$3,0
	li	$2,2			# 0x2
	dsll	$2,$2,$4
	dsra	$3,$9,$3
	dsll	$5,$9,$6
	li	$4,-1			# 0xffffffffffffffff
	xor	$5,$7,$5
	xor	$3,$8,$3
	dsll	$4,$4,$6
	daddiu	$2,$2,-1
	and	$4,$4,$5
	and	$2,$2,$3
	xor	$7,$7,$4
	xor	$8,$8,$2
	sd	$8,8($10)
	.set	noreorder
	.set	nomacro
	b	.L39
	sd	$7,0($10)
	.set	macro
	.set	reorder

.L87:
	dsll	$6,$7,3
	li	$5,64			# 0x40
	ld	$7,16($10)
	dsubu	$5,$5,$11
	daddiu	$6,$6,-129
	sll	$5,$5,0
	sll	$6,$6,0
	li	$2,2			# 0x2
	dsra	$4,$3,$5
	dsll	$2,$2,$6
	xor	$4,$7,$4
	daddiu	$2,$2,-1
	and	$2,$2,$4
	dsra	$5,$9,$5
	dsll	$3,$3,$12
	or	$5,$5,$3
	xor	$7,$7,$2
	sd	$7,16($10)
	.set	noreorder
	.set	nomacro
	b	.L39
	sd	$5,8($10)
	.set	macro
	.set	reorder

	.end	avcall_call
	.ident	"GCC: (GNU) 4.0.2"
