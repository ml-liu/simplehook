	.file	"vacall-powerpc64.c"
	.csect .text[PR]
	.toc
	.csect .text[PR]
	.toc
LC..0:
	.tc vacall_function[TC],vacall_function[UA]
	.csect .text[PR]
	.align 2
	.align 4
	.globl vacall_receiver
	.globl .vacall_receiver
	.csect vacall_receiver[DS],3
vacall_receiver:
	.llong .vacall_receiver, TOC[tc0], 0
	.csect .text[PR]
.vacall_receiver:
	mflr 0
	std 31,-8(1)
	li 11,0
	std 0,16(1)
	li 0,0
	stdu 1,-304(1)
	mr 31,1
	std 2,40(1)
	stw 0,112(31)
	stw 11,152(31)
	stw 11,168(31)
	std 9,400(31)
	addi 9,31,352
	std 3,352(31)
	stfd 1,172(31)
	std 4,360(31)
	std 5,368(31)
	std 6,376(31)
	std 7,384(31)
	std 8,392(31)
	stfd 2,180(31)
	addi 3,31,112
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
	std 11,144(31)
	std 10,408(31)
	ld 9,LC..0(2)
	ld 9,0(9)
	ld 10,0(9)
	ld 11,16(9)
	mtctr 10
	ld 2,8(9)
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
	ld 31,-8(1)
	mtlr 0
	blr
	.align 4
L..20:
	lbz 3,120(31)
	addi 1,31,304
	ld 0,16(1)
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
LT..vacall_receiver:
	.long 0
	.byte 0,0,32,97,128,1,8,0
	.long 0
	.long LT..vacall_receiver-.vacall_receiver
	.short 15
	.byte "vacall_receiver"
	.byte 31
	.align 2
_section_.text:
	.csect .data[RW],4
	.llong _section_.text
	.extern vacall_function[UA]
