	.file	1 "vacall-mips.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	vacall_receiver
	.ent	vacall_receiver
	.type	vacall_receiver, @function
vacall_receiver:
	.frame	$fp,104,$31		# vars= 72, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	addiu	$sp,$sp,-104
	sw	$fp,96($sp)
	move	$fp,$sp
	sw	$31,100($sp)
	.cprestore	16
	sw	$4,104($fp)
	la	$8,vacall_function
	addiu	$4,$fp,120
	sw	$4,56($fp)
	lw	$25,0($8)
	addiu	$4,$fp,104
	sw	$5,108($fp)
	sw	$4,40($fp)
	sw	$6,112($fp)
	sw	$7,116($fp)
	swc1	$f12,80($fp)
	swc1	$f13,84($fp)
	swc1	$f14,88($fp)
	swc1	$f15,92($fp)
	swc1	$f12,68($fp)
	swc1	$f14,72($fp)
	sw	$0,24($fp)
	sw	$0,44($fp)
	sw	$0,48($fp)
	sw	$0,60($fp)
	sw	$0,64($fp)
	addiu	$4,$fp,24
	jal	$25
	lw	$5,48($fp)
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L38
	li	$4,1			# 0x1
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L39
	li	$4,2			# 0x2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L39
	li	$4,3			# 0x3
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L45
	li	$4,4			# 0x4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L46
	li	$4,5			# 0x5
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L47
	li	$4,6			# 0x6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L43
	li	$4,7			# 0x7
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L43
	li	$4,8			# 0x8
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L43
	li	$4,9			# 0x9
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L43
	addiu	$4,$5,-10
	.set	macro
	.set	reorder

	sltu	$4,$4,2
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L48
	li	$4,12			# 0xc
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L49
	li	$4,13			# 0xd
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L50
	li	$4,14			# 0xe
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L43
	li	$4,15			# 0xf
	.set	macro
	.set	reorder

	bne	$5,$4,$L38
	lw	$4,24($fp)
	andi	$4,$4,0x2
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L31
	li	$4,1			# 0x1
	.set	macro
	.set	reorder

	lw	$5,52($fp)
	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L51
	li	$4,2			# 0x2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L52
	li	$4,4			# 0x4
	.set	macro
	.set	reorder

	bne	$5,$4,$L38
	lw	$4,44($fp)
	lw	$2,0($4)
$L38:
	move	$sp,$fp
$L53:
	lw	$31,100($sp)
	lw	$fp,96($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,104
	.set	macro
	.set	reorder

$L39:
	move	$sp,$fp
	lb	$2,32($fp)
	lw	$31,100($sp)
	lw	$fp,96($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,104
	.set	macro
	.set	reorder

$L46:
	lh	$2,32($fp)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

$L43:
	lw	$2,32($fp)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

$L45:
	lbu	$2,32($fp)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

$L47:
	lhu	$2,32($fp)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

$L49:
	lwc1	$f0,32($fp)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

$L48:
	lw	$2,32($fp)
	lw	$3,36($fp)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

$L50:
	lwc1	$f0,32($fp)
	lwc1	$f1,36($fp)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

$L31:
	lw	$2,44($fp)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

$L51:
	lw	$4,44($fp)
	lbu	$2,0($4)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

$L52:
	lw	$4,44($fp)
	lhu	$2,0($4)
	.set	noreorder
	.set	nomacro
	b	$L53
	move	$sp,$fp
	.set	macro
	.set	reorder

	.end	vacall_receiver
	.ident	"GCC: (GNU) 4.0.2"
