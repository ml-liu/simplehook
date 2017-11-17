#include "asm-hppa.h"
	.LEVEL 1.1
	IMPORT_MILLICODE($$dyncall)
	TEXT1()
	TEXT2()
	.align 4
		DECLARE_FUNCTION(callback_receiver)
DEF(callback_receiver)
	.PROC
	.CALLINFO FRAME=192,CALLS,SAVE_RP,SAVE_SP,ENTRY_GR=5
	.ENTRY
	copy %r3,%r1
	stw %r2,-20(%r30)
	copy %r30,%r3
	stwm %r1,192(%r30)
	ldo -32(%r3),%r2
	ldo 16(%r3),%r21
	ldo 88(%r3),%r20
	stw %r5,96(%r3)
	sub %r21,%r2,%r31
	copy %r19,%r5
	stw %r4,100(%r3)
	ldo 80(%r31),%r4
	ldo 64(%r31),%r31
	stw %r19,-32(%r30)
	stw %r25,-40(%r3)
	copy %r21,%r25
	ldo 80(%r3),%r21
	fstds %fr5,0(%r20)
	ldo 76(%r3),%r20
	fstws %fr4L,0(%r20)
	ldo 68(%r3),%r20
	stw %r0,36(%r3)
	stw %r28,48(%r3)
	fstds %fr7,0(%r21)
	ldo 72(%r3),%r21
	fstws %fr5L,0(%r21)
	ldo 64(%r3),%r21
	fstws %fr6L,0(%r20)
	ldo -48(%r3),%r20
	stw %r26,-36(%r3)
	fstws %fr7L,0(%r21)
	ldw 0(%r29),%r22
	stw %r20,52(%r3)
	stw %r31,56(%r3)
	stw %r4,60(%r3)
	stw %r24,-44(%r3)
	stw %r23,-48(%r3)
	stw %r0,16(%r3)
	stw %r2,32(%r3)
	stw %r0,40(%r3)
	ldw 4(%r29),%r26
	.CALL	ARGW0=GR
	bl $$dyncall,%r31
	copy %r31,%r2
	ldw 40(%r3),%r21
	comib,= 0,%r21,L(1)
	copy %r5,%r19
	comib,= 1,%r21,L(48)
	ldb 24(%r3),%r20
	comib,=,n 2,%r21,L(48)
	comib,=,n 3,%r21,L(43)
	comib,=,n 4,%r21,L(44)
	comib,=,n 5,%r21,L(45)
	comib,=,n 6,%r21,L(41)
	comib,=,n 7,%r21,L(41)
	comib,=,n 8,%r21,L(41)
	comib,= 9,%r21,L(41)
	ldo -10(%r21),%r20
	comib,<<,n 1,%r20,L(22)
	ldw 24(%r3),%r28
DEF(L(40))
	ldw 28(%r3),%r29
DEF(L(1))
	ldw -20(%r3),%r2
DEF(L(49))
DEF(L(50))
	ldw 96(%r3),%r5
	ldw 100(%r3),%r4
	ldo 64(%r3),%r30
	bv %r0(%r2)
	ldwm -64(%r30),%r3
DEF(L(22))
	comib,= 12,%r21,L(46)
	ldo 24(%r3),%r20
	comib,=,n 13,%r21,L(47)
	comib,=,n 14,%r21,L(1)
	ldw 24(%r3),%r28
	comib,<> 15,%r21,L(49)
	ldw -20(%r3),%r2
	ldw 16(%r3),%r20
	bb,>= %r20,30,L(49)
	ldw 44(%r3),%r4
	ldo -1(%r4),%r20
	comib,<< 7,%r20,L(50)
	ldw 36(%r3),%r20
	extru %r20,31,2,%r31
	copy %r20,%r2
	depi 0,31,2,%r2
	comib,<< 4,%r4,L(33)
	addl %r31,%r4,%r5
	zdep %r31,28,29,%r31
	mtsar %r31
	zvdepi 2,32,%r20
	comib,<< 4,%r5,L(34)
	ldo -1(%r20),%r31
	ldw 0(%r2),%r20
	zdep %r5,28,29,%r21
	ldo -1(%r21),%r21
	and %r20,%r31,%r20
	mtsar %r21
	vextrs %r20,32,%r20
	movb,tr %r20,%r28,L(49)
	ldw -20(%r3),%r2
