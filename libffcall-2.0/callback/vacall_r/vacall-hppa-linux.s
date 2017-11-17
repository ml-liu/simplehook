	.LEVEL 1.1
	.text
	.align 4
		.type		 callback_receiver,@function
callback_receiver:
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
	comib,= 0,%r21,.L1
	copy %r5,%r19
	comib,= 1,%r21,.L48
	ldb 24(%r3),%r20
	comib,=,n 2,%r21,.L48
	comib,=,n 3,%r21,.L43
	comib,=,n 4,%r21,.L44
	comib,=,n 5,%r21,.L45
	comib,=,n 6,%r21,.L41
	comib,=,n 7,%r21,.L41
	comib,=,n 8,%r21,.L41
	comib,= 9,%r21,.L41
	ldo -10(%r21),%r20
	comib,<<,n 1,%r20,.L22
	ldw 24(%r3),%r28
.L40:
	ldw 28(%r3),%r29
.L1:
	ldw -20(%r3),%r2
.L49:
.L50:
	ldw 96(%r3),%r5
	ldw 100(%r3),%r4
	ldo 64(%r3),%r30
	bv %r0(%r2)
	ldwm -64(%r30),%r3
.L22:
	comib,= 12,%r21,.L46
	ldo 24(%r3),%r20
	comib,=,n 13,%r21,.L47
	comib,=,n 14,%r21,.L1
	ldw 24(%r3),%r28
	comib,<> 15,%r21,.L49
	ldw -20(%r3),%r2
	ldw 16(%r3),%r20
	bb,>= %r20,30,.L49
	ldw 44(%r3),%r4
	ldo -1(%r4),%r20
	comib,<< 7,%r20,.L50
	ldw 36(%r3),%r20
	extru %r20,31,2,%r31
	copy %r20,%r2
	depi 0,31,2,%r2
	comib,<< 4,%r4,.L33
	addl %r31,%r4,%r5
	zdep %r31,28,29,%r31
	mtsar %r31
	zvdepi 2,32,%r20
	comib,<< 4,%r5,.L34
	ldo -1(%r20),%r31
	ldw 0(%r2),%r20
	zdep %r5,28,29,%r21
	ldo -1(%r21),%r21
	and %r20,%r31,%r20
	mtsar %r21
	vextrs %r20,32,%r20
	movb,tr %r20,%r28,.L49
	ldw -20(%r3),%r2
.L34:
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
.L39:
	b .L1
	or %r21,%r20,%r28
.L33:
	zdep %r31,28,29,%r31
	mtsar %r31
	zvdepi 2,32,%r20
	comib,<< 8,%r5,.L37
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
	movb,tr %r22,%r28,.L1
	or %r21,%r31,%r29
.L37:
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
	b .L39
	vextrs %r20,32,%r20
.L41:
	b .L1
	ldw 24(%r3),%r28
.L47:
	ldw 24(%r3),%r28
	b .L40
	fldds 0(%r20),%fr4
.L46:
	ldw 24(%r3),%r28
	b .L1
	fldws 0(%r20),%fr4L
.L45:
	b .L1
	ldh 24(%r3),%r28
.L44:
	ldh 24(%r3),%r20
	b .L1
	extrs %r20,31,16,%r28
.L43:
	b .L1
	ldb 24(%r3),%r28
.L48:
	b .L1
	extrs %r20,31,8,%r28
	.EXIT
	.PROCEND
.Lfe1:
	.size	callback_receiver,.Lfe1-callback_receiver
	.data
	.align 4
.LC0:
	.word	P%callback_receiver
	.text
	.align 4
.globl callback_get_receiver
		.type		 callback_get_receiver,@function
callback_get_receiver:
	.PROC
	.CALLINFO FRAME=64,NO_CALLS,SAVE_SP,ENTRY_GR=3
	.ENTRY
	copy %r3,%r1
	copy %r30,%r3
	stwm %r1,64(%r30)
	addil LT'.LC0,%r19
	stw %r19,-32(%r30)
	ldw RT'.LC0(%r1),%r1
	ldw 0(%r1),%r28
	ldo 64(%r3),%r30
	bv %r0(%r2)
	ldwm -64(%r30),%r3
	.EXIT
	.PROCEND
.Lfe2:
	.size	callback_get_receiver,.Lfe2-callback_get_receiver
	.ident	"GCC: (GNU) 3.1"
