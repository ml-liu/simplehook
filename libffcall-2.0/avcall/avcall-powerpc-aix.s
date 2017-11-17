	.file	"avcall-powerpc.c"
	.toc
	.csect .text[PR]
	.align 2
	.globl avcall_call
	.globl .avcall_call
	.csect avcall_call[DS]
avcall_call:
	.long .avcall_call, TOC[tc0], 0
	.csect .text[PR]
.avcall_call:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	mflr 0
	stw 0,8(1)
	stw 30,-8(1)
	stw 31,-4(1)
	stw 29,-12(1)
	stwu 1,-72(1)
	lwz 0,20(3)
	lwz 11,24(3)
	mr 30,3
	subfc 0,11,0
	srawi 8,0,2
	li 3,8
	lwz 9,0(1)
	cmpw 0,3,8
	mr 31,1
	stwu 9,-1040(1)
	addi 0,1,71
	rlwinm 10,0,0,0,27
	bge- 0,L..89
L..6:
	slwi 9,3,2
	addi 3,3,1
	cmpw 0,3,8
	lwzx 0,9,11
	add 9,9,10
	stw 0,-32(9)
	blt+ 0,L..6
L..88:
	lwz 9,40(30)
	subfc 9,30,9
	addi 9,9,-44
	srawi. 9,9,3
	beq- 0,L..8
	cmpwi 0,9,1
	beq- 0,L..11
	cmpwi 0,9,2
	beq- 0,L..14
	cmpwi 0,9,3
	beq- 0,L..17
	cmpwi 0,9,4
	beq- 0,L..20
	cmpwi 0,9,5
	beq- 0,L..23
	cmpwi 0,9,6
	beq- 0,L..26
	cmpwi 0,9,7
	beq- 0,L..29
	cmpwi 0,9,8
	beq- 0,L..32
	cmpwi 0,9,9
	beq- 0,L..35
	cmpwi 0,9,10
	beq- 0,L..38
	cmpwi 0,9,11
	beq- 0,L..41
	cmpwi 0,9,12
	beq- 0,L..44
L..47:
	lfd 13,140(30)
L..44:
	lfd 12,132(30)
L..41:
	lfd 11,124(30)
L..38:
	lfd 10,116(30)
L..35:
	lfd 9,108(30)
L..32:
	lfd 8,100(30)
L..29:
	lfd 7,92(30)
L..26:
	lfd 6,84(30)
L..23:
	lfd 5,76(30)
L..20:
	lfd 4,68(30)
L..17:
	lfd 3,60(30)
L..14:
	lfd 2,52(30)
L..11:
	lfd 1,44(30)
L..8:
	lwz 29,4(30)
	lwz 9,24(11)
	lwz 0,0(29)
	lwz 10,28(11)
	lwz 3,0(11)
	mtctr 0
	lwz 4,4(11)
	lwz 5,8(11)
	lwz 6,12(11)
	lwz 7,16(11)
	lwz 8,20(11)
	stw 2,20(1)
	lwz 11,8(29)
	lwz 2,4(29)
	bctrl
	lwz 2,20(1)
	lwz 9,12(30)
	cmpwi 0,9,1
	beq- 0,L..49
	cmpwi 0,9,0
	beq- 0,L..99
	cmpwi 0,9,2
	beq- 0,L..92
	cmpwi 0,9,3
	beq- 0,L..92
	cmpwi 0,9,4
	beq- 0,L..92
	cmpwi 0,9,5
	beq- 0,L..91
	cmpwi 0,9,6
	beq- 0,L..91
	cmpwi 0,9,7
	beq- 0,L..99
	cmpwi 0,9,8
	beq- 0,L..99
	cmpwi 0,9,9
	beq- 0,L..99
	cmpwi 0,9,10
	beq- 0,L..99
	addi 0,9,-11
	cmplwi 0,0,1
	ble- 0,L..98
	cmpwi 0,9,13
	beq- 0,L..100
	cmpwi 0,9,14
	beq- 0,L..101
	cmpwi 0,9,15
	beq- 0,L..99
	cmpwi 0,9,16
	beq- 0,L..102
L..49:
	lwz 1,0(1)
	li 3,0
	lwz 0,8(1)
	lwz 29,-12(1)
	mtlr 0
	lwz 30,-8(1)
	lwz 31,-4(1)
	blr
L..102:
	lwz 0,0(30)
	andi. 9,0,512
	beq- 0,L..49
	lwz 0,16(30)
	cmpwi 0,0,1
	beq- 0,L..92
	cmpwi 0,0,2
	beq- 0,L..91
	cmpwi 0,0,4
	beq- 0,L..99
	cmpwi 0,0,8
	bne+ 0,L..49
L..98:
	lwz 9,8(30)
	stw 4,4(9)
L..90:
	stw 3,0(9)
	b L..49
L..99:
	lwz 9,8(30)
	b L..90
L..91:
	lwz 9,8(30)
	sth 3,0(9)
	b L..49
L..92:
	lwz 9,8(30)
	stb 3,0(9)
	b L..49
L..101:
	lwz 9,8(30)
	stfd 1,0(9)
	b L..49
L..100:
	lwz 9,8(30)
	frsp 0,1
	stfs 0,0(9)
	b L..49
L..89:
	lwz 11,24(30)
	b L..88
LT..avcall_call:
	.long 0
	.byte 0,0,32,97,128,3,1,0
	.long 0
	.long LT..avcall_call-.avcall_call
	.short 11
	.byte "avcall_call"
	.byte 31
	.align 2
_section_.text:
	.csect .data[RW],3
	.long _section_.text
