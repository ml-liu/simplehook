#include "asm-hppa64.h"
	.LEVEL 2.0w
	TEXT1()
	TEXT2()
	.align 8
GLOBL(__TR_clear_cache)
		DECLARE_FUNCTION(__TR_clear_cache)
DEF(__TR_clear_cache)
	.PROC
	.CALLINFO FRAME=128,NO_CALLS
	.ENTRY
	ldo 128(%r30),%r30
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
	bve (%r2)
	ldo -128(%r30),%r30
	.EXIT
	.PROCEND
DEF(L(fe1))
	FUNEND(__TR_clear_cache)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
