#include "asm-x86_64.h"
	TEXT()
	P2ALIGN(4,15)
	DECLARE_FUNCTION(callback_receiver)
FUNBEGIN(callback_receiver)
L(FB0):
	INSN1(push,q	,R(rbp))
L(CFI0):
	INSN2(mov,q	,R(rsp), R(rbp))
L(CFI1):
	INSN2(sub,q	,NUM(144), R(rsp))
	INSN2(mov,q	,R(rcx),X8 MEM_DISP(rbp,16))
	INSN2(lea,q	,X8 MEM_DISP(rbp,16), R(rcx))
	INSN2(mov,q	,R(rdx),X8 MEM_DISP(rbp,24))
	INSN2(mov,q	,R(r8),X8 MEM_DISP(rbp,32))
	INSN2(lea,q	,X8 MEM_DISP(rbp,-112), R(rdx))
	INSN2(mov,q	,R(r9),X8 MEM_DISP(rbp,40))
	INSN2(mov,q	,R(rcx),X8 MEM_DISP(rbp,-88))
	INSN2S(movs,s	,R(xmm0),X4 MEM_DISP(rbp,-52))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(rbp,-112))
	INSN2S(movs,s	,R(xmm1),X4 MEM_DISP(rbp,-48))
	INSN2(mov,q	,NUM(0),X8 MEM_DISP(rbp,-80))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(rbp,-72))
	INSN2S(movs,s	,R(xmm2),X4 MEM_DISP(rbp,-44))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(rbp,-56))
	INSN2S(movs,s	,R(xmm3),X4 MEM_DISP(rbp,-40))
	INSN2(mov,q	,X8 MEM_DISP(r10,8), R(rcx))
	INSN2S(movs,d	,R(xmm0),X8 MEM_DISP(rbp,-32))
	INSN2S(movs,d	,R(xmm1),X8 MEM_DISP(rbp,-24))
	INSN2S(movs,d	,R(xmm2),X8 MEM_DISP(rbp,-16))
	INSN2S(movs,d	,R(xmm3),X8 MEM_DISP(rbp,-8))
	INSN1(call,_	,INDIR(X8 MEM(r10)))
	INSN2(mov,l	,X4 MEM_DISP(rbp,-72), R(edx))
	INSN2(test,l	,R(edx), R(edx))
	INSN1(je,_	,L(1))
	INSN2(cmp,l	,NUM(1), R(edx))
	INSN1(je,_	,L(34))
	INSN2(cmp,l	,NUM(2), R(edx))
	INSN1(je,_	,L(34))
	INSN2(cmp,l	,NUM(3), R(edx))
	INSN1(je,_	,L(37))
	INSN2(cmp,l	,NUM(4), R(edx))
	INSN1(je,_	,L(38))
	INSN2(cmp,l	,NUM(5), R(edx))
	INSN1(je,_	,L(39))
	INSN2(cmp,l	,NUM(6), R(edx))
	INSN1(je,_	,L(40))
	INSN2(cmp,l	,NUM(7), R(edx))
	INSN1(je,_	,L(41))
	INSN2(cmp,l	,NUM(8), R(edx))
	INSN1(je,_	,L(35))
	INSN2(cmp,l	,NUM(9), R(edx))
	INSN1(je,_	,L(35))
	INSN2(cmp,l	,NUM(10), R(edx))
	INSN1(je,_	,L(35))
	INSN2(cmp,l	,NUM(11), R(edx))
	INSN1(je,_	,L(35))
	INSN2(cmp,l	,NUM(12), R(edx))
	INSN1(je,_	,L(42))
	INSN2(cmp,l	,NUM(13), R(edx))
	INSN1(je,_	,L(43))
	INSN2(cmp,l	,NUM(14), R(edx))
	INSN1(je,_	,L(35))
	INSN2(cmp,l	,NUM(15), R(edx))
	INSN1(jne,_	,L(1))
	INSN2(test,b	,NUM(4),X1 MEM_DISP(rbp,-111))
	INSN1(je,_	,L(17))
	INSN2(mov,q	,X8 MEM_DISP(rbp,-64), R(rdx))
	INSN2(lea,q	,X8 MEM_DISP(rdx,-4), R(rcx))
	INSN2(test,q	,NUM(-5), R(rcx))
	INSN1(je,_	,L(20))
	INSN2(lea,q	,X8 MEM_DISP(rdx,-1), R(rcx))
	INSN2(cmp,q	,NUM(1), R(rcx))
	INSN1(ja,_	,L(1))
L(20):
	INSN2(mov,q	,X8 MEM_DISP(rbp,-80), R(r8))
	INSN2(mov,q	,R(r8), R(r9))
	INSN2(and,l	,NUM(7), R(r8d))
	INSN2(add,q	,R(r8), R(rdx))
	INSN2(and,q	,NUM(-8), R(r9))
	INSN2(cmp,q	,NUM(8), R(rdx))
	INSN1(ja,_	,L(19))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(-1,rdx,8), R(ecx))
	INSN2(mov,l	,NUM(2), R(edx))
	INSN2(sal,q	,R(cl), R(rdx))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(0,r8,8), R(ecx))
	INSN2(sub,q	,NUM(1), R(rdx))
	INSN2(and,q	,X8 MEM(r9), R(rdx))
	INSN2(sar,q	,R(cl), R(rdx))
	INSN2(mov,q	,R(rdx), R(rax))
L(1):
	leave
L(CFI2):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(34):
L(CFI3):
	INSN2MOVXQ(movs,b,X1 MEM_DISP(rbp,-104), R(rax))
	leave
L(CFI4):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(35):
L(CFI5):
	INSN2(mov,q	,X8 MEM_DISP(rbp,-104), R(rax))
	leave
