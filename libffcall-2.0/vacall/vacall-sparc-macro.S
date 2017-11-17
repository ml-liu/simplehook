#include "asm-sparc.h"
#ifdef __PIC__
	.section	".text"
	.align 4
L(LGETPC0):
	retl
	add	%o7, %l7, %l7
	.align 4
	.global C(vacall_receiver)
	DECLARE_FUNCTION(vacall_receiver)
	.proc	020
FUNBEGIN(vacall_receiver)
	!$PROLOGUE$ 0
	save	%sp, -144, %sp
	sethi	%hi(C(vacall_function)), %o0
	sethi	%hi(_GLOBAL_OFFSET_TABLE_-4), %l7
	call	L(LGETPC0)
	add	%l7, %lo(_GLOBAL_OFFSET_TABLE_+4), %l7
	or	%o0, %lo(C(vacall_function)), %o0
	ld	[%l7+%o0], %o1
	st	%i2, [%fp+76]
	ld	[%o1], %o2
	add	%fp, 68, %o0
	ld	[%fp+64], %o1
	st	%o0, [%fp-32]
	st	%o1, [%fp-16]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%i5, [%fp+88]
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%g0, [%fp-48]
	st	%g0, [%fp-28]
	st	%g0, [%fp-24]
	call	%o2, 0
	add	%fp, -48, %o0
	ld	[%fp-24], %o1
	cmp	%o1, 0
	be	L(L1)
	cmp	%o1, 1
	be	L(L44)
	cmp	%o1, 2
	be	L(L44)
	cmp	%o1, 3
	be	L(L45)
	cmp	%o1, 4
	be	L(L46)
	cmp	%o1, 5
	be	L(L47)
	cmp	%o1, 6
	be	L(L43)
	cmp	%o1, 7
	be	L(L43)
	cmp	%o1, 8
	be	L(L43)
	cmp	%o1, 9
	be	L(L43)
	add	%o1, -10, %o0
	cmp	%o0, 1
	bgu	L(L22)
	cmp	%o1, 12
	ld	[%fp-40], %i0
	b	L(L1)
	ld	[%fp-36], %i1
L(L22):
	be	L(L48)
	cmp	%o1, 13
	be	L(L49)
	cmp	%o1, 14
	be	L(L43)
	cmp	%o1, 15
	bne	L(L1)
	ld	[%fp-48], %o0
	andcc	%o0, 16, %g0
	be	L(L33)
	andcc	%o0, 2, %g0
	ld	[%fp-20], %o0
	ld	[%i7+8], %o1
	and	%o0, 4095, %o0
	cmp	%o0, %o1
	bne	L(L1)
	ld	[%fp-28], %i0
	b	L(L1)
	add	%i7, 4, %i7
L(L33):
	be,a	L(L1)
	add	%i7, 4, %i7
	ld	[%fp-20], %o0
	cmp	%o0, 1
	be	L(L50)
	cmp	%o0, 2
	be	L(L51)
	cmp	%o0, 4
	bne,a	L(L1)
	add	%i7, 4, %i7
	ld	[%fp-28], %o0
	b	L(L1)
	ld	[%o0], %i0
L(L51):
	ld	[%fp-28], %o0
	b	L(L1)
	lduh	[%o0], %i0
L(L50):
	ld	[%fp-28], %o0
	b	L(L1)
	ldub	[%o0], %i0
L(L43):
	b	L(L1)
	ld	[%fp-40], %i0
L(L49):
	b	L(L1)
	ldd	[%fp-40], %f0
L(L48):
	ld	[%fp-48], %o0
	andcc	%o0, 32, %g0
	be,a	L(L1)
	ld	[%fp-40], %f0
	ld	[%fp-40], %f2
	b	L(L1)
	fstod	%f2, %f0
L(L47):
	b	L(L1)
	lduh	[%fp-40], %i0
L(L46):
	b	L(L1)
	ldsh	[%fp-40], %i0
