	.file	"../../vacall/vacall-powerpc64.c"
	.csect .text[PR]
	.toc
	.csect .text[PR]
	.align 2
	.align 4
	.lglobl .callback_receiver
	.csect callback_receiver[DS],3
callback_receiver:
	.llong .callback_receiver, TOC[tc0], 0
	.csect .text[PR]
.callback_receiver:
	mflr 0
	std 30,-16(1)
	std 31,-8(1)
	li 30,0
	std 0,16(1)
	li 0,0
	stdu 1,-304(1)
	ld 12,0(11)
	mr 31,1
	std 9,400(31)
	addi 9,31,352
	stfd 1,172(31)
	stw 0,152(31)
	stw 0,168(31)
	std 3,352(31)
	std 4,360(31)
	ld 3,8(11)
	std 5,368(31)
	addi 4,31,112
	std 6,376(31)
	std 7,384(31)
	std 8,392(31)
	std 10,408(31)
	stfd 2,180(31)
	stfd 3,188(31)
	stfd 4,196(31)
	stfd 5,204(31)
	stfd 6,212(31)
	stfd 7,220(31)
	stfd 8,228(31)
	stfd 9,236(31)
	stfd 10,244(31)
	stfd 11,252(31)
	stfd 12,260(31)
	stfd 13,268(31)
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
	beq 7,L..1
	cmplwi 7,9,1
	beq 7,L..20
	cmplwi 7,9,2
	beq 7,L..23
	cmplwi 7,9,3
	beq 7,L..20
	cmplwi 7,9,4
	beq 7,L..24
	cmplwi 7,9,5
	beq 7,L..25
	cmplwi 7,9,6
	beq 7,L..26
	cmplwi 7,9,7
	beq 7,L..27
	cmplwi 7,9,8
	beq 7,L..21
	cmplwi 7,9,9
	beq 7,L..21
	cmplwi 7,9,10
	beq 7,L..21
	cmplwi 7,9,11
	beq 7,L..21
	cmplwi 7,9,12
	beq 7,L..28
	cmplwi 7,9,13
	beq 7,L..29
	cmplwi 7,9,14
	beq 7,L..21
L..1:
	addi 1,31,304
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.align 4
L..20:
	lbz 3,120(31)
	addi 1,31,304
	ld 0,16(1)
	ld 30,-16(1)
	ld 31,-8(1)
	mtlr 0
	blr
	.align 4
L..23:
	lbz 9,120(31)
	extsb 3,9
	b L..1
	.align 4
L..21:
	ld 3,120(31)
	b L..1
	.align 4
L..24:
	lha 3,120(31)
	b L..1
	.align 4
L..25:
	lhz 3,120(31)
	b L..1
	.align 4
L..26:
	lwa 3,120(31)
	b L..1
	.align 4
L..28:
	lfs 1,120(31)
	b L..1
	.align 4
L..27:
	lwz 3,120(31)
	b L..1
L..29:
	lfd 1,120(31)
	b L..1
LT..callback_receiver:
	.long 0
	.byte 0,0,32,97,128,2,8,0
	.long 0
	.long LT..callback_receiver-.callback_receiver
	.short 17
	.byte "callback_receiver"
	.byte 31
	.align 2
	.toc
LC..0:
	.tc callback_receiver[TC],callback_receiver
	.csect .text[PR]
	.align 2
	.align 4
	.globl callback_get_receiver
	.globl .callback_get_receiver
	.csect callback_get_receiver[DS],3
callback_get_receiver:
	.llong .callback_get_receiver, TOC[tc0], 0
	.csect .text[PR]
.callback_get_receiver:
	std 31,-8(1)
	ld 3,LC..0(2)
	stdu 1,-64(1)
	mr 31,1
	addi 1,31,64
	ld 31,-8(1)
	blr
LT..callback_get_receiver:
	.long 0
	.byte 0,0,32,96,128,1,0,0
	.long LT..callback_get_receiver-.callback_get_receiver
	.short 21
	.byte "callback_get_receiver"
	.byte 31
	.align 2
_section_.text:
	.csect .data[RW],4
	.llong _section_.text
