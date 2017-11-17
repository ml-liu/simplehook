	.file	"avcall-s390x.c"
.text
	.align	8
.globl avcall_call
	.type	avcall_call, @function
avcall_call:
.LFB0:
	.cfi_startproc
	stmg	%r7,%r15,56(%r15)
	.cfi_offset 7, -104
	.cfi_offset 8, -96
	.cfi_offset 9, -88
	.cfi_offset 10, -80
	.cfi_offset 11, -72
	.cfi_offset 12, -64
	.cfi_offset 13, -56
	.cfi_offset 14, -48
	.cfi_offset 15, -40
	larl	%r13,.L78
	aghi	%r15,-176
	.cfi_def_cfa_offset 336
	lgr	%r11,%r15
	.cfi_def_cfa_register 11
	aghi	%r15,-2056
	lg	%r9,48(%r2)
	lg	%r1,40(%r2)
	sgr	%r1,%r9
	srag	%r1,%r1,3
	stg	%r2,168(%r11)
	stg	%r6,160(%r11)
	ltr	%r1,%r1
	la	%r8,160(%r15)
	l	%r0,64(%r2)
	l	%r7,112(%r2)
	jle	.L6
	lgfr	%r1,%r1
	sllg	%r1,%r1,3
	aghi	%r1,-8
	srlg	%r1,%r1,3
	aghi	%r1,1
	lghi	%r14,0
.L5:
	lg	%r10,0(%r14,%r9)
	stg	%r10,0(%r14,%r8)
	aghi	%r14,8
	brctg	%r1,.L5
.L6:
	ltr	%r0,%r0
	je	.L7
	lg	%r1,168(%r11)
	cl	%r0,.L79-.L78(%r13)
	lg	%r2,72(%r1)
	jle	.L7
	chi	%r0,2
	lg	%r3,80(%r1)
	je	.L7
	chi	%r0,3
	lg	%r4,88(%r1)
	je	.L7
	chi	%r0,4
	lg	%r5,96(%r1)
	jne	.L73
.L7:
	ltr	%r7,%r7
	je	.L9
	lg	%r10,168(%r11)
	l	%r1,120(%r10)
	tmll	%r1,1
	je	.L10
	ld	%f0,144(%r10)
.L11:
	cl	%r7,.L79-.L78(%r13)
	jle	.L9
	tmll	%r1,2
	lg	%r10,168(%r11)
	jne	.L74
	tm	119(%r10),2
	je	.L14
	le	%f2,128(%r10)
.L14:
	chi	%r7,2
	je	.L9
	tmll	%r1,4
	lg	%r10,168(%r11)
	je	.L15
	ld	%f4,160(%r10)
.L16:
	chi	%r7,3
	je	.L9
	tmll	%r1,8
	lg	%r1,168(%r11)
	jne	.L75
	tm	119(%r1),8
	je	.L9
	le	%f6,136(%r1)
.L9:
	lg	%r1,168(%r11)
	l	%r1,24(%r1)
	chi	%r1,13
	je	.L76
	chi	%r1,14
	je	.L77
	lg	%r10,168(%r11)
	lg	%r1,8(%r10)
	basr	%r14,%r1
	l	%r1,24(%r10)
	chi	%r1,1
	lgr	%r0,%r2
	je	.L19
	ltr	%r1,%r1
	je	.L67
	chi	%r1,2
	je	.L69
	chi	%r1,3
	je	.L69
	chi	%r1,4
	je	.L69
	chi	%r1,5
	je	.L71
	chi	%r1,6
	je	.L71
	chi	%r1,7
	je	.L70
	chi	%r1,8
	je	.L70
	lr	%r9,%r1
	nill	%r9,65533
	chi	%r9,9
	je	.L67
	chi	%r1,10
	je	.L67
	chi	%r1,12
	je	.L67
	chi	%r1,15
	je	.L67
.L19:
	lg	%r4,288(%r11)
	lg	%r6,160(%r11)
	lghi	%r2,0
	lmg	%r7,%r15,232(%r11)
	.cfi_remember_state
	.cfi_restore 15
	.cfi_restore 14
	.cfi_restore 13
	.cfi_restore 12
	.cfi_restore 11
	.cfi_restore 10
	.cfi_restore 9
	.cfi_restore 8
	.cfi_restore 7
	.cfi_def_cfa 15, 160
	br	%r4
.L10:
	.cfi_restore_state
	lg	%r10,168(%r11)
	tm	119(%r10),1
	je	.L11
	le	%f0,124(%r10)
	j	.L11
.L67:
	lg	%r1,168(%r11)
	lghi	%r2,0
	lg	%r1,16(%r1)
	stg	%r0,0(%r1)
	lg	%r4,288(%r11)
	lg	%r6,160(%r11)
	lmg	%r7,%r15,232(%r11)
	.cfi_remember_state
	.cfi_restore 7
	.cfi_restore 8
	.cfi_restore 9
	.cfi_restore 10
	.cfi_restore 11
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	.cfi_def_cfa 15, 160
	br	%r4
.L74:
	.cfi_restore_state
	ld	%f2,152(%r10)
	j	.L14
.L69:
	lg	%r1,168(%r11)
	lghi	%r2,0
	lg	%r1,16(%r1)
	stc	%r0,0(%r1)
	lg	%r4,288(%r11)
	lg	%r6,160(%r11)
	lmg	%r7,%r15,232(%r11)
	.cfi_remember_state
	.cfi_restore 7
	.cfi_restore 8
	.cfi_restore 9
	.cfi_restore 10
	.cfi_restore 11
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	.cfi_def_cfa 15, 160
	br	%r4
.L77:
	.cfi_restore_state
	lg	%r0,168(%r11)
	lgr	%r1,%r0
	lgr	%r10,%r0
	lg	%r1,8(%r1)
	lg	%r10,16(%r10)
	basr	%r14,%r1
	lg	%r4,288(%r11)
	std	%f0,0(%r10)
	lg	%r6,160(%r11)
	lghi	%r2,0
	lmg	%r7,%r15,232(%r11)
	.cfi_remember_state
	.cfi_restore 7
	.cfi_restore 8
	.cfi_restore 9
	.cfi_restore 10
	.cfi_restore 11
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	.cfi_def_cfa 15, 160
	br	%r4
.L76:
	.cfi_restore_state
	lg	%r0,168(%r11)
	lgr	%r1,%r0
	lgr	%r10,%r0
	lg	%r1,8(%r1)
	lg	%r10,16(%r10)
	basr	%r14,%r1
	ste	%f0,0(%r10)
	j	.L19
.L15:
	tm	119(%r10),4
	je	.L16
	le	%f4,132(%r10)
	j	.L16
.L71:
	lg	%r1,168(%r11)
	lg	%r1,16(%r1)
	sth	%r0,0(%r1)
	j	.L19
.L73:
	lg	%r6,104(%r1)
	j	.L7
.L75:
	ld	%f6,168(%r1)
	j	.L9
.L70:
	lg	%r1,168(%r11)
	lg	%r1,16(%r1)
	st	%r0,0(%r1)
	j	.L19
	.section	.rodata
	.align	8
.L78:
.L79:
	.long	1
	.align	2
	.previous
	.cfi_endproc
.LFE0:
	.size	avcall_call, .-avcall_call
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
