	.file	"avcall-sparc64.c"
	.section	".text"
	.align 4
	.global avcall_call
	.type	avcall_call, #function
	.proc	04
avcall_call:
	.register	%g2, #scratch
	.register	%g3, #scratch
	save	%sp, -192, %sp
	ldx	[%i0+48], %g2
	ldx	[%i0+40], %g1
	lduw	[%i0+68], %g3
	sub	%g1, %g2, %g1
	cmp	%g3, 0
	be,pt	%icc, .LL2
	 srlx	%g1, 3, %o7
	andcc	%g3, 1, %g0
	bne,pt	%xcc, .LL100
	 andcc	%g3, 2, %g0
	bne,pt	%xcc, .LL101
	 andcc	%g3, 4, %g0
.LL130:
	bne,pt	%xcc, .LL102
	 andcc	%g3, 8, %g0
.LL129:
	bne,pt	%xcc, .LL103
	 andcc	%g3, 16, %g0
.LL128:
	bne,pt	%xcc, .LL104
	 andcc	%g3, 32, %g0
.LL127:
	bne,pt	%xcc, .LL105
	 andcc	%g3, 64, %g0
.LL126:
	bne,pt	%xcc, .LL106
	 andcc	%g3, 128, %g0
.LL125:
	bne,pt	%xcc, .LL107
	 andcc	%g3, 256, %g0
.LL124:
	bne,pt	%xcc, .LL108
	 andcc	%g3, 512, %g0
.LL123:
	bne,pt	%xcc, .LL109
	 andcc	%g3, 1024, %g0
.LL134:
	bne,pt	%xcc, .LL110
	 andcc	%g3, 2048, %g0
.LL133:
	bne,pt	%xcc, .LL111
	 sethi	%hi(4096), %g1
.LL132:
	andcc	%g3, %g1, %g0
	bne,pt	%icc, .LL112
	 sethi	%hi(8192), %g1
.LL131:
	andcc	%g3, %g1, %g0
	bne,pt	%icc, .LL113
	 sethi	%hi(16384), %g1
.LL136:
	andcc	%g3, %g1, %g0
	bne,pt	%icc, .LL114
	 sethi	%hi(32768), %g1
.LL135:
	andcc	%g3, %g1, %g0
	bne,pt	%icc, .LL115
	 nop
.LL2:
	cmp	%o7, 6
.LL137:
	bg,pn	%icc, .LL120
	 add	%o7, -6, %g1
	ldx	[%i0+48], %g3
.LL122:
	ldx	[%g3+40], %o5
.LL119:
	ldx	[%i0+8], %g1
	ldx	[%g3], %o0
	ldx	[%g3+8], %o1
	ldx	[%g3+16], %o2
	ldx	[%g3+24], %o3
	call	%g1, 0
	 ldx	[%g3+32], %o4
	mov	%o0, %l3
	nop
	lduw	[%i0+24], %g1
	cmp	%g1, 1
	be,pn	%icc, .LL38
	 cmp	%g1, 0
	be,a,pt	%icc, .LL121
	 ldx	[%i0+16], %g1
	cmp	%g1, 2
	be,pn	%icc, .LL92
	 cmp	%g1, 3
	be,pn	%icc, .LL92
	 cmp	%g1, 4
	be,pn	%icc, .LL92
	 cmp	%g1, 5
	be,pn	%icc, .LL93
	 cmp	%g1, 6
	be,pn	%icc, .LL93
	 cmp	%g1, 7
	be,pn	%icc, .LL94
	 cmp	%g1, 8
	be,pn	%icc, .LL94
	 cmp	%g1, 9
	be,pn	%icc, .LL98
	 cmp	%g1, 10
	be,pn	%icc, .LL98
	 cmp	%g1, 11
	be,pn	%icc, .LL98
	 cmp	%g1, 12
	be,pn	%icc, .LL98
	 cmp	%g1, 13
	be,pn	%icc, .LL117
	 cmp	%g1, 14
	be,pn	%icc, .LL118
	 cmp	%g1, 15
	be,pn	%icc, .LL98
	 cmp	%g1, 16
	bne,pt	%icc, .LL38
	 nop
	lduw	[%i0], %g1
	andcc	%g1, 512, %g0
	be,pn	%xcc, .LL38
	 nop
	ldx	[%i0+32], %g2
	add	%g2, -1, %g1
	cmp	%g1, 31
	bgu,pn	%xcc, .LL38
	 cmp	%g2, 8
	ldx	[%i0+16], %g1
	and	%g1, 7, %g5
	and	%g1, -8, %i0
	bgu,pt	%xcc, .LL73
	 add	%g2, %g5, %g4
	cmp	%g4, 8
	bgu,pt	%xcc, .LL75
	 sllx	%g5, 3, %g2
	sllx	%g5, 3, %g3
	sllx	%g4, 3, %g4
	ldx	[%i0], %g5
	srax	%o0, %g3, %o7
	sub	%g0, %g4, %g4
	xor	%g5, %o7, %o7
	xnor	%g0, %g3, %g3
	mov	2, %g1
	mov	1, %g2
	sllx	%g1, %g3, %g1
	sllx	%g2, %g4, %g2
	sub	%g1, %g2, %g1
	and	%g1, %o7, %g1
	xor	%g5, %g1, %g5
	stx	%g5, [%i0]
