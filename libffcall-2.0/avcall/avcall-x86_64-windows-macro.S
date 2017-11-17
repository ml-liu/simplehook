#include "asm-x86_64.h"
	TEXT()
	P2ALIGN(4,15)
	GLOBL(C(avcall_call))
	DECLARE_FUNCTION(avcall_call)
FUNBEGIN(avcall_call)
L(FB0):
	INSN1(push,q	,R(rbp))
L(CFI0):
	INSN2(mov,q	,R(rsp), R(rbp))
L(CFI1):
	INSN1(push,q	,R(rsi))
	INSN1(push,q	,R(rbx))
L(CFI2):
	INSN2(mov,q	,R(rcx), R(rbx))
	INSN2(sub,q	,NUM(32), R(rsp))
	INSN2(mov,q	,X8 MEM_DISP(rcx,48), R(rcx))
	INSN2(mov,q	,X8 MEM_DISP(rbx,40), R(rax))
	INSN2(sub,q	,NUM(2064), R(rsp))
	INSN2(sub,q	,R(rcx), R(rax))
	INSN2(sar,q	,NUM(3), R(rax))
	INSN2(cmp,l	,NUM(4), R(eax))
	INSN1(jle,_	,L(6))
	INSN2(lea,l	,X4 MEM_DISP(rax,-5), R(r8d))
	INSN2(lea,q	,X8 MEM_DISP(rsp,32), R(r9))
	INSN2(xor,l	,R(eax), R(eax))
	INSN2(add,q	,NUM(1), R(r8))
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(5):
	INSN2(mov,q	,X8 MEM_DISP_SHINDEX(rcx,32,rax,8), R(rdx))
	INSN2(mov,q	,R(rdx),X8 MEM_SHINDEX(r9,rax,8))
	INSN2(add,q	,NUM(1), R(rax))
	INSN2(cmp,q	,R(r8), R(rax))
	INSN1(jne,_	,L(5))
L(6):
	INSN2(mov,l	,X4 MEM_DISP(rbx,68), R(eax))
	INSN2(test,l	,R(eax), R(eax))
	INSN1(je,_	,L(7))
	INSN2(test,b	,NUM(1), R(al))
	INSN1(je,_	,L(8))
	INSN2S(movs,s	,X4 MEM_DISP(rbx,76), R(xmm0))
L(8):
	INSN2(test,b	,NUM(2), R(al))
	INSN1(je,_	,L(9))
	INSN2S(movs,s	,X4 MEM_DISP(rbx,80), R(xmm1))
L(9):
	INSN2(test,b	,NUM(4), R(al))
	INSN1(je,_	,L(10))
	INSN2S(movs,s	,X4 MEM_DISP(rbx,84), R(xmm2))
L(10):
	INSN2(test,b	,NUM(8), R(al))
	INSN1(jne,_	,L(78))
L(7):
	INSN2(mov,l	,X4 MEM_DISP(rbx,72), R(eax))
	INSN2(test,l	,R(eax), R(eax))
	INSN1(je,_	,L(12))
	INSN2(test,b	,NUM(1), R(al))
	INSN1(je,_	,L(13))
	INSN2S(movs,d	,X8 MEM_DISP(rbx,96), R(xmm0))
L(13):
	INSN2(test,b	,NUM(2), R(al))
	INSN1(je,_	,L(14))
	INSN2S(movs,d	,X8 MEM_DISP(rbx,104), R(xmm1))
L(14):
	INSN2(test,b	,NUM(4), R(al))
	INSN1(je,_	,L(15))
	INSN2S(movs,d	,X8 MEM_DISP(rbx,112), R(xmm2))
L(15):
	INSN2(test,b	,NUM(8), R(al))
	INSN1(jne,_	,L(79))
