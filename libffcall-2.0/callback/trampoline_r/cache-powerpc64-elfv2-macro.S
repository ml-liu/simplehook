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
 # 25 "cache-powerpc64.c" 1
	icbi 0,3; dcbf 0,3
 # 0 "" 2
	addi 9,3,4
 # 26 "cache-powerpc64.c" 1
	icbi 0,9; dcbf 0,9
 # 0 "" 2
	addi 9,3,8
 # 27 "cache-powerpc64.c" 1
	icbi 0,9; dcbf 0,9
 # 0 "" 2
	addi 3,3,12
 # 28 "cache-powerpc64.c" 1
	icbi 0,3; dcbf 0,3
 # 0 "" 2
 # 29 "cache-powerpc64.c" 1
	sync; isync
 # 0 "" 2
	blr
	.long 0
	.byte 0,0,0,0,0,0,0,0
	.size	__TR_clear_cache,.-__TR_clear_cache
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
