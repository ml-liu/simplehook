	.file	"vacall-powerpc64.c"
	.machine power4
	.section	".toc","aw"
	.section	".text"
	.align 2
	.p2align 4,,15
	.section	".opd","aw"
	.align 3
callback_receiver:
	.quad	.L.callback_receiver,.TOC.@tocbase,0
	.previous
	.type	callback_receiver, @function
.L.callback_receiver:
	mflr 0
	std 30,-16(1)
	std 31,-8(1)
	li 30,0
	std 0,16(1)
	stdu 1,-304(1)
	li 0,0
	mr 31,1
	ld 12,0(11)
	std 9,400(31)
	addi 9,31,352
	stw 0,152(31)
	stw 0,168(31)
	std 3,352(31)
	std 4,360(31)
	ld 3,8(11)
	std 5,368(31)
	std 6,376(31)
	addi 4,31,112
	std 7,384(31)
	std 8,392(31)
	std 10,408(31)
	stfd 1,176(31)
	stfd 2,184(31)
	stfd 3,192(31)
	stfd 4,200(31)
	stfd 5,208(31)
	stfd 6,216(31)
	stfd 7,224(31)
	stfd 8,232(31)
	stfd 9,240(31)
	stfd 10,248(31)
	stfd 11,256(31)
	stfd 12,264(31)
	stfd 13,272(31)
	std 9,136(31)
	std 0,144(31)
	stw 30,112(31)
	std 2,40(1)
	ld 9,0(12)
	ld 11,16(12)
	mtctr 9
	ld 2,8(12)
	bctrl
	ld 2,40(1)
	lwz 9,152(31)
	cmpdi 7,9,0
	beq 7,.L1
	cmplwi 7,9,1
	beq 7,.L20
	cmplwi 7,9,2
	beq 7,.L23
	cmplwi 7,9,3
	beq 7,.L20
	cmplwi 7,9,4
	beq 7,.L24
	cmplwi 7,9,5
	beq 7,.L25
	cmplwi 7,9,6
	beq 7,.L26
	cmplwi 7,9,7
	beq 7,.L27
	cmplwi 7,9,8
	beq 7,.L21
	cmplwi 7,9,9
	beq 7,.L21
	cmplwi 7,9,10
	beq 7,.L21
	cmplwi 7,9,11
	beq 7,.L21
	cmplwi 7,9,12
	beq 7,.L28
	cmplwi 7,9,13
	beq 7,.L29
	cmplwi 7,9,14
	beq 7,.L21
.L1:
	addi 1,31,304
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.p2align 4,,15
.L20:
	lbz 3,120(31)
	addi 1,31,304
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.p2align 4,,15
.L23:
	lbz 9,120(31)
	extsb 3,9
	b .L1
	.p2align 4,,15
.L21:
	ld 3,120(31)
	b .L1
	.p2align 4,,15
.L24:
	lha 3,120(31)
	b .L1
	.p2align 4,,15
.L25:
	lhz 3,120(31)
	b .L1
	.p2align 4,,15
.L26:
	lwa 3,120(31)
	b .L1
	.p2align 4,,15
.L28:
	lfs 1,120(31)
	b .L1
	.p2align 4,,15
.L27:
	lwz 3,120(31)
	b .L1
.L29:
	lfd 1,120(31)
	b .L1
	.long 0
	.byte 0,0,0,1,128,2,0,0
	.size	callback_receiver,.-.L.callback_receiver
	.align 2
	.p2align 4,,15
	.globl callback_get_receiver
	.section	".opd","aw"
	.align 3
callback_get_receiver:
	.quad	.L.callback_get_receiver,.TOC.@tocbase,0
	.previous
	.type	callback_get_receiver, @function
.L.callback_get_receiver:
	std 31,-8(1)
	stdu 1,-64(1)
	addis 3,2,callback_receiver@toc@ha
	addi 3,3,callback_receiver@toc@l
	mr 31,1
	addi 1,31,64
	ld 31,-8(1)
	blr
	.long 0
	.byte 0,0,0,0,128,1,0,0
	.size	callback_get_receiver,.-.L.callback_get_receiver
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