.LL38:
	return	%i7+8
	 mov	0, %o0
.LL98:
	ldx	[%i0+16], %g1
.LL121:
	stx	%l3, [%g1]
	return	%i7+8
	 mov	0, %o0
.LL115:
	ldd [%g2+120],%f30
	cmp	%o7, 6
	ble,a,pt %icc, .LL122
	 ldx	[%i0+48], %g3
	add	%o7, -6, %g1
.LL120:
	sra	%g1, 0, %g1
	sllx	%g1, 3, %g1
	add	%g1, 15, %g1
	and	%g1, -16, %g1
	mov	6, %g4
	sub	%sp, %g1, %sp
	ldx	[%i0+48], %g3
	add	%sp, 2238, %g1
	and	%g1, -16, %g1
	add	%g1, -48, %g5
.LL37:
	sra	%g4, 0, %g1
	add	%g4, 1, %g4
	sllx	%g1, 3, %g1
	cmp	%o7, %g4
	ldx	[%g1+%g3], %g2
	bne,pt	%icc, .LL37
	 stx	%g2, [%g5+%g1]
	ba,pt	%xcc, .LL119
	 ldx	[%g3+40], %o5
.LL107:
	ldd [%g2+56],%f14
	andcc	%g3, 256, %g0
	be,pt	%xcc, .LL123
	 andcc	%g3, 512, %g0
	ba,pt	%xcc, .LL108
	 nop
.LL106:
	ldd [%g2+48],%f12
	andcc	%g3, 128, %g0
	be,pt	%xcc, .LL124
	 andcc	%g3, 256, %g0
	ba,pt	%xcc, .LL107
	 nop
.LL105:
	ldd [%g2+40],%f10
	andcc	%g3, 64, %g0
	be,pt	%xcc, .LL125
	 andcc	%g3, 128, %g0
	ba,pt	%xcc, .LL106
	 nop
.LL104:
	ldd [%g2+32],%f8
	andcc	%g3, 32, %g0
	be,pt	%xcc, .LL126
	 andcc	%g3, 64, %g0
	ba,pt	%xcc, .LL105
	 nop
.LL103:
	ldd [%g2+24],%f6
	andcc	%g3, 16, %g0
	be,pt	%xcc, .LL127
	 andcc	%g3, 32, %g0
	ba,pt	%xcc, .LL104
	 nop
.LL102:
	ldd [%g2+16],%f4
	andcc	%g3, 8, %g0
	be,pt	%xcc, .LL128
	 andcc	%g3, 16, %g0
	ba,pt	%xcc, .LL103
	 nop
.LL101:
	ldd [%g2+8],%f2
	andcc	%g3, 4, %g0
	be,pt	%xcc, .LL129
	 andcc	%g3, 8, %g0
	ba,pt	%xcc, .LL102
	 nop
.LL100:
	ldd [%g2+0],%f0
	andcc	%g3, 2, %g0
	be,pt	%xcc, .LL130
	 andcc	%g3, 4, %g0
	ba,pt	%xcc, .LL101
	 nop
.LL111:
	ldd [%g2+88],%f22
	sethi	%hi(4096), %g1
	andcc	%g3, %g1, %g0
	be,pt	%icc, .LL131
	 sethi	%hi(8192), %g1
	ba,pt	%xcc, .LL112
	 nop
.LL110:
	ldd [%g2+80],%f20
	andcc	%g3, 2048, %g0
	be,pt	%xcc, .LL132
	 sethi	%hi(4096), %g1
	ba,pt	%xcc, .LL111
	 nop
.LL109:
	ldd [%g2+72],%f18
	andcc	%g3, 1024, %g0
	be,pt	%xcc, .LL133
	 andcc	%g3, 2048, %g0
	ba,pt	%xcc, .LL110
	 nop
