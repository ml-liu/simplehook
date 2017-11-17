#include "asm-mips.h"
	.file	1 "vacall-mipsn32.c"
	.text
	.align	2
	.align	3
	.globl	vacall_receiver
	.ent	vacall_receiver
	DECLARE_FUNCTION(vacall_receiver)
vacall_receiver:
	.frame	$fp,272,$31		
	.mask	0xd00f0000,-80
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-272
	sd	$28,176($sp)
	lui	$28,%hi(%neg(%gp_rel(vacall_receiver)))
	addu	$28,$28,$25
	addiu	$28,$28,%lo(%neg(%gp_rel(vacall_receiver)))
	lw	$12,%got_disp(vacall_function)($28)
	sd	$fp,184($sp)
	sd	$31,192($sp)
	sd	$19,168($sp)
	sd	$18,160($sp)
	sd	$17,152($sp)
	sd	$16,144($sp)
	move	$fp,$sp
	lw	$25,0($12)
	addiu	$12,$fp,208
	sd	$4,208($fp)
	sd	$5,216($fp)
	sd	$6,224($fp)
	sd	$7,232($fp)
	sd	$8,240($fp)
	sd	$9,248($fp)
	sd	$10,256($fp)
	sd	$11,264($fp)
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
	sw	$0,0($fp)
	move	$4,$fp
	sw	$12,24($fp)
	sw	$0,28($fp)
	sw	$0,32($fp)
	jal	$25
	sw	$0,40($fp)

	lw	$13,32($fp)
	beq	$13,$0,.L60
	li	$12,1			

	beq	$13,$12,.L61
	li	$12,2			

	beq	$13,$12,.L61
	li	$12,3			

	beq	$13,$12,.L67
	li	$12,4			

	beq	$13,$12,.L68
	li	$12,5			

	beq	$13,$12,.L69
	li	$12,6			

	beq	$13,$12,.L64
	li	$12,7			

	beq	$13,$12,.L63
	li	$12,8			

	beq	$13,$12,.L64
	li	$12,9			

	beq	$13,$12,.L63
	li	$12,10			

	beq	$13,$12,.L65
	li	$12,11			

	beq	$13,$12,.L65
	li	$12,12			

	beq	$13,$12,.L70
	li	$12,13			

	beq	$13,$12,.L71
	li	$12,14			

	beq	$13,$12,.L64
	li	$12,15			

	bnel	$13,$12,.L77
	move	$sp,$fp

	lw	$19,0($fp)
	andi	$12,$19,0x400
	beq	$12,$0,.L60
	andi	$12,$19,0x4

	beql	$12,$0,.L34
	lw	$18,36($fp)

	lw	$13,36($fp)
	li	$12,1			
	beq	$13,$12,.L72
	li	$12,2			

	beq	$13,$12,.L73
	li	$12,4			

	beq	$13,$12,.L74
	li	$12,8			

	bnel	$13,$12,.L77
	move	$sp,$fp

	lw	$12,28($fp)
	ld	$2,0($12)
	.align	3
.L60:
	move	$sp,$fp
.L77:
	ld	$31,192($sp)
	ld	$fp,184($sp)
	ld	$28,176($sp)
	ld	$19,168($sp)
	ld	$18,160($sp)
	ld	$17,152($sp)
	ld	$16,144($sp)
	j	$31
	addiu	$sp,$sp,272

	.align	3
.L61:
	move	$sp,$fp
	lb	$2,8($fp)
	ld	$31,192($sp)
	ld	$fp,184($sp)
	ld	$28,176($sp)
	ld	$19,168($sp)
	ld	$18,160($sp)
	ld	$17,152($sp)
	ld	$16,144($sp)
	j	$31
	addiu	$sp,$sp,272

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
	li	$13,-8			
	sltu	$14,$18,9
	andi	$25,$12,0x7
	and	$24,$12,$13
	beq	$14,$0,.L45
	addu	$13,$18,$25

	sltu	$12,$13,9
	beq	$12,$0,.L47
	sll	$13,$13,3

	addiu	$13,$13,-1
	ld	$14,0($24)
	li	$12,2			
	dsll	$12,$12,$13
	daddiu	$12,$12,-1
	and	$12,$12,$14
	sll	$13,$25,3
	dsra	$2,$12,$13
.L43:
	andi	$12,$19,0x800
.L78:
	beq	$12,$0,.L79
	andi	$12,$19,0x1000

	li	$12,4			
	beq	$18,$12,.L75
	li	$12,8			

	bne	$18,$12,.L79
	andi	$12,$19,0x1000

	lw	$12,28($fp)
	lwc1	$f2,4($12)
	lwc1	$f0,0($12)
.L51:
	andi	$12,$19,0x1000
.L79:
	beq	$12,$0,.L60
	li	$12,8			

	beq	$18,$12,.L76
	li	$12,16			

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
	beq	$12,$0,.L49
	sll	$12,$13,3

	addiu	$12,$12,-65
	ld	$16,8($24)
	li	$14,2			
	dsll	$14,$14,$12
	daddiu	$14,$14,-1
	sll	$12,$25,2
	ld	$15,0($24)
	li	$13,32			
	and	$14,$14,$16
	subu	$13,$13,$12
	sll	$16,$25,3
	dsll	$12,$14,$13
	dsll	$12,$12,$13
	dsra	$15,$15,$16
	or	$2,$15,$12
	b	.L43
	dsra	$3,$14,$16

.L72:
	lw	$12,28($fp)
	b	.L60
	lbu	$2,0($12)

.L76:
	lw	$12,28($fp)
	b	.L60
	ldc1	$f0,0($12)

.L47:
	addiu	$13,$13,-65
	ld	$16,8($24)
	li	$12,2			
	dsll	$12,$12,$13
	ld	$14,0($24)
	sll	$15,$25,3
	daddiu	$12,$12,-1
	and	$12,$12,$16
	subu	$13,$0,$15
	dsll	$12,$12,$13
	dsra	$14,$14,$15
	b	.L43
	or	$2,$14,$12

.L49:
	addiu	$12,$12,-129
	ld	$17,16($24)
	li	$13,2			
	dsll	$13,$13,$12
	ld	$15,8($24)
	ld	$16,0($24)
	sll	$14,$25,3
	daddiu	$13,$13,-1
	li	$12,64			
	and	$13,$13,$17
	subu	$12,$12,$14
	dsra	$17,$15,$14
	dsll	$13,$13,$12
	dsra	$16,$16,$14
	dsll	$15,$15,$12
	or	$2,$16,$15
	b	.L43
	or	$3,$17,$13

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
	.end	vacall_receiver