DEF(L(34))
	ldw 0(%r2),%r20
	zdep %r5,28,29,%r22
	ldw 4(%r2),%r21
	and %r20,%r31,%r20
	ldo -33(%r22),%r2
	subi 63,%r22,%r22
	mtsar %r22
	zvdep %r20,32,%r20
	mtsar %r2
	vextrs %r21,32,%r21
DEF(L(39))
	b L(1)
	or %r21,%r20,%r28
DEF(L(33))
	zdep %r31,28,29,%r31
	mtsar %r31
	zvdepi 2,32,%r20
	comib,<< 8,%r5,L(37)
	ldo -1(%r20),%r4
	ldw 0(%r2),%r22
	zdep %r5,29,30,%r20
	and %r22,%r4,%r22
	ldw 4(%r2),%r31
	subi 47,%r20,%r4
	zdep %r5,28,29,%r20
	mtsar %r4
	ldo -33(%r20),%r20
	zvdep %r22,32,%r21
	zvdep %r21,32,%r21
	mtsar %r20
	vextrs %r31,32,%r31
	vextrs %r22,32,%r22
	movb,tr %r22,%r28,L(1)
	or %r21,%r31,%r29
DEF(L(37))
	ldw 0(%r2),%r21
	zdep %r5,28,29,%r31
	ldw 8(%r2),%r22
	and %r21,%r4,%r21
	ldo -65(%r31),%r4
	ldw 4(%r2),%r20
	mtsar %r4
	subi 95,%r31,%r2
	vextrs %r22,32,%r22
	mtsar %r2
	zvdep %r20,32,%r31
	zvdep %r21,32,%r21
	or %r31,%r22,%r29
	mtsar %r4
	b L(39)
	vextrs %r20,32,%r20
DEF(L(41))
	b L(1)
	ldw 24(%r3),%r28
DEF(L(47))
	ldw 24(%r3),%r28
	b L(40)
	fldds 0(%r20),%fr4
DEF(L(46))
	ldw 24(%r3),%r28
	b L(1)
	fldws 0(%r20),%fr4L
DEF(L(45))
	b L(1)
	ldh 24(%r3),%r28
DEF(L(44))
	ldh 24(%r3),%r20
	b L(1)
	extrs %r20,31,16,%r28
DEF(L(43))
	b L(1)
	ldb 24(%r3),%r28
DEF(L(48))
	b L(1)
	extrs %r20,31,8,%r28
	.EXIT
	.PROCEND
DEF(L(fe1))
	FUNEND(callback_receiver)
	.data
	.align 4
DEF(L(C0))
	.word	P%callback_receiver
	TEXT1()
	TEXT2()
	.align 4
GLOBL(callback_get_receiver)
		DECLARE_FUNCTION(callback_get_receiver)
DEF(callback_get_receiver)
	.PROC
	.CALLINFO FRAME=64,NO_CALLS,SAVE_SP,ENTRY_GR=3
	.ENTRY
	copy %r3,%r1
	copy %r30,%r3
	stwm %r1,64(%r30)
	addil LT!L(C0),%r19
	stw %r19,-32(%r30)
	ldw RT!L(C0)(%r1),%r1
	ldw 0(%r1),%r28
	ldo 64(%r3),%r30
	bv %r0(%r2)
	ldwm -64(%r30),%r3
	.EXIT
	.PROCEND
DEF(L(fe2))
	FUNEND(callback_get_receiver)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
