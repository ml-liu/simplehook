	.set noreorder
	.set volatile
	.set noat
	.set nomacro
	.text
	.align 2
	.align 4
	.globl __TR_clear_cache
	.ent __TR_clear_cache
$__TR_clear_cache..ng:
__TR_clear_cache:
	.frame $30,0,$26,0
	.prologue 0
	.set	macro
	call_pal 0x86
	.set	nomacro
	ret $31,($26),1
	.end __TR_clear_cache
	.ident	"GCC: (GNU) 4.0.2"
	.section	.note.GNU-stack,"",@progbits
