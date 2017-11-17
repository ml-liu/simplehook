#include "asm-hppa64.h"
	.LEVEL 2.0w
	TEXT1()
	TEXT2()
	.align 8
GLOBL(avcall_call)
		DECLARE_FUNCTION(avcall_call)
DEF(avcall_call)
	.PROC
	.CALLINFO FRAME=256,CALLS,SAVE_RP,SAVE_SP,ENTRY_GR=9
	.ENTRY
	copy %r3,%r1
	std %r2,-16(%r30)
	copy %r30,%r3
	std,ma %r1,256(%r30)
	ldi 8,%r31
	std %r9,16(%r3)
	copy %r27,%r9
	std %r8,24(%r3)
	copy %r26,%r8
	std %r7,32(%r3)
	ldo -80(%r30),%r7
	std %r6,40(%r3)
	std %r5,48(%r3)
	std %r4,56(%r3)
	ldd 40(%r26),%r29
	ldd 48(%r26),%r5
	sub %r29,%r5,%r29
	extrd,s %r29,29+32-1,32,%r6
	cmpb,<= %r6,%r31,L(115)
	ldo 2112(%r30),%r30
DEF(L(6))
	depd,z %r31,60,61,%r29
	ldo 1(%r31),%r31
	add,l %r29,%r5,%r2
	extrd,s %r31,63,32,%r31
	ldd 0(%r2),%r4
	add,l %r29,%r7,%r29
	cmpb,> %r6,%r31,L(6)
	std %r4,0(%r29)
DEF(L(115))
	ldw 24(%r8),%r31
	ldi 16,%r29
	cmpb,= %r29,%r31,L(120)
	copy %r31,%r4
DEF(L(7))
	cmpib,>=,n 0,%r6,L(8)
	ldw 68(%r8),%r2
	extrw,u %r2,31,1,%r29
	cmpib,=,n 0,%r29,L(9)
	fldd 0(%r5),%fr4
DEF(L(10))
	cmpib,>=,n 1,%r6,L(8)
	ldi 2,%r31
	and %r2,%r31,%r29
	cmpib,=,n 0,%r29,L(14)
	fldd 8(%r5),%fr5
DEF(L(15))
	cmpib,>=,n 2,%r6,L(8)
	ldi 4,%r31
	and %r2,%r31,%r29
	cmpib,=,n 0,%r29,L(19)
	fldd 16(%r5),%fr6
DEF(L(20))
	cmpib,>=,n 3,%r6,L(8)
	ldi 8,%r31
	and %r2,%r31,%r29
	cmpib,=,n 0,%r29,L(24)
	fldd 24(%r5),%fr7
DEF(L(25))
	cmpib,>=,n 4,%r6,L(8)
	ldi 16,%r31
	and %r2,%r31,%r29
	cmpib,=,n 0,%r29,L(29)
	fldd 32(%r5),%fr8
DEF(L(30))
	cmpib,>=,n 5,%r6,L(8)
	ldi 32,%r31
	and %r2,%r31,%r29
	cmpib,=,n 0,%r29,L(34)
	fldd 40(%r5),%fr9
DEF(L(35))
	cmpib,>=,n 6,%r6,L(8)
	ldi 64,%r31
	and %r2,%r31,%r29
	cmpib,=,n 0,%r29,L(39)
	fldd 48(%r5),%fr10
DEF(L(40))
	cmpib,>=,n 7,%r6,L(8)
	ldi 128,%r31
	and %r2,%r31,%r29
	cmpib,=,n 0,%r29,L(44)
	fldd 56(%r5),%fr11
DEF(L(45))
	cmpiclr,>= 8,%r6,%r0
	ldo 64(%r7),%r1
DEF(L(8))
	cmpib,=,n 13,%r4,L(121)
	cmpib,=,n 14,%r4,L(122)
	copy %r1,%r29
	ldd 8(%r8),%r31
	ldd 16(%r31),%r2
	ldd 24(%r31),%r27
	bve,l (%r2),%r2
	nop
	ldw 24(%r8),%r2
	copy %r9,%r27
	cmpib,= 1,%r2,L(50)
	copy %r28,%r1
	cmpib,=,n 0,%r2,L(116)
	cmpib,=,n 2,%r2,L(119)
	cmpib,=,n 3,%r2,L(119)
	cmpib,=,n 4,%r2,L(119)
	cmpib,=,n 5,%r2,L(118)
	cmpib,=,n 6,%r2,L(118)
	cmpib,=,n 7,%r2,L(117)
	cmpib,=,n 8,%r2,L(117)
	cmpib,=,n 9,%r2,L(116)
	cmpib,=,n 11,%r2,L(116)
	cmpib,=,n 10,%r2,L(116)
	cmpib,=,n 12,%r2,L(116)
	cmpib,= 15,%r2,L(116)
	ldi 16,%r31
	cmpb,=,n %r31,%r2,L(123)
