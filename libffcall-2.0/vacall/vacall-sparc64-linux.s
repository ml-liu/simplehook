	.file	"vacall-sparc64.c"
	.section	".text"
	.align 4
	.global vacall_receiver
	.type	vacall_receiver, #function
	.proc	020
vacall_receiver:
	.register	%g2, #scratch
	.register	%g3, #scratch
	save	%sp, -448, %sp
	add	%fp, 2175, %g1
	stx	%i0, [%fp+2175]
	stx	%i1, [%fp+2183]
	stx	%i2, [%fp+2191]
	stx	%i3, [%fp+2199]
	stx	%i4, [%fp+2207]
	stx	%i5, [%fp+2215]
	std	%f0, [%fp+1903]
	std	%f2, [%fp+1911]
	std	%f4, [%fp+1919]
	std	%f6, [%fp+1927]
	std	%f8, [%fp+1935]
	std	%f10, [%fp+1943]
	std	%f12, [%fp+1951]
	std	%f14, [%fp+1959]
	std	%f16, [%fp+1967]
	std	%f18, [%fp+1975]
	std	%f20, [%fp+1983]
	std	%f22, [%fp+1991]
	std	%f24, [%fp+1999]
	std	%f26, [%fp+2007]
	std	%f28, [%fp+2015]
	std	%f30, [%fp+2023]
	st	%f1, [%fp+1835]
	st	%f3, [%fp+1839]
	st	%f5, [%fp+1843]
	st	%f7, [%fp+1847]
	st	%f9, [%fp+1851]
	st	%f11, [%fp+1855]
	st	%f13, [%fp+1859]
	st	%f15, [%fp+1863]
	st	%f17, [%fp+1867]
	st	%f19, [%fp+1871]
	st	%f21, [%fp+1875]
	sethi	%lm(vacall_function), %g2
	st	%f23, [%fp+1879]
	stx	%g1, [%fp+1799]
	st	%f25, [%fp+1883]
	st	%f27, [%fp+1887]
	st	%f29, [%fp+1891]
	st	%f31, [%fp+1895]
	st	%g0, [%fp+1775]
	stx	%g0, [%fp+1807]
	st	%g0, [%fp+1815]
	st	%g0, [%fp+1831]
	sethi	%hh(vacall_function), %g1
	or	%g1, %hm(vacall_function), %g1
	sllx	%g1, 32, %g1
	add	%g1, %g2, %g1
	ldx	[%g1+%lo(vacall_function)], %g3
	call	%g3, 0
	 add	%fp, 1775, %o0
	lduw	[%fp+1815], %g1
	cmp	%g1, 0
	be,pn	%icc, .LL61
	 cmp	%g1, 1
	be,pn	%icc, .LL50
	 cmp	%g1, 2
	be,pn	%icc, .LL50
	 cmp	%g1, 3
	be,pn	%icc, .LL53
	 cmp	%g1, 4
	be,pn	%icc, .LL54
	 cmp	%g1, 5
	be,pn	%icc, .LL55
	 cmp	%g1, 6
	be,pn	%icc, .LL56
	 cmp	%g1, 7
	be,pn	%icc, .LL57
	 cmp	%g1, 8
	be,pn	%icc, .LL51
	 cmp	%g1, 9
	be,pn	%icc, .LL51
	 cmp	%g1, 10
	be,pn	%icc, .LL51
	 cmp	%g1, 11
	be,pn	%icc, .LL51
	 cmp	%g1, 12
	be,pn	%icc, .LL58
	 cmp	%g1, 13
	be,pn	%icc, .LL59
	 cmp	%g1, 14
	be,pn	%icc, .LL51
	 cmp	%g1, 15
	bne,pt	%icc, .LL61
	 lduw	[%fp+1775], %g1
	andcc	%g1, 1024, %g0
	be,pn	%xcc, .LL61
	 ldx	[%fp+1823], %g5
	add	%g5, -1, %g1
	cmp	%g1, 31
	bgu,pn	%xcc, .LL61
	 ldx	[%fp+1807], %g1
	cmp	%g5, 8
	and	%g1, 7, %o2
	and	%g1, -8, %l0
	bgu,pt	%xcc, .LL35
	 add	%g5, %o2, %g2
	cmp	%g2, 8
	bgu,pt	%xcc, .LL37
	 sllx	%o2, 3, %g4
	sllx	%g2, 3, %g2
	ldx	[%l0], %g3
	sub	%g0, %g2, %g2
	mov	-1, %g1
	sllx	%g1, %g2, %g1
	and	%g1, %g3, %g1
	return	%i7+8
	 sllx	%g1, %g4, %o0
