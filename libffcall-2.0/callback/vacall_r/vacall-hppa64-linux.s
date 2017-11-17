	.LEVEL 2.0w
	.text
	.align 8
.globl callback_receiver
		.type		 callback_receiver,@function
callback_receiver:
	.PROC
	.CALLINFO FRAME=384,CALLS,SAVE_RP,SAVE_SP,ENTRY_GR=9
	.ENTRY
	copy %r3,%r1
	std %r2,-16(%r30)
	copy %r30,%r3
	std,ma %r1,384(%r30)
	std %r5,224(%r3)
	copy %r27,%r5
	std %r9,192(%r3)
	std %r8,200(%r3)
	std %r7,208(%r3)
	std %r6,216(%r3)
	std %r4,232(%r3)
	std %r26,-64(%r29)
	std %r25,-56(%r29)
	std %r19,-8(%r29)
	std %r24,-48(%r29)
	std %r23,-40(%r29)
	std %r22,-32(%r29)
	std %r21,-24(%r29)
	std %r20,-16(%r29)
#APP
	fstw %fr4R,88(%r3)
	fstw %fr5R,92(%r3)
	fstw %fr6R,96(%r3)
	fstw %fr7R,100(%r3)
	fstw %fr8R,104(%r3)
	fstw %fr9R,108(%r3)
	fstw %fr10R,112(%r3)
	fstw %fr11R,116(%r3)
#NO_APP
	fstd %fr10,168(%r3)
	ldo -64(%r29),%r2
	ldo 16(%r3),%r25
	std %r0,48(%r3)
	std %r2,40(%r3)
	std %r29,80(%r3)
	ldo -16(%r30),%r29
	fstd %fr11,176(%r3)
	fstd %fr4,120(%r3)
	fstd %fr5,128(%r3)
	fstd %fr6,136(%r3)
	fstd %fr7,144(%r3)
	fstd %fr8,152(%r3)
	fstd %fr9,160(%r3)
	stw %r0,16(%r3)
	stw %r0,56(%r3)
	ldd 0(%r31),%r4
	ldd 8(%r31),%r26
	ldd 16(%r4),%r2
	ldd 24(%r4),%r27
	bve,l (%r2),%r2
	nop
	ldw 56(%r3),%r2
	cmpib,= 0,%r2,.L1
	copy %r5,%r27
	cmpib,=,n 1,%r2,.L43
	cmpib,=,n 2,%r2,.L43
	cmpib,=,n 3,%r2,.L44
	cmpib,=,n 4,%r2,.L45
	cmpib,=,n 5,%r2,.L46
	cmpib,=,n 6,%r2,.L47
	cmpib,=,n 7,%r2,.L41
	cmpib,=,n 8,%r2,.L40
	cmpib,=,n 10,%r2,.L40
	cmpib,=,n 9,%r2,.L40
	cmpib,=,n 11,%r2,.L40
	cmpib,=,n 12,%r2,.L48
	cmpib,=,n 13,%r2,.L49
	cmpib,=,n 14,%r2,.L40
	cmpib,= 15,%r2,.L50
	ldw 16(%r3),%r2
.L1:
	ldd -16(%r3),%r2
	ldd 192(%r3),%r9
	ldd 200(%r3),%r8
	ldd 208(%r3),%r7
	ldd 216(%r3),%r6
	ldd 224(%r3),%r5
	ldd 232(%r3),%r4
	ldo 64(%r3),%r30
	bve (%r2)
	ldd,mb -64(%r30),%r3
.L50:
	extrd,u %r2,53+1-1,1,%r2
	cmpib,= 0,%r2,.L1
	ldd 48(%r3),%r28
	ldd 48(%r3),%r2
	ldd 64(%r3),%r4
	extrd,u %r2,63,3,%r7
	copy %r2,%r1
	depdi 0,63,3,%r1
	cmpib,*<< 8,%r4,.L32
	add,l %r7,%r4,%r5
	cmpib,*<< 8,%r5,.L33
	depd,z %r5,60,61,%r2
	subi 64,%r2,%r2
	ldd 0(%r1),%r4
	extrd,s %r2,63,32,%r2
	mtsarcm %r2
	depd,z %r7,60,61,%r5
	depdi,z 1,%sar,64,%r2
	mtsarcm %r5
	sub %r0,%r2,%r2
	and %r4,%r2,%r4
	depd,z %r4,%sar,64,%r4
	b .L1
	copy %r4,%r28
