	.file	1 "vacall-mipsn32.c"
	.section .mdebug.abiN32
	.previous
	.abicalls
	.text
	.align	2
	.align	3
	.ent	callback_receiver
	.type	callback_receiver, @function
callback_receiver:
	.frame	$fp,256,$31		# vars= 144, regs= 6/0, args= 0, gp= 0
	.mask	0xc00f0000,-72
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-256
	sd	$fp,176($sp)
	move	$fp,$sp
	sd	$31,184($sp)
	sd	$19,168($sp)
	sd	$18,160($sp)
	sd	$17,152($sp)
	sd	$16,144($sp)
	sw	$0,28($fp)
	sd	$4,192($fp)
	lw	$25,0($2)
	lw	$4,4($2)
	addiu	$12,$fp,192
	sd	$5,200($fp)
	sd	$6,208($fp)
	sd	$7,216($fp)
	sd	$8,224($fp)
	sd	$9,232($fp)
	sd	$10,240($fp)
	sd	$11,248($fp)
	sdc1	$f12,80($fp)
	sdc1	$f13,88($fp)
	sdc1	$f14,96($fp)
	sdc1	$f15,104($fp)
	sdc1	$f16,112($fp)
	sdc1	$f17,120($fp)
	sdc1	$f18,128($fp)
	sdc1	$f19,136($fp)
	swc1	$f12,44($fp)
	swc1	$f13,48($fp)
	swc1	$f14,52($fp)
	swc1	$f15,56($fp)
	swc1	$f16,60($fp)
	swc1	$f17,64($fp)
	swc1	$f18,68($fp)
	swc1	$f19,72($fp)
	move	$5,$fp
	sw	$0,0($fp)
	sw	$12,24($fp)
	sw	$0,32($fp)
	jal	$25
	sw	$0,40($fp)

	lw	$13,32($fp)
	beq	$13,$0,.L60
	li	$12,1			# 0x1

	beq	$13,$12,.L61
	li	$12,2			# 0x2

	beq	$13,$12,.L61
	li	$12,3			# 0x3

	beq	$13,$12,.L67
	li	$12,4			# 0x4

	beq	$13,$12,.L68
	li	$12,5			# 0x5

	beq	$13,$12,.L69
	li	$12,6			# 0x6

	beq	$13,$12,.L64
	li	$12,7			# 0x7

	beq	$13,$12,.L63
	li	$12,8			# 0x8

	beq	$13,$12,.L64
	li	$12,9			# 0x9

	beq	$13,$12,.L63
	li	$12,10			# 0xa

	beq	$13,$12,.L65
	li	$12,11			# 0xb

	beq	$13,$12,.L65
	li	$12,12			# 0xc

	beq	$13,$12,.L70
	li	$12,13			# 0xd

	beq	$13,$12,.L71
	li	$12,14			# 0xe

	beq	$13,$12,.L64
	li	$12,15			# 0xf

	bnel	$13,$12,.L77
	move	$sp,$fp

	lw	$19,0($fp)
	andi	$12,$19,0x400
	beq	$12,$0,.L60
	andi	$12,$19,0x4

	beql	$12,$0,.L34
	lw	$18,36($fp)

	lw	$13,36($fp)
	li	$12,1			# 0x1
	beq	$13,$12,.L72
	li	$12,2			# 0x2

	beq	$13,$12,.L73
	li	$12,4			# 0x4

	beq	$13,$12,.L74
	li	$12,8			# 0x8

	bnel	$13,$12,.L77
	move	$sp,$fp

	lw	$12,28($fp)
	ld	$2,0($12)
	.align	3
.L60:
	move	$sp,$fp
.L77:
	ld	$31,184($sp)
	ld	$fp,176($sp)
	ld	$19,168($sp)
	ld	$18,160($sp)
	ld	$17,152($sp)
	ld	$16,144($sp)
	j	$31
	addiu	$sp,$sp,256

	.align	3
.L61:
	move	$sp,$fp
	lb	$2,8($fp)
	ld	$31,184($sp)
	ld	$fp,176($sp)
	ld	$19,168($sp)
	ld	$18,160($sp)
	ld	$17,152($sp)
	ld	$16,144($sp)
	j	$31
	addiu	$sp,$sp,256

.L68:
	b	.L60
	lh	$2,8($fp)

.L64:
	b	.L60
	lw	$2,8($fp)

.L67:
	b	.L60
	lbu	$2,8($fp)

.L69:
	b	.L60
	lhu	$2,8($fp)

.L63:
	b	.L60
	lwu	$2,8($fp)

.L65:
	b	.L60
	ld	$2,8($fp)

.L70:
	b	.L60
	lwc1	$f0,8($fp)

