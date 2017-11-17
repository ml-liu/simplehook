	.file	"avcall-ia64.c"
	.pred.safe_across_calls p1-p5,p16-p63
	.text
	.align 16
	.global avcall_call#
	.proc avcall_call#
avcall_call:
	.prologue 14, 34
	.mmi
	.save ar.pfs, r35
	alloc r35 = ar.pfs, 1, 6, 8, 0
	adds r14 = 40, r32
	adds r20 = 48, r32
	.mmi
	adds r16 = 64, r32
	adds r21 = 72, r32
	adds r19 = -2032, r12
	;;
	.mmb
	ld8 r15 = [r14]
	ld8 r17 = [r20]
	nop 0
	.mii
	.vframe r36
	mov r36 = r12
	.save ar.lc, r38
	mov r38 = ar.lc
	mov r37 = r1
	;;
	.mmi
	sub r15 = r15, r17
	ld8 r14 = [r16]
	.save rp, r34
	mov r34 = b0
	.body
	.mmi
	nop 0
	;;
	nop 0
	shr.u r15 = r15, 3
	.mmi
	sub r14 = r14, r21
	;;
	nop 0
	shr.u r18 = r14, 3
	.mmb
	nop 0
	cmp4.ge p6, p7 = 8, r15
	(p6) br.cond.dptk .L2
	.mii
	sub r14 = 8, r15
	addl r16 = 8, r0
	;;
	andcm r14 = -1, r14
	;;
	.mii
	nop 0
	addp4 r14 = r14, r0
	;;
	mov ar.lc = r14
.L4:
	.mii
	nop 0
	sxt4 r14 = r16
	adds r16 = 1, r16
	;;
	.mmi
	shladd r14 = r14, 3, r0
	;;
	add r15 = r17, r14
	add r14 = r19, r14
	;;
	.mmb
	adds r14 = -64, r14
	ld8 r15 = [r15]
	nop 0
	;;
	.mfb
	st8 [r14] = r15
	nop 0
	br.cloop.sptk.few .L4
.L2:
	.mmi
	adds r33 = 24, r32
	;;
	ld4 r15 = [r33]
	nop 0
	;;
	.mii
	nop 0
	cmp4.ne p6, p7 = 16, r15
	;;
	(p7) adds r14 = 16, r32
	;;
	.mfi
	(p7) ld8 r8 = [r14]
	nop 0
	cmp4.ge p6, p7 = 0, r18
	.mfb
	adds r14 = 80, r32
	nop 0
	(p6) br.cond.dpnt .L7
	;;
	.mmb
	nop 0
	cmp4.ge p6, p7 = 1, r18
	nop 0
	.mfb
	ldfd f8 = [r21]
	nop 0
	(p6) br.cond.dpnt .L7
	;;
	.mmb
	nop 0
	cmp4.ge p6, p7 = 2, r18
	nop 0
	.mfb
	ldfd f9 = [r14]
	nop 0
	(p7) br.cond.dptk .L71
	;;
.L7:
	.mib
	nop 0
	cmp4.ne p6, p7 = 13, r15
	(p7) br.cond.dpnt .L72
	;;
