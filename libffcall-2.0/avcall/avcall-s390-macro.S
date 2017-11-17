	.file	"avcall-s390.c"
.text
	.align	4
.globl avcall_call
	.type	avcall_call,@function
avcall_call:
	stm	%r6,%r15,24(%r15)
	bras	%r13,.LTN0_0
.LT0_0:
.LC0:
	.long	1
.LTN0_0:
	lr	%r14,%r15
	ahi	%r15,-96
	lr	%r10,%r2
	lr	%r11,%r15
	lhi	%r2,0
	st	%r14,0(%r15)
	l	%r1,0(%r15)
	ahi	%r15,-1032
	l	%r3,20(%r10)
	l	%r4,24(%r10)
	sr	%r3,%r4
	sra	%r3,2
	la	%r5,96(%r15)
	st	%r1,0(%r15)
	cr	%r2,%r3
	l	%r0,64(%r10)
	jhe	.L55
.L6:
	lr	%r1,%r2
	sll	%r1,2
	ahi	%r2,1
	cr	%r2,%r3
	l	%r9,0(%r1,%r4)
	st	%r9,0(%r1,%r5)
	jl	.L6
.L55:
	ltr	%r0,%r0
	je	.L7
	l	%r1,72(%r10)
	tml	%r1,1
	je	.L8
	ld	%f0,88(%r10)
.L9:
	cl	%r0,.LC0-.LT0_0(%r13)
	jle	.L7
	tml	%r1,2
	je	.L12
	ld	%f2,96(%r10)
.L7:
	l	%r1,4(%r10)
	l	%r4,52(%r10)
	l	%r2,44(%r10)
	l	%r3,48(%r10)
	l	%r5,56(%r10)
	l	%r6,60(%r10)
	basr	%r14,%r1
	l	%r4,12(%r10)
	chi	%r4,1
	je	.L16
	ltr	%r4,%r4
	je	.L65
	chi	%r4,2
	je	.L58
	chi	%r4,3
	je	.L58
	chi	%r4,4
	je	.L58
	chi	%r4,5
	je	.L57
	chi	%r4,6
	je	.L57
	chi	%r4,7
	je	.L65
	chi	%r4,8
	je	.L65
	chi	%r4,9
	je	.L65
	chi	%r4,10
	je	.L65
	lr	%r1,%r4
	ahi	%r1,-11
	cl	%r1,.LC0-.LT0_0(%r13)
	jle	.L64
	chi	%r4,13
	je	.L66
	chi	%r4,14
	je	.L67
	chi	%r4,15
	je	.L65
	chi	%r4,16
	je	.L68
.L16:
	lhi	%r2,0
	l	%r4,152(%r11)
	lm	%r6,%r15,120(%r11)
	br	%r4
.L68:
	tm	2(%r10),2
	je	.L16
	l	%r1,16(%r10)
	chi	%r1,1
	je	.L58
	chi	%r1,2
	je	.L57
	chi	%r1,4
	je	.L65
	chi	%r1,8
	jne	.L16
.L64:
	l	%r1,8(%r10)
	st	%r3,4(%r1)
.L56:
	st	%r2,0(%r1)
	j	.L16
.L65:
	l	%r1,8(%r10)
	j	.L56
.L57:
	l	%r1,8(%r10)
	sth	%r2,0(%r1)
	j	.L16
.L58:
	l	%r1,8(%r10)
	stc	%r2,0(%r1)
	j	.L16
.L67:
	l	%r1,8(%r10)
	std	%f0,0(%r1)
	j	.L16
.L66:
	l	%r1,8(%r10)
	ste	%f0,0(%r1)
	j	.L16
.L12:
	tm	71(%r10),2
	je	.L7
	le	%f2,80(%r10)
	j	.L7
.L8:
	tm	71(%r10),1
	je	.L9
	le	%f0,76(%r10)
	j	.L9
.Lfe1:
	.size	avcall_call,.Lfe1-avcall_call
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