.LL108:
	ldd [%g2+64],%f16
	andcc	%g3, 512, %g0
	be,pt	%xcc, .LL134
	 andcc	%g3, 1024, %g0
	ba,pt	%xcc, .LL109
	 nop
.LL113:
	ldd [%g2+104],%f26
	sethi	%hi(16384), %g1
	andcc	%g3, %g1, %g0
	be,pt	%icc, .LL135
	 sethi	%hi(32768), %g1
	ba,pt	%xcc, .LL114
	 nop
.LL112:
	ldd [%g2+96],%f24
	sethi	%hi(8192), %g1
	andcc	%g3, %g1, %g0
	be,pt	%icc, .LL136
	 sethi	%hi(16384), %g1
	ba,pt	%xcc, .LL113
	 nop
.LL114:
	ldd [%g2+112],%f28
	sethi	%hi(32768), %g1
	andcc	%g3, %g1, %g0
	be,pt	%icc, .LL137
	 cmp	%o7, 6
	ba,pt	%xcc, .LL115
	 nop
.LL92:
	ldx	[%i0+16], %g1
	stb	%l3, [%g1]
	return	%i7+8
	 mov	0, %o0
.LL93:
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 sth	%l3, [%g1]
.LL94:
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 st	%l3, [%g1]
.LL117:
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 st	%f0, [%g1]
.LL118:
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 std	%f0, [%g1]
.LL75:
	sllx	%g4, 3, %l0
	ldx	[%i0], %g5
	srax	%o0, %g2, %g4
	sub	%g0, %g2, %g3
	xor	%g5, %g4, %g4
	xnor	%g0, %g2, %g2
	mov	2, %g1
	sllx	%g1, %g2, %g1
	add	%g1, -1, %g1
	and	%g1, %g4, %g1
	ldx	[%i0+8], %o7
	xor	%g5, %g1, %g5
	sub	%g0, %l0, %l0
	sllx	%o0, %g3, %g3
	mov	-1, %g1
	xor	%o7, %g3, %g3
	sllx	%g1, %l0, %g1
	stx	%g5, [%i0]
	and	%g1, %g3, %g1
	xor	%o7, %g1, %o7
	ba,pt	%xcc, .LL38
	 stx	%o7, [%i0+8]
.LL73:
	cmp	%g2, 16
	bgu,pt	%xcc, .LL77
	 cmp	%g2, 24
	sll	%g5, 3, %l2
	xnor	%g0, %l2, %g2
	ldx	[%i0], %g3
	mov	2, %g1
	cmp	%g4, 16
	sllx	%g1, %g2, %g1
	srax	%o0, %l2, %g2
	add	%g1, -1, %g1
	xor	%g3, %g2, %g2
	and	%g1, %g2, %g1
	xor	%g3, %g1, %g3
	bgu,pt	%xcc, .LL79
	 stx	%g3, [%i0]
	sllx	%g5, 2, %g5
	mov	32, %g2
	sub	%g2, %g5, %g2
	ldx	[%i0+8], %g3
	sllx	%o0, %g2, %g1
	sllx	%g4, 3, %g4
	sllx	%g1, %g2, %g1
	srax	%o1, %l2, %o7
	sub	%g0, %g4, %g4
	or	%g1, %o7, %g1
	mov	-1, %g2
	xor	%g3, %g1, %g1
	sllx	%g2, %g4, %g2
	and	%g2, %g1, %g2
	xor	%g3, %g2, %g3
	ba,pt	%xcc, .LL38
	 stx	%g3, [%i0+8]
.LL77:
	bgu,pt	%xcc, .LL81
	 sll	%g5, 3, %l4
	sll	%g5, 3, %l2
	xnor	%g0, %l2, %g2
	ldx	[%i0], %g3
	mov	2, %g1
	cmp	%g4, 24
	sllx	%g1, %g2, %g1
	srax	%o0, %l2, %g2
	add	%g1, -1, %g1
	xor	%g3, %g2, %g2
	and	%g1, %g2, %g1
	xor	%g3, %g1, %g3
	bgu,pt	%xcc, .LL83
	 stx	%g3, [%i0]
	sllx	%g5, 2, %g2
	mov	32, %g1
	sub	%g1, %g2, %g1
	ldx	[%i0+16], %o7
	sllx	%g4, 3, %g5
	sllx	%o0, %g1, %g3
	sllx	%o1, %g1, %g2
	sllx	%g3, %g1, %g3
	sllx	%g2, %g1, %g2
	srax	%o2, %l2, %l0
	sub	%g0, %g5, %g5
	or	%g2, %l0, %g2
	srax	%o1, %l2, %g4
	xor	%o7, %g2, %g2
	or	%g3, %g4, %g3
	mov	-1, %g1
	stx	%g3, [%i0+8]
	sllx	%g1, %g5, %g1
	and	%g1, %g2, %g1
	xor	%o7, %g1, %o7
	ba,pt	%xcc, .LL38
	 stx	%o7, [%i0+16]