.L16:
	.mib
	cmp4.ne p6, p7 = 14, r15
	adds r15 = 8, r32
	(p7) br.cond.dpnt .L73
	.mmb
	nop 0
	ld8 r14 = [r20]
	nop 0
	;;
	.mmi
	ld8 r15 = [r15]
	adds r16 = 8, r14
	adds r17 = 16, r14
	.mmi
	adds r18 = 24, r14
	adds r19 = 32, r14
	adds r20 = 40, r14
	.mmi
	nop 0
	adds r21 = 48, r14
	adds r22 = 56, r14
	.mmi
	ld8 r39 = [r14]
	;;
	ld8 r14 = [r15], 8
	nop 0
	.mii
	ld8 r40 = [r16]
	nop 0
	;;
	mov b6 = r14
	.mmb
	ld8 r1 = [r15]
	ld8 r41 = [r17]
	nop 0
	.mmb
	ld8 r42 = [r18]
	ld8 r43 = [r19]
	nop 0
	.mmb
	ld8 r44 = [r20]
	ld8 r45 = [r21]
	nop 0
	.mbb
	ld8 r46 = [r22]
	nop 0
	br.call.sptk.many b0 = b6
	;;
	.mmi
	mov r1 = r37
	ld4 r14 = [r33]
	mov r28 = r8
	;;
	.mfb
	cmp4.eq p6, p7 = 1, r14
	nop 0
	(p6) br.cond.dpnt .L18
	;;
	.mib
	nop 0
	cmp4.ne p6, p7 = 0, r14
	(p7) br.cond.dptk .L69
	;;
	.mfb
	cmp4.ne p6, p7 = 2, r14
	nop 0
	(p7) br.cond.dpnt .L65
	;;
	.mfb
	cmp4.ne p6, p7 = 3, r14
	nop 0
	(p7) br.cond.dpnt .L65
	;;
	.mfb
	cmp4.ne p6, p7 = 4, r14
	nop 0
	(p7) br.cond.dpnt .L65
	;;
	.mfb
	cmp4.ne p6, p7 = 5, r14
	nop 0
	(p7) br.cond.dpnt .L66
	;;
	.mfb
	cmp4.ne p6, p7 = 6, r14
	nop 0
	(p7) br.cond.dpnt .L66
	;;
	.mfb
	cmp4.ne p6, p7 = 7, r14
	nop 0
	(p7) br.cond.dpnt .L67
	;;
	.mfb
	cmp4.ne p6, p7 = 8, r14
	nop 0
	(p7) br.cond.dpnt .L67
	;;
	.mii
	nop 0
	cmp4.ne p6, p7 = 9, r14
	;;
	nop 0
	.mfb
	cmp4.ne.and.orcm p6, p7 = 11, r14
	nop 0
	(p7) br.cond.dptk .L69
	;;
	.mii
	nop 0
	cmp4.ne p6, p7 = 10, r14
	;;
	nop 0
	.mfb
	cmp4.ne.and.orcm p6, p7 = 12, r14
	nop 0
	(p7) br.cond.dptk .L69
	;;
	.mfb
	cmp4.ne p6, p7 = 15, r14
	nop 0
	(p7) br.cond.dpnt .L69
	;;
	.mib
	nop 0
	cmp4.ne p6, p7 = 16, r14
	(p6) br.cond.dptk .L18
	.mmi
	ld4 r14 = [r32]
	;;
	nop 0
	tbit.z p6, p7 = r14, 9
	.mfb
	adds r14 = 32, r32
	nop 0
	(p6) br.cond.dpnt .L18
	;;
	.mmi
	ld8 r19 = [r14]
	;;
	adds r14 = -1, r19
	nop 0
	;;
	.mib
	cmp.ltu p6, p7 = 31, r14
	adds r14 = 16, r32
	(p6) br.cond.dpnt .L18
	;;
	.mii
	ld8 r14 = [r14]
	cmp.ltu p6, p7 = 8, r19
	;;
	and r17 = 7, r14
	.mii
	nop 0
	and r27 = -8, r14
	;;
	nop 0
	.mfb
	add r23 = r19, r17
	nop 0
	(p6) br.cond.dptk .L47
	;;
	.mib
	nop 0
	cmp.ltu p6, p7 = 8, r23
	(p6) br.cond.dptk .L49
	.mmi
	shladd r15 = r23, 3, r0
	addl r14 = 2, r0
	shladd r18 = r17, 3, r0
	.mmi
	ld8 r17 = [r27]
	;;
	adds r15 = -1, r15
	nop 0
	;;
	.mii
	nop 0
	sxt4 r15 = r15
	;;
	shl r14 = r14, r15
	.mii
	addl r15 = 1, r0
	shl r16 = r8, r18
	;;
	shl r15 = r15, r18
	.mii
	nop 0
	xor r16 = r16, r17
	;;
	sub r14 = r14, r15
	;;
	.mmi
	and r14 = r16, r14
	;;
	xor r17 = r14, r17
	nop 0
	;;
	.mfb
	st8 [r27] = r17
	nop 0
	nop 0
