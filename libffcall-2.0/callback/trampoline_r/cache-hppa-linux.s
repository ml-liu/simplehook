	.LEVEL 1.1
	.text
	.align 4
.globl __TR_clear_cache
		.type		 __TR_clear_cache,@function
__TR_clear_cache:
	.PROC
	.CALLINFO FRAME=0,NO_CALLS
	.ENTRY
#APP
	fdc 0(0,%r26)
	fdc 0(0,%r25)
	sync
	mfsp %sr0,%r20
	ldsid (0,%r26),%r26
	mtsp %r26,%sr0
	fic 0(%sr0,%r26)
	fic 0(%sr0,%r25)
	sync
	mtsp %r20,%sr0
	nop
	nop
	nop
	nop
	nop
	nop
#NO_APP
	bv,n %r0(%r2)
	.EXIT
	.PROCEND
.Lfe1:
	.size	__TR_clear_cache,.Lfe1-__TR_clear_cache
	.ident	"GCC: (GNU) 3.1"
