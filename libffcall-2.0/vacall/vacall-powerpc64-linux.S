	.file	"vacall-powerpc64.c"
	.machine power4
	.section	".toc","aw"
	.section	".text"
	.section	".toc","aw"
.LC0:
	.quad	vacall_function
	.section	".text"
	.align 2
	.p2align 4,,15
	.globl vacall_receiver
	.section	".opd","aw"
	.align 3
vacall_receiver:
	.quad	.L.vacall_receiver,.TOC.@tocbase,0
	.previous
	.type	vacall_receiver, @function
.L.vacall_receiver:
	mflr 0
	std 31,-8(1)
	li 11,0
	std 0,16(1)
	stdu 1,-304(1)
	li 0,0
	mr 31,1
	std 2,40(1)
	stw 11,152(31)
	stw 0,112(31)
	stw 11,168(31)
	std 9,400(31)
	std 3,352(31)
	std 4,360(31)
	std 5,368(31)
	std 6,376(31)
	std 7,384(31)
	std 8,392(31)
	std 10,408(31)
	stfd 1,176(31)
	addi 9,31,352
	stfd 2,184(31)
	stfd 3,192(31)
	stfd 4,200(31)
	stfd 5,208(31)
	addis 10,2,.LC0@toc@ha
	addi 3,31,112
	stfd 6,216(31)
	stfd 7,224(31)
	stfd 8,232(31)
	stfd 9,240(31)
	stfd 10,248(31)
	stfd 11,256(31)
	stfd 12,264(31)
	stfd 13,272(31)
	std 9,136(31)
	std 11,144(31)
	ld 9,.LC0@toc@l(10)
	ld 9,0(9)
	ld 10,0(9)
	ld 11,16(9)
	mtctr 10
	ld 2,8(9)
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
	ld 31,-8(1)
	mtlr 0
	blr
	.p2align 4,,15
.L20:
	lbz 3,120(31)
	addi 1,31,304
	ld 0,16(1)
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
	.byte 0,0,0,1,128,1,0,0
	.size	vacall_receiver,.-.L.vacall_receiver
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
