.text
	.align 2
	.globl _avcall_call
_avcall_call:
	mflr r0
	stmw r29,-12(r1)
	stw r0,8(r1)
	mr r29,r3
	stwu r1,-1104(r1)
	li r3,8
	lwz r0,20(r29)
	mr r30,r1
	lwz r9,24(r29)
	addi r10,r1,56
	subf r0,r9,r0
	srawi r11,r0,2
	cmpw cr0,r3,r11
	bge- cr0,L89
	mr r12,r9
L6:
	slwi r9,r3,2
	addi r3,r3,1
	cmpw cr0,r3,r11
	lwzx r0,r9,r12
	add r9,r9,r10
	stw r0,-32(r9)
	blt+ cr0,L6
L88:
	lwz r9,40(r29)
	subf r9,r29,r9
	addi r9,r9,-44
	srawi. r9,r9,3
	beq- cr0,L8
	cmpwi cr0,r9,1
	beq- cr0,L11
	cmpwi cr0,r9,2
	beq- cr0,L14
	cmpwi cr0,r9,3
	beq- cr0,L17
	cmpwi cr0,r9,4
	beq- cr0,L20
	cmpwi cr0,r9,5
	beq- cr0,L23
	cmpwi cr0,r9,6
	beq- cr0,L26
	cmpwi cr0,r9,7
	beq- cr0,L29
	cmpwi cr0,r9,8
	beq- cr0,L32
	cmpwi cr0,r9,9
	beq- cr0,L35
	cmpwi cr0,r9,10
	beq- cr0,L38
	cmpwi cr0,r9,11
	beq- cr0,L41
	cmpwi cr0,r9,12
	beq- cr0,L44
L47:
	lfd f13,140(r29)
L44:
	lfd f12,132(r29)
L41:
	lfd f11,124(r29)
L38:
	lfd f10,116(r29)
L35:
	lfd f9,108(r29)
L32:
	lfd f8,100(r29)
L29:
	lfd f7,92(r29)
L26:
	lfd f6,84(r29)
L23:
	lfd f5,76(r29)
L20:
	lfd f4,68(r29)
L17:
	lfd f3,60(r29)
L14:
	lfd f2,52(r29)
L11:
	lfd f1,44(r29)
L8:
	lwz r0,4(r29)
	lwz r9,24(r12)
	lwz r10,28(r12)
	mtctr r0
	lwz r3,0(r12)
	lwz r4,4(r12)
	lwz r5,8(r12)
	lwz r6,12(r12)
	lwz r7,16(r12)
	lwz r8,20(r12)
	bctrl
	lwz r9,12(r29)
	cmpwi cr0,r9,1
	beq- cr0,L49
	cmpwi cr0,r9,0
	beq- cr0,L99
	cmpwi cr0,r9,2
	beq- cr0,L92
	cmpwi cr0,r9,3
	beq- cr0,L92
	cmpwi cr0,r9,4
	beq- cr0,L92
	cmpwi cr0,r9,5
	beq- cr0,L91
	cmpwi cr0,r9,6
	beq- cr0,L91
	cmpwi cr0,r9,7
	beq- cr0,L99
	cmpwi cr0,r9,8
	beq- cr0,L99
	cmpwi cr0,r9,9
	beq- cr0,L99
	cmpwi cr0,r9,10
	beq- cr0,L99
	addi r0,r9,-11
	cmplwi cr0,r0,1
	ble- cr0,L98
	cmpwi cr0,r9,13
	beq- cr0,L100
	cmpwi cr0,r9,14
	beq- cr0,L101
	cmpwi cr0,r9,15
	beq- cr0,L99
	cmpwi cr0,r9,16
	beq- cr0,L102
L49:
	lwz r1,0(r1)
	li r3,0
	lwz r0,8(r1)
	lmw r29,-12(r1)
	mtlr r0
	blr
L102:
	lwz r0,0(r29)
	andi. r9,r0,512
	beq- cr0,L49
	lwz r0,16(r29)
	cmpwi cr0,r0,1
	beq- cr0,L92
	cmpwi cr0,r0,2
	beq- cr0,L91
	cmpwi cr0,r0,4
	beq- cr0,L99
	cmpwi cr0,r0,8
	bne+ cr0,L49
L98:
	lwz r9,8(r29)
	stw r4,4(r9)
L90:
	stw r3,0(r9)
	b L49
L99:
	lwz r9,8(r29)
	b L90
L91:
	lwz r9,8(r29)
	sth r3,0(r9)
	b L49
L92:
	lwz r9,8(r29)
	stb r3,0(r9)
	b L49
L101:
	lwz r9,8(r29)
	stfd f1,0(r9)
	b L49
L100:
	lwz r9,8(r29)
	stfs f1,0(r9)
	b L49
L89:
	lwz r12,24(r29)
	b L88
