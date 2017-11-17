	.file	"vacall-powerpc64.c"
	.machine power4
	.abiversion 2
	.section	".toc","aw"
	.section	".text"
	.align 2
	.p2align 4,,15
	.type	callback_receiver, @function
callback_receiver:
0:	addis 2,12,.TOC.-0b@ha
	addi 2,2,.TOC.-0b@l
	.localentry	callback_receiver,.-callback_receiver
	mflr 0
	std 30,-16(1)
	std 31,-8(1)
	std 0,16(1)
	stdu 1,-224(1)
	li 0,0
	ld 30,0(11)
	mr 31,1
	std 3,256(31)
	std 4,264(31)
	addi 4,31,32
	ld 3,8(11)
	std 9,304(31)
	mtctr 30
	li 9,0
	std 5,272(31)
	std 6,280(31)
	std 7,288(31)
	std 8,296(31)
	stw 9,32(31)
	std 10,312(31)
	stfd 1,96(31)
	stfd 2,104(31)
	mr 12,30
	addi 9,31,256
	stfd 3,112(31)
	stfd 4,120(31)
	stfd 5,128(31)
	stfd 6,136(31)
	std 9,56(31)
	stfd 7,144(31)
	stfd 8,152(31)
	stfd 9,160(31)
	stfd 10,168(31)
	stfd 11,176(31)
	stfd 12,184(31)
	stfd 13,192(31)
	std 0,64(31)
	stw 0,72(31)
	stw 0,88(31)
	std 2,24(1)
	bctrl
	ld 2,24(1)
	lwz 9,72(31)
	cmpdi 7,9,0
	beq 7,.L1
	cmplwi 7,9,1
	beq 7,.L27
	cmplwi 7,9,2
	beq 7,.L30
	cmplwi 7,9,3
	beq 7,.L27
	cmplwi 7,9,4
	beq 7,.L31
	cmplwi 7,9,5
	beq 7,.L32
	cmplwi 7,9,6
	beq 7,.L33
	cmplwi 7,9,7
	beq 7,.L34
	cmplwi 7,9,8
	beq 7,.L28
	cmplwi 7,9,9
	beq 7,.L28
	cmplwi 7,9,10
	beq 7,.L28
	cmplwi 7,9,11
	beq 7,.L28
	cmplwi 7,9,12
	beq 7,.L35
	cmplwi 7,9,13
	beq 7,.L36
	cmplwi 7,9,14
	beq 7,.L28
	cmplwi 7,9,15
	bne 7,.L1
	lwz 9,32(31)
	rldicl. 10,9,54,63
	beq 0,.L1
	ld 9,80(31)
	addi 10,9,-1
	cmpldi 7,10,15
	bgt 7,.L1
	ld 8,64(31)
	cmpldi 7,9,8
	rldicl 10,8,0,61
	rldicr 8,8,0,60
	add 9,9,10
	bgt 7,.L17
	cmpldi 7,9,8
	slwi 9,9,3
	bgt 7,.L18
	ld 7,0(8)
	addi 9,9,-1
	li 8,2
	slwi 10,10,3
	sld 9,8,9
	addi 9,9,-1
	and 9,9,7
	srad 3,9,10
.L1:
	addi 1,31,224
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.p2align 4,,15
.L27:
	addi 1,31,224
	lbz 3,40(31)
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.p2align 4,,15
.L30:
	lbz 9,40(31)
	extsb 3,9
	b .L1
	.p2align 4,,15
.L28:
	ld 3,40(31)
	b .L1
	.p2align 4,,15
.L31:
	lha 3,40(31)
	b .L1
	.p2align 4,,15
.L32:
	lhz 3,40(31)
	b .L1
	.p2align 4,,15
.L33:
	lwa 3,40(31)
	b .L1
	.p2align 4,,15
.L35:
	lfs 1,40(31)
	b .L1
	.p2align 4,,15
.L34:
	lwz 3,40(31)
	b .L1
.L36:
	lfd 1,40(31)
	b .L1
.L17:
	cmpldi 7,9,16
	rldicl 10,10,0,32
	slwi 9,9,3
	ble 7,.L37
	li 7,2
	addi 9,9,-129
	ld 0,16(8)
	ld 5,0(8)
	mulli 6,10,-8
	sld 9,7,9
	ld 7,8(8)
	addi 8,9,-1
	slwi 9,10,3
	addi 6,6,64
	and 10,8,0
	srad 8,5,9
	sld 5,7,6
	srad 9,7,9
	sld 10,10,6
	or 3,8,5
	or 4,10,9
	b .L1
.L18:
	rldicl 10,10,0,32
	li 7,2
	ld 6,8(8)
	ld 8,0(8)
	addi 9,9,-65
	sld 9,7,9
	mulli 7,10,-8
	slwi 10,10,3
	addi 9,9,-1
	srad 10,8,10
	and 9,9,6
	addi 7,7,64
	sld 9,9,7
	or 3,9,10
	b .L1
.L37:
	li 7,2
	addi 9,9,-65
	ld 5,8(8)
	ld 6,0(8)
	sld 9,7,9
	mulli 7,10,-4
	addi 9,9,-1
	addi 7,7,32
	and 8,9,5
	slwi 9,10,3
	sld 10,8,7
	srad 6,6,9
	srad 4,8,9
	sld 7,10,7
	or 3,6,7
	b .L1
	.long 0
	.byte 0,0,0,1,128,2,0,0
	.size	callback_receiver,.-callback_receiver
	.align 2
	.p2align 4,,15
	.globl callback_get_receiver
	.type	callback_get_receiver, @function
callback_get_receiver:
0:	addis 2,12,.TOC.-0b@ha
	addi 2,2,.TOC.-0b@l
	.localentry	callback_get_receiver,.-callback_get_receiver
	std 31,-8(1)
	stdu 1,-48(1)
	addis 3,2,callback_receiver@toc@ha
	addi 3,3,callback_receiver@toc@l
	mr 31,1
	addi 1,31,48
	ld 31,-8(1)
	blr
	.long 0
	.byte 0,0,0,0,128,1,0,0
	.size	callback_get_receiver,.-callback_get_receiver
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
