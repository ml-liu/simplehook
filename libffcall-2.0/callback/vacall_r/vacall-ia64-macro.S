	.file	"vacall-ia64.c"
	.pred.safe_across_calls p1-p5,p16-p63
	.text
	.align 16
	.proc callback_receiver#
callback_receiver:
	.prologue 14, 42
	.spill 48
	.mmb
	.save ar.pfs, r43
	alloc r43 = ar.pfs, 8, 6, 2, 0
	.vframe r44
	mov r44 = r12
	nop 0
	.mmi
	adds r12 = -208, r12
	adds r18 = 8, r15
	mov r45 = r1
	;;
	.mmi
	adds r16 = -48, r44
	adds r14 = -136, r44
	adds r17 = -48, r44
	.mmi
	adds r40 = -152, r44
	adds r47 = -192, r44
	adds r41 = -160, r44
	;;
	.mmb
	st8 [r14] = r8
	adds r14 = -32, r44
	nop 0
	.mfi
	st8 [r16] = r32, 8
	nop 0
	.save rp, r42
	mov r42 = b0
	.body
	;;
	.mfi
	st8 [r14] = r34
	nop 0
	adds r14 = -24, r44
	.mmb
	st8 [r16] = r33
	ld8 r16 = [r15]
	nop 0
	;;
	.mmi
	nop 0
	st8 [r14] = r35
	adds r14 = -16, r44
	.mmi
	st8 [r41] = r0
	;;
	st8 [r14] = r36
	adds r14 = -8, r44
	.mmb
	st4 [r40] = r0
	ld8 r46 = [r18]
	nop 0
	;;
	.mmi
	nop 0
	st8 [r14] = r37
	adds r14 = 8, r44
	.mmi
	st8 [r44] = r38
	;;
	st8 [r14] = r39
	adds r14 = -112, r44
	.mmi
	st4 [r47] = r0
	;;
	stfd [r14] = f8
	nop 0
	.mmi
	adds r14 = -104, r44
	;;
	stfd [r14] = f9
	adds r14 = -96, r44
	;;
	.mfi
	stfd [r14] = f10
	nop 0
	adds r14 = -88, r44
	.mmi
	nop 0
	;;
	stfd [r14] = f11
	nop 0
	.mmi
	adds r14 = -80, r44
	;;
	stfd [r14] = f12
	adds r14 = -72, r44
	;;
	.mfi
	stfd [r14] = f13
	nop 0
	adds r14 = -64, r44
	.mmi
	nop 0
	;;
	stfd [r14] = f14
	nop 0
	.mmi
	adds r14 = -56, r44
	;;
	stfd [r14] = f15
	adds r14 = -168, r44
	;;
	.mii
	st8 [r14] = r17
	adds r14 = -128, r44
	;;
	nop 0
	.mii
	st8 [r14] = r17
	adds r14 = -120, r44
	;;
	nop 0
	.mmb
	st4 [r14] = r0
	ld8 r14 = [r16], 8
	nop 0
	;;
	.mib
	nop 0
	mov b6 = r14
	nop 0
	.mbb
	ld8 r1 = [r16]
	nop 0
	br.call.sptk.many b0 = b6
	;;
	.mmb
	mov r1 = r45
	ld4 r40 = [r40]
	nop 0
	;;
	.mfb
	cmp4.eq p6, p7 = 0, r40
	nop 0
	(p6) br.cond.dpnt .L49
	;;
	.mfb
	cmp4.ne p6, p7 = 1, r40
	nop 0
	(p7) br.cond.dpnt .L50
	;;
	.mfb
	cmp4.ne p6, p7 = 2, r40
	nop 0
	(p7) br.cond.dpnt .L50
	;;
	.mii
	nop 0
	cmp4.ne p6, p7 = 3, r40
	;;
	(p7) adds r14 = -184, r44
	;;
	.mfb
	(p7) ld1 r8 = [r14]
	nop 0
	(p7) br.cond.dpnt .L49
	.mii
	nop 0
	cmp4.ne p6, p7 = 4, r40
	;;
	nop 0
	.mmi
	(p7) adds r14 = -184, r44
	;;
	(p7) ld2 r14 = [r14]
	nop 0
	;;
	.mib
	nop 0
	(p7) sxt2 r8 = r14
	(p7) br.cond.dpnt .L49
	.mii
	nop 0
	cmp4.ne p6, p7 = 5, r40
	;;
	(p7) adds r14 = -184, r44
	;;
	.mfb
	(p7) ld2 r8 = [r14]
	nop 0
	(p7) br.cond.dpnt .L49
	.mii
	nop 0
	cmp4.ne p6, p7 = 6, r40
	;;
	nop 0
	.mmi
	(p7) adds r14 = -184, r44
	;;
	(p7) ld4 r14 = [r14]
	nop 0
	;;
	.mib
	nop 0
	(p7) sxt4 r8 = r14
	(p7) br.cond.dpnt .L49
	.mii
	nop 0
	cmp4.ne p6, p7 = 7, r40
	;;
	(p7) adds r14 = -184, r44
	;;
	.mfb
	(p7) ld4 r8 = [r14]
	nop 0
	(p7) br.cond.dpnt .L49
	.mfb
	cmp4.ne p6, p7 = 8, r40
	nop 0
	(p7) br.cond.dpnt .L54
	;;
	.mfb
	cmp4.ne p6, p7 = 9, r40
	nop 0
	(p7) br.cond.dpnt .L54
	;;
	.mfb
	cmp4.ne p6, p7 = 10, r40
	nop 0
	(p7) br.cond.dpnt .L54
	;;
	.mfb
	cmp4.ne p6, p7 = 11, r40
	nop 0
	(p7) br.cond.dpnt .L54
	;;
	.mii
	nop 0
	cmp4.ne p6, p7 = 12, r40
	;;
	(p7) adds r14 = -184, r44
	;;
	.mfb
	(p7) ldfs f8 = [r14]
	nop 0
	(p7) br.cond.dpnt .L49
	.mii
	nop 0
	cmp4.ne p6, p7 = 13, r40
	;;
	(p7) adds r14 = -184, r44
	;;
	.mfb
	(p7) ldfd f8 = [r14]
	nop 0
	(p7) br.cond.dpnt .L49
	.mfb
	cmp4.ne p6, p7 = 14, r40
	nop 0
	(p7) br.cond.dpnt .L54
	;;
	.mib
	nop 0
	cmp4.ne p6, p7 = 15, r40
	(p6) br.cond.dptk .L49
	.mii
	nop 0
	adds r16 = -192, r44
	;;
	nop 0
	.mmi
	ld4 r14 = [r16]
	;;
	nop 0
	tbit.z p6, p7 = r14, 10
	.mfb
	adds r14 = -144, r44
	nop 0
	(p6) br.cond.dpnt .L49
	;;
	.mmi
	ld8 r22 = [r14]
	;;
	adds r14 = -1, r22
	nop 0
	;;
	.mib
	nop 0
	cmp.ltu p6, p7 = 31, r14
	(p6) br.cond.dpnt .L49
	.mmi
	ld8 r14 = [r41]
	;;
	and r21 = 7, r14
	and r24 = -8, r14
	.mii
	nop 0
	cmp.ltu p6, p7 = 8, r22
	;;
	nop 0
	.mfb
	add r14 = r22, r21
	nop 0
	(p6) br.cond.dptk .L35
	;;
	.mib
	nop 0
	cmp.ltu p6, p7 = 8, r14
	(p6) br.cond.dptk .L37
	.mfi
	shladd r16 = r14, 3, r0
	nop 0
	addl r14 = 2, r0
	.mii
	ld8 r17 = [r24]
	shladd r18 = r21, 3, r0
	;;
	adds r16 = -1, r16
	;;
	.mii
	nop 0
	sxt4 r16 = r16
	;;
	shl r14 = r14, r16
	;;
	.mmi
	adds r14 = -1, r14
	;;
	and r14 = r17, r14
	nop 0
	.mmi
	nop 0
	;;
	nop 0
	shr r8 = r14, r18
