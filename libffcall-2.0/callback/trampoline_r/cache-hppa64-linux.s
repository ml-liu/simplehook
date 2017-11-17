	.LEVEL 2.0w
	.text
	.align 8
.globl __TR_clear_cache
		.type		 __TR_clear_cache,@function
__TR_clear_cache:
	.PROC
	.CALLINFO FRAME=128,NO_CALLS
	.ENTRY
	ldo 128(%r30),%r30
#APP
	fdc 0(0,%r26)
	fdc 0(0,%r25)
	sync
	mfsp %sr0,%r31
	ldsid (0,%r26),%r28
	mtsp %r28,%sr0
	fic 0(%sr0,%r26)
	fic 0(%sr0,%r25)
	sync
	mtsp %r31,%sr0
	nop
	nop
	nop
	nop
	nop
	nop
#NO_APP
	bve (%r2)
	ldo -128(%r30),%r30
	.EXIT
	.PROCEND
.Lfe1:
	.size	__TR_clear_cache,.Lfe1-__TR_clear_cache
	.ident	"GCC: (GNU) 3.1"
