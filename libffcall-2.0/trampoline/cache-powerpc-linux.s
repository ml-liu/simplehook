	.file	"cache-powerpc.c"
	.section	".text"
	.align 2
	.globl __TR_clear_cache
	.type	__TR_clear_cache, @function
__TR_clear_cache:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	stwu 1,-32(1)
#APP
	icbi 0,3; dcbf 0,3
#NO_APP
	addi 0,3,4
#APP
	icbi 0,0; dcbf 0,0
#NO_APP
	addi 9,3,8
#APP
	icbi 0,9; dcbf 0,9
#NO_APP
	addi 0,3,12
#APP
	icbi 0,0; dcbf 0,0
#NO_APP
	addi 9,3,16
#APP
	icbi 0,9; dcbf 0,9
#NO_APP
	addi 0,3,20
#APP
	icbi 0,0; dcbf 0,0
#NO_APP
	addi 9,3,24
#APP
	icbi 0,9; dcbf 0,9
#NO_APP
	addi 0,3,28
#APP
	icbi 0,0; dcbf 0,0
#NO_APP
	addi 3,3,32
#APP
	icbi 0,3; dcbf 0,3
	sync; isync
#NO_APP
	addi 1,1,32
	blr
	.size	__TR_clear_cache, .-__TR_clear_cache
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.6"