L(12):
	INSN2(mov,l	,X4 MEM_DISP(rbx,24), R(eax))
	INSN2(cmp,l	,NUM(13), R(eax))
	INSN1(je,_	,L(80))
	INSN2(cmp,l	,NUM(14), R(eax))
	INSN1(je,_	,L(81))
	INSN2(mov,q	,X8 MEM_DISP(rcx,8), R(rdx))
	INSN2(mov,q	,X8 MEM_DISP(rcx,24), R(r9))
	INSN2(mov,q	,X8 MEM_DISP(rcx,16), R(r8))
	INSN2(mov,q	,X8 MEM(rcx), R(rcx))
	INSN1(call,_	,INDIR(X8 MEM_DISP(rbx,8)))
	INSN2(mov,l	,X4 MEM_DISP(rbx,24), R(edx))
	INSN2(cmp,l	,NUM(1), R(edx))
	INSN1(je,_	,L(18))
	INSN2(test,l	,R(edx), R(edx))
	INSN1(je,_	,L(76))
	INSN2(cmp,l	,NUM(2), R(edx))
	INSN1(je,_	,L(73))
	INSN2(cmp,l	,NUM(3), R(edx))
	INSN1(je,_	,L(73))
	INSN2(cmp,l	,NUM(4), R(edx))
	INSN1(je,_	,L(73))
	INSN2(cmp,l	,NUM(5), R(edx))
	INSN1(je,_	,L(74))
	INSN2(cmp,l	,NUM(6), R(edx))
	INSN1(je,_	,L(74))
	INSN2(cmp,l	,NUM(7), R(edx))
	INSN1(je,_	,L(75))
	INSN2(cmp,l	,NUM(8), R(edx))
	INSN1(je,_	,L(75))
	INSN2(cmp,l	,NUM(9), R(edx))
	INSN1(je,_	,L(76))
	INSN2(cmp,l	,NUM(10), R(edx))
	INSN1(je,_	,L(76))
	INSN2(cmp,l	,NUM(11), R(edx))
	INSN1(je,_	,L(76))
	INSN2(cmp,l	,NUM(12), R(edx))
	INSN1(je,_	,L(76))
	INSN2(cmp,l	,NUM(15), R(edx))
	INSN1(je,_	,L(76))
	INSN2(cmp,l	,NUM(16), R(edx))
	INSN1(jne,_	,L(18))
	INSN2(test,l	,NUM(512),X4 MEM(rbx))
	INSN1(je,_	,L(18))
	INSN2(mov,q	,X8 MEM_DISP(rbx,32), R(r8))
	INSN2(lea,q	,X8 MEM_DISP(r8,-4), R(rdx))
	INSN2(test,q	,NUM(-5), R(rdx))
	INSN1(je,_	,L(35))
	INSN2(lea,q	,X8 MEM_DISP(r8,-1), R(rdx))
	INSN2(cmp,q	,NUM(1), R(rdx))
	INSN1(ja,_	,L(18))
L(35):
	INSN2(mov,q	,X8 MEM_DISP(rbx,16), R(rdx))
	INSN2(mov,q	,R(rdx), R(r9))
	INSN2(and,l	,NUM(7), R(edx))
	INSN2(add,q	,R(rdx), R(r8))
	INSN2(and,q	,NUM(-8), R(r9))
	INSN2(cmp,q	,NUM(8), R(r8))
	INSN1(jbe,_	,L(82))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(0,rdx,8), R(ecx))
	INSN2(mov,q	,X8 MEM(r9), R(r10))
	INSN2(mov,q	,R(rax), R(rsi))
	INSN2(mov,q	,NUM(-1), R(r11))
	INSN1(neg,l	,R(edx))
	INSN2(sal,q	,R(cl), R(rsi))
	INSN2(sal,q	,R(cl), R(r11))
	INSN2(mov,q	,R(rsi), R(rcx))
	INSN2(xor,q	,R(r10), R(rcx))
	INSN2(and,q	,R(r11), R(rcx))
	INSN2(xor,q	,R(r10), R(rcx))
	INSN2(mov,q	,X8 MEM_DISP(r9,8), R(r10))
	INSN2(mov,q	,R(rcx),X8 MEM(r9))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(-65,r8,8), R(ecx))
	INSN2(mov,l	,NUM(2), R(r8d))
	INSN2(sal,q	,R(cl), R(r8))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(64,rdx,8), R(ecx))
	INSN2(sub,q	,NUM(1), R(r8))
	INSN2(sar,q	,R(cl), R(rax))
	INSN2(xor,q	,R(r10), R(rax))
	INSN2(and,q	,R(r8), R(rax))
	INSN2(xor,q	,R(r10), R(rax))
	INSN2(mov,q	,R(rax),X8 MEM_DISP(r9,8))
L(18):
	INSN2(lea,q	,X8 MEM_DISP(rbp,-16), R(rsp))
	INSN2(xor,l	,R(eax), R(eax))
	INSN1(pop,q	,R(rbx))
L(CFI3):
	INSN1(pop,q	,R(rsi))
L(CFI4):
	INSN1(pop,q	,R(rbp))
L(CFI5):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(79):
L(CFI6):
	INSN2S(movs,d	,X8 MEM_DISP(rbx,120), R(xmm3))
	INSN1(jmp,_	,L(12))
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(78):
	INSN2S(movs,s	,X4 MEM_DISP(rbx,88), R(xmm3))
	INSN1(jmp,_	,L(7))
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(76):
	INSN2(mov,q	,X8 MEM_DISP(rbx,16), R(rdx))
	INSN2(mov,q	,R(rax),X8 MEM(rdx))
	INSN2(lea,q	,X8 MEM_DISP(rbp,-16), R(rsp))
	INSN2(xor,l	,R(eax), R(eax))
	INSN1(pop,q	,R(rbx))
L(CFI7):
	INSN1(pop,q	,R(rsi))
L(CFI8):
	INSN1(pop,q	,R(rbp))
L(CFI9):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(73):
L(CFI10):
	INSN2(mov,q	,X8 MEM_DISP(rbx,16), R(rdx))
	INSN2(mov,b	,R(al),X1 MEM(rdx))
	INSN2(lea,q	,X8 MEM_DISP(rbp,-16), R(rsp))
	INSN2(xor,l	,R(eax), R(eax))
	INSN1(pop,q	,R(rbx))