.L18:
	.mfi
	mov r8 = r0
	nop 0
	mov b0 = r34
	.mmi
	nop 0
	.label_state 1
	.restore sp
	mov r12 = r36
	mov ar.pfs = r35
	.mib
	nop 0
	mov ar.lc = r38
	br.ret.sptk.many b0
.L71:
	.body
	.copy_state 1
	.mfi
	adds r14 = 88, r32
	nop 0
	cmp4.ge p6, p7 = 3, r18
	;;
	.mfb
	ldfd f10 = [r14]
	nop 0
	(p6) br.cond.dptk .L7
	.mfi
	adds r14 = 96, r32
	nop 0
	cmp4.ge p6, p7 = 4, r18
	;;
	.mfb
	ldfd f11 = [r14]
	nop 0
	(p6) br.cond.dptk .L7
	.mfi
	adds r14 = 104, r32
	nop 0
	cmp4.ge p6, p7 = 5, r18
	;;
	.mfb
	ldfd f12 = [r14]
	nop 0
	(p6) br.cond.dptk .L7
	.mfi
	adds r14 = 112, r32
	nop 0
	cmp4.ge p6, p7 = 6, r18
	;;
	.mfb
	ldfd f13 = [r14]
	nop 0
	(p6) br.cond.dptk .L7
	.mii
	adds r14 = 120, r32
	cmp4.ge p6, p7 = 7, r18
	;;
	nop 0
	.mii
	ldfd f14 = [r14]
	(p7) adds r14 = 128, r32
	;;
	nop 0
	.mmb
	(p7) ldfd f15 = [r14]
	cmp4.ne p6, p7 = 13, r15
	(p6) br.cond.dptk .L16
.L72:
	.mmb
	adds r16 = 8, r32
	adds r15 = 16, r32
	nop 0
	.mfi
	ld8 r14 = [r20]
	nop 0
	mov ar.lc = r38
	;;
	.mmi
	ld8 r33 = [r15]
	ld8 r15 = [r16]
	adds r17 = 8, r14
	.mmi
	adds r18 = 16, r14
	adds r19 = 24, r14
	adds r20 = 32, r14
	.mmi
	adds r21 = 40, r14
	adds r22 = 48, r14
	adds r23 = 56, r14
	.mii
	ld8 r39 = [r14]
	nop 0
	;;
	nop 0
	.mmb
	ld8 r14 = [r15], 8
	ld8 r40 = [r17]
	nop 0
	;;
	.mmi
	ld8 r1 = [r15]
	ld8 r41 = [r18]
	mov b6 = r14
	.mmb
	ld8 r42 = [r19]
	ld8 r43 = [r20]
	nop 0
	.mmb
	ld8 r44 = [r21]
	ld8 r45 = [r22]
	nop 0
	.mbb
	ld8 r46 = [r23]
	nop 0
	br.call.sptk.many b0 = b6
	;;
	.mmb
	.label_state 2
	.restore sp
	mov r12 = r36
	mov r8 = r0
	nop 0
	.mmi
	mov r1 = r37
	stfs [r33] = f8
	mov b0 = r34
	.mib
	nop 0
	mov ar.pfs = r35
	br.ret.sptk.many b0
	;;
.L69:
	.body
	.copy_state 2
	.mmi
	adds r14 = 16, r32
	mov r8 = r0
	mov b0 = r34
	.mmi
	.label_state 3
	.restore sp
	mov r12 = r36
	;;
	ld8 r14 = [r14]
	mov ar.pfs = r35
	.mii
	nop 0
	mov ar.lc = r38
	;;
	nop 0
	.mfb
	st8 [r14] = r28
	nop 0
	br.ret.sptk.many b0
