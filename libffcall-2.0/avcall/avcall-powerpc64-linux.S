	.file	"avcall-powerpc64.c"
	.machine power4
	.section	".toc","aw"
	.section	".text"
	.align 2
	.p2align 4,,15
	.globl avcall_call
	.section	".opd","aw"
	.align 3
avcall_call:
	.quad	.L.avcall_call,.TOC.@tocbase,0
	.previous
	.type	avcall_call, @function
.L.avcall_call:
	mflr 0
	std 30,-16(1)
	std 31,-8(1)
	mr 30,3
	std 0,16(1)
	stdu 1,-128(1)
	ld 3,48(3)
	ld 9,40(30)
	mr 31,1
	ld 10,0(1)
	subf 9,3,9
	stdu 10,-2064(1)
	sradi 9,9,3
	cmpwi 7,9,8
	ble 7,.L6
	addi 10,9,-9
	addi 8,1,112
	addi 9,3,56
	rldicl 10,10,0,32
	addi 8,8,-8
	addi 10,10,8
	sldi 10,10,3
	add 10,3,10
	.p2align 4,,15
.L5:
	ldu 7,8(9)
	cmpld 7,10,9
	stdu 7,8(8)
	bne 7,.L5
.L6:
	ld 10,64(30)
	addi 9,30,72
	subf 9,9,10
	sradi 9,9,3
	extsw 9,9
	cmpwi 7,9,0
	ble 7,.L4
	cmpwi 7,9,1
	beq 7,.L7
	cmpwi 7,9,2
	beq 7,.L8
	cmpwi 7,9,3
	beq 7,.L9
	cmpwi 7,9,4
	beq 7,.L10
	cmpwi 7,9,5
	beq 7,.L11
	cmpwi 7,9,6
	beq 7,.L12
	cmpwi 7,9,7
	beq 7,.L13
	cmpwi 7,9,8
	beq 7,.L14
	cmpwi 7,9,9
	beq 7,.L15
	cmpwi 7,9,10
	beq 7,.L16
	cmpwi 7,9,11
	beq 7,.L17
	cmpwi 7,9,12
	beq 7,.L18
	lfd 13,168(30)
.L18:
	lfd 12,160(30)
.L17:
	lfd 11,152(30)
.L16:
	lfd 10,144(30)
.L15:
	lfd 9,136(30)
.L14:
	lfd 8,128(30)
.L13:
	lfd 7,120(30)
.L12:
	lfd 6,112(30)
.L11:
	lfd 5,104(30)
.L10:
	lfd 4,96(30)
.L9:
	lfd 3,88(30)
.L8:
	lfd 2,80(30)
.L7:
	lfd 1,72(30)
.L4:
	ld 9,48(3)
	ld 10,56(3)
	ld 8,40(3)
	ld 7,32(3)
	ld 6,24(3)
	ld 5,16(3)
	ld 4,8(3)
	ld 3,0(3)
	std 2,40(1)
	ld 12,8(30)
	ld 0,0(12)
	ld 11,16(12)
	mtctr 0
	ld 2,8(12)
	bctrl
	ld 2,40(1)
	lwz 9,24(30)
	cmplwi 7,9,1
	beq 7,.L19
	cmpdi 7,9,0
	beq 7,.L36
	cmplwi 7,9,2
	beq 7,.L38
	cmplwi 7,9,3
	beq 7,.L38
	cmplwi 7,9,4
	beq 7,.L38
	cmplwi 7,9,5
	beq 7,.L39
	cmplwi 7,9,6
	beq 7,.L39
	cmplwi 7,9,7
	beq 7,.L40
	cmplwi 7,9,8
	beq 7,.L40
	cmplwi 7,9,9
	beq 7,.L36
	cmplwi 7,9,10
	beq 7,.L36
	cmplwi 7,9,11
	beq 7,.L36
	cmplwi 7,9,12
	beq 7,.L36
	cmplwi 7,9,13
	beq 7,.L42
	cmplwi 7,9,14
	beq 7,.L43
	cmplwi 7,9,15
	beq 7,.L36
.L19:
	addi 1,31,128
	li 3,0
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.p2align 4,,15
.L36:
	ld 9,16(30)
	std 3,0(9)
	addi 1,31,128
	li 3,0
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.p2align 4,,15
.L38:
	ld 9,16(30)
	stb 3,0(9)
	addi 1,31,128
	li 3,0
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
.L39:
	ld 9,16(30)
	sth 3,0(9)
	b .L19
.L40:
	ld 9,16(30)
	stw 3,0(9)
	b .L19
.L42:
	ld 9,16(30)
	stfs 1,0(9)
	b .L19
.L43:
	ld 9,16(30)
	stfd 1,0(9)
	b .L19
	.long 0
	.byte 0,0,0,1,128,2,0,0
	.size	avcall_call,.-.L.avcall_call
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