L(CFI11):
	INSN1(pop,q	,R(rsi))
L(CFI12):
	INSN1(pop,q	,R(rbp))
L(CFI13):
	ret
	P2ALIGN(4,10)
	P2ALIGN(3,7)
L(81):
L(CFI14):
	INSN2(mov,q	,X8 MEM_DISP(rbx,16), R(rsi))
	INSN2(mov,q	,X8 MEM_DISP(rcx,8), R(rdx))
	INSN2(mov,q	,X8 MEM_DISP(rcx,24), R(r9))
	INSN2(mov,q	,X8 MEM_DISP(rcx,16), R(r8))
	INSN2(mov,q	,X8 MEM(rcx), R(rcx))
	INSN1(call,_	,INDIR(X8 MEM_DISP(rbx,8)))
	INSN2S(movs,d	,R(xmm0),X8 MEM(rsi))
	INSN2(lea,q	,X8 MEM_DISP(rbp,-16), R(rsp))
	INSN2(xor,l	,R(eax), R(eax))
	INSN1(pop,q	,R(rbx))
L(CFI15):
	INSN1(pop,q	,R(rsi))
L(CFI16):
	INSN1(pop,q	,R(rbp))
L(CFI17):
	ret
L(80):
L(CFI18):
	INSN2(mov,q	,X8 MEM_DISP(rbx,16), R(rsi))
	INSN2(mov,q	,X8 MEM_DISP(rcx,8), R(rdx))
	INSN2(mov,q	,X8 MEM_DISP(rcx,24), R(r9))
	INSN2(mov,q	,X8 MEM_DISP(rcx,16), R(r8))
	INSN2(mov,q	,X8 MEM(rcx), R(rcx))
	INSN1(call,_	,INDIR(X8 MEM_DISP(rbx,8)))
	INSN2S(movs,s	,R(xmm0),X4 MEM(rsi))
	INSN1(jmp,_	,L(18))
L(74):
	INSN2(mov,q	,X8 MEM_DISP(rbx,16), R(rdx))
	INSN2(mov,w	,R(ax),X2 MEM(rdx))
	INSN1(jmp,_	,L(18))
L(75):
	INSN2(mov,q	,X8 MEM_DISP(rbx,16), R(rdx))
	INSN2(mov,l	,R(eax),X4 MEM(rdx))
	INSN1(jmp,_	,L(18))
L(82):
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(-1,r8,8), R(ecx))
	INSN2(mov,q	,X8 MEM(r9), R(r10))
	INSN2(sal,l	,NUM(3), R(edx))
	INSN2(mov,l	,NUM(2), R(r8d))
	INSN2(mov,l	,NUM(1), R(r11d))
	INSN2(sal,q	,R(cl), R(r8))
	INSN2(mov,l	,R(edx), R(ecx))
	INSN2(sal,q	,R(cl), R(r11))
	INSN2(sal,q	,R(cl), R(rax))
	INSN2(sub,q	,R(r11), R(r8))
	INSN2(xor,q	,R(r10), R(rax))
	INSN2(and,q	,R(r8), R(rax))
	INSN2(xor,q	,R(r10), R(rax))
	INSN2(mov,q	,R(rax),X8 MEM(r9))
	INSN1(jmp,_	,L(18))
L(FE0):
	FUNEND(avcall_call, .-avcall_call)
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
	.byte	0x84
	.uleb128 0x3
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	L(CFI3)-.LCFI2
	.byte	0xa
	.byte	0xc3
	.byte	0x4
	.long	L(CFI4)-.LCFI3
	.byte	0xc4
	.byte	0x4
	.long	L(CFI5)-.LCFI4
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI6)-.LCFI5
	.byte	0xb
	.byte	0x4
	.long	L(CFI7)-.LCFI6
	.byte	0xa
	.byte	0xc3
	.byte	0x4
	.long	L(CFI8)-.LCFI7
	.byte	0xc4
	.byte	0x4
	.long	L(CFI9)-.LCFI8
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI10)-.LCFI9
	.byte	0xb
	.byte	0x4
	.long	L(CFI11)-.LCFI10
	.byte	0xa
	.byte	0xc3
	.byte	0x4
	.long	L(CFI12)-.LCFI11
	.byte	0xc4
	.byte	0x4
	.long	L(CFI13)-.LCFI12
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI14)-.LCFI13
	.byte	0xb
	.byte	0x4
	.long	L(CFI15)-.LCFI14
	.byte	0xa
	.byte	0xc3
	.byte	0x4
	.long	L(CFI16)-.LCFI15
	.byte	0xc4
	.byte	0x4
	.long	L(CFI17)-.LCFI16
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	L(CFI18)-.LCFI17
	.byte	0xb
	.align 8
L(EFDE1):
#endif
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
