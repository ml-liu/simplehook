	.file	"avcall-powerpc64.c"
	.machine power4
	.abiversion 2
	.section	".toc","aw"
	.section	".text"
	.align 2
	.p2align 4,,15
	.globl avcall_call
	.type	avcall_call, @function
avcall_call:
0:	addis 2,12,.TOC.-0b@ha
	addi 2,2,.TOC.-0b@l
	.localentry	avcall_call,.-avcall_call
	mflr 0
	std 30,-16(1)
	std 31,-8(1)
	mr 30,3
	std 0,16(1)
	stdu 1,-112(1)
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
	addi 8,1,96
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
	ld 11,8(30)
	ld 9,48(3)
	ld 10,56(3)
	ld 8,40(3)
	ld 7,32(3)
	ld 6,24(3)
	ld 5,16(3)
	ld 4,8(3)
	mtctr 11
	ld 3,0(3)
	mr 12,11
	std 2,24(1)
	bctrl
	ld 2,24(1)
	lwz 9,24(30)
	cmplwi 7,9,1
	beq 7,.L19
	cmpdi 7,9,0
	beq 7,.L50
	cmplwi 7,9,2
	beq 7,.L45
	cmplwi 7,9,3
	beq 7,.L45
	cmplwi 7,9,4
	beq 7,.L45
	cmplwi 7,9,5
	beq 7,.L46
	cmplwi 7,9,6
	beq 7,.L46
	cmplwi 7,9,7
	beq 7,.L47
	cmplwi 7,9,8
	beq 7,.L47
	cmplwi 7,9,9
	beq 7,.L50
	cmplwi 7,9,10
	beq 7,.L50
	cmplwi 7,9,11
	beq 7,.L50
	cmplwi 7,9,12
	beq 7,.L50
	cmplwi 7,9,13
	beq 7,.L52
	cmplwi 7,9,14
	beq 7,.L53
	cmplwi 7,9,15
	beq 7,.L50
	cmplwi 7,9,16
	bne 7,.L19
	lwz 9,0(30)
	rldicl. 10,9,55,63
	beq 0,.L19
	ld 10,32(30)
	addi 9,10,-1
	cmpldi 7,9,15
	bgt 7,.L19
	ld 8,16(30)
	cmpldi 7,10,8
	rldicl 9,8,0,61
	rldicr 8,8,0,60
	add 10,10,9
	bgt 7,.L35
	cmpldi 7,10,8
	bgt 7,.L36
	slwi 10,10,3
	li 7,2
	ld 6,0(8)
	slwi 9,9,3
	addi 10,10,-1
	sld 10,7,10
	li 7,1
	sld 7,7,9
	sld 9,3,9
	subf 10,7,10
	xor 9,9,6
	and 9,10,9
	xor 9,9,6
	std 9,0(8)
.L19:
	addi 1,31,112
	li 3,0
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.p2align 4,,15
.L50:
	ld 9,16(30)
	std 3,0(9)
	addi 1,31,112
	li 3,0
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.p2align 4,,15
.L45:
	ld 9,16(30)
	stb 3,0(9)
	addi 1,31,112
	li 3,0
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
.L46:
	ld 9,16(30)
	sth 3,0(9)
	b .L19
.L47:
	ld 9,16(30)
	stw 3,0(9)
	b .L19
.L52:
	ld 9,16(30)
	stfs 1,0(9)
	b .L19
.L53:
	ld 9,16(30)
	stfd 1,0(9)
	b .L19
.L36:
	rldicl 9,9,0,32
	slwi 10,10,3
	ld 11,0(8)
	ld 4,8(8)
	li 7,2
	mulli 6,9,-8
	addi 10,10,-65
	slwi 9,9,3
	sld 10,7,10
	sld 5,3,9
	li 7,-1
	addi 6,6,64
	addi 10,10,-1
	sld 7,7,9
	srad 3,3,6
	xor 6,5,11
	xor 9,3,4
	and 7,7,6
	and 9,10,9
	xor 10,7,11
	xor 9,9,4
	std 10,0(8)
	std 9,8(8)
	b .L19
.L35:
	rldicl 9,9,0,32
	ld 11,0(8)
	li 6,-1
	cmpldi 7,10,16
	slwi 5,9,3
	sld 7,3,5
	sld 6,6,5
	xor 7,7,11
	and 7,6,7
	xor 7,7,11
	std 7,0(8)
	ble 7,.L54
	mulli 9,9,-8
	ld 11,16(8)
	slwi 10,10,3
	li 7,2
	addi 10,10,-129
	addi 9,9,64
	sld 7,7,10
	srad 6,4,9
	srad 3,3,9
	addi 7,7,-1
	sld 9,4,5
	xor 10,6,11
	or 9,3,9
	and 10,7,10
	std 9,8(8)
	xor 10,10,11
	std 10,16(8)
	b .L19
.L54:
	mulli 9,9,-4
	slwi 10,10,3
	ld 11,8(8)
	sld 4,4,5
	addi 10,10,-65
	li 6,2
	addi 9,9,32
	sld 10,6,10
	srad 3,3,9
	srad 9,3,9
	or 7,9,4
	addi 9,10,-1
	xor 10,7,11
	and 9,10,9
	xor 9,9,11
	std 9,8(8)
	b .L19
	.long 0
	.byte 0,0,0,1,128,2,0,0
	.size	avcall_call,.-avcall_call
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
