	.file	"cache-powerpc64.c"
	.machine power4
	.abiversion 2
	.section	".toc","aw"
	.section	".text"
	.align 2
	.p2align 4,,15
	.globl __TR_clear_cache
	.type	__TR_clear_cache, @function
__TR_clear_cache:
#APP
 # 25 "cache-powerpc64.c" 1
	icbi 0,3; dcbf 0,3
 # 0 "" 2
#NO_APP
	addi 9,3,4
#APP
 # 26 "cache-powerpc64.c" 1
	icbi 0,9; dcbf 0,9
 # 0 "" 2
#NO_APP
	addi 9,3,8
#APP
 # 27 "cache-powerpc64.c" 1
	icbi 0,9; dcbf 0,9
 # 0 "" 2
#NO_APP
	addi 3,3,12
#APP
 # 28 "cache-powerpc64.c" 1
	icbi 0,3; dcbf 0,3
 # 0 "" 2
 # 29 "cache-powerpc64.c" 1
	sync; isync
 # 0 "" 2
#NO_APP
	blr
	.long 0
	.byte 0,0,0,0,0,0,0,0
	.size	__TR_clear_cache,.-__TR_clear_cache
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