.L73:
	.body
	.copy_state 3
	.mmb
	adds r16 = 8, r32
	adds r15 = 16, r32
	nop 0
	.mfi
	ld8 r14 = [r20]
	nop 0
	mov ar.lc = r38
	;;
	.mmi
	ld8 r33 = [r15]
	ld8 r15 = [r16]
	adds r17 = 8, r14
	.mmi
	adds r18 = 16, r14
	adds r19 = 24, r14
	adds r20 = 32, r14
	.mmi
	adds r21 = 40, r14
	adds r22 = 48, r14
	adds r23 = 56, r14
	.mii
	ld8 r39 = [r14]
	nop 0
	;;
	nop 0
	.mmb
	ld8 r14 = [r15], 8
	ld8 r40 = [r17]
	nop 0
	;;
	.mmi
	ld8 r1 = [r15]
	ld8 r41 = [r18]
	mov b6 = r14
	.mmb
	ld8 r42 = [r19]
	ld8 r43 = [r20]
	nop 0
	.mmb
	ld8 r44 = [r21]
	ld8 r45 = [r22]
	nop 0
	.mbb
	ld8 r46 = [r23]
	nop 0
	br.call.sptk.many b0 = b6
	;;
	.mmb
	.label_state 4
	.restore sp
	mov r12 = r36
	mov r8 = r0
	nop 0
	.mmi
	mov r1 = r37
	stfd [r33] = f8
	mov b0 = r34
	.mib
	nop 0
	mov ar.pfs = r35
	br.ret.sptk.many b0
	;;
.L65:
	.body
	.copy_state 4
	.mmi
	adds r14 = 16, r32
	mov r8 = r0
	mov b0 = r34
	.mmi
	.label_state 5
	.restore sp
	mov r12 = r36
	;;
	ld8 r14 = [r14]
	mov ar.pfs = r35
	.mii
	nop 0
	mov ar.lc = r38
	;;
	nop 0
	.mfb
	st1 [r14] = r28
	nop 0
	br.ret.sptk.many b0
.L66:
	.body
	.copy_state 5
	.mmi
	adds r14 = 16, r32
	mov r8 = r0
	mov b0 = r34
	.mmi
	.label_state 6
	.restore sp
	mov r12 = r36
	;;
	ld8 r14 = [r14]
	mov ar.pfs = r35
	.mii
	nop 0
	mov ar.lc = r38
	;;
	nop 0
	.mfb
	st2 [r14] = r28
	nop 0
	br.ret.sptk.many b0
.L67:
	.body
	.copy_state 6
	.mmi
	adds r14 = 16, r32
	mov r8 = r0
	mov b0 = r34
	.mmi
	.label_state 7
	.restore sp
	mov r12 = r36
	;;
	ld8 r14 = [r14]
	mov ar.pfs = r35
	.mii
	nop 0
	mov ar.lc = r38
	;;
	nop 0
	.mfb
	st4 [r14] = r28
	nop 0
	br.ret.sptk.many b0
