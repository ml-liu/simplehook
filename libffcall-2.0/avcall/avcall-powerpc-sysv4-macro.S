	.file	"avcall-powerpc.c"
	.section	".text"
	.align 2
	.globl avcall_call
	.type	avcall_call, @function
avcall_call:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	stwu 1,-1056(1)
	mflr 0
	stw 0,1060(1)
	addi 10,1,8
	stw 30,1048(1)
	mr 30,3
	lwz 0,20(30)
	li 3,0
	lwz 11,24(30)
	stw 31,1052(1)
	mr 31,1
	subfc 0,11,0
	srawi 0,0,2
	cmpw 0,3,0
	bge- 0,.L73
	mtctr 0
.L74:
	slwi 9,3,2
	addi 3,3,1
	lwzx 0,9,11
	stwx 0,9,10
	bdnz .L74
.L73:
	lwz 9,76(30)
	subfc 9,30,9
	addi 9,9,-80
	srawi. 9,9,3
	beq- 0,.L8
	cmpwi 0,9,1
	beq- 0,.L11
	cmpwi 0,9,2
	beq- 0,.L14
	cmpwi 0,9,3
	beq- 0,.L17
	cmpwi 0,9,4
	beq- 0,.L20
	cmpwi 0,9,5
	beq- 0,.L23
	cmpwi 0,9,6
	beq- 0,.L26
	cmpwi 0,9,7
	beq- 0,.L29
.L32:
	lfd 8,136(30)
.L29:
	lfd 7,128(30)
.L26:
	lfd 6,120(30)
.L23:
	lfd 5,112(30)
.L20:
	lfd 4,104(30)
.L17:
	lfd 3,96(30)
.L14:
	lfd 2,88(30)
.L11:
	lfd 1,80(30)
.L8:
	lwz 0,4(30)
	lwz 9,68(30)
	lwz 3,44(30)
	mtctr 0
	lwz 4,48(30)
	lwz 5,52(30)
	lwz 6,56(30)
	lwz 7,60(30)
	lwz 8,64(30)
	lwz 10,72(30)
	crxor 6,6,6
	bctrl
	lwz 9,12(30)
	cmpwi 0,9,1
	beq- 0,.L34
	cmpwi 0,9,0
	beq- 0,.L84
	cmpwi 0,9,2
	beq- 0,.L77
	cmpwi 0,9,3
	beq- 0,.L77
	cmpwi 0,9,4
	beq- 0,.L77
	cmpwi 0,9,5
	beq- 0,.L76
	cmpwi 0,9,6
	beq- 0,.L76
	cmpwi 0,9,7
	beq- 0,.L84
	cmpwi 0,9,8
	beq- 0,.L84
	cmpwi 0,9,9
	beq- 0,.L84
	cmpwi 0,9,10
	beq- 0,.L84
	addi 0,9,-11
	cmplwi 0,0,1
	ble- 0,.L83
	cmpwi 0,9,13
	beq- 0,.L85
	cmpwi 0,9,14
	beq- 0,.L86
	cmpwi 0,9,15
	beq- 0,.L84
	cmpwi 0,9,16
	beq- 0,.L87
.L34:
	lwz 11,0(1)
	li 3,0
	lwz 0,4(11)
	lwz 30,-8(11)
	lwz 31,-4(11)
	mtlr 0
	mr 1,11
	blr
.L87:
	lwz 0,0(30)
	andi. 9,0,512
	beq- 0,.L34
	lwz 0,16(30)
	cmpwi 0,0,1
	beq- 0,.L77
	cmpwi 0,0,2
	beq- 0,.L76
	cmpwi 0,0,4
	beq- 0,.L84
	cmpwi 0,0,8
	bne+ 0,.L34
.L83:
	lwz 9,8(30)
	stw 4,4(9)
.L75:
	stw 3,0(9)
	b .L34
.L84:
	lwz 9,8(30)
	b .L75
.L76:
	lwz 9,8(30)
	sth 3,0(9)
	b .L34
.L77:
	lwz 9,8(30)
	stb 3,0(9)
	b .L34
.L86:
	lwz 9,8(30)
	stfd 1,0(9)
	b .L34
.L85:
	frsp 0,1
	lwz 9,8(30)
	stfs 0,0(9)
	b .L34
	.size	avcall_call, .-avcall_call
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