.LL47:
	ldx	[%l0], %g1
	sllx	%g1, %o4, %g1
	ldx	[%l0+8], %g4
	ldx	[%l0+16], %g5
	sllx	%g4, %o4, %o1
	sllx	%g5, %o4, %o0
	ldx	[%l0+24], %o5
	sllx	%g2, 3, %o3
	sllx	%o5, %o4, %o7
	ldx	[%l0+32], %o2
	sub	%g0, %o3, %o3
	mov	64, %g3
	sub	%g3, %o4, %g3
	srax	%g4, %g3, %g4
	srax	%g5, %g3, %g5
	or	%g1, %g4, %i0
	srax	%o5, %g3, %o5
	mov	-1, %g1
	or	%o1, %g5, %i1
	sllx	%g1, %o3, %g1
	or	%o0, %o5, %i2
	and	%g1, %o2, %g1
	srax	%g1, %g3, %g1
	or	%o7, %g1, %i3
.LL61:
	return	%i7+8
	 nop
.LL50:
	ldsb	[%fp+1783], %i0
	return	%i7+8
	 nop
.LL54:
	ldsh	[%fp+1783], %i0
	return	%i7+8
	 nop
.LL53:
	ldub	[%fp+1783], %i0
	return	%i7+8
	 nop
.LL51:
	ldx	[%fp+1783], %i0
	return	%i7+8
	 nop
.LL55:
	lduh	[%fp+1783], %i0
	return	%i7+8
	 nop
.LL56:
	ldsw	[%fp+1783], %i0
	return	%i7+8
	 nop
.LL57:
	lduw	[%fp+1783], %i0
	return	%i7+8
	 nop
.LL58:
	ld	[%fp+1783], %f0
	return	%i7+8
	 nop
.LL59:
	ldd	[%fp+1783], %f0
	return	%i7+8
	 nop
.LL35:
	cmp	%g5, 16
	bgu,pt	%xcc, .LL39
	 cmp	%g5, 24
	cmp	%g2, 16
	bgu,pt	%xcc, .LL41
	 sllx	%o2, 3, %o5
	sllx	%g2, 3, %g3
	ldx	[%l0+8], %g2
	sll	%o2, 3, %g5
	sllx	%o2, 2, %o5
	sub	%g0, %g3, %g3
	ldx	[%l0], %g4
	mov	-1, %g1
	sllx	%g4, %g5, %g4
	sllx	%g1, %g3, %g1
	and	%g1, %g2, %g1
	mov	32, %g2
	sllx	%g1, %g5, %i1
	sub	%g2, %o5, %g2
	srax	%g1, %g2, %g1
	srax	%g1, %g2, %g1
	return	%i7+8
	 or	%g4, %g1, %o0
.LL37:
	sllx	%g2, 3, %g3
	ldx	[%l0+8], %g5
	sub	%g0, %g3, %g3
	sub	%g0, %g4, %o5
	ldx	[%l0], %g2
	mov	-1, %g1
	sllx	%g2, %g4, %g2
	sllx	%g1, %g3, %g1
	and	%g1, %g5, %g1
	srax	%g1, %o5, %g1
	return	%i7+8
	 or	%g2, %g1, %o0
