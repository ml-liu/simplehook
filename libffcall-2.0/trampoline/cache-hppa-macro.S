#include "asm-hppa.h"
	.LEVEL 1.1
	IMPORT_MILLICODE($$dyncall)
	TEXT1()
	TEXT2()
	.align 4
GLOBL(__TR_clear_cache)
		DECLARE_FUNCTION(__TR_clear_cache)
DEF(__TR_clear_cache)
	.PROC
	.CALLINFO FRAME=0,NO_CALLS
	.ENTRY
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
	bv,n %r0(%r2)
	.EXIT
	.PROCEND
DEF(L(fe1))
	FUNEND(__TR_clear_cache)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