L(L45):
	b	L(L1)
	ldub	[%fp-40], %i0
L(L44):
	ldsb	[%fp-40], %i0
L(L38):
L(L1):
	nop
	ret
	restore
L(Lfe1):
	FUNEND(vacall_receiver)
#else
	.section	".text"
	.align 4
	.global C(vacall_receiver)
	DECLARE_FUNCTION(vacall_receiver)
	.proc	020
FUNBEGIN(vacall_receiver)
	!$PROLOGUE$ 0
	save	%sp, -144, %sp
	!$PROLOGUE$ 1
	sethi	%hi(C(vacall_function)), %o0
	ld	[%o0+%lo(C(vacall_function))], %o2
	st	%i2, [%fp+76]
	add	%fp, 68, %o0
	ld	[%fp+64], %o1
	st	%o0, [%fp-32]
	st	%o1, [%fp-16]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%i5, [%fp+88]
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%g0, [%fp-48]
	st	%g0, [%fp-28]
	st	%g0, [%fp-24]
	call	%o2, 0
	add	%fp, -48, %o0
	ld	[%fp-24], %o1
	cmp	%o1, 0
	be	L(L1)
	cmp	%o1, 1
	be	L(L44)
	cmp	%o1, 2
	be	L(L44)
	cmp	%o1, 3
	be	L(L45)
	cmp	%o1, 4
	be	L(L46)
	cmp	%o1, 5
	be	L(L47)
	cmp	%o1, 6
	be	L(L43)
	cmp	%o1, 7
	be	L(L43)
	cmp	%o1, 8
	be	L(L43)
	cmp	%o1, 9
	be	L(L43)
	add	%o1, -10, %o0
	cmp	%o0, 1
	bgu	L(L22)
	cmp	%o1, 12
	ld	[%fp-40], %i0
	b	L(L1)
	ld	[%fp-36], %i1
L(L22):
	be	L(L48)
	cmp	%o1, 13
	be	L(L49)
	cmp	%o1, 14
	be	L(L43)
	cmp	%o1, 15
	bne	L(L1)
	ld	[%fp-48], %o0
	andcc	%o0, 16, %g0
	be	L(L33)
	andcc	%o0, 2, %g0
	ld	[%fp-20], %o0
	ld	[%i7+8], %o1
	and	%o0, 4095, %o0
	cmp	%o0, %o1
	bne	L(L1)
	ld	[%fp-28], %i0
	b	L(L1)
	add	%i7, 4, %i7
L(L33):
	be,a	L(L1)
	add	%i7, 4, %i7
	ld	[%fp-20], %o0
	cmp	%o0, 1
	be	L(L50)
	cmp	%o0, 2
	be	L(L51)
	cmp	%o0, 4
	bne,a	L(L1)
	add	%i7, 4, %i7
	ld	[%fp-28], %o0
	b	L(L1)
	ld	[%o0], %i0
L(L51):
	ld	[%fp-28], %o0
	b	L(L1)
	lduh	[%o0], %i0
L(L50):
	ld	[%fp-28], %o0
	b	L(L1)
	ldub	[%o0], %i0
L(L43):
	b	L(L1)
	ld	[%fp-40], %i0
L(L49):
	b	L(L1)
	ldd	[%fp-40], %f0
L(L48):
	ld	[%fp-48], %o0
	andcc	%o0, 32, %g0
	be,a	L(L1)
	ld	[%fp-40], %f0
	ld	[%fp-40], %f2
	b	L(L1)
	fstod	%f2, %f0
L(L47):
	b	L(L1)
	lduh	[%fp-40], %i0
L(L46):
	b	L(L1)
	ldsh	[%fp-40], %i0
L(L45):
	b	L(L1)
	ldub	[%fp-40], %i0
L(L44):
	ldsb	[%fp-40], %i0
L(L38):
L(L1):
	nop
	ret
	restore
L(Lfe1):
	FUNEND(vacall_receiver)
#endif
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
