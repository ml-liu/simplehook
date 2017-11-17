	.file	1 "vacall-mips64.c"
	.section .mdebug.abi64
	.previous
	.abicalls
	.text
	.align	2
	.align	3
	.globl	vacall_receiver
	.ent	vacall_receiver
	.type	vacall_receiver, @function
vacall_receiver:
	.frame	$fp,288,$31		# vars= 160, regs= 8/0, args= 0, gp= 0
	.mask	0xd01f0000,-72
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	daddiu	$sp,$sp,-288
	sd	$28,200($sp)
	lui	$28,%hi(%neg(%gp_rel(vacall_receiver)))
	daddu	$28,$28,$25
	daddiu	$28,$28,%lo(%neg(%gp_rel(vacall_receiver)))
	ld	$12,%got_disp(vacall_function)($28)
	sd	$fp,208($sp)
	sd	$31,216($sp)
	sd	$20,192($sp)
	sd	$19,184($sp)
	sd	$18,176($sp)
	sd	$17,168($sp)
	sd	$16,160($sp)
	move	$fp,$sp
	ld	$25,0($12)
	daddiu	$12,$fp,224
	sd	$4,224($fp)
	sd	$5,232($fp)
	sd	$6,240($fp)
	sd	$7,248($fp)
	sd	$8,256($fp)
	sd	$9,264($fp)
	sd	$10,272($fp)
	sd	$11,280($fp)
	sdc1	$f12,96($fp)
	sdc1	$f13,104($fp)
	sdc1	$f14,112($fp)
	sdc1	$f15,120($fp)
	sdc1	$f16,128($fp)
	sdc1	$f17,136($fp)
	sdc1	$f18,144($fp)
	sdc1	$f19,152($fp)
	swc1	$f12,60($fp)
	swc1	$f13,64($fp)
	swc1	$f14,68($fp)
	swc1	$f15,72($fp)
	swc1	$f16,76($fp)
	swc1	$f17,80($fp)
	swc1	$f18,84($fp)
	swc1	$f19,88($fp)
	move	$4,$fp
	sw	$0,0($fp)
	sd	$12,24($fp)
	sd	$0,32($fp)
	sw	$0,40($fp)
	jal	$25
	sw	$0,56($fp)

	lw	$13,40($fp)
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

	beq	$13,$12,.L70
	li	$12,7			# 0x7

	beq	$13,$12,.L71
	li	$12,8			# 0x8

	beq	$13,$12,.L65
	li	$12,9			# 0x9

	beq	$13,$12,.L65
	li	$12,10			# 0xa

	beq	$13,$12,.L65
	li	$12,11			# 0xb

	beq	$13,$12,.L65
	li	$12,12			# 0xc

	beq	$13,$12,.L72
	li	$12,13			# 0xd

	beq	$13,$12,.L73
	li	$12,14			# 0xe

	beq	$13,$12,.L65
	li	$12,15			# 0xf

	bnel	$13,$12,.L79
	move	$sp,$fp

	lw	$20,0($fp)
	andi	$12,$20,0x400
	beq	$12,$0,.L60
	andi	$12,$20,0x4

	beql	$12,$0,.L34
	ld	$19,48($fp)

	ld	$13,48($fp)
	li	$12,1			# 0x1
	beq	$13,$12,.L74
	li	$12,2			# 0x2

	beq	$13,$12,.L75
	li	$12,4			# 0x4

	beq	$13,$12,.L76
	li	$12,8			# 0x8

	bnel	$13,$12,.L79
	move	$sp,$fp

	ld	$12,32($fp)
	ld	$2,0($12)
	.align	3
.L60:
	move	$sp,$fp
.L79:
	ld	$31,216($sp)
	ld	$fp,208($sp)
	ld	$28,200($sp)
	ld	$20,192($sp)
	ld	$19,184($sp)
	ld	$18,176($sp)
	ld	$17,168($sp)
	ld	$16,160($sp)
	j	$31
	daddiu	$sp,$sp,288

	.align	3
.L61:
	move	$sp,$fp
	lb	$2,8($fp)
	ld	$31,216($sp)
	ld	$fp,208($sp)
	ld	$28,200($sp)
	ld	$20,192($sp)
	ld	$19,184($sp)
	ld	$18,176($sp)
	ld	$17,168($sp)
	ld	$16,160($sp)
	j	$31
	daddiu	$sp,$sp,288

.L68:
	b	.L60
	lh	$2,8($fp)

.L67:
	b	.L60
	lbu	$2,8($fp)

.L65:
	b	.L60
	ld	$2,8($fp)

.L69:
	b	.L60
	lhu	$2,8($fp)