.LL79:
	srax	%o1, %l2, %g5
	mov	64, %g1
	sub	%g1, %l2, %g1
	sllx	%o1, %g1, %g2
	sllx	%o0, %g1, %g1
	or	%g1, %g5, %g1
	sllx	%g4, 3, %g3
	stx	%g1, [%i0+8]
	ldx	[%i0+16], %g4
	sub	%g0, %g3, %g3
	xor	%g4, %g2, %g2
	mov	-1, %g1
	sllx	%g1, %g3, %g1
	and	%g1, %g2, %g1
	xor	%g4, %g1, %g4
	ba,pt	%xcc, .LL38
	 stx	%g4, [%i0+16]
.LL83:
	sllx	%g4, 3, %g5
	srax	%o2, %l2, %l0
	mov	64, %g1
	sub	%g1, %l2, %g1
	sllx	%o2, %g1, %g4
	sllx	%o0, %g1, %g2
	sllx	%o1, %g1, %g1
	or	%g1, %l0, %g1
	ldx	[%i0+24], %o7
	sub	%g0, %g5, %g5
	xor	%o7, %g4, %g4
	stx	%g1, [%i0+16]
	srax	%o1, %l2, %g3
	mov	-1, %g1
	or	%g2, %g3, %g2
	sllx	%g1, %g5, %g1
	stx	%g2, [%i0+8]
	and	%g1, %g4, %g1
	xor	%o7, %g1, %o7
	ba,pt	%xcc, .LL38
	 stx	%o7, [%i0+24]
.LL81:
	xnor	%g0, %l4, %g2
	ldx	[%i0], %g3
	mov	2, %g1
	cmp	%g4, 32
	sllx	%g1, %g2, %g1
	srax	%o0, %l4, %g2
	add	%g1, -1, %g1
	xor	%g3, %g2, %g2
	and	%g1, %g2, %g1
	xor	%g3, %g1, %g3
	bgu,pt	%xcc, .LL85
	 stx	%g3, [%i0]
	sllx	%g5, 2, %g2
	mov	32, %g1
	sub	%g1, %g2, %g1
	ldx	[%i0+24], %l0
	sllx	%g4, 3, %l1
	sllx	%o0, %g1, %g3
	sllx	%o1, %g1, %g4
	sllx	%g3, %g1, %g3
	sllx	%g4, %g1, %g4
	sllx	%o2, %g1, %g2
	srax	%o3, %l4, %l2
	sllx	%g2, %g1, %g2
	sub	%g0, %l1, %l1
	or	%g2, %l2, %g2
	srax	%o1, %l4, %g5
	xor	%l0, %g2, %g2
	or	%g3, %g5, %g3
	srax	%o2, %l4, %o7
	mov	-1, %g1
	or	%g4, %o7, %g4
	sllx	%g1, %l1, %g1
	stx	%g3, [%i0+8]
	and	%g1, %g2, %g1
	stx	%g4, [%i0+16]
	xor	%l0, %g1, %l0
	ba,pt	%xcc, .LL38
	 stx	%l0, [%i0+24]
.LL85:
	srax	%o3, %l4, %l2
	mov	64, %g1
	sub	%g1, %l4, %g1
	sllx	%o3, %g1, %o7
	sllx	%o0, %g1, %g2
	sllx	%o1, %g1, %g3
	sllx	%o2, %g1, %g1
	or	%g1, %l2, %g1
	ldx	[%i0+32], %l0
	sllx	%g4, 3, %l1
	xor	%l0, %o7, %o7
	sub	%g0, %l1, %l1
	stx	%g1, [%i0+24]
	srax	%o1, %l4, %g4
	srax	%o2, %l4, %g5
	or	%g2, %g4, %g2
	or	%g3, %g5, %g3
	mov	-1, %g1
	stx	%g2, [%i0+8]
	sllx	%g1, %l1, %g1
	stx	%g3, [%i0+16]
	and	%g1, %o7, %g1
	xor	%l0, %g1, %l0
	ba,pt	%xcc, .LL38
	 stx	%l0, [%i0+32]
	.size	avcall_call, .-avcall_call
	.ident	"GCC: (GNU) 4.0.2"
	.section	".note.GNU-stack"