.L33:
	subi 128,%r2,%r2
	depd,z %r7,60,61,%r4
	extrd,s %r2,63,32,%r2
	subi 64,%r4,%r6
	mtsarcm %r2
	subi 63,%r4,%r8
	depdi,z 1,%sar,64,%r2
	mtsar %r8
	ldd 8(%r1),%r5
	sub %r0,%r2,%r2
	extrd,s %r6,63,32,%r6
	ldd 0(%r1),%r4
	subi 63,%r6,%r6
	and %r5,%r2,%r5
	depd,z %r4,%sar,64,%r4
	mtsar %r6
	extrd,s %r5,%sar,64,%r5
.L39:
	b .L1
	or %r5,%r4,%r28
.L32:
	ldi 16,%r2
	cmpb,*<< %r2,%r5,.L36
	depd,z %r5,60,61,%r2
	subi 128,%r2,%r2
	depd,z %r7,61,62,%r4
	extrd,s %r2,63,32,%r2
	subi 32,%r4,%r4
	mtsarcm %r2
	extrd,s %r4,63,32,%r4
	depdi,z 1,%sar,64,%r2
	subi 63,%r4,%r8
	ldd 8(%r1),%r5
	sub %r0,%r2,%r2
	mtsar %r8
	ldd 0(%r1),%r6
	and %r5,%r2,%r5
	depd,z %r7,60,61,%r2
	extrd,s %r5,%sar,64,%r4
	subi 63,%r2,%r2
	extrd,s %r4,%sar,64,%r4
	mtsar %r2
	depd,z %r5,%sar,64,%r5
	depd,z %r6,%sar,64,%r6
	copy %r5,%r29
	b .L1
	or %r6,%r4,%r28
.L36:
	subi 192,%r2,%r2
	depd,z %r7,60,61,%r4
	extrd,s %r2,63,32,%r2
	subi 64,%r4,%r7
	mtsarcm %r2
	subi 63,%r4,%r9
	depdi,z 1,%sar,64,%r2
	mtsar %r9
	ldd 8(%r1),%r4
	sub %r0,%r2,%r2
	ldd 16(%r1),%r6
	extrd,s %r7,63,32,%r7
	subi 63,%r7,%r7
	and %r6,%r2,%r6
	ldd 0(%r1),%r5
	depd,z %r4,%sar,64,%r2
	mtsar %r7
	extrd,s %r6,%sar,64,%r6
	mtsar %r9
	depd,z %r5,%sar,64,%r5
	or %r2,%r6,%r29
	mtsar %r7
	b .L39
	extrd,s %r4,%sar,64,%r4
.L40:
	b .L1
	ldd 24(%r3),%r28
.L49:
	b .L40
	fldd 24(%r3),%fr4
.L48:
#APP
	fldw 24(%r3),%fr4R
#NO_APP
.L41:
	ldw 24(%r3),%r2
.L42:
	b .L1
	copy %r2,%r28
.L47:
	ldw 24(%r3),%r2
	b .L1
	extrd,s %r2,63,32,%r28
.L46:
	b .L42
	ldh 24(%r3),%r2
.L45:
	ldh 24(%r3),%r2
	b .L1
	extrd,s %r2,63,16,%r28
.L44:
	b .L42
	ldb 24(%r3),%r2
.L43:
	ldb 24(%r3),%r2
	b .L1
	extrd,s %r2,63,8,%r28
	.EXIT
	.PROCEND
.Lfe1:
	.size	callback_receiver,.Lfe1-callback_receiver
	.data
	.align 8
.LC0:
	.dword	P%callback_receiver
	.text
	.align 8
.globl callback_get_receiver
		.type		 callback_get_receiver,@function
callback_get_receiver:
	.PROC
	.CALLINFO FRAME=128,NO_CALLS,SAVE_SP,ENTRY_GR=3
	.ENTRY
	copy %r3,%r1
	copy %r30,%r3
	std,ma %r1,128(%r30)
	addil LT'.LC0,%r27
	ldd RT'.LC0(%r1),%r1
	ldd 0(%r1),%r28
	ldo 64(%r3),%r30
	bve (%r2)
	ldd,mb -64(%r30),%r3
	.EXIT
	.PROCEND
.Lfe2:
	.size	callback_get_receiver,.Lfe2-callback_get_receiver
	.ident	"GCC: (GNU) 3.1"