.L47:
	.body
	.copy_state 7
	.mib
	nop 0
	cmp.ltu p6, p7 = 16, r19
	(p6) br.cond.dptk .L51
	;;
	.mfi
	shladd r20 = r17, 3, r0
	nop 0
	addl r14 = -1, r0
	.mii
	ld8 r16 = [r27]
	cmp.ltu p6, p7 = 16, r23
	;;
	nop 0
	.mii
	mov r19 = r20
	shl r15 = r8, r20
	shl r14 = r14, r20
	;;
	.mmi
	xor r15 = r15, r16
	;;
	and r14 = r15, r14
	nop 0
	;;
	.mii
	nop 0
	xor r16 = r14, r16
	;;
	nop 0
	.mfb
	st8 [r27] = r16
	nop 0
	(p6) br.cond.dptk .L53
	.mmi
	shladd r17 = r17, 2, r0
	shladd r16 = r23, 3, r0
	addl r15 = 2, r0
	.mmi
	adds r19 = 8, r27
	.label_state 8
	.restore sp
	mov r12 = r36
	shl r20 = r9, r20
	;;
	.mmb
	sub r17 = 32, r17
	adds r16 = -65, r16
	nop 0
	.mii
	ld8 r18 = [r19]
	mov b0 = r34
	mov ar.pfs = r35
	;;
	.mii
	nop 0
	sxt4 r16 = r16
	sxt4 r17 = r17
	.mib
	nop 0
	mov ar.lc = r38
	nop 0
	;;
	.mii
	nop 0
	shr r14 = r8, r17
	shl r15 = r15, r16
	.mmi
	mov r8 = r0
	;;
	nop 0
	shr r14 = r14, r17
	.mii
	nop 0
	adds r15 = -1, r15
	;;
	or r14 = r20, r14
	;;
	.mii
	nop 0
	xor r14 = r14, r18
	;;
	and r15 = r14, r15
	;;
	.mii
	nop 0
	xor r18 = r15, r18
	;;
	nop 0
	.mfb
	st8 [r19] = r18
	nop 0
	br.ret.sptk.many b0
.L49:
	.body
	.copy_state 8
	.mmi
	shladd r14 = r23, 3, r0
	addl r15 = 2, r0
	mov b0 = r34
	.mmi
	shladd r18 = r17, 3, r0
	ld8 r19 = [r27]
	.label_state 9
	.restore sp
	mov r12 = r36
	;;
	.mmi
	adds r14 = -65, r14
	sub r16 = 64, r18
	mov ar.pfs = r35
	.mii
	nop 0
	mov ar.lc = r38
	;;
	sxt4 r14 = r14
	.mii
	nop 0
	shl r17 = r8, r18
	;;
	shl r15 = r15, r14
	.mii
	addl r14 = -1, r0
	sxt4 r16 = r16
	;;
	shr r16 = r8, r16
	.mii
	mov r8 = r0
	xor r17 = r17, r19
	shl r14 = r14, r18
	.mii
	nop 0
	adds r15 = -1, r15
	;;
	and r14 = r17, r14
	;;
	.mmi
	xor r19 = r14, r19
	;;
	st8 [r27] = r19, 8
	nop 0
	;;
	.mmi
	ld8 r14 = [r27]
	;;
	xor r16 = r16, r14
	nop 0
	;;
	.mmi
	and r15 = r16, r15
	;;
	xor r14 = r15, r14
	nop 0
	;;
	.mfb
	st8 [r27] = r14
	nop 0
	br.ret.sptk.many b0
.L53:
	.body
	.copy_state 9
	.mmi
	shladd r15 = r23, 3, r0
	addl r14 = 2, r0
	sub r17 = 64, r20
	.mmi
	adds r21 = 16, r27
	adds r20 = 8, r27
	shl r19 = r9, r19
	;;
	.mii
	adds r15 = -129, r15
	mov b0 = r34
	sxt4 r17 = r17
	.mmi
	.label_state 10
	.restore sp
	mov r12 = r36
	nop 0
	mov ar.pfs = r35
	;;
	.mii
	nop 0
	shr r18 = r9, r17
	sxt4 r15 = r15
	;;
	.mii
	nop 0
	shl r14 = r14, r15
	shr r16 = r8, r17
	.mmi
	ld8 r15 = [r21]
	mov r8 = r0
	mov ar.lc = r38
	;;
	.mii
	xor r18 = r18, r15
	adds r14 = -1, r14
	or r16 = r19, r16
	;;
	.mmb
	and r14 = r18, r14
	st8 [r20] = r16
	nop 0
	;;
	.mii
	nop 0
	xor r15 = r14, r15
	;;
	nop 0
	.mfb
	st8 [r21] = r15
	nop 0
	br.ret.sptk.many b0
