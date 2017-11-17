	.LEVEL 1.1
	.text
	.align 4
.globl avcall_call
		.type		 avcall_call,@function
avcall_call:
	.PROC
	.CALLINFO FRAME=1152,CALLS,SAVE_RP,SAVE_SP,ENTRY_GR=5
	.ENTRY
	copy %r3,%r1
	stw %r2,-20(%r30)
	copy %r30,%r3
	stwm %r1,1152(%r30)
	stw %r5,1040(%r3)
	ldo -32(%r30),%r25
	copy %r19,%r5
	stw %r4,1044(%r3)
	stw %r19,-32(%r30)
	ldw 28(%r26),%r21
	ldw 20(%r26),%r20
	sub %r21,%r20,%r20
	extrs %r20,29,30,%r20
	sub %r0,%r20,%r23
	comib,<= -4,%r23,.L49
	copy %r26,%r4
	copy %r21,%r24
.L6:
	zdep %r23,29,30,%r20
	ldo 1(%r23),%r23
	addl %r20,%r24,%r22
	addl %r20,%r25,%r20
	ldw 0(%r22),%r21
	comib,> -4,%r23,.L6
	stw %r21,0(%r20)
.L48:
	ldw 12(%r4),%r21
	ldi 16,%r20
	comb,=,n %r20,%r21,.L54
.L7:
	ldw -16(%r24),%r23
	ldw -4(%r24),%r26
	ldw -8(%r24),%r25
	ldw 4(%r4),%r22
	ldw -12(%r24),%r24
	.CALL	ARGW0=GR
	bl $$dyncall,%r31
	copy %r31,%r2
	ldw 12(%r4),%r21
	copy %r5,%r19
	comib,= 1,%r21,.L9
	copy %r28,%r2
	comib,=,n 0,%r21,.L53
	comib,=,n 2,%r21,.L52
	comib,=,n 3,%r21,.L52
	comib,=,n 4,%r21,.L52
	comib,=,n 5,%r21,.L51
	comib,=,n 6,%r21,.L51
	comib,=,n 7,%r21,.L53
	comib,=,n 8,%r21,.L53
	comib,=,n 9,%r21,.L53
	comib,=,n 10,%r21,.L53
	ldo -11(%r21),%r20
	comib,<<,n 1,%r20,.L30
	ldw 8(%r4),%r20
	stw %r29,4(%r20)
.L50:
	stw %r2,0(%r20)
.L9:
	ldw -20(%r3),%r2
.L57:
	ldi 0,%r28
	ldw 1040(%r3),%r5
	ldw 1044(%r3),%r4
	ldo 64(%r3),%r30
	bv %r0(%r2)
	ldwm -64(%r30),%r3
.L30:
	comib,=,n 13,%r21,.L55
	comib,=,n 14,%r21,.L56
	comib,=,n 15,%r21,.L53
	ldi 16,%r20
	comb,<>,n %r20,%r21,.L57
	ldw -20(%r3),%r2
	ldw 0(%r4),%r20
	bb,>=,n %r20,30,.L57
	ldw -20(%r3),%r2
	ldw 16(%r4),%r22
	ldo -1(%r22),%r20
	comib,<<,n 7,%r20,.L57
	ldw -20(%r3),%r2
	ldw 8(%r4),%r20
	extru %r20,31,2,%r26
	copy %r20,%r4
	depi 0,31,2,%r4
	comib,<< 4,%r22,.L41
	addl %r26,%r22,%r21
	comib,<< 4,%r21,.L42
	zdep %r21,28,29,%r20
	ldo -1(%r20),%r25
	zdep %r26,28,29,%r21
	mtsar %r25
	ldw 0(%r4),%r23
	zvdep %r28,32,%r20
	mtsar %r21
	zvdepi 2,32,%r21
	xor %r23,%r20,%r20
	mtsar %r25
	zvdepi 1,32,%r22
	sub %r21,%r22,%r21
	and %r20,%r21,%r20
	xor %r23,%r20,%r23
	b .L9
	stw %r23,0(%r4)
.L42:
	subi 63,%r20,%r31
	zdep %r26,28,29,%r26
	ldo -33(%r20),%r20
	ldw 0(%r4),%r25
	mtsar %r20
	ldw 4(%r4),%r24
	zvdep %r28,32,%r23
	mtsar %r26
	zvdepi 2,32,%r22
	xor %r24,%r23,%r23
	mtsar %r31
	ldo -1(%r22),%r22
	vextrs %r28,32,%r21
	mtsar %r20
	zvdepi 1,32,%r20
	xor %r25,%r21,%r21
	sub %r0,%r20,%r20
	and %r21,%r22,%r21
	and %r23,%r20,%r23
	xor %r25,%r21,%r25
	xor %r24,%r23,%r24
	stw %r25,0(%r4)
	b .L9
	stw %r24,4(%r4)
.L41:
	zdep %r26,28,29,%r26
	mtsar %r26
	zvdepi 2,32,%r20
	comib,<< 8,%r21,.L45
	ldo -1(%r20),%r25
	zdep %r21,29,30,%r20
	subi 47,%r20,%r24
	zdep %r21,28,29,%r21
	mtsar %r24
	ldo -33(%r21),%r26
	vextrs %r29,32,%r22
	vextrs %r22,32,%r22
	mtsar %r26
	ldw 0(%r4),%r24
	ldw 4(%r4),%r23
	zvdep %r28,32,%r20
	or %r20,%r22,%r20
	zvdep %r29,32,%r29
	zvdepi 1,32,%r21
	xor %r24,%r20,%r20
	xor %r23,%r29,%r29
	sub %r0,%r21,%r21
	and %r20,%r25,%r20
	and %r29,%r21,%r29
	xor %r24,%r20,%r24
	xor %r23,%r29,%r23
	stw %r24,0(%r4)
	b .L9
	stw %r23,4(%r4)
.L45:
	zdep %r21,28,29,%r20
	ldo -65(%r20),%r31
	subi 95,%r20,%r26
	ldw 8(%r4),%r23
	mtsar %r31
	ldw 0(%r4),%r24
	zvdep %r29,32,%r22
	zvdepi 1,32,%r21
	xor %r23,%r22,%r22
	mtsar %r26
	sub %r0,%r21,%r21
	vextrs %r28,32,%r20
	and %r22,%r21,%r22
	mtsar %r31
	xor %r24,%r20,%r20
	zvdep %r28,32,%r21
	and %r20,%r25,%r20
	mtsar %r26
	xor %r24,%r20,%r24
	vextrs %r29,32,%r29
	xor %r23,%r22,%r23
	or %r21,%r29,%r21
	stw %r23,8(%r4)
	stw %r24,0(%r4)
	b .L9
	stw %r21,4(%r4)
.L53:
	b .L50
	ldw 8(%r4),%r20
.L56:
	ldw 8(%r4),%r20
	b .L9
	fstds %fr4,0(%r20)
.L55:
	ldw 8(%r4),%r20
	b .L9
	fstws %fr4L,0(%r20)
.L51:
	ldw 8(%r4),%r20
	b .L9
	sth %r2,0(%r20)
.L52:
	ldw 8(%r4),%r20
	b .L9
	stb %r2,0(%r20)
.L54:
	b .L7
	ldw 8(%r4),%r28
.L49:
	b .L48
	ldw 28(%r26),%r24
	.EXIT
	.PROCEND
.Lfe1:
	.size	avcall_call,.Lfe1-avcall_call
	.ident	"GCC: (GNU) 3.1"
