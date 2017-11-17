	.file	"cache-sparc.c"
	.section	".text"
	.align 4
	.global __TR_clear_cache_4
	.type	__TR_clear_cache_4, #function
	.proc	020
__TR_clear_cache_4:
	iflush %o0+0;iflush %o0+8;iflush %o0+16;iflush %o0+24
	jmp	%o7+8
	 nop
	.size	__TR_clear_cache_4, .-__TR_clear_cache_4
	.ident	"GCC: (GNU) 4.0.2"
	.section	".note.GNU-stack"
