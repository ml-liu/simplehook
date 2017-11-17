#include "asm-mips.h"
	.file	1 "vacall-mips64.c"
	.text
	.align	2
	.align	3
	.ent	callback_receiver
	DECLARE_FUNCTION(callback_receiver)
callback_receiver:
	.frame	$fp,272,$31		
	.mask	0xc00f0000,-72
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	daddiu	$sp,$sp,-272
	sd	$fp,192($sp)
	move	$fp,$sp
	sd	$31,200($sp)
	sd	$19,184($sp)
	sd	$18,176($sp)
	sd	$17,168($sp)
	sd	$16,160($sp)
	sd	$0,32($fp)
	sd	$4,208($fp)
	ld	$25,0($2)
	ld	$4,8($2)
	daddiu	$12,$fp,208
	sd	$5,216($fp)
	sd	$6,224($fp)
	sd	$7,232($fp)
	sd	$8,240($fp)
	sd	$9,248($fp)
	sd	$10,256($fp)
	sd	$11,264($fp)
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
	move	$5,$fp
	sw	$0,0($fp)
	sd	$12,24($fp)
	sw	$0,40($fp)
	jal	$25
	sw	$0,56($fp)

	lw	$13,40($fp)
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

	beq	$13,$12,.L70
	li	$12,7			

	beq	$13,$12,.L71
	li	$12,8			

	beq	$13,$12,.L65
	li	$12,9			

	beq	$13,$12,.L65
	li	$12,10			

	beq	$13,$12,.L65
	li	$12,11			

	beq	$13,$12,.L65
	li	$12,12			

	beq	$13,$12,.L72
	li	$12,13			

	beq	$13,$12,.L73
	li	$12,14			

	beq	$13,$12,.L65
	li	$12,15			

	bnel	$13,$12,.L79
	move	$sp,$fp

	lw	$19,0($fp)
	andi	$12,$19,0x400
	beq	$12,$0,.L60
	andi	$12,$19,0x4

	beql	$12,$0,.L34
	ld	$18,48($fp)

	ld	$13,48($fp)
	li	$12,1			
	beq	$13,$12,.L74
	li	$12,2			

	beq	$13,$12,.L75
	li	$12,4			

	beq	$13,$12,.L76
	li	$12,8			

	bnel	$13,$12,.L79
	move	$sp,$fp

	ld	$12,32($fp)
	ld	$2,0($12)
	.align	3
.L60:
	move	$sp,$fp
.L79:
	ld	$31,200($sp)
	ld	$fp,192($sp)
	ld	$19,184($sp)
	ld	$18,176($sp)
	ld	$17,168($sp)
	ld	$16,160($sp)
	j	$31
	daddiu	$sp,$sp,272

	.align	3
.L61:
	move	$sp,$fp
	lb	$2,8($fp)
	ld	$31,200($sp)
	ld	$fp,192($sp)
	ld	$19,184($sp)
	ld	$18,176($sp)
	ld	$17,168($sp)
	ld	$16,160($sp)
	j	$31
	daddiu	$sp,$sp,272

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
	daddiu	$12,$18,-1
	sltu	$12,$12,16
	beq	$12,$0,.L80
	andi	$12,$19,0x800

	ld	$12,32($fp)
	li	$13,-8			
	sltu	$14,$18,9
	andi	$25,$12,0x7
	and	$24,$12,$13
	beq	$14,$0,.L45
	daddu	$13,$18,$25

	sltu	$12,$13,9
	beq	$12,$0,.L47
	dsll	$12,$13,3

	dsll	$13,$13,3
	daddiu	$13,$13,-1
	sll	$13,$13,0
	ld	$14,0($24)
	li	$12,2			
	dsll	$12,$12,$13
	daddiu	$12,$12,-1
	dsll	$13,$25,3
	and	$12,$12,$14
	sll	$13,$13,0
	dsra	$2,$12,$13
.L43:
	andi	$12,$19,0x800
.L80:
	beq	$12,$0,.L81
	andi	$12,$19,0x1000

	li	$12,4			
	beq	$18,$12,.L77
	li	$12,8			

	bne	$18,$12,.L81
	andi	$12,$19,0x1000

	ld	$12,32($fp)
	lwc1	$f2,4($12)
	lwc1	$f0,0($12)
.L51:
	andi	$12,$19,0x1000
.L81:
	beq	$12,$0,.L60
	li	$12,8			

	beq	$18,$12,.L78
	li	$12,16			

	bnel	$18,$12,.L79
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

	daddiu	$12,$12,-65
	sll	$12,$12,0
	ld	$17,8($24)
	li	$13,2			
	dsll	$13,$13,$12
	dsll	$14,$25,2
	li	$15,32			
	dsubu	$15,$15,$14
	daddiu	$13,$13,-1
	ld	$16,0($24)
	and	$13,$13,$17
	sll	$15,$15,0
	dsll	$14,$25,3
	sll	$14,$14,0
	dsll	$12,$13,$15
	dsll	$12,$12,$15
	dsra	$16,$16,$14
	or	$2,$16,$12
	b	.L43
	dsra	$3,$13,$14

.L47:
	daddiu	$12,$12,-65
	sll	$12,$12,0
	ld	$16,8($24)
	li	$13,2			
	dsll	$13,$13,$12
	dsll	$14,$25,3
	ld	$15,0($24)
	li	$12,64			
	dsubu	$12,$12,$14
	daddiu	$13,$13,-1
	and	$13,$13,$16
	sll	$12,$12,0
	sll	$14,$14,0
	dsra	$15,$15,$14
	dsll	$13,$13,$12
	b	.L43
	or	$2,$15,$13

.L49:
	daddiu	$12,$12,-129
	sll	$12,$12,0
	ld	$17,16($24)
	li	$13,2			
	dsll	$13,$13,$12
	dsll	$14,$25,3
	ld	$15,8($24)
	ld	$16,0($24)
	li	$12,64			
	dsubu	$12,$12,$14
	daddiu	$13,$13,-1
	and	$13,$13,$17
	sll	$14,$14,0
	sll	$12,$12,0
	dsra	$17,$15,$14
	dsll	$13,$13,$12
	dsra	$16,$16,$14
	dsll	$15,$15,$12
	or	$2,$16,$15
	b	.L43
	or	$3,$17,$13

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
	.end	callback_receiver
	.align	2
	.align	3
	.globl	callback_get_receiver
	.ent	callback_get_receiver
	DECLARE_FUNCTION(callback_get_receiver)
callback_get_receiver:
	.frame	$fp,16,$31		
	.mask	0x40000000,-16
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	lui	$13,%hi(%neg(%gp_rel(callback_get_receiver)))
	daddiu	$sp,$sp,-16
	daddu	$13,$13,$25
	sd	$fp,0($sp)
	daddiu	$13,$13,%lo(%neg(%gp_rel(callback_get_receiver)))
	move	$fp,$sp
	move	$sp,$fp
	ld	$12,%got_page(callback_receiver)($13)
	ld	$fp,0($sp)
	daddiu	$sp,$sp,16
	j	$31
	daddiu	$2,$12,%got_ofst(callback_receiver)

	.set	macro
	.set	reorder
	.end	callback_get_receiver