DEF(L(50))
	ldd -16(%r3),%r2
DEF(L(138))
	ldi 0,%r28
	ldd 16(%r3),%r9
	ldd 24(%r3),%r8
	ldd 32(%r3),%r7
	ldd 40(%r3),%r6
	ldd 48(%r3),%r5
	ldd 56(%r3),%r4
	ldo 64(%r3),%r30
	bve (%r2)
	ldd,mb -64(%r30),%r3
DEF(L(123))
	ldw 0(%r8),%r31
	extrd,u %r31,54+1-1,1,%r31
	cmpib,= 0,%r31,L(138)
	ldd -16(%r3),%r2
	ldd 32(%r8),%r2
	ldo -1(%r2),%r31
	cmpib,*<<,n 15,%r31,L(138)
	ldd -16(%r3),%r2
	cmpib,*=,n 1,%r2,L(124)
	cmpib,*=,n 2,%r2,L(125)
	cmpib,*= 3,%r2,L(126)
	extrd,s %r28,23,24,%r4
	cmpib,*= 4,%r2,L(127)
	extrd,s %r28,31,32,%r5
	cmpib,*=,n 5,%r2,L(128)
	cmpib,*=,n 6,%r2,L(129)
	cmpib,*= 7,%r2,L(130)
	ldo -8(%r2),%r31
	cmpib,*<< 8,%r31,L(50)
	extrd,s %r28,7,8,%r31
	ldd 16(%r8),%r2
	stb %r31,0(%r2)
	extrd,s %r28,15,16,%r4
	ldd 16(%r8),%r31
	extrd,s %r28,23,24,%r2
	stb %r4,1(%r31)
	extrd,s %r28,31,32,%r5
	ldd 16(%r8),%r31
	extrd,s %r28,39,40,%r4
	stb %r2,2(%r31)
	extrd,s %r28,47,48,%r6
	ldd 16(%r8),%r2
	extrd,s %r28,55,56,%r7
	stb %r5,3(%r2)
	ldd 16(%r8),%r31
	stb %r4,4(%r31)
	ldd 16(%r8),%r2
	stb %r6,5(%r2)
	ldd 16(%r8),%r31
	stb %r7,6(%r31)
	ldd 16(%r8),%r2
	stb %r28,7(%r2)
	ldd 32(%r8),%r2
	cmpib,*=,n 8,%r2,L(138)
	ldd -16(%r3),%r2
	cmpib,*=,n 9,%r2,L(131)
	cmpib,*=,n 10,%r2,L(132)
	cmpib,*=,n 11,%r2,L(133)
	cmpib,*=,n 12,%r2,L(134)
	cmpib,*= 13,%r2,L(135)
	extrd,s %r29,7,8,%r31
	cmpib,*=,n 14,%r2,L(136)
	cmpib,*= 15,%r2,L(137)
	ldi 16,%r31
	cmpb,*<> %r31,%r2,L(138)
	ldd -16(%r3),%r2
	ldd 16(%r8),%r2
	extrd,s %r29,7,8,%r31
	stb %r31,8(%r2)
	extrd,s %r29,15,16,%r4
	ldd 16(%r8),%r31
	extrd,s %r29,23,24,%r2
	stb %r4,9(%r31)
	extrd,s %r29,31,32,%r5
	ldd 16(%r8),%r31
	extrd,s %r29,39,40,%r4
	stb %r2,10(%r31)
	extrd,s %r29,47,48,%r6
	ldd 16(%r8),%r2
	extrd,s %r29,55,56,%r7
	stb %r5,11(%r2)
	ldd 16(%r8),%r31
	stb %r4,12(%r31)
	ldd 16(%r8),%r2
	stb %r6,13(%r2)
	ldd 16(%r8),%r31
	stb %r7,14(%r31)
	ldd 16(%r8),%r2
	b L(50)
	stb %r29,15(%r2)
DEF(L(137))
	ldd 16(%r8),%r2
	extrd,s %r29,7,8,%r31
	stb %r31,8(%r2)
	extrd,s %r29,15,16,%r4
	ldd 16(%r8),%r31
	extrd,s %r29,23,24,%r2
	stb %r4,9(%r31)
	extrd,s %r29,31,32,%r5
	ldd 16(%r8),%r31
	extrd,s %r29,39,40,%r4
	stb %r2,10(%r31)
	extrd,s %r29,47,48,%r6
	ldd 16(%r8),%r2
	extrd,s %r29,55,56,%r29
	stb %r5,11(%r2)
	ldd 16(%r8),%r31
	stb %r4,12(%r31)
	ldd 16(%r8),%r2
	stb %r6,13(%r2)
	ldd 16(%r8),%r31
	b L(50)
	stb %r29,14(%r31)
