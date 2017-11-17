	.file	"vacall-s390.c"
.text
	.align	4
.globl vacall_receiver
	.type	vacall_receiver,@function
vacall_receiver:
	stm	%r6,%r15,24(%r15)
	bras	%r13,.LTN0_0
.LT0_0:
.LC0:
	.long	vacall_function
.LC1:
	.long	0
.LC2:
	.long	255
.LC3:
	.long	65535
.LC4:
	.long	1
.LTN0_0:
	l	%r1,.LC0-.LT0_0(%r13)
	lr	%r14,%r15
	ahi	%r15,-184
	lr	%r11,%r15
	l	%r12,0(%r1)
	st	%r14,0(%r15)
	la	%r1,280(%r11)
	st	%r2,132(%r11)
	la	%r2,96(%r11)
	st	%r4,140(%r11)
	st	%r5,144(%r11)
	st	%r6,148(%r11)
	st	%r3,136(%r11)
	std	%f2,176(%r11)
	std	%f0,168(%r11)
	ste	%f2,160(%r11)
	ste	%f0,156(%r11)
	mvc	96(4,%r11),.LC1-.LT0_0(%r13)
	st	%r1,112(%r11)
	mvc	116(4,%r11),.LC1-.LT0_0(%r13)
	mvc	120(4,%r11),.LC1-.LT0_0(%r13)
	mvc	128(4,%r11),.LC1-.LT0_0(%r13)
	mvc	152(4,%r11),.LC1-.LT0_0(%r13)
	basr	%r14,%r12
	icm	%r4,15,120(%r11)
	je	.L1
	chi	%r4,1
	je	.L43
	chi	%r4,2
	je	.L44
	chi	%r4,3
	je	.L43
	chi	%r4,4
	je	.L45
	chi	%r4,5
	je	.L46
	chi	%r4,6
	je	.L40
	chi	%r4,7
	je	.L40
	chi	%r4,8
	je	.L40
	chi	%r4,9
	je	.L40
	lr	%r1,%r4
	ahi	%r1,-10
	cl	%r1,.LC4-.LT0_0(%r13)
	jh	.L22
	l	%r2,104(%r11)
	l	%r3,108(%r11)
.L1:
	l	%r4,240(%r11)
	lm	%r6,%r15,208(%r11)
	br	%r4
.L22:
	chi	%r4,12
	je	.L47
	chi	%r4,13
	je	.L48
	chi	%r4,14
	je	.L40
	chi	%r4,15
	jne	.L1
	tm	98(%r11),4
	je	.L1
	l	%r1,124(%r11)
	chi	%r1,1
	je	.L49
	chi	%r1,2
	je	.L50
	chi	%r1,4
	je	.L51
	chi	%r1,8
	jne	.L1
	l	%r1,116(%r11)
	l	%r3,4(%r1)
.L39:
	l	%r2,0(%r1)
	j	.L1
.L51:
	l	%r1,116(%r11)
	j	.L39
.L50:
	l	%r1,116(%r11)
	lh	%r4,0(%r1)
	lr	%r2,%r4
.L41:
	n	%r2,.LC3-.LT0_0(%r13)
	j	.L1
.L49:
	l	%r1,116(%r11)
	ic	%r4,0(%r1)
	lr	%r2,%r4
.L42:
	n	%r2,.LC2-.LT0_0(%r13)
	j	.L1
.L40:
	l	%r2,104(%r11)
	j	.L1
.L48:
	ld	%f0,104(%r11)
	j	.L1
.L47:
	le	%f0,104(%r11)
	j	.L1
.L46:
	lh	%r1,104(%r11)
	lr	%r2,%r1
	j	.L41
.L45:
	lh	%r2,104(%r11)
	j	.L1
.L43:
	ic	%r1,104(%r11)
	lr	%r2,%r1
	j	.L42
.L44:
	icm	%r1,8,104(%r11)
	lr	%r2,%r1
	sra	%r2,24
	j	.L1
.Lfe1:
	.size	vacall_receiver,.Lfe1-vacall_receiver
	.ident	"GCC: (GNU) 3.1"