L(CFI6):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(37):
L(CFI7):
	INSN2MOVXL(movz,b,X1 MEM_DISP(rbp,-104), R(eax))
	leave
L(CFI8):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(38):
L(CFI9):
	INSN2MOVXQ(movs,w,X2 MEM_DISP(rbp,-104), R(rax))
	leave
L(CFI10):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(39):
L(CFI11):
	INSN2MOVXL(movz,w,X2 MEM_DISP(rbp,-104), R(eax))
	leave
L(CFI12):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(40):
L(CFI13):
	INSN2MOVXLQ(movs,l,X4 MEM_DISP(rbp,-104), R(rax))
	leave
L(CFI14):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(42):
L(CFI15):
	INSN2S(movs,s	,X4 MEM_DISP(rbp,-104), R(xmm0))
	leave
L(CFI16):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(41):
L(CFI17):
	INSN2(mov,l	,X4 MEM_DISP(rbp,-104), R(eax))
	leave
L(CFI18):
	ret
L(43):
L(CFI19):
	INSN2S(movs,d	,X8 MEM_DISP(rbp,-104), R(xmm0))
	leave
L(CFI20):
	ret
L(17):
L(CFI21):
	INSN2(mov,q	,X8 MEM_DISP(rbp,-80), R(rax))
	leave
L(CFI22):
	ret
L(19):
L(CFI23):
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(-65,rdx,8), R(ecx))
	INSN2(mov,l	,NUM(2), R(edx))
	INSN2(sal,q	,R(cl), R(rdx))
	INSN2(mov,l	,R(r8d), R(ecx))
	INSN2(sub,q	,NUM(1), R(rdx))
	INSN2(and,q	,X8 MEM_DISP(r9,8), R(rdx))
	INSN1(neg,l	,R(ecx))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(64,rcx,8), R(ecx))
	INSN2(sal,q	,R(cl), R(rdx))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(0,r8,8), R(ecx))
	INSN2(mov,q	,X8 MEM(r9), R(r8))
	leave
L(CFI24):
	INSN2(sar,q	,R(cl), R(r8))
	INSN2(or,q	,R(r8), R(rdx))
	INSN2(mov,q	,R(rdx), R(rax))
	ret
L(FE0):
	FUNEND(callback_receiver, .-callback_receiver)
	P2ALIGN(4,15)
	GLOBL(C(callback_get_receiver))
	DECLARE_FUNCTION(callback_get_receiver)
FUNBEGIN(callback_get_receiver)
L(FB1):
	INSN1(push,q	,R(rbp))
L(CFI25):
	INSN2(lea,q	,ADDR_PCRELATIVE(C(callback_receiver)), R(rax))
	INSN2(mov,q	,R(rsp), R(rbp))
L(CFI26):
	INSN1(pop,q	,R(rbp))
L(CFI27):
	ret
L(FE1):
	FUNEND(callback_get_receiver, .-callback_get_receiver)
#if !(defined __sun || (defined __APPLE__ && defined __MACH__) || (defined _WIN32 || defined __WIN32__ || defined __CYGWIN__))
	.section	EH_FRAME_SECTION
L(frame1):
	.long	L(ECIE1)-.LSCIE1
L(SCIE1):
	.long	0
	.byte	0x3
	.string	"zR"
	.uleb128 0x1
	.sleb128 -8
	.uleb128 0x10
	.uleb128 0x1
	.byte	0x1b
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
L(ECIE1):
L(SFDE1):
	.long	L(EFDE1)-.LASFDE1
L(ASFDE1):
	.long	L(ASFDE1)-.Lframe1
	.long	L(FB0)-.
	.long	L(FE0)-.LFB0
	.uleb128 0
	.byte	0x4
	.long	L(CFI0)-.LFB0
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	L(CFI1)-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	L(CFI2)-.LCFI1
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI3)-.LCFI2
	.byte	0xb
	.byte	0x4
	.long	L(CFI4)-.LCFI3
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI5)-.LCFI4
	.byte	0xb
	.byte	0x4
	.long	L(CFI6)-.LCFI5
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI7)-.LCFI6
	.byte	0xb
	.byte	0x4
	.long	L(CFI8)-.LCFI7
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI9)-.LCFI8
	.byte	0xb
	.byte	0x4
	.long	L(CFI10)-.LCFI9
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI11)-.LCFI10
	.byte	0xb
	.byte	0x4
	.long	L(CFI12)-.LCFI11
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI13)-.LCFI12
	.byte	0xb
	.byte	0x4
	.long	L(CFI14)-.LCFI13
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI15)-.LCFI14
	.byte	0xb
	.byte	0x4
	.long	L(CFI16)-.LCFI15
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI17)-.LCFI16
	.byte	0xb
	.byte	0x4
	.long	L(CFI18)-.LCFI17
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI19)-.LCFI18
	.byte	0xb
	.byte	0x4
	.long	L(CFI20)-.LCFI19
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI21)-.LCFI20
	.byte	0xb
	.byte	0x4
	.long	L(CFI22)-.LCFI21
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI23)-.LCFI22
	.byte	0xb
	.byte	0x4
	.long	L(CFI24)-.LCFI23
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
L(EFDE1):
L(SFDE3):
	.long	L(EFDE3)-.LASFDE3
L(ASFDE3):
	.long	L(ASFDE3)-.Lframe1
	.long	L(FB1)-.
	.long	L(FE1)-.LFB1
	.uleb128 0
	.byte	0x4
	.long	L(CFI25)-.LFB1
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	L(CFI26)-.LCFI25
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	L(CFI27)-.LCFI26
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
L(EFDE3):
#endif
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