DEF(L(136))
	ldd 16(%r8),%r2
	stb %r31,8(%r2)
	extrd,s %r29,15,16,%r4
	ldd 16(%r8),%r31
	extrd,s %r29,23,24,%r2
	stb %r4,9(%r31)
	extrd,s %r29,31,32,%r5
	ldd 16(%r8),%r31
	extrd,s %r29,39,40,%r4
	stb %r2,10(%r31)
	extrd,s %r29,47,48,%r29
	ldd 16(%r8),%r31
	stb %r5,11(%r31)
	ldd 16(%r8),%r2
	stb %r4,12(%r2)
	ldd 16(%r8),%r31
	b L(50)
	stb %r29,13(%r31)
DEF(L(135))
	ldd 16(%r8),%r2
	stb %r31,8(%r2)
	extrd,s %r29,15,16,%r4
	ldd 16(%r8),%r31
	extrd,s %r29,23,24,%r5
	stb %r4,9(%r31)
	extrd,s %r29,31,32,%r6
	ldd 16(%r8),%r2
	extrd,s %r29,39,40,%r29
	stb %r5,10(%r2)
	ldd 16(%r8),%r31
	stb %r6,11(%r31)
	ldd 16(%r8),%r2
	b L(50)
	stb %r29,12(%r2)
DEF(L(134))
	ldd 16(%r8),%r2
	extrd,s %r29,7,8,%r31
	stb %r31,8(%r2)
	extrd,s %r29,15,16,%r4
	ldd 16(%r8),%r31
	extrd,s %r29,23,24,%r5
	stb %r4,9(%r31)
	extrd,s %r29,31,32,%r29
	ldd 16(%r8),%r31
	stb %r5,10(%r31)
	ldd 16(%r8),%r2
	b L(50)
	stb %r29,11(%r2)
DEF(L(133))
	ldd 16(%r8),%r2
	extrd,s %r29,7,8,%r31
	stb %r31,8(%r2)
	extrd,s %r29,15,16,%r4
	ldd 16(%r8),%r2
	extrd,s %r29,23,24,%r29
	stb %r4,9(%r2)
	ldd 16(%r8),%r31
	b L(50)
	stb %r29,10(%r31)
DEF(L(132))
	ldd 16(%r8),%r2
	extrd,s %r29,7,8,%r31
	stb %r31,8(%r2)
	extrd,s %r29,15,16,%r29
	ldd 16(%r8),%r31
	b L(50)
	stb %r29,9(%r31)
DEF(L(131))
	ldd 16(%r8),%r31
	extrd,s %r29,7,8,%r29
	b L(50)
	stb %r29,8(%r31)
DEF(L(130))
	ldd 16(%r8),%r31
	extrd,s %r28,7,8,%r29
	stb %r29,0(%r31)
	extrd,s %r28,15,16,%r2
	ldd 16(%r8),%r29
	extrd,s %r28,23,24,%r31
	stb %r2,1(%r29)
	extrd,s %r28,31,32,%r4
	ldd 16(%r8),%r29
	extrd,s %r28,39,40,%r2
	stb %r31,2(%r29)
	extrd,s %r28,47,48,%r5
	ldd 16(%r8),%r31
	extrd,s %r28,55,56,%r6
	stb %r4,3(%r31)
	ldd 16(%r8),%r29
	stb %r2,4(%r29)
	ldd 16(%r8),%r31
	stb %r5,5(%r31)
	ldd 16(%r8),%r29
	b L(50)
	stb %r6,6(%r29)
DEF(L(129))
	ldd 16(%r8),%r31
	extrd,s %r28,7,8,%r29
	stb %r29,0(%r31)
	extrd,s %r28,15,16,%r2
	ldd 16(%r8),%r29
	extrd,s %r28,23,24,%r31
	stb %r2,1(%r29)
	extrd,s %r28,31,32,%r4
	ldd 16(%r8),%r29
	extrd,s %r28,39,40,%r2
	stb %r31,2(%r29)
	extrd,s %r28,47,48,%r5
	ldd 16(%r8),%r29
	stb %r4,3(%r29)
	ldd 16(%r8),%r31
	stb %r2,4(%r31)
	ldd 16(%r8),%r29
	b L(50)
	stb %r5,5(%r29)
DEF(L(128))
	ldd 16(%r8),%r31
	extrd,s %r28,7,8,%r29
	stb %r29,0(%r31)
	extrd,s %r28,15,16,%r2
	ldd 16(%r8),%r29
	stb %r2,1(%r29)
	ldd 16(%r8),%r31
	extrd,s %r28,39,40,%r2
	stb %r4,2(%r31)
	ldd 16(%r8),%r29
	stb %r5,3(%r29)
	ldd 16(%r8),%r31
	b L(50)
	stb %r2,4(%r31)
