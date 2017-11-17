	.file	1 "avcall-mips.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	avcall_call
	.ent	avcall_call
	.type	avcall_call, @function
avcall_call:
	.frame	$fp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0xc0010000,-8
	.fmask	0x00000000,0
	addiu	$sp,$sp,-40
	sw	$fp,28($sp)
	move	$fp,$sp
	sw	$31,32($sp)
	sw	$16,24($sp)
	.cprestore	16
	lw	$3,24($4)
	lw	$2,20($4)
	move	$16,$4
	lw	$4,40($4)
	subu	$2,$2,$3
	addiu	$sp,$sp,-1032
	andi	$3,$4,0x1
	sra	$7,$2,2
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L2
	move	$5,$sp
	.set	macro
	.set	reorder

#APP
	l.s $f12,48($16)
#NO_APP
$L2:
	lw	$3,44($16)
	#nop
	andi	$2,$3,0x1
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L63
	andi	$2,$4,0x2
	.set	macro
	.set	reorder

#APP
	l.d $f12,56($16)
#NO_APP
	andi	$2,$4,0x2
$L63:
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L64
	andi	$2,$3,0x2
	.set	macro
	.set	reorder

#APP
	l.s $f14,52($16)
#NO_APP
	andi	$2,$3,0x2
$L64:
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L65
	slt	$2,$7,5
	.set	macro
	.set	reorder

#APP
	l.d $f14,64($16)
#NO_APP
	slt	$2,$7,5
$L65:
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L51
	li	$4,4			# 0x4
	.set	macro
	.set	reorder

	lw	$6,24($16)
$L10:
	sll	$2,$4,2
	addu	$2,$2,$6
	lw	$3,0($2)
	addiu	$4,$4,1
	sw	$3,16($5)
	.set	noreorder
	.set	nomacro
	bne	$7,$4,$L10
	addiu	$5,$5,4
	.set	macro
	.set	reorder

$L11:
	lw	$4,0($6)
	lw	$5,4($6)
	lw	$7,12($6)
	lw	$25,4($16)
	lw	$6,8($6)
	jalr	$25
	lw	$4,12($16)
	move	$5,$2
	li	$2,1			# 0x1
	lw	$28,16($fp)
	beq	$4,$2,$L12
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L57
	li	$2,2			# 0x2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L56
	li	$2,3			# 0x3
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L56
	li	$2,4			# 0x4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L56
	li	$2,5			# 0x5
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L58
	li	$2,6			# 0x6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L58
	li	$2,7			# 0x7
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L57
	li	$2,8			# 0x8
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L57
	li	$2,9			# 0x9
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L57
	li	$2,10			# 0xa
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L57
	addiu	$2,$4,-11
	.set	macro
	.set	reorder

	sltu	$2,$2,2
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L60
	li	$2,13			# 0xd
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L61
	li	$2,14			# 0xe
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L62
	li	$2,15			# 0xf
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$4,$2,$L57
	li	$2,16			# 0x10
	.set	macro
	.set	reorder

	bne	$4,$2,$L12
	lw	$2,0($16)
	#nop
	andi	$2,$2,0x2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L12
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

	lw	$3,16($16)
	#nop
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L56
	li	$2,2			# 0x2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L58
	li	$2,4			# 0x4
	.set	macro
	.set	reorder

	beq	$3,$2,$L57
$L12:
	move	$sp,$fp
	lw	$31,32($fp)
	lw	$fp,28($sp)
	lw	$16,24($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,40
	.set	macro
	.set	reorder

$L51:
	lw	$6,24($16)
	b	$L11
$L57:
	lw	$2,8($16)
	move	$sp,$fp
	sw	$5,0($2)
	lw	$31,32($sp)
	lw	$fp,28($sp)
	lw	$16,24($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,40
	.set	macro
	.set	reorder

$L56:
	lw	$2,8($16)
	move	$sp,$fp
	sb	$5,0($2)
	lw	$31,32($sp)
	lw	$fp,28($sp)
	lw	$16,24($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,40
	.set	macro
	.set	reorder

$L58:
	lw	$2,8($16)
	.set	noreorder
	.set	nomacro
	b	$L12
	sh	$5,0($2)
	.set	macro
	.set	reorder

$L61:
	lw	$2,8($16)
	.set	noreorder
	.set	nomacro
	b	$L12
	swc1	$f0,0($2)
	.set	macro
	.set	reorder

$L60:
	lw	$2,8($16)
	#nop
	sw	$3,4($2)
	.set	noreorder
	.set	nomacro
	b	$L12
	sw	$5,0($2)
	.set	macro
	.set	reorder

$L62:
	lw	$2,8($16)
	#nop
	swc1	$f0,4($2)
	.set	noreorder
	.set	nomacro
	b	$L12
	swc1	$f1,0($2)
	.set	macro
	.set	reorder

	.end	avcall_call
	.ident	"GCC: (GNU) 4.0.2"
