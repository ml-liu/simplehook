#include "asm-sparc.h"
	.section	".text"
	.align 4
	.global C(__TR_clear_cache_2)
	DECLARE_FUNCTION(__TR_clear_cache_2)
	.proc	020
FUNBEGIN(__TR_clear_cache_2)
	iflush %o0+0;iflush %o0+8
	jmp	%o7+8
	 nop
	FUNEND(__TR_clear_cache_2)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
