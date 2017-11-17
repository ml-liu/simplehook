#include "asm-sparc.h"
	.section	".text"
	.align 4
	.global C(avcall_call)
	DECLARE_FUNCTION(avcall_call)
	.proc	04
FUNBEGIN(avcall_call)
	!$PROLOGUE$ 0
	save	%sp, -1152, %sp
	ld	[%i0+20], %g3
	add	%sp, 68, %l1
	ld	[%i0+24], %o7
	ld	[%i0+12], %l0
	sub	%g3, %o7, %g3
	cmp	%l0, 16
	be	L(L54)
	sra	%g3, 2, %g4
L(L2):
	mov	6, %l0
	cmp	%l0, %g4
	bge	L(L49)
	ld	[%i0+24], %g1
L(L7):
	sll	%l0, 2, %g3
	ld	[%g1+%g3], %o7
	add	%l0, 1, %l0
	cmp	%l0, %g4
	bl	L(L7)
	st	%o7, [%l1+%g3]
L(L49):
	ld	[%i0+12], %g3
	cmp	%g3, 16
	be,a	L(L55)
	ld	[%i0], %g3
	ld	[%g1+20], %o5
L(L60):
	ld	[%i0+4], %g3
	ld	[%g1], %o0
	ld	[%g1+4], %o1
	ld	[%g1+8], %o2
	ld	[%g1+12], %o3
	call	%g3, 0
	ld	[%g1+16], %o4
	nop
	ld	[%i0+12], %o7
	cmp	%o7, 1
	be	L(L10)
	mov	%o0, %l0
	cmp	%o7, 0
	be,a	L(L59)
	ld	[%i0+8], %g3
	cmp	%o7, 2
	be	L(L53)
	cmp	%o7, 3
	be	L(L53)
	cmp	%o7, 4
	be	L(L53)
	cmp	%o7, 5
	be	L(L52)
	cmp	%o7, 6
	be	L(L52)
	cmp	%o7, 7
	be	L(L51)
	cmp	%o7, 8
	be	L(L51)
	cmp	%o7, 9
	be	L(L51)
	cmp	%o7, 10
	be	L(L51)
	add	%o7, -11, %g3
	cmp	%g3, 1
	bgu	L(L31)
	cmp	%o7, 13
	ld	[%i0+8], %g3
	st	%o0, [%g3]
	b	L(L10)
	st	%o1, [%g3+4]
L(L31):
	be	L(L56)
	cmp	%o7, 14
	be	L(L57)
	cmp	%o7, 15
	be	L(L51)
	cmp	%o7, 16
	bne	L(L10)
	nop
	ld	[%i0], %g3
	andcc	%g3, 2, %g0
	be	L(L10)
	nop
	ld	[%i0+16], %g3
	cmp	%g3, 1
	be	L(L53)
	cmp	%g3, 2
	be	L(L52)
	cmp	%g3, 4
	bne	L(L10)
	nop
L(L51):
	ld	[%i0+8], %g3
L(L59):
	b	L(L10)
	st	%l0, [%g3]
L(L52):
	ld	[%i0+8], %g3
	b	L(L10)
	sth	%l0, [%g3]
L(L53):
	ld	[%i0+8], %g3
	b	L(L10)
	stb	%l0, [%g3]
L(L57):
	ld	[%i0+8], %g3
	b	L(L10)
	std	%f0, [%g3]
L(L56):
	ld	[%i0], %g3
	andcc	%g3, 32, %g0
	bne,a	L(L34)
	fdtos	%f0, %f0
L(L34):
	ld	[%i0+8], %g3
	b	L(L10)
	st	%f0, [%g3]
L(L55):
	andcc	%g3, 16, %g0
	be,a	L(L60)
	ld	[%g1+20], %o5
	b	L(L58)
	ld	[%i0+16], %l0
L(L54):
	ld	[%i0+8], %g3
	b	L(L2)
	st	%g3, [%sp+64]
L(L58):
	sethi	%hi(-1614774272), %g3
	sethi	%hi(16777216), %o7
	st	%g3, [%fp-32]
	st	%o7, [%fp-28]
	sethi	%hi(-1341120512), %o7
	sethi	%hi(-2117607424), %g3
	st	%o7, [%fp-20]
	or	%g3, 8, %g3
	and	%l0, 4095, %l0
	st	%g3, [%fp-16]
	sethi	%hi(-2115502080), %o7
	st	%l0, [%fp-24]
	st	%o7, [%fp-12]
	add	%fp, -32, %g3
	iflush %g3
	add	%fp, -24, %o7
	iflush %o7
	add	%fp, -16, %g3
	iflush %g3
	add	%fp, -12, %o7
	iflush %o7
	ld	[%g1+20], %o5
	ld	[%i0+4], %g2
	ld	[%g1], %o0
	ld	[%g1+4], %o1
	ld	[%g1+8], %o2
	ld	[%g1+12], %o3
	jmp	%fp-32
	ld	[%g1+16], %o4
L(L10):
	ret
	restore %g0, 0, %o0
L(Lfe1):
	FUNEND(avcall_call)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