.L51:
	.body
	.copy_state 10
	.mib
	nop 0
	cmp.ltu p6, p7 = 24, r19
	(p6) br.cond.dptk .L55
	;;
	.mfi
	shladd r19 = r17, 3, r0
	nop 0
	addl r14 = -1, r0
	.mii
	ld8 r16 = [r27]
	cmp.ltu p6, p7 = 24, r23
	;;
	nop 0
	.mii
	mov r29 = r19
	shl r15 = r8, r19
	shl r14 = r14, r19
	;;
	.mmi
	xor r15 = r15, r16
	;;
	and r14 = r15, r14
	nop 0
	;;
	.mii
	nop 0
	xor r16 = r14, r16
	;;
	nop 0
	.mfb
	st8 [r27] = r16
	nop 0
	(p6) br.cond.dptk .L57
	.mmi
	shladd r14 = r17, 2, r0
	shladd r18 = r23, 3, r0
	addl r16 = 2, r0
	.mmi
	adds r22 = 16, r27
	adds r20 = 8, r27
	shl r21 = r10, r29
	;;
	.mmi
	sub r14 = 32, r14
	adds r18 = -65, r18
	mov b0 = r34
	.mii
	.label_state 11
	.restore sp
	mov r12 = r36
	shl r19 = r9, r29
	mov ar.pfs = r35
	;;
	.mii
	nop 0
	sxt4 r18 = r18
	sxt4 r14 = r14
	.mib
	nop 0
	mov ar.lc = r38
	nop 0
	;;
	.mii
	nop 0
	shr r15 = r9, r14
	shr r17 = r8, r14
	.mii
	mov r8 = r0
	nop 0
	shl r16 = r16, r18
	;;
	.mii
	nop 0
	shr r15 = r15, r14
	shr r17 = r17, r14
	.mii
	ld8 r14 = [r22]
	nop 0
	adds r16 = -1, r16
	;;
	.mii
	or r15 = r21, r15
	or r17 = r19, r17
	;;
	xor r15 = r15, r14
	.mmi
	st8 [r20] = r17
	;;
	and r16 = r15, r16
	nop 0
	;;
	.mii
	nop 0
	xor r14 = r16, r14
	;;
	nop 0
	.mfb
	st8 [r22] = r14
	nop 0
	br.ret.sptk.many b0
.L55:
	.body
	.copy_state 11
	.mfi
	shladd r18 = r17, 3, r0
	nop 0
	addl r14 = -1, r0
	.mii
	ld8 r16 = [r27]
	cmp.ltu p6, p7 = 32, r23
	;;
	nop 0
	.mii
	mov r29 = r18
	shl r15 = r8, r18
	shl r14 = r14, r18
	;;
	.mmi
	xor r15 = r15, r16
	;;
	and r14 = r15, r14
	nop 0
	;;
	.mii
	nop 0
	xor r16 = r14, r16
	;;
	nop 0
	.mfb
	st8 [r27] = r16
	nop 0
	(p6) br.cond.dptk .L59
	.mmi
	shladd r14 = r17, 2, r0
	addl r15 = 2, r0
	shl r20 = r10, r18
	.mmi
	shladd r18 = r23, 3, r0
	adds r23 = 24, r27
	shl r19 = r9, r29
	;;
	.mmi
	sub r14 = 32, r14
	adds r18 = -65, r18
	mov b0 = r34
	.mmi
	adds r21 = 8, r27
	adds r22 = 16, r27
	.label_state 12
	.restore sp
	mov r12 = r36
	.mii
	nop 0
	mov ar.pfs = r35
	;;
	sxt4 r18 = r18
	.mii
	nop 0
	sxt4 r14 = r14
	mov ar.lc = r38
	;;
	.mii
	nop 0
	shr r16 = r8, r14
	shr r17 = r9, r14
	.mii
	mov r8 = r0
	nop 0
	shl r15 = r15, r18
	;;
	.mii
	nop 0
	shr r16 = r16, r14
	shr r17 = r17, r14
	.mii
	ld8 r14 = [r23]
	adds r15 = -1, r15
	;;
	or r16 = r19, r16
	.mmi
	or r17 = r20, r17
	;;
	st8 [r21] = r16
	xor r16 = r14, r16
	.mmi
	st8 [r22] = r17
	;;
	and r15 = r16, r15
	nop 0
	;;
	.mii
	nop 0
	xor r14 = r15, r14
	;;
	nop 0
	.mfb
	st8 [r23] = r14
	nop 0
	br.ret.sptk.many b0
