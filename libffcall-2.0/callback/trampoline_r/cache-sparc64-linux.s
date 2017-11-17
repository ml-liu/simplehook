	.file	"cache-sparc.c"
	.section	".text"
	.align 4
	.global __TR_clear_cache_2
	.type	__TR_clear_cache_2, #function
	.proc	020
__TR_clear_cache_2:
	iflush %o0+0;iflush %o0+8
	jmp	%o7+8
	 nop
	.size	__TR_clear_cache_2, .-__TR_clear_cache_2
	.ident	"GCC: (GNU) 4.0.2"
	.section	".note.GNU-stack"