.L70:
	b	.L60
	lw	$2,8($fp)

.L71:
	b	.L60
	lwu	$2,8($fp)

.L72:
	b	.L60
	lwc1	$f0,8($fp)

.L73:
	b	.L60
	ldc1	$f0,8($fp)

.L34:
	daddiu	$12,$19,-1
	sltu	$12,$12,16
	beq	$12,$0,.L80
	andi	$12,$20,0x800

	ld	$12,32($fp)
	li	$13,-8			# 0xfffffffffffffff8
	sltu	$14,$19,9
	andi	$25,$12,0x7
	and	$24,$12,$13
	beq	$14,$0,.L45
	daddu	$13,$19,$25

	sltu	$12,$13,9
	beq	$12,$0,.L47
	dsll	$12,$13,3

	li	$13,64			# 0x40
	dsubu	$13,$13,$12
	ld	$15,0($24)
	sll	$13,$13,0
	li	$14,-1			# 0xffffffffffffffff
	dsll	$14,$14,$13
	dsll	$12,$25,3
	and	$14,$14,$15
	sll	$12,$12,0
	dsll	$2,$14,$12
.L43:
	andi	$12,$20,0x800
.L80:
	beq	$12,$0,.L81
	andi	$12,$20,0x1000

	li	$12,4			# 0x4
	beq	$19,$12,.L77
	li	$12,8			# 0x8

	bne	$19,$12,.L81
	andi	$12,$20,0x1000

	ld	$12,32($fp)
	lwc1	$f2,4($12)
	lwc1	$f0,0($12)
.L51:
	andi	$12,$20,0x1000
.L81:
	beq	$12,$0,.L60
	li	$12,8			# 0x8

	beq	$19,$12,.L78
	li	$12,16			# 0x10

	bnel	$19,$12,.L79
	move	$sp,$fp

	ld	$12,32($fp)
	ldc1	$f2,8($12)
	b	.L60
	ldc1	$f0,0($12)

.L74:
	ld	$12,32($fp)
	b	.L60
	lbu	$2,0($12)

.L78:
	ld	$12,32($fp)
	b	.L60
	ldc1	$f0,0($12)

.L75:
	ld	$12,32($fp)
	b	.L60
	lhu	$2,0($12)

.L45:
	sltu	$12,$13,17
	beq	$12,$0,.L49
	dsll	$12,$13,3

	dsll	$13,$13,3
	li	$12,128			# 0x80
	dsubu	$12,$12,$13
	ld	$17,8($24)
	sll	$12,$12,0
	dsll	$14,$25,2
	li	$15,-1			# 0xffffffffffffffff
	li	$13,32			# 0x20
	dsll	$15,$15,$12
	dsubu	$13,$13,$14
	ld	$16,0($24)
	and	$15,$15,$17
	sll	$13,$13,0
	dsll	$14,$25,3
	sll	$14,$14,0
	dsra	$12,$15,$13
	dsra	$12,$12,$13
	dsll	$16,$16,$14
	or	$2,$16,$12
	b	.L43
	dsll	$3,$15,$14

.L47:
	li	$14,128			# 0x80
	dsubu	$14,$14,$12
	ld	$17,8($24)
	dsll	$15,$25,3
	sll	$14,$14,0
	ld	$16,0($24)
	li	$12,-1			# 0xffffffffffffffff
	li	$13,64			# 0x40
	dsubu	$13,$13,$15
	dsll	$12,$12,$14
	and	$12,$12,$17
	sll	$13,$13,0
	sll	$15,$15,0
	dsll	$16,$16,$15
	dsra	$12,$12,$13
	b	.L43
	or	$2,$16,$12

.L49:
	li	$14,192			# 0xc0
	dsubu	$14,$14,$12
	ld	$18,16($24)
	dsll	$15,$25,3
	sll	$14,$14,0
	ld	$16,8($24)
	ld	$17,0($24)
	li	$12,-1			# 0xffffffffffffffff
	li	$13,64			# 0x40
	dsll	$12,$12,$14
	dsubu	$13,$13,$15
	sll	$13,$13,0
	sll	$15,$15,0
	and	$12,$12,$18
	dsll	$14,$16,$15
	dsra	$12,$12,$13
	dsll	$17,$17,$15
	dsra	$16,$16,$13
	or	$2,$17,$16
	b	.L43
	or	$3,$14,$12

.L77:
	ld	$12,32($fp)
	b	.L51
	lwc1	$f0,0($12)

.L76:
	ld	$12,32($fp)
	b	.L60
	lwu	$2,0($12)

	.set	macro
	.set	reorder
	.end	vacall_receiver
	.ident	"GCC: (GNU) 4.0.2"