.LL39:
	bgu,pt	%xcc, .LL43
	 cmp	%g2, 32
	cmp	%g2, 24
	bgu,pt	%xcc, .LL45
	 sllx	%o2, 3, %o4
	sllx	%o2, 2, %g1
	sll	%o2, 3, %g5
	sllx	%g2, 3, %o5
	ldx	[%l0+8], %g3
	ldx	[%l0+16], %o4
	sllx	%g3, %g5, %o3
	sub	%g0, %o5, %o5
	mov	32, %g4
	ldx	[%l0], %g2
	sub	%g4, %g1, %g4
	sllx	%g2, %g5, %g2
	srax	%g3, %g4, %g3
	mov	-1, %g1
	srax	%g3, %g4, %g3
	sllx	%g1, %o5, %g1
	and	%g1, %o4, %g1
	sllx	%g1, %g5, %i2
	srax	%g1, %g4, %g1
	srax	%g1, %g4, %g1
	or	%o3, %g1, %i1
	return	%i7+8
	 or	%g2, %g3, %o0
.LL41:
	sllx	%g2, 3, %g5
	ldx	[%l0+8], %g3
	ldx	[%l0+16], %o4
	sllx	%g3, %o5, %o3
	sub	%g0, %g5, %g5
	mov	64, %g4
	ldx	[%l0], %g2
	sub	%g4, %o5, %g4
	sllx	%g2, %o5, %g2
	srax	%g3, %g4, %g3
	mov	-1, %g1
	sllx	%g1, %g5, %g1
	and	%g1, %o4, %g1
	srax	%g1, %g4, %g1
	or	%o3, %g1, %i1
	return	%i7+8
	 or	%g2, %g3, %o0
.LL45:
	ldx	[%l0], %g1
	sllx	%g1, %o4, %g1
	ldx	[%l0+8], %g3
	ldx	[%l0+16], %g4
	sllx	%g3, %o4, %o3
	sllx	%g4, %o4, %o1
	sllx	%g2, 3, %o5
	ldx	[%l0+24], %o2
	sub	%g0, %o5, %o5
	mov	64, %g5
	sub	%g5, %o4, %g5
	srax	%g3, %g5, %g3
	srax	%g4, %g5, %g4
	or	%g1, %g3, %i0
	or	%o3, %g4, %i1
	mov	-1, %g1
	sllx	%g1, %o5, %g1
	and	%g1, %o2, %g1
	srax	%g1, %g5, %g1
	or	%o1, %g1, %i2
	return	%i7+8
	 nop
.LL43:
	bgu,pt	%xcc, .LL47
	 sllx	%o2, 3, %o4
	sll	%o2, 3, %o5
	ldx	[%l0], %g1
	sllx	%g1, %o5, %g1
	sllx	%o2, 2, %o4
	sllx	%g2, 3, %g5
	ldx	[%l0+8], %g3
	ldx	[%l0+16], %g4
	sllx	%g3, %o5, %o2
	sllx	%g4, %o5, %o1
	ldx	[%l0+24], %o3
	sub	%g0, %g5, %g5
	mov	32, %g2
	sub	%g2, %o4, %g2
	srax	%g3, %g2, %g3
	srax	%g4, %g2, %g4
	srax	%g3, %g2, %g3
	srax	%g4, %g2, %g4
	or	%g1, %g3, %i0
	or	%o2, %g4, %i1
	mov	-1, %g1
	sllx	%g1, %g5, %g1
	and	%g1, %o3, %g1
	sllx	%g1, %o5, %i3
	srax	%g1, %g2, %g1
	srax	%g1, %g2, %g1
	or	%o1, %g1, %i2
	return	%i7+8
	 nop
	.size	vacall_receiver, .-vacall_receiver
	.ident	"GCC: (GNU) 4.0.2"
	.section	".note.GNU-stack"
