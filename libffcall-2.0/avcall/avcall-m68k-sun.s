#NO_APP
	.text
	.even
	.globl	_avcall_call
_avcall_call:
	link a6,#0
	moveml #0x3820,sp@-
	movel a6@(8),a2
	lea sp@(-1024),sp
	movel a2@(24),d1
	movel a2@(20),d0
	subl d1,d0
	asrl #2,d0
	jle L54
	movel sp,a1
	movel d1,a0
	movel d0,d2
	.even
L6:
	movel a0@+,a1@+
	subql #1,d2
	jne L6
L54:
	moveq #16,d0
	cmpl a2@(12),d0
	jeq L59
L7:
	movel a2@(4),a0
	jsr a0@
	movel d0,d2
	movel d1,d3
	movel a2@(12),a1
	moveq #1,d1
	cmpl a1,d1
	jeq L9
	tstl a1
	jeq L55
	moveq #2,d4
	cmpl a1,d4
	jeq L58
	moveq #3,d4
	cmpl a1,d4
	jeq L58
	moveq #4,d4
	cmpl a1,d4
	jeq L58
	moveq #5,d4
	cmpl a1,d4
	jeq L57
	moveq #6,d4
	cmpl a1,d4
	jeq L57
	moveq #7,d4
	cmpl a1,d4
	jeq L55
	moveq #8,d4
	cmpl a1,d4
	jeq L55
	moveq #9,d4
	cmpl a1,d4
	jeq L55
	moveq #10,d4
	cmpl a1,d4
	jeq L55
	lea a1@(-11),a0
	moveq #1,d4
	cmpl a0,d4
	jcc L56
	moveq #13,d4
	cmpl a1,d4
	jeq L60
	moveq #14,d4
	cmpl a1,d4
	jeq L61
	moveq #15,d0
	cmpl a1,d0
	jeq L55
	moveq #16,d1
	cmpl a1,d1
	jne L9
	btst #1,a2@(2)
	jeq L9
	movel a2@(16),d0
	moveq #1,d4
	cmpl d0,d4
	jeq L58
	moveq #2,d1
	cmpl d0,d1
	jeq L57
	moveq #4,d4
	cmpl d0,d4
	jeq L55
	moveq #8,d1
	cmpl d0,d1
	jne L9
L56:
	movel a2@(8),a0
	movel d2,a0@
	movel d3,a0@(4)
	jra L9
	.even
L55:
	movel a2@(8),a0
	movel d2,a0@
	jra L9
	.even
L57:
	movel a2@(8),a0
	movew d2,a0@
	jra L9
	.even
L58:
	movel a2@(8),a0
	moveb d2,a0@
	jra L9
	.even
L61:
	btst #6,a2@(3)
	jeq L39
	movel a2@(8),a0
	fmoved fp0,a0@
	jra L9
	.even
L39:
	movel a2@(8),a0
	movel d0,a0@
	movel d1,a0@(4)
	jra L9
	.even
L60:
	movel a2@,d2
	btst #6,d2
	jeq L33
	movel a2@(8),a0
	fmoves fp0,a0@
	jra L9
	.even
L33:
	btst #5,d2
	jeq L35
	movel a2@(8),a0
	movel d1,sp@-
	movel d0,sp@-
	fmoved sp@+,fp0
	fmoves fp0,a0@
	jra L9
	.even
L35:
	movel a2@(8),a0
	movel d0,a0@
	jra L9
	.even
L59:
#APP
	movel a2@(8),a1
#NO_APP
	jra L7
	.even
L9:
	clrl d0
	moveml a6@(-16),#0x41c
	unlk a6
	rts
