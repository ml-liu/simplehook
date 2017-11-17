#include "asm-mips.h"
	.file	1 "vacall-mips.c"
	.text
	.align	2
	.ent	callback_receiver
	DECLARE_FUNCTION(callback_receiver)
callback_receiver:
	.frame	$fp,104,$31		
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
	sw	$0,44($fp)
	sw	$5,108($fp)
	addiu	$5,$fp,120
	sw	$4,104($fp)
	sw	$5,56($fp)
	lw	$4,4($2)
	addiu	$5,$fp,104
	lw	$25,0($2)
	sw	$5,40($fp)
	sw	$6,112($fp)
	addiu	$5,$fp,24
	sw	$7,116($fp)
	swc1	$f12,80($fp)
	swc1	$f13,84($fp)
	swc1	$f14,88($fp)
	swc1	$f15,92($fp)
	swc1	$f12,68($fp)
	swc1	$f14,72($fp)
	sw	$0,24($fp)
	sw	$0,48($fp)
	sw	$0,60($fp)
	sw	$0,64($fp)
	jal	$25
	lw	$5,48($fp)
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L38
	li	$4,1			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L39
	li	$4,2			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L39
	li	$4,3			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L45
	li	$4,4			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L46
	li	$4,5			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L47
	li	$4,6			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L43
	li	$4,7			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L43
	li	$4,8			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L43
	li	$4,9			
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
	li	$4,12			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L49
	li	$4,13			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L50
	li	$4,14			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L43
	li	$4,15			
	.set	macro
	.set	reorder

	bne	$5,$4,$L38
	lw	$4,24($fp)
	andi	$4,$4,0x2
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L31
	li	$4,1			
	.set	macro
	.set	reorder

	lw	$5,52($fp)
	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L51
	li	$4,2			
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L52
	li	$4,4			
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

	.end	callback_receiver
	.align	2
	.globl	callback_get_receiver
	.ent	callback_get_receiver
	DECLARE_FUNCTION(callback_get_receiver)
callback_get_receiver:
	.frame	$fp,8,$31		
	.mask	0x40000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	addiu	$sp,$sp,-8
	sw	$fp,0($sp)
	move	$fp,$sp
	move	$sp,$fp
	lw	$fp,0($sp)
	la	$2,callback_receiver
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,8
	.set	macro
	.set	reorder

	.end	callback_get_receiver