DEF(L(127))
	ldd 16(%r8),%r31
	extrd,s %r28,7,8,%r29
	stb %r29,0(%r31)
	extrd,s %r28,15,16,%r2
	ldd 16(%r8),%r29
	stb %r2,1(%r29)
	ldd 16(%r8),%r29
	stb %r4,2(%r29)
	ldd 16(%r8),%r31
	b L(50)
	stb %r5,3(%r31)
DEF(L(126))
	ldd 16(%r8),%r31
	extrd,s %r28,7,8,%r29
	stb %r29,0(%r31)
	extrd,s %r28,15,16,%r2
	ldd 16(%r8),%r31
	stb %r2,1(%r31)
	ldd 16(%r8),%r29
	b L(50)
	stb %r4,2(%r29)
DEF(L(125))
	ldd 16(%r8),%r31
	extrd,s %r28,7,8,%r29
	stb %r29,0(%r31)
	extrd,s %r28,15,16,%r2
	ldd 16(%r8),%r29
	b L(50)
	stb %r2,1(%r29)
DEF(L(124))
	ldd 16(%r8),%r31
	extrd,s %r28,7,8,%r29
	b L(50)
	stb %r29,0(%r31)
DEF(L(116))
	ldd 16(%r8),%r29
	b L(50)
	std %r1,0(%r29)
DEF(L(117))
	ldd 16(%r8),%r29
	b L(50)
	stw %r1,0(%r29)
DEF(L(118))
	ldd 16(%r8),%r29
	b L(50)
	sth %r1,0(%r29)
DEF(L(119))
	ldd 16(%r8),%r29
	b L(50)
	stb %r1,0(%r29)
DEF(L(122))
	copy %r1,%r29
	ldd 8(%r8),%r31
	ldd 16(%r31),%r2
	ldd 24(%r31),%r27
	bve,l (%r2),%r2
	nop
	ldd 16(%r8),%r29
	copy %r9,%r27
	b L(50)
	fstd %fr4,0(%r29)
DEF(L(121))
	copy %r1,%r29
	ldd 8(%r8),%r31
	ldd 16(%r31),%r2
	ldd 24(%r31),%r27
	bve,l (%r2),%r2
	nop
	ldd 16(%r8),%r29
	copy %r9,%r27
	b L(50)
	fstw %fr4R,0(%r29)
DEF(L(44))
	ldw 64(%r8),%r29
	and %r29,%r31,%r29
	cmpib,=,n 0,%r29,L(45)
	ldd 56(%r5),%r19
	fldw 60(%r5),%fr11R
	b,n L(45)
DEF(L(39))
	ldw 64(%r8),%r29
	and %r29,%r31,%r29
	cmpib,=,n 0,%r29,L(40)
	ldd 48(%r5),%r20
	fldw 52(%r5),%fr10R
	b,n L(40)
DEF(L(34))
	ldw 64(%r8),%r29
	and %r29,%r31,%r29
	cmpib,=,n 0,%r29,L(35)
	ldd 40(%r5),%r21
	fldw 44(%r5),%fr9R
	b,n L(35)
DEF(L(29))
	ldw 64(%r8),%r29
	and %r29,%r31,%r29
	cmpib,=,n 0,%r29,L(30)
	ldd 32(%r5),%r22
	fldw 36(%r5),%fr8R
	b,n L(30)
DEF(L(24))
	ldw 64(%r8),%r29
	and %r29,%r31,%r29
	cmpib,=,n 0,%r29,L(25)
	ldd 24(%r5),%r23
	fldw 28(%r5),%fr7R
	b,n L(25)
DEF(L(19))
	ldw 64(%r8),%r29
	and %r29,%r31,%r29
	cmpib,=,n 0,%r29,L(20)
	ldd 16(%r5),%r24
	fldw 20(%r5),%fr6R
	b,n L(20)
DEF(L(14))
	ldw 64(%r8),%r29
	and %r29,%r31,%r29
	cmpib,=,n 0,%r29,L(15)
	ldd 8(%r5),%r25
	fldw 12(%r5),%fr5R
	b,n L(15)
DEF(L(9))
	ldw 64(%r8),%r29
	extrw,u %r29,31,1,%r29
	cmpib,=,n 0,%r29,L(10)
	ldd 0(%r5),%r26
	fldw 4(%r5),%fr4R
	b,n L(10)
DEF(L(120))
	b L(7)
	ldd 16(%r8),%r28
	.EXIT
	.PROCEND
DEF(L(fe1))
	FUNEND(avcall_call)
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
