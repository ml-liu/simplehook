#include "asm-hppa.h"
	.LEVEL 1.1
	IMPORT_MILLICODE($$dyncall)
	TEXT1()
	TEXT2()
	.align 4
GLOBL(vacall_receiver)
		DECLARE_FUNCTION(vacall_receiver)
DEF(vacall_receiver)
	.PROC
	.CALLINFO FRAME=192,CALLS,SAVE_RP,SAVE_SP,ENTRY_GR=3
	.ENTRY
	copy %r3,%r1
	stw %r2,-20(%r30)
	copy %r30,%r3
	stwm %r1,192(%r30)
	addil LR!vacall_function-$global$,%r27
	ldo -32(%r3),%r2
	ldo 16(%r3),%r22
	sub %r22,%r2,%r20
	ldo 104(%r3),%r19
	ldo 72(%r3),%r21
	ldo 80(%r20),%r31
	fstds %fr5,-16(%r19)
	ldo 64(%r20),%r20
	ldo -48(%r3),%r19
	stw %r26,-36(%r3)
	copy %r22,%r26
	stw %r20,56(%r3)
	fstws %fr7L,-8(%r21)
	stw %r19,52(%r3)
	stw %r31,60(%r3)
	stw %r25,-40(%r3)
	stw %r24,-44(%r3)
	stw %r23,-48(%r3)
	fstds %fr7,8(%r21)
	fstws %fr4L,4(%r21)
	fstws %fr5L,0(%r21)
	fstws %fr6L,-4(%r21)
	stw %r0,16(%r3)
	stw %r2,32(%r3)
	stw %r0,36(%r3)
	stw %r0,40(%r3)
	stw %r28,48(%r3)
	ldw RR!vacall_function-$global$(%r1),%r22
	.CALL	ARGW0=GR
	bl $$dyncall,%r31
	copy %r31,%r2
	ldw 40(%r3),%r20
	comib,= 0,%r20,L(48)
	ldw -20(%r3),%r2
	comib,= 1,%r20,L(49)
	ldb 24(%r3),%r19
	comib,=,n 2,%r20,L(49)
	comib,=,n 3,%r20,L(43)
	comib,=,n 4,%r20,L(44)
	comib,=,n 5,%r20,L(45)
	comib,=,n 6,%r20,L(41)
	comib,=,n 7,%r20,L(41)
	comib,=,n 8,%r20,L(41)
	comib,= 9,%r20,L(41)
	ldo -10(%r20),%r19
	comib,<<,n 1,%r19,L(22)
	ldw 24(%r3),%r28
DEF(L(40))
	ldw 28(%r3),%r29
DEF(L(1))
	ldw -20(%r3),%r2
DEF(L(48))
	ldo 64(%r3),%r30
	bv %r0(%r2)
	ldwm -64(%r30),%r3
DEF(L(22))
	comib,= 12,%r20,L(46)
	ldo 40(%r3),%r19
	comib,=,n 13,%r20,L(47)
	comib,=,n 14,%r20,L(1)
	ldw 24(%r3),%r28
	comib,<> 15,%r20,L(48)
	ldw -20(%r3),%r2
	ldw 16(%r3),%r19
	bb,>= %r19,30,L(1)
	ldw 44(%r3),%r2
	ldo -1(%r2),%r19
	comib,<< 7,%r19,L(1)
	ldw 36(%r3),%r19
	extru %r19,31,2,%r22
	copy %r19,%r31
	depi 0,31,2,%r31
	comib,<< 4,%r2,L(33)
	addl %r22,%r2,%r1
	zdep %r22,28,29,%r22
	mtsar %r22
	zvdepi 2,32,%r19
	comib,<< 4,%r1,L(34)
	ldo -1(%r19),%r22
	ldw 0(%r31),%r19
	zdep %r1,28,29,%r20
	ldo -1(%r20),%r20
	and %r19,%r22,%r19
	mtsar %r20
	vextrs %r19,32,%r19
	movb,tr %r19,%r28,L(48)
	ldw -20(%r3),%r2
DEF(L(34))
	ldw 0(%r31),%r19
	zdep %r1,28,29,%r21
	ldw 4(%r31),%r20
	and %r19,%r22,%r19
	ldo -33(%r21),%r31
	subi 63,%r21,%r21
	mtsar %r21
	zvdep %r19,32,%r19
	mtsar %r31
	vextrs %r20,32,%r20
DEF(L(39))
	b L(1)
	or %r20,%r19,%r28
DEF(L(33))
	zdep %r22,28,29,%r22
	mtsar %r22
	zvdepi 2,32,%r19
	comib,<< 8,%r1,L(37)
	ldo -1(%r19),%r2
	ldw 0(%r31),%r21
	zdep %r1,29,30,%r19
	and %r21,%r2,%r21
	ldw 4(%r31),%r22
	subi 47,%r19,%r2
	zdep %r1,28,29,%r19
	mtsar %r2
	ldo -33(%r19),%r19
	zvdep %r21,32,%r20
	zvdep %r20,32,%r20
	mtsar %r19
	vextrs %r22,32,%r22
	vextrs %r21,32,%r21
	movb,tr %r21,%r28,L(1)
	or %r20,%r22,%r29
DEF(L(37))
	ldw 0(%r31),%r20
	zdep %r1,28,29,%r22
	ldw 8(%r31),%r21
	and %r20,%r2,%r20
	ldo -65(%r22),%r2
	ldw 4(%r31),%r19
	mtsar %r2
	subi 95,%r22,%r31
	vextrs %r21,32,%r21
	mtsar %r31
	zvdep %r19,32,%r22
	zvdep %r20,32,%r20
	or %r22,%r21,%r29
	mtsar %r2
	b L(39)
	vextrs %r19,32,%r19
DEF(L(41))
	b L(1)
	ldw 24(%r3),%r28
DEF(L(47))
	ldw 24(%r3),%r28
	b L(40)
	fldds -16(%r19),%fr4
DEF(L(46))
	ldw 24(%r3),%r28
	b L(1)
	fldws -16(%r19),%fr4L
DEF(L(45))
	b L(1)
	ldh 24(%r3),%r28
DEF(L(44))
	ldh 24(%r3),%r19
	b L(1)
	extrs %r19,31,16,%r28
DEF(L(43))
	b L(1)
	ldb 24(%r3),%r28
DEF(L(49))
	b L(1)
	extrs %r19,31,8,%r28
	.EXIT
	.PROCEND
DEF(L(fe1))
	FUNEND(vacall_receiver)
IMPORT_DATA(vacall_function)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
