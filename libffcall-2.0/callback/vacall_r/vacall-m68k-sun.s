#NO_APP
	.text
	.even
_callback_receiver:
	link a6,#-32
	moveml #0x3030,sp@-
	clrl a6@(-32)
	lea a6@(8),a2
	movel a2,a6@(-20)
	clrl a6@(-16)
	clrl a6@(-12)
	movel a1,a6@(-4)
	pea a6@(-32)
	movel a0@(4),sp@-
	movel a0@,a2
	jsr a2@
	addql #8,sp
	movel a6@(-12),a3
	tstl a3
	jeq L1
	moveq #1,d2
	cmpl a3,d2
	jeq L46
	moveq #2,d3
	cmpl a3,d3
	jeq L46
	moveq #3,d2
	cmpl a3,d2
	jeq L47
	moveq #4,d3
	cmpl a3,d3
	jeq L48
	moveq #5,d2
	cmpl a3,d2
	jeq L49
	moveq #6,d3
	cmpl a3,d3
	jeq L45
	moveq #7,d2
	cmpl a3,d2
	jeq L45
	moveq #8,d3
	cmpl a3,d3
	jeq L45
	moveq #9,d2
	cmpl a3,d2
	jeq L45
	lea a3@(-10),a2
	moveq #1,d3
	cmpl a2,d3
	jcs L22
	movel a6@(-28),d0
	movel a6@(-24),d1
	jra L1
	.even
L22:
	moveq #12,d2
	cmpl a3,d2
	jeq L50
	moveq #13,d2
	cmpl a3,d2
	jeq L51
	moveq #14,d3
	cmpl a3,d3
	jeq L52
	moveq #15,d2
	cmpl a3,d2
	jne L1
	btst #2,a6@(-30)
	jeq L1
	movel a6@(-8),d2
	moveq #1,d3
	cmpl d2,d3
	jeq L53
	moveq #2,d3
	cmpl d2,d3
	jeq L54
	moveq #4,d3
	cmpl d2,d3
	jeq L55
	moveq #8,d3
	cmpl d2,d3
	jne L1
	movel a6@(-16),a2
	movel a2@,d0
	movel a2@(4),d1
	jra L1
	.even
L55:
	movel a6@(-16),a2
	movel a2@,d0
	jra L1
	.even
L54:
	movel a6@(-16),a2
	clrl d0
	movew a2@,d0
	jra L1
	.even
L53:
	movel a6@(-16),a2
	clrl d0
	moveb a2@,d0
	jra L1
	.even
L52:
	movel a6@(-28),d0
	movel d0,a0
	jra L1
	.even
L51:
	btst #6,a6@(-29)
	jeq L31
	fmoved a6@(-28),fp0
	jra L1
	.even
L31:
	movel a6@(-28),d0
	movel a6@(-24),d1
	jra L1
	.even
L50:
	movel a6@(-32),d2
	btst #6,d2
	jeq L25
	fmoves a6@(-28),fp0
	jra L1
	.even
L25:
	btst #5,d2
	jeq L27
	fmoves a6@(-28),fp1
	fmoved fp1,sp@-
	movel sp@+,d0
	movel sp@+,d1
	jra L1
	.even
L27:
	movel a6@(-28),d0
	jra L1
	.even
L45:
	movel a6@(-28),d0
	jra L1
	.even
L49:
	clrl d0
	movew a6@(-28),d0
	jra L1
	.even
L48:
	movew a6@(-28),d0
	extl d0
	jra L1
	.even
L47:
	clrl d0
	moveb a6@(-28),d0
	jra L1
	.even
L46:
	moveb a6@(-28),d0
	extbl d0
L1:
	moveml a6@(-48),#0xc0c
	unlk a6
	rts
	.even
	.globl	_callback_get_receiver
_callback_get_receiver:
	link a6,#0
	movel a5,sp@-
	movel #__GLOBAL_OFFSET_TABLE_, a5
	lea pc@(0,a5:l),a5
	movel a5@(_callback_receiver:l),d0
	movel sp@+,a5
	unlk a6
	rts
