	.file	"vacall-ia64.c"
	.pred.safe_across_calls p1-p5,p16-p63
	.text
	.align 16
	.global vacall_receiver#
	.proc vacall_receiver#
vacall_receiver:
	.prologue 14, 41
	.spill 48
	.mmb
	.save ar.pfs, r42
	alloc r42 = ar.pfs, 8, 5, 1, 0
	.vframe r43
	mov r43 = r12
	nop 0
	.mmi
	adds r12 = -208, r12
	mov r44 = r1
	.save rp, r41
	mov r41 = b0
	.body
	;;
	.mmi
	adds r14 = -48, r43
	adds r16 = -48, r43
	adds r40 = -152, r43
	.mmb
	adds r45 = -192, r43
	st8 [r43] = r38
	nop 0
	;;
	.mmi
	nop 0
	st8 [r14] = r32, 8
	adds r32 = -160, r43
	.mmi
	st4 [r40] = r0
	;;
	st8 [r14] = r33
	adds r14 = -32, r43
	.mmi
	st4 [r45] = r0
	;;
	st8 [r14] = r34
	addl r14 = @ltoffx(vacall_function#), r1
	.mmb
	nop 0
	st8 [r32] = r0
	nop 0
	;;
	.mmi
	ld8.mov r14 = [r14], vacall_function#
	;;
	ld8 r15 = [r14]
	nop 0
	.mmi
	adds r14 = -24, r43
	;;
	st8 [r14] = r35
	adds r14 = -16, r43
	;;
	.mfi
	st8 [r14] = r36
	nop 0
	adds r14 = -8, r43
	.mmi
	nop 0
	;;
	st8 [r14] = r37
	nop 0
	.mmi
	adds r14 = 8, r43
	;;
	st8 [r14] = r39
	adds r14 = -112, r43
	;;
	.mfi
	stfd [r14] = f8
	nop 0
	adds r14 = -104, r43
	.mmi
	nop 0
	;;
	stfd [r14] = f9
	nop 0
	.mmi
	adds r14 = -96, r43
	;;
	stfd [r14] = f10
	adds r14 = -88, r43
	;;
	.mfi
	stfd [r14] = f11
	nop 0
	adds r14 = -80, r43
	.mmi
	nop 0
	;;
	stfd [r14] = f12
	nop 0
	.mmi
	adds r14 = -72, r43
	;;
	stfd [r14] = f13
	adds r14 = -64, r43
	;;
	.mfi
	stfd [r14] = f14
	nop 0
	adds r14 = -56, r43
	.mmi
	nop 0
	;;
	stfd [r14] = f15
	nop 0
	.mmi
	adds r14 = -168, r43
	;;
	st8 [r14] = r16
	adds r14 = -128, r43
	;;
	.mii
	st8 [r14] = r16
	adds r14 = -120, r43
	;;
	nop 0
	.mii
	st4 [r14] = r0
	adds r14 = -136, r43
	;;
	nop 0
	.mmb
	st8 [r14] = r8
	ld8 r14 = [r15], 8
	nop 0
	;;
	.mib
	nop 0
	mov b6 = r14
	nop 0
	.mbb
	ld8 r1 = [r15]
	nop 0
	br.call.sptk.many b0 = b6
	;;
	.mmb
	mov r1 = r44
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
	(p7) adds r14 = -184, r43
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
	(p7) adds r14 = -184, r43
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
	(p7) adds r14 = -184, r43
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
	(p7) adds r14 = -184, r43
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
	(p7) adds r14 = -184, r43
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
	(p7) adds r14 = -184, r43
	;;
	.mfb
	(p7) ldfs f8 = [r14]
	nop 0
	(p7) br.cond.dpnt .L49
	.mii
	nop 0
	cmp4.ne p6, p7 = 13, r40
	;;
	(p7) adds r14 = -184, r43
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
	adds r15 = -192, r43
	;;
	nop 0
	.mmi
	ld4 r14 = [r15]
	;;
	nop 0
	tbit.z p6, p7 = r14, 10
	.mfb
	adds r14 = -144, r43
	nop 0
	(p6) br.cond.dpnt .L49
	;;
	.mmi
	ld8 r21 = [r14]
	;;
	adds r14 = -1, r21
	nop 0
	;;
	.mib
	nop 0
	cmp.ltu p6, p7 = 31, r14
	(p6) br.cond.dpnt .L49
	.mmi
	ld8 r14 = [r32]
	;;
	and r20 = 7, r14
	and r23 = -8, r14
	.mii
	nop 0
	cmp.ltu p6, p7 = 8, r21
	;;
	nop 0
	.mfb
	add r14 = r21, r20
	nop 0
	(p6) br.cond.dptk .L35
	;;
	.mib
	nop 0
	cmp.ltu p6, p7 = 8, r14
	(p6) br.cond.dptk .L37
	.mfi
	shladd r15 = r14, 3, r0
	nop 0
	addl r14 = 2, r0
	.mii
	ld8 r16 = [r23]
	shladd r17 = r20, 3, r0
	;;
	adds r15 = -1, r15
	;;
	.mii
	nop 0
	sxt4 r15 = r15
	;;
	shl r14 = r14, r15
	;;
	.mmi
	adds r14 = -1, r14
	;;
	and r14 = r16, r14
	nop 0
	.mmi
	nop 0
	;;
	nop 0
	shr r8 = r14, r17
.L49:
	.mii
	nop 0
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.label_state 1
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
.L50:
	.body
	.copy_state 1
	.mii
	nop 0
	adds r14 = -184, r43
	;;
	nop 0
	.mii
	ld1 r14 = [r14]
	nop 0
	;;
	sxt1 r8 = r14
	.mii
	nop 0
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.label_state 2
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
.L54:
	.body
	.copy_state 2
	.mmb
	nop 0
	adds r14 = -184, r43
	nop 0
	;;
	.mii
	ld8 r8 = [r14]
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.label_state 3
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
.L35:
	.body
	.copy_state 3
	.mib
	nop 0
	cmp.ltu p6, p7 = 16, r21
	(p6) br.cond.dptk .L39
	;;
	.mib
	nop 0
	cmp.ltu p6, p7 = 16, r14
	(p6) br.cond.dptk .L41
	.mmi
	shladd r15 = r14, 3, r0
	adds r14 = 8, r23
	shladd r16 = r20, 2, r0
	.mmb
	shladd r18 = r20, 3, r0
	ld8 r17 = [r23]
	nop 0
	;;
	.mfi
	ld8 r19 = [r14]
	nop 0
	addl r14 = 2, r0
	.mii
	adds r15 = -65, r15
	sub r16 = 32, r16
	;;
	sxt4 r15 = r15
	.mii
	nop 0
	sxt4 r16 = r16
	shr r17 = r17, r18
	;;
	.mii
	nop 0
	shl r14 = r14, r15
	;;
	adds r14 = -1, r14
	;;
	.mii
	nop 0
	and r14 = r19, r14
	;;
	shl r15 = r14, r16
	.mii
	nop 0
	shr r9 = r14, r18
	;;
	shl r15 = r15, r16
	;;
	.mii
	or r8 = r15, r17
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.label_state 4
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
.L37:
	.body
	.copy_state 4
	.mfi
	shladd r15 = r14, 3, r0
	nop 0
	addl r14 = 2, r0
	.mii
	ld8 r17 = [r23], 8
	shladd r18 = r20, 3, r0
	;;
	adds r15 = -65, r15
	.mii
	ld8 r19 = [r23]
	sub r16 = 64, r18
	;;
	sxt4 r15 = r15
	.mii
	nop 0
	sxt4 r16 = r16
	;;
	shl r14 = r14, r15
	.mii
	nop 0
	shr r17 = r17, r18
	;;
	adds r14 = -1, r14
	;;
	.mii
	nop 0
	and r14 = r19, r14
	;;
	shl r14 = r14, r16
	;;
	.mii
	or r8 = r14, r17
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.label_state 5
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
.L39:
	.body
	.copy_state 5
	.mib
	nop 0
	cmp.ltu p6, p7 = 24, r21
	(p6) br.cond.dptk .L43
	;;
	.mib
	nop 0
	cmp.ltu p6, p7 = 24, r14
	(p6) br.cond.dptk .L45
	.mmi
	shladd r15 = r14, 3, r0
	adds r14 = 8, r23
	shladd r16 = r20, 2, r0
	.mmb
	shladd r19 = r20, 3, r0
	ld8 r18 = [r23], 16
	nop 0
	;;
	.mmi
	ld8 r17 = [r14]
	addl r14 = 2, r0
	adds r15 = -65, r15
	.mmb
	sub r16 = 32, r16
	ld8 r20 = [r23]
	nop 0
	;;
	.mii
	nop 0
	sxt4 r15 = r15
	sxt4 r16 = r16
	.mii
	nop 0
	shr r18 = r18, r19
	;;
	shl r14 = r14, r15
	.mii
	nop 0
	shl r15 = r17, r16
	shr r17 = r17, r19
	;;
	.mii
	nop 0
	shl r15 = r15, r16
	adds r14 = -1, r14
	;;
	.mii
	and r14 = r20, r14
	or r8 = r15, r18
	;;
	shl r15 = r14, r16
	.mii
	nop 0
	shr r10 = r14, r19
	;;
	shl r15 = r15, r16
	;;
	.mii
	or r9 = r15, r17
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.label_state 6
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
.L41:
	.body
	.copy_state 6
	.mfi
	shladd r16 = r14, 3, r0
	nop 0
	adds r14 = 8, r23
	.mfi
	ld8 r18 = [r23], 16
	nop 0
	shladd r15 = r20, 3, r0
	;;
	.mmi
	ld8 r17 = [r14]
	addl r14 = 2, r0
	adds r16 = -129, r16
	.mmi
	ld8 r20 = [r23]
	mov r19 = r15
	sub r15 = 64, r15
	;;
	.mii
	nop 0
	sxt4 r16 = r16
	sxt4 r15 = r15
	;;
	.mii
	nop 0
	shl r14 = r14, r16
	shr r18 = r18, r19
	.mii
	nop 0
	shl r16 = r17, r15
	shr r17 = r17, r19
	;;
	.mmi
	adds r14 = -1, r14
	;;
	and r14 = r20, r14
	or r8 = r16, r18
	;;
	.mib
	nop 0
	shl r14 = r14, r15
	nop 0
	;;
	.mii
	or r9 = r14, r17
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.label_state 7
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
.L45:
	.body
	.copy_state 7
	.mmi
	shladd r16 = r14, 3, r0
	adds r14 = 24, r23
	shladd r15 = r20, 3, r0
	.mmi
	adds r18 = 8, r23
	ld8 r20 = [r23]
	adds r19 = 16, r23
	;;
	.mmi
	ld8 r22 = [r14]
	addl r14 = 2, r0
	adds r16 = -129, r16
	.mmi
	mov r17 = r15
	ld8 r18 = [r18]
	sub r15 = 64, r15
	;;
	.mib
	nop 0
	sxt4 r16 = r16
	nop 0
	.mii
	ld8 r19 = [r19]
	sxt4 r15 = r15
	;;
	shl r14 = r14, r16
	.mii
	nop 0
	shr r21 = r19, r17
	shl r16 = r18, r15
	.mii
	nop 0
	shr r20 = r20, r17
	shr r18 = r18, r17
	.mii
	nop 0
	shl r19 = r19, r15
	;;
	nop 0
	.mmi
	adds r14 = -1, r14
	;;
	and r14 = r22, r14
	or r8 = r16, r20
	.mii
	nop 0
	or r9 = r19, r18
	;;
	shl r14 = r14, r15
	;;
	.mii
	or r10 = r14, r21
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.label_state 8
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
.L43:
	.body
	.copy_state 8
	.mib
	nop 0
	cmp.ltu p6, p7 = 32, r14
	(p6) br.cond.dptk .L47
	.mmi
	adds r15 = 24, r23
	shladd r14 = r14, 3, r0
	adds r17 = 8, r23
	.mmi
	shladd r16 = r20, 2, r0
	adds r18 = 16, r23
	shladd r20 = r20, 3, r0
	;;
	.mmi
	nop 0
	ld8 r22 = [r15]
	addl r15 = 2, r0
	.mmi
	adds r14 = -65, r14
	ld8 r19 = [r17]
	sub r16 = 32, r16
	;;
	.mii
	nop 0
	sxt4 r14 = r14
	sxt4 r16 = r16
	.mmb
	ld8 r21 = [r18]
	ld8 r18 = [r23]
	nop 0
	;;
	.mii
	nop 0
	shl r15 = r15, r14
	shl r14 = r19, r16
	.mii
	nop 0
	shr r18 = r18, r20
	shl r17 = r21, r16
	;;
	.mii
	nop 0
	shl r14 = r14, r16
	shr r19 = r19, r20
	.mii
	adds r15 = -1, r15
	shl r17 = r17, r16
	shr r21 = r21, r20
	;;
	.mmi
	nop 0
	and r15 = r22, r15
	or r8 = r14, r18
	.mmi
	or r9 = r17, r19
	;;
	nop 0
	shl r14 = r15, r16
	.mii
	nop 0
	shr r11 = r15, r20
	;;
	shl r14 = r14, r16
	;;
	.mii
	or r10 = r14, r21
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.label_state 9
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
.L47:
	.body
	.copy_state 9
	.mmb
	shladd r16 = r14, 3, r0
	adds r14 = 32, r23
	nop 0
	.mmi
	adds r18 = 8, r23
	adds r19 = 16, r23
	shladd r15 = r20, 3, r0
	;;
	.mfi
	ld8 r22 = [r14]
	nop 0
	adds r14 = 24, r23
	.mmi
	ld8 r20 = [r18]
	adds r16 = -129, r16
	mov r17 = r15
	.mfi
	ld8 r18 = [r19]
	nop 0
	sub r15 = 64, r15
	;;
	.mmi
	ld8 r19 = [r14]
	addl r14 = 2, r0
	sxt4 r16 = r16
	.mii
	nop 0
	sxt4 r15 = r15
	;;
	shl r21 = r20, r15
	.mii
	nop 0
	shr r20 = r20, r17
	shl r14 = r14, r16
	.mii
	ld8 r16 = [r23]
	shr r23 = r19, r17
	shl r19 = r19, r15
	;;
	.mii
	nop 0
	shr r16 = r16, r17
	shr r17 = r18, r17
	.mii
	adds r14 = -1, r14
	shl r18 = r18, r15
	;;
	and r14 = r22, r14
	.mmi
	nop 0
	or r8 = r21, r16
	or r10 = r19, r17
	.mii
	nop 0
	or r9 = r18, r20
	;;
	shl r14 = r14, r15
	;;
	.mii
	or r11 = r14, r23
	mov ar.pfs = r42
	mov b0 = r41
	.mib
	nop 0
	.restore sp
	mov r12 = r43
	br.ret.sptk.many b0
	.endp vacall_receiver#
	.ident	"GCC: (GNU) 4.0.1"