.L49:
	.mii
	nop 0
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.label_state 1
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
.L50:
	.body
	.copy_state 1
	.mii
	nop 0
	adds r14 = -184, r44
	;;
	nop 0
	.mii
	ld1 r14 = [r14]
	nop 0
	;;
	sxt1 r8 = r14
	.mii
	nop 0
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.label_state 2
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
.L54:
	.body
	.copy_state 2
	.mmb
	nop 0
	adds r14 = -184, r44
	nop 0
	;;
	.mii
	ld8 r8 = [r14]
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.label_state 3
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
.L35:
	.body
	.copy_state 3
	.mib
	nop 0
	cmp.ltu p6, p7 = 16, r22
	(p6) br.cond.dptk .L39
	;;
	.mib
	nop 0
	cmp.ltu p6, p7 = 16, r14
	(p6) br.cond.dptk .L41
	.mmi
	shladd r16 = r14, 3, r0
	adds r14 = 8, r24
	shladd r17 = r21, 2, r0
	.mmb
	shladd r19 = r21, 3, r0
	ld8 r18 = [r24]
	nop 0
	;;
	.mfi
	ld8 r20 = [r14]
	nop 0
	addl r14 = 2, r0
	.mii
	adds r16 = -65, r16
	sub r17 = 32, r17
	;;
	sxt4 r16 = r16
	.mii
	nop 0
	sxt4 r17 = r17
	shr r18 = r18, r19
	;;
	.mii
	nop 0
	shl r14 = r14, r16
	;;
	adds r14 = -1, r14
	;;
	.mii
	nop 0
	and r14 = r20, r14
	;;
	shl r16 = r14, r17
	.mii
	nop 0
	shr r9 = r14, r19
	;;
	shl r16 = r16, r17
	;;
	.mii
	or r8 = r16, r18
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.label_state 4
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
.L37:
	.body
	.copy_state 4
	.mfi
	shladd r16 = r14, 3, r0
	nop 0
	addl r14 = 2, r0
	.mii
	ld8 r18 = [r24], 8
	shladd r19 = r21, 3, r0
	;;
	adds r16 = -65, r16
	.mii
	ld8 r20 = [r24]
	sub r17 = 64, r19
	;;
	sxt4 r16 = r16
	.mii
	nop 0
	sxt4 r17 = r17
	;;
	shl r14 = r14, r16
	.mii
	nop 0
	shr r18 = r18, r19
	;;
	adds r14 = -1, r14
	;;
	.mii
	nop 0
	and r14 = r20, r14
	;;
	shl r14 = r14, r17
	;;
	.mii
	or r8 = r14, r18
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.label_state 5
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
.L39:
	.body
	.copy_state 5
	.mib
	nop 0
	cmp.ltu p6, p7 = 24, r22
	(p6) br.cond.dptk .L43
	;;
	.mib
	nop 0
	cmp.ltu p6, p7 = 24, r14
	(p6) br.cond.dptk .L45
	.mmi
	shladd r16 = r14, 3, r0
	adds r14 = 8, r24
	shladd r17 = r21, 2, r0
	.mmb
	shladd r20 = r21, 3, r0
	ld8 r19 = [r24], 16
	nop 0
	;;
	.mmi
	ld8 r18 = [r14]
	addl r14 = 2, r0
	adds r16 = -65, r16
	.mmb
	sub r17 = 32, r17
	ld8 r21 = [r24]
	nop 0
	;;
	.mii
	nop 0
	sxt4 r16 = r16
	sxt4 r17 = r17
	.mii
	nop 0
	shr r19 = r19, r20
	;;
	shl r14 = r14, r16
	.mii
	nop 0
	shl r16 = r18, r17
	shr r18 = r18, r20
	;;
	.mii
	nop 0
	shl r16 = r16, r17
	adds r14 = -1, r14
	;;
	.mii
	and r14 = r21, r14
	or r8 = r16, r19
	;;
	shl r16 = r14, r17
	.mii
	nop 0
	shr r10 = r14, r20
	;;
	shl r16 = r16, r17
	;;
	.mii
	or r9 = r16, r18
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.label_state 6
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
.L41:
	.body
	.copy_state 6
	.mfi
	shladd r17 = r14, 3, r0
	nop 0
	adds r14 = 8, r24
	.mfi
	ld8 r19 = [r24], 16
	nop 0
	shladd r16 = r21, 3, r0
	;;
	.mmi
	ld8 r18 = [r14]
	addl r14 = 2, r0
	adds r17 = -129, r17
	.mmi
	ld8 r21 = [r24]
	mov r20 = r16
	sub r16 = 64, r16
	;;
	.mii
	nop 0
	sxt4 r17 = r17
	sxt4 r16 = r16
	;;
	.mii
	nop 0
	shl r14 = r14, r17
	shr r19 = r19, r20
	.mii
	nop 0
	shl r17 = r18, r16
	shr r18 = r18, r20
	;;
	.mmi
	adds r14 = -1, r14
	;;
	and r14 = r21, r14
	or r8 = r17, r19
	;;
	.mib
	nop 0
	shl r14 = r14, r16
	nop 0
	;;
	.mii
	or r9 = r14, r18
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.label_state 7
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
.L45:
	.body
	.copy_state 7
	.mmi
	shladd r17 = r14, 3, r0
	adds r14 = 24, r24
	shladd r16 = r21, 3, r0
	.mmi
	adds r19 = 8, r24
	ld8 r21 = [r24]
	adds r20 = 16, r24
	;;
	.mmi
	ld8 r23 = [r14]
	addl r14 = 2, r0
	adds r17 = -129, r17
	.mmi
	mov r18 = r16
	ld8 r19 = [r19]
	sub r16 = 64, r16
	;;
	.mib
	nop 0
	sxt4 r17 = r17
	nop 0
	.mii
	ld8 r20 = [r20]
	sxt4 r16 = r16
	;;
	shl r14 = r14, r17
	.mii
	nop 0
	shr r22 = r20, r18
	shl r17 = r19, r16
	.mii
	nop 0
	shr r21 = r21, r18
	shr r19 = r19, r18
	.mii
	nop 0
	shl r20 = r20, r16
	;;
	nop 0
	.mmi
	adds r14 = -1, r14
	;;
	and r14 = r23, r14
	or r8 = r17, r21
	.mii
	nop 0
	or r9 = r20, r19
	;;
	shl r14 = r14, r16
	;;
	.mii
	or r10 = r14, r22
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.label_state 8
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
.L43:
	.body
	.copy_state 8
	.mib
	nop 0
	cmp.ltu p6, p7 = 32, r14
	(p6) br.cond.dptk .L47
	.mmi
	adds r16 = 24, r24
	shladd r14 = r14, 3, r0
	adds r18 = 8, r24
	.mmi
	shladd r17 = r21, 2, r0
	adds r19 = 16, r24
	shladd r21 = r21, 3, r0
	;;
	.mmi
	nop 0
	ld8 r23 = [r16]
	addl r16 = 2, r0
	.mmi
	adds r14 = -65, r14
	ld8 r20 = [r18]
	sub r17 = 32, r17
	;;
	.mii
	nop 0
	sxt4 r14 = r14
	sxt4 r17 = r17
	.mmb
	ld8 r22 = [r19]
	ld8 r19 = [r24]
	nop 0
	;;
	.mii
	nop 0
	shl r16 = r16, r14
	shl r14 = r20, r17
	.mii
	nop 0
	shr r19 = r19, r21
	shl r18 = r22, r17
	;;
	.mii
	nop 0
	shl r14 = r14, r17
	shr r20 = r20, r21
	.mii
	adds r16 = -1, r16
	shl r18 = r18, r17
	shr r22 = r22, r21
	;;
	.mmi
	nop 0
	and r16 = r23, r16
	or r8 = r14, r19
	.mmi
	or r9 = r18, r20
	;;
	nop 0
	shl r14 = r16, r17
	.mii
	nop 0
	shr r11 = r16, r21
	;;
	shl r14 = r14, r17
	;;
	.mii
	or r10 = r14, r22
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.label_state 9
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
.L47:
	.body
	.copy_state 9
	.mmb
	shladd r17 = r14, 3, r0
	adds r14 = 32, r24
	nop 0
	.mmi
	adds r19 = 8, r24
	adds r20 = 16, r24
	shladd r16 = r21, 3, r0
	;;
	.mfi
	ld8 r23 = [r14]
	nop 0
	adds r14 = 24, r24
	.mmi
	ld8 r21 = [r19]
	adds r17 = -129, r17
	mov r18 = r16
	.mfi
	ld8 r19 = [r20]
	nop 0
	sub r16 = 64, r16
	;;
	.mmi
	ld8 r20 = [r14]
	addl r14 = 2, r0
	sxt4 r17 = r17
	.mii
	nop 0
	sxt4 r16 = r16
	;;
	shl r22 = r21, r16
	.mii
	nop 0
	shr r21 = r21, r18
	shl r14 = r14, r17
	.mii
	ld8 r17 = [r24]
	shr r24 = r20, r18
	shl r20 = r20, r16
	;;
	.mii
	nop 0
	shr r17 = r17, r18
	shr r18 = r19, r18
	.mii
	adds r14 = -1, r14
	shl r19 = r19, r16
	;;
	and r14 = r23, r14
	.mmi
	nop 0
	or r8 = r22, r17
	or r10 = r20, r18
	.mii
	nop 0
	or r9 = r19, r21
	;;
	shl r14 = r14, r16
	;;
	.mii
	or r11 = r14, r24
	mov ar.pfs = r43
	mov b0 = r42
	.mib
	nop 0
	.restore sp
	mov r12 = r44
	br.ret.sptk.many b0
	.endp callback_receiver#
	.align 16
	.global callback_get_receiver#
	.proc callback_get_receiver#
callback_get_receiver:
	.prologue 2, 2
	.mfi
	.vframe r2
	mov r2 = r12
	.body
	nop 0
	addl r8 = @ltoff(@fptr(callback_receiver#)), gp
	;;
	.mib
	ld8 r8 = [r8]
	.restore sp
	mov r12 = r2
	br.ret.sptk.many b0
	.endp callback_get_receiver#
	.ident	"GCC: (GNU) 4.0.1"
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