.L71:
	b	.L60
	ldc1	$f0,8($fp)

.L34:
	addiu	$12,$18,-1
	sltu	$12,$12,16
	beq	$12,$0,.L78
	andi	$12,$19,0x800

	lw	$12,28($fp)
	li	$13,-8			# 0xfffffffffffffff8
	sltu	$14,$18,9
	andi	$25,$12,0x7
	and	$24,$12,$13
	beq	$14,$0,.L45
	addu	$13,$18,$25

	sltu	$12,$13,9
	beq	$12,$0,.L47
	sll	$13,$13,3

	ld	$14,0($24)
	subu	$13,$0,$13
	li	$12,-1			# 0xffffffffffffffff
	dsll	$12,$12,$13
	and	$12,$12,$14
	sll	$13,$25,3
	dsll	$2,$12,$13
.L43:
	andi	$12,$19,0x800
.L78:
	beq	$12,$0,.L79
	andi	$12,$19,0x1000

	li	$12,4			# 0x4
	beq	$18,$12,.L75
	li	$12,8			# 0x8

	bne	$18,$12,.L79
	andi	$12,$19,0x1000

	lw	$12,28($fp)
	lwc1	$f2,4($12)
	lwc1	$f0,0($12)
.L51:
	andi	$12,$19,0x1000
.L79:
	beq	$12,$0,.L60
	li	$12,8			# 0x8

	beq	$18,$12,.L76
	li	$12,16			# 0x10

	bnel	$18,$12,.L77
	move	$sp,$fp

	lw	$12,28($fp)
	ldc1	$f2,8($12)
	b	.L60
	ldc1	$f0,0($12)

.L73:
	lw	$12,28($fp)
	b	.L60
	lhu	$2,0($12)

.L45:
	sltu	$12,$13,17
	beql	$12,$0,.L49
	ld	$17,16($24)

	sll	$12,$13,3
	ld	$16,8($24)
	subu	$12,$0,$12
	li	$14,-1			# 0xffffffffffffffff
	dsll	$14,$14,$12
	sll	$17,$25,2
	ld	$15,0($24)
	li	$13,32			# 0x20
	and	$14,$14,$16
	subu	$13,$13,$17
	sll	$16,$25,3
	dsra	$12,$14,$13
	dsra	$12,$12,$13
	dsll	$15,$15,$16
	or	$2,$15,$12
	b	.L43
	dsll	$3,$14,$16

.L72:
	lw	$12,28($fp)
	b	.L60
	lbu	$2,0($12)

.L76:
	lw	$12,28($fp)
	b	.L60
	ldc1	$f0,0($12)

.L47:
	ld	$16,8($24)
	subu	$13,$0,$13
	ld	$14,0($24)
	li	$12,-1			# 0xffffffffffffffff
	dsll	$12,$12,$13
	sll	$15,$25,3
	and	$12,$12,$16
	subu	$13,$0,$15
	dsra	$12,$12,$13
	dsll	$14,$14,$15
	b	.L43
	or	$2,$14,$12

.L49:
	sll	$13,$13,3
	subu	$13,$0,$13
	ld	$15,8($24)
	ld	$16,0($24)
	li	$12,-1			# 0xffffffffffffffff
	sll	$14,$25,3
	dsll	$12,$12,$13
	li	$13,64			# 0x40
	and	$12,$12,$17
	subu	$13,$13,$14
	dsll	$17,$15,$14
	dsra	$12,$12,$13
	dsll	$16,$16,$14
	dsra	$15,$15,$13
	or	$2,$16,$15
	b	.L43
	or	$3,$17,$12

.L75:
	lw	$12,28($fp)
	b	.L51
	lwc1	$f0,0($12)

.L74:
	lw	$12,28($fp)
	b	.L60
	lwu	$2,0($12)

	.set	macro
	.set	reorder
	.end	callback_receiver
	.align	2
	.align	3
	.globl	callback_get_receiver
	.ent	callback_get_receiver
	.type	callback_get_receiver, @function
callback_get_receiver:
	.frame	$fp,16,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-16
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	lui	$13,%hi(%neg(%gp_rel(callback_get_receiver)))
	addiu	$sp,$sp,-16
	addu	$13,$13,$25
	sd	$fp,0($sp)
	addiu	$13,$13,%lo(%neg(%gp_rel(callback_get_receiver)))
	move	$fp,$sp
	move	$sp,$fp
	lw	$12,%got_page(callback_receiver)($13)
	ld	$fp,0($sp)
	addiu	$sp,$sp,16
	j	$31
	addiu	$2,$12,%got_ofst(callback_receiver)

	.set	macro
	.set	reorder
	.end	callback_get_receiver
	.ident	"GCC: (GNU) 4.0.2"