.L57:
	.body
	.copy_state 12
	.mmi
	shladd r14 = r23, 3, r0
	addl r15 = 2, r0
	sub r16 = 64, r19
	.mmi
	adds r24 = 24, r27
	adds r22 = 8, r27
	shl r21 = r10, r29
	;;
	.mii
	adds r14 = -129, r14
	sxt4 r16 = r16
	shl r20 = r9, r29
	.mmi
	adds r23 = 16, r27
	.label_state 13
	.restore sp
	mov r12 = r36
	mov b0 = r34
	;;
	.mii
	nop 0
	shr r18 = r10, r16
	sxt4 r14 = r14
	;;
	.mii
	nop 0
	shl r15 = r15, r14
	shr r19 = r8, r16
	.mmi
	ld8 r14 = [r24]
	mov r8 = r0
	mov ar.pfs = r35
	.mib
	nop 0
	shr r17 = r9, r16
	nop 0
	;;
	.mii
	xor r18 = r18, r14
	mov ar.lc = r38
	adds r15 = -1, r15
	.mmi
	or r19 = r20, r19
	;;
	and r15 = r18, r15
	or r17 = r21, r17
	.mii
	st8 [r22] = r19
	nop 0
	;;
	xor r14 = r15, r14
	.mmb
	nop 0
	st8 [r23] = r17
	nop 0
	;;
	.mfb
	st8 [r24] = r14
	nop 0
	br.ret.sptk.many b0
.L59:
	.body
	.copy_state 13
	.mmi
	shladd r16 = r23, 3, r0
	addl r15 = 2, r0
	sub r14 = 64, r18
	.mmi
	adds r24 = 8, r27
	adds r25 = 16, r27
	adds r26 = 24, r27
	;;
	.mmi
	nop 0
	adds r16 = -129, r16
	sxt4 r14 = r14
	.mmi
	adds r27 = 32, r27
	.restore sp
	mov r12 = r36
	shl r23 = r11, r29
	;;
	.mii
	nop 0
	sxt4 r16 = r16
	shr r22 = r11, r14
	;;
	.mii
	nop 0
	shl r15 = r15, r16
	shr r17 = r8, r14
	.mii
	mov r8 = r0
	shr r18 = r9, r14
	shr r19 = r10, r14
	.mii
	ld8 r14 = [r27]
	shl r20 = r9, r29
	shl r21 = r10, r29
	;;
	.mmi
	xor r22 = r22, r14
	adds r15 = -1, r15
	mov b0 = r34
	;;
	.mmi
	and r15 = r22, r15
	or r19 = r23, r19
	mov ar.pfs = r35
	.mmi
	or r17 = r20, r17
	or r18 = r21, r18
	mov ar.lc = r38
	;;
	.mmb
	xor r14 = r15, r14
	st8 [r24] = r17
	nop 0
	.mmb
	st8 [r25] = r18
	st8 [r26] = r19
	nop 0
	;;
	.mfb
	st8 [r27] = r14
	nop 0
	br.ret.sptk.many b0
	.endp avcall_call#
	.ident	"GCC: (GNU) 4.0.1"
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
