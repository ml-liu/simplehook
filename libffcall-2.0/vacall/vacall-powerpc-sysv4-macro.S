	.file	"vacall-powerpc.c"
	.section	".text"
	.align 2
	.globl vacall_receiver
	.type	vacall_receiver, @function
vacall_receiver:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	stwu 1,-176(1)
	mflr 0
	li 11,0
	stw 0,180(1)
	stw 31,172(1)
	mr 31,1
	stw 9,76(31)
	addi 0,31,184
	lis 9,vacall_function@ha
	stw 3,52(31)
	lwz 9,vacall_function@l(9)
	addi 3,31,16
	stw 5,60(31)
	mtctr 9
	stw 6,64(31)
	stw 7,68(31)
	stw 8,72(31)
	stw 10,80(31)
	stw 0,32(31)
	stw 11,84(31)
	stw 4,56(31)
	stfd 1,88(31)
	stfd 2,96(31)
	stfd 3,104(31)
	stfd 4,112(31)
	stfd 5,120(31)
	stfd 6,128(31)
	stfd 7,136(31)
	stfd 8,144(31)
	stw 11,16(31)
	stw 11,48(31)
	stw 11,36(31)
	stw 11,40(31)
	bctrl
	lwz 9,40(31)
	cmpwi 0,9,0
	beq- 0,.L1
	cmpwi 0,9,1
	beq- 0,.L41
	cmpwi 0,9,2
	beq- 0,.L42
	cmpwi 0,9,3
	beq- 0,.L41
	cmpwi 0,9,4
	beq- 0,.L43
	cmpwi 0,9,5
	beq- 0,.L44
	cmpwi 0,9,6
	beq- 0,.L40
	cmpwi 0,9,7
	beq- 0,.L40
	cmpwi 0,9,8
	beq- 0,.L40
	cmpwi 0,9,9
	beq- 0,.L40
	addi 0,9,-10
	cmplwi 0,0,1
	bgt- 0,.L22
	lwz 3,24(31)
	lwz 4,28(31)
.L1:
	lwz 11,0(1)
	lwz 0,4(11)
	lwz 31,-4(11)
	mtlr 0
	mr 1,11
	blr
.L22:
	cmpwi 0,9,12
	beq- 0,.L45
	cmpwi 0,9,13
	beq- 0,.L46
	cmpwi 0,9,14
	beq- 0,.L40
	cmpwi 0,9,15
	bne+ 0,.L1
	lwz 0,16(31)
	andi. 9,0,1024
	beq- 0,.L1
	lwz 0,44(31)
	cmpwi 0,0,1
	beq- 0,.L47
	cmpwi 0,0,2
	beq- 0,.L48
	cmpwi 0,0,4
	beq- 0,.L49
	cmpwi 0,0,8
	bne+ 0,.L1
	lwz 9,36(31)
	lwz 4,4(9)
.L39:
	lwz 3,0(9)
	b .L1
.L49:
	lwz 9,36(31)
	b .L39
.L48:
	lwz 9,36(31)
	lhz 3,0(9)
	b .L1
.L47:
	lwz 9,36(31)
	lbz 3,0(9)
	b .L1
.L40:
	lwz 3,24(31)
	b .L1
.L46:
	lfd 1,24(31)
	b .L1
.L45:
	lfs 1,24(31)
	b .L1
.L44:
	lhz 3,24(31)
	b .L1
.L43:
	lha 3,24(31)
	b .L1
.L41:
	lbz 3,24(31)
	b .L1
.L42:
	lbz 0,24(31)
	slwi 0,0,24
	srawi 3,0,24
	b .L1
	.size	vacall_receiver, .-vacall_receiver
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
