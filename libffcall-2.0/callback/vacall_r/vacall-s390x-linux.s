	.file	"vacall-s390x.c"
.text
	.align	8
	.type	callback_receiver, @function
callback_receiver:
.LFB0:
	.cfi_startproc
	stmg	%r10,%r15,80(%r15)
	.cfi_offset 10, -80
	.cfi_offset 11, -72
	.cfi_offset 12, -64
	.cfi_offset 13, -56
	.cfi_offset 14, -48
	.cfi_offset 15, -40
	aghi	%r15,-320
	.cfi_def_cfa_offset 480
	lgr	%r11,%r15
	.cfi_def_cfa_register 11
	lgr	%r1,%r0
	lhi	%r14,0
	stg	%r2,224(%r11)
	lg	%r10,0(%r1)
	st	%r14,160(%r11)
	la	%r14,480(%r11)
	stg	%r14,184(%r11)
	lghi	%r14,0
	stg	%r3,232(%r11)
	lg	%r2,8(%r1)
	stg	%r4,240(%r11)
	stg	%r5,248(%r11)
	stg	%r6,256(%r11)
	ste	%f0,268(%r11)
	ste	%f2,272(%r11)
	ste	%f4,276(%r11)
	ste	%f6,280(%r11)
	std	%f0,288(%r11)
	std	%f2,296(%r11)
	std	%f4,304(%r11)
	std	%f6,312(%r11)
	stg	%r14,192(%r11)
	st	%r14,200(%r11)
	st	%r14,216(%r11)
	st	%r14,264(%r11)
	la	%r3,160(%r11)
	basr	%r14,%r10
	icm	%r1,15,200(%r11)
	je	.L1
	chi	%r1,1
	je	.L18
	chi	%r1,2
	je	.L21
	chi	%r1,3
	je	.L18
	chi	%r1,4
	je	.L22
	chi	%r1,5
	je	.L23
	chi	%r1,6
	je	.L24
	chi	%r1,7
	je	.L25
	lr	%r10,%r1
	nill	%r10,65533
	chi	%r10,8
	je	.L19
	chi	%r10,9
	je	.L19
	chi	%r1,12
	je	.L26
	chi	%r1,13
	je	.L27
	chi	%r1,14
	je	.L19
.L1:
	lg	%r4,432(%r11)
	lmg	%r10,%r15,400(%r11)
	.cfi_remember_state
	.cfi_restore 15
	.cfi_restore 14
	.cfi_restore 13
	.cfi_restore 12
	.cfi_restore 11
	.cfi_restore 10
	.cfi_def_cfa 15, 160
	br	%r4
.L18:
	.cfi_restore_state
	lg	%r4,432(%r11)
	llgc	%r2,168(%r11)
	lmg	%r10,%r15,400(%r11)
	.cfi_remember_state
	.cfi_restore 10
	.cfi_restore 11
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	.cfi_def_cfa 15, 160
	br	%r4
.L21:
	.cfi_restore_state
	icmh	%r2,8,168(%r11)
	srag	%r2,%r2,56
	j	.L1
.L19:
	lg	%r2,168(%r11)
	j	.L1
.L22:
	lgh	%r2,168(%r11)
	j	.L1
.L23:
	llgh	%r2,168(%r11)
	j	.L1
.L24:
	lgf	%r2,168(%r11)
	j	.L1
.L26:
	le	%f0,168(%r11)
	j	.L1
.L25:
	llgf	%r2,168(%r11)
	j	.L1
.L27:
	ld	%f0,168(%r11)
	j	.L1
	.cfi_endproc
.LFE0:
	.size	callback_receiver, .-callback_receiver
	.align	8
.globl callback_get_receiver
	.type	callback_get_receiver, @function
callback_get_receiver:
.LFB1:
	.cfi_startproc
	stg	%r11,88(%r15)
	.cfi_offset 11, -72
	lgr	%r11,%r15
	.cfi_def_cfa_register 11
	larl	%r2,callback_receiver
	lg	%r11,88(%r11)
	.cfi_restore 11
	.cfi_def_cfa_register 15
	br	%r14
	.cfi_endproc
.LFE1:
	.size	callback_get_receiver, .-callback_get_receiver
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
