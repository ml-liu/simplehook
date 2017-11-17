	.file	"cache-sparc.c"
	.section	".text"
	.align 4
	.global __TR_clear_cache_2
	.type	__TR_clear_cache_2,#function
	.proc	020
__TR_clear_cache_2:
	!#PROLOGUE# 0
	iflush %o0+0;iflush %o0+8
	nop
	retl
	nop
.LLfe1:
	.size	__TR_clear_cache_2,.LLfe1-__TR_clear_cache_2
	.ident	"GCC: (GNU) 3.1"
