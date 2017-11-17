	.LEVEL 2.0w
	.text
	.align 8
.globl vacall_receiver
		.type		 vacall_receiver,@function
vacall_receiver:
	.PROC
	.CALLINFO FRAME=384,CALLS,SAVE_RP,SAVE_SP,ENTRY_GR=8
	.ENTRY
	copy %r3,%r1
	std %r2,-16(%r30)
	copy %r30,%r3
	std,ma %r1,384(%r30)
	std %r4,224(%r3)
	copy %r27,%r4
	std %r8,192(%r3)
	std %r7,200(%r3)
	std %r6,208(%r3)
	std %r5,216(%r3)
	std %r26,-64(%r29)
	std %r19,-8(%r29)
	std %r25,-56(%r29)
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
	addil LT'vacall_function,%r27
	ldo -64(%r29),%r31
	ldd RT'vacall_function(%r1),%r1
	ldo 16(%r3),%r26
	std %r31,40(%r3)
	std %r29,80(%r3)
	ldo -16(%r30),%r29
	ldd 0(%r1),%r31
	fstd %fr11,176(%r3)
	fstd %fr4,120(%r3)
	fstd %fr5,128(%r3)
	fstd %fr6,136(%r3)
	fstd %fr7,144(%r3)
	fstd %fr8,152(%r3)
	fstd %fr9,160(%r3)
	stw %r0,16(%r3)
	std %r0,48(%r3)
	stw %r0,56(%r3)
	ldd 16(%r31),%r2
	ldd 24(%r31),%r27
	bve,l (%r2),%r2
	nop
	ldw 56(%r3),%r31
	cmpib,= 0,%r31,.L1
	copy %r4,%r27
	cmpib,=,n 1,%r31,.L43
	cmpib,=,n 2,%r31,.L43
	cmpib,=,n 3,%r31,.L44
	cmpib,=,n 4,%r31,.L45
	cmpib,=,n 5,%r31,.L46
	cmpib,=,n 6,%r31,.L47
	cmpib,=,n 7,%r31,.L41
	cmpib,=,n 8,%r31,.L40
	cmpib,=,n 10,%r31,.L40
	cmpib,=,n 9,%r31,.L40
	cmpib,=,n 11,%r31,.L40
	cmpib,=,n 12,%r31,.L48
	cmpib,=,n 13,%r31,.L49
	cmpib,=,n 14,%r31,.L40
	cmpib,= 15,%r31,.L50
	ldw 16(%r3),%r31
.L1:
	ldd -16(%r3),%r2
	ldd 192(%r3),%r8
	ldd 200(%r3),%r7
	ldd 208(%r3),%r6
	ldd 216(%r3),%r5
	ldd 224(%r3),%r4
	ldo 64(%r3),%r30
	bve (%r2)
	ldd,mb -64(%r30),%r3
.L50:
	extrd,u %r31,53+1-1,1,%r31
	cmpib,= 0,%r31,.L1
	ldd 48(%r3),%r28
	ldd 48(%r3),%r31
	ldd 64(%r3),%r2
	extrd,u %r31,63,3,%r6
	copy %r31,%r1
	depdi 0,63,3,%r1
	cmpib,*<< 8,%r2,.L32
	add,l %r6,%r2,%r4
	cmpib,*<< 8,%r4,.L33
	depd,z %r4,60,61,%r31
	subi 64,%r31,%r31
	ldd 0(%r1),%r2
	extrd,s %r31,63,32,%r31
	mtsarcm %r31
	depd,z %r6,60,61,%r4
	depdi,z 1,%sar,64,%r31
	mtsarcm %r4
	sub %r0,%r31,%r31
	and %r2,%r31,%r2
	depd,z %r2,%sar,64,%r2
	b .L1
	copy %r2,%r28
.L33:
	subi 128,%r31,%r31
	depd,z %r6,60,61,%r2
	extrd,s %r31,63,32,%r31
	subi 64,%r2,%r5
	mtsarcm %r31
	subi 63,%r2,%r7
	depdi,z 1,%sar,64,%r31
	mtsar %r7
	ldd 8(%r1),%r4
	sub %r0,%r31,%r31
	extrd,s %r5,63,32,%r5
	ldd 0(%r1),%r2
	subi 63,%r5,%r5
	and %r4,%r31,%r4
	depd,z %r2,%sar,64,%r2
	mtsar %r5
	extrd,s %r4,%sar,64,%r4
.L39:
	b .L1
	or %r4,%r2,%r28
.L32:
	ldi 16,%r31
	cmpb,*<< %r31,%r4,.L36
	depd,z %r4,60,61,%r31
	subi 128,%r31,%r31
	depd,z %r6,61,62,%r2
	extrd,s %r31,63,32,%r31
	subi 32,%r2,%r2
	mtsarcm %r31
	extrd,s %r2,63,32,%r2
	depdi,z 1,%sar,64,%r31
	subi 63,%r2,%r7
	ldd 8(%r1),%r4
	sub %r0,%r31,%r31
	mtsar %r7
	ldd 0(%r1),%r5
	and %r4,%r31,%r4
	depd,z %r6,60,61,%r31
	extrd,s %r4,%sar,64,%r2
	subi 63,%r31,%r31
	extrd,s %r2,%sar,64,%r2
	mtsar %r31
	depd,z %r4,%sar,64,%r4
	depd,z %r5,%sar,64,%r5
	copy %r4,%r29
	b .L1
	or %r5,%r2,%r28
.L36:
	subi 192,%r31,%r31
	depd,z %r6,60,61,%r2
	extrd,s %r31,63,32,%r31
	subi 64,%r2,%r6
	mtsarcm %r31
	subi 63,%r2,%r8
	depdi,z 1,%sar,64,%r31
	mtsar %r8
	ldd 8(%r1),%r2
	sub %r0,%r31,%r31
	ldd 16(%r1),%r5
	extrd,s %r6,63,32,%r6
	subi 63,%r6,%r6
	and %r5,%r31,%r5
	ldd 0(%r1),%r4
	depd,z %r2,%sar,64,%r31
	mtsar %r6
	extrd,s %r5,%sar,64,%r5
	mtsar %r8
	depd,z %r4,%sar,64,%r4
	or %r31,%r5,%r29
	mtsar %r6
	b .L39
	extrd,s %r2,%sar,64,%r2
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
	ldw 24(%r3),%r31
.L42:
	b .L1
	copy %r31,%r28
.L47:
	ldw 24(%r3),%r31
	b .L1
	extrd,s %r31,63,32,%r28
.L46:
	b .L42
	ldh 24(%r3),%r31
.L45:
	ldh 24(%r3),%r31
	b .L1
	extrd,s %r31,63,16,%r28
.L44:
	b .L42
	ldb 24(%r3),%r31
.L43:
	ldb 24(%r3),%r31
	b .L1
	extrd,s %r31,63,8,%r28
	.EXIT
	.PROCEND
.Lfe1:
	.size	vacall_receiver,.Lfe1-vacall_receiver
	.ident	"GCC: (GNU) 3.1"
