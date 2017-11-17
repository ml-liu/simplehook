	.file	"cache-sparc.c"
	.section	".text"
	.align 4
	.global __TR_clear_cache_4
	.type	__TR_clear_cache_4,#function
	.proc	020
__TR_clear_cache_4:
	!#PROLOGUE# 0
	iflush %o0+0;iflush %o0+8;iflush %o0+16;iflush %o0+24
	nop
	retl
	nop
.LLfe1:
	.size	__TR_clear_cache_4,.LLfe1-__TR_clear_cache_4
	.ident	"GCC: (GNU) 3.1"
