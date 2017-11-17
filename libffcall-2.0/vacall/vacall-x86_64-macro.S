#include "asm-x86_64.h"
	TEXT()
	P2ALIGN(4,15)
GLOBL(C(vacall_receiver))
	DECLARE_FUNCTION(vacall_receiver)
FUNBEGIN(vacall_receiver)
L(FB2):
	INSN1(push,q	,R(rbp))
L(CFI0):
	INSN2(mov,q	,R(rsp), R(rbp))
L(CFI1):
	INSN1(push,q	,R(r12))
L(CFI2):
	INSN2(sub,q	,NUM(200), R(rsp))
L(CFI3):
	INSN2(mov,q	,R(rcx),X8 MEM_DISP(rbp,-48))
	INSN2(lea,q	,X8 MEM_DISP(rbp,16), R(rcx))
	INSN2(mov,q	,R(rdi),X8 MEM_DISP(rbp,-72))
	INSN2(mov,q	,R(rsi),X8 MEM_DISP(rbp,-64))
	INSN2S(movs,d	,R(xmm0),X8 MEM_DISP(rbp,-144))
	INSN2(mov,q	,R(rcx),X8 MEM_DISP(rbp,-184))
	INSN2(mov,q	,R(rdx),X8 MEM_DISP(rbp,-56))
	INSN2S(movs,d	,R(xmm1),X8 MEM_DISP(rbp,-136))
	INSN2(mov,q	,R(r8),X8 MEM_DISP(rbp,-40))
	INSN2S(movs,d	,R(xmm2),X8 MEM_DISP(rbp,-128))
	INSN2(lea,q	,X8 MEM_DISP(rbp,-208), R(rdi))
	INSN2(mov,q	,R(r9),X8 MEM_DISP(rbp,-32))
	INSN2S(movs,d	,R(xmm3),X8 MEM_DISP(rbp,-120))
	INSN2S(movs,d	,R(xmm4),X8 MEM_DISP(rbp,-112))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(rbp,-208))
	INSN2S(movs,d	,R(xmm5),X8 MEM_DISP(rbp,-104))
	INSN2(mov,q	,NUM(0),X8 MEM_DISP(rbp,-176))
	INSN2S(movs,d	,R(xmm6),X8 MEM_DISP(rbp,-96))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(rbp,-168))
	INSN2S(movs,d	,R(xmm7),X8 MEM_DISP(rbp,-88))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(rbp,-80))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(rbp,-152))
	INSN1(call,_	,INDIR(X8 MEM_PCRELATIVE(C(vacall_function))))
	INSN2(mov,l	,X4 MEM_DISP(rbp,-168), R(ecx))
	INSN2(test,l	,R(ecx), R(ecx))
	INSN1(je,_	,L(41))
	INSN2(cmp,l	,NUM(1), R(ecx))
	INSN1(je,_	,L(42))
	INSN2(cmp,l	,NUM(2), R(ecx))
	INSN1(je,_	,L(42))
	INSN2(cmp,l	,NUM(3), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(48))
	INSN2(cmp,l	,NUM(4), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(49))
	INSN2(cmp,l	,NUM(5), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(50))
	INSN2(cmp,l	,NUM(6), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(51))
	INSN2(cmp,l	,NUM(7), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(52))
	INSN2(cmp,l	,NUM(8), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(46))
	INSN2(cmp,l	,NUM(9), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(46))
	INSN2(cmp,l	,NUM(10), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(46))
	INSN2(cmp,l	,NUM(11), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(46))
	INSN2(cmp,l	,NUM(12), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(53))
	INSN2(cmp,l	,NUM(13), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(54))
	INSN2(cmp,l	,NUM(14), R(ecx))
	P2ALIGN(4,5)
	INSN1(je,_	,L(46))
	INSN2(cmp,l	,NUM(15), R(ecx))
	P2ALIGN(4,5)
	INSN1(jne,_	,L(41))
	INSN2(test,b	,NUM(4),X1 MEM_DISP(rbp,-207))
	P2ALIGN(4,2)
	INSN1(je,_	,L(41))
	INSN2(mov,q	,X8 MEM_DISP(rbp,-160), R(rsi))
	INSN2(lea,q	,X8 MEM_DISP(rsi,-1), R(rcx))
	INSN2(cmp,q	,NUM(15), R(rcx))
	INSN1(ja,_	,L(41))
	INSN2(mov,q	,X8 MEM_DISP(rbp,-176), R(rcx))
	INSN2(mov,q	,R(rcx), R(r11))
	INSN2(mov,q	,R(rcx), R(r8))
	INSN2(and,l	,NUM(7), R(r8d))
	INSN2(and,q	,NUM(-8), R(r11))
	INSN2(cmp,q	,NUM(8), R(rsi))
	INSN2(lea,q	,X8 MEM_INDEX(rsi,r8), R(r10))
	INSN1(ja,_	,L(35))
	INSN2(cmp,q	,NUM(8), R(r10))
	INSN1(ja,_	,L(37))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(-1,r10,8), R(ecx))
	INSN2(mov,l	,NUM(2), R(esi))
	INSN2(sal,q	,R(cl), R(rsi))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(0,r8,8), R(ecx))
	INSN1(dec,q	,R(rsi))
	INSN2(and,q	,X8 MEM(r11), R(rsi))
	INSN2(mov,q	,R(rsi), R(rax))
	INSN2(sar,q	,R(cl), R(rax))
	P2ALIGN(4,7)
L(41):
	INSN2(add,q	,NUM(200), R(rsp))
	INSN1(pop,q	,R(r12))
	leave
	ret
	P2ALIGN(4,7)
L(42):
	INSN2MOVXQ(movs,b,X1 MEM_DISP(rbp,-200),R(rax))
	INSN2(add,q	,NUM(200), R(rsp))
	INSN1(pop,q	,R(r12))
	leave
	ret
L(49):
	INSN2MOVXQ(movs,w,X2 MEM_DISP(rbp,-200),R(rax))
	INSN1(jmp,_	,L(41))
L(48):
	INSN2MOVXQ(movz,b,X1 MEM_DISP(rbp,-200), R(rax))
	INSN1(jmp,_	,L(41))
L(46):
	INSN2(mov,q	,X8 MEM_DISP(rbp,-200), R(rax))
	INSN1(jmp,_	,L(41))
L(50):
	INSN2MOVXQ(movz,w,X2 MEM_DISP(rbp,-200), R(rax))
	INSN1(jmp,_	,L(41))
L(51):
	INSN2MOVXLQ(movs,l,X4 MEM_DISP(rbp,-200),R(rax))
	INSN1(jmp,_	,L(41))
L(52):
	INSN2(mov,l	,X4 MEM_DISP(rbp,-200), R(eax))
	INSN1(jmp,_	,L(41))
L(53):
	INSN2S(movs,s	,X4 MEM_DISP(rbp,-200), R(xmm0))
	INSN1(jmp,_	,L(41))
L(54):
	INSN2(movlp,d	,X8 MEM_DISP(rbp,-200), R(xmm0))
	INSN1(jmp,_	,L(41))
L(35):
	INSN2(cmp,q	,NUM(16), R(r10))
	INSN1(ja,_	,L(39))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(-65,r10,8), R(ecx))
	INSN2(mov,l	,NUM(2), R(esi))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(0,r8,8), R(r9d))
	INSN2(mov,l	,NUM(32), R(edi))
	INSN2(sal,q	,R(cl), R(rsi))
	INSN2(lea,q	,X8 MEM_DISP_SHINDEX0(0,r8,4), R(rcx))
	INSN2(mov,q	,X8 MEM(r11), R(r8))
	INSN1(dec,q	,R(rsi))
	INSN2(and,q	,X8 MEM_DISP(r11,8), R(rsi))
	INSN2(sub,l	,R(ecx), R(edi))
	INSN2(mov,l	,R(r9d), R(ecx))
	INSN2(sar,q	,R(cl), R(r8))
	INSN2(mov,l	,R(edi), R(ecx))
	INSN2(mov,q	,R(r8), R(rax))
	INSN2(mov,q	,R(rsi), R(r10))
	INSN2(mov,q	,R(rsi), R(rdx))
	INSN2(sal,q	,R(cl), R(r10))
	INSN2(sal,q	,R(cl), R(r10))
	INSN2(mov,l	,R(r9d), R(ecx))
	INSN2(or,q	,R(r10), R(rax))
	INSN2(sar,q	,R(cl), R(rdx))
	INSN1(jmp,_	,L(41))
L(37):
	INSN2(mov,q	,X8 MEM(r11), R(rdi))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(-65,r10,8), R(esi))
	INSN2(sal,q	,NUM(3), R(r8))
	INSN2(mov,l	,R(r8d), R(ecx))
	INSN2(mov,l	,NUM(2), R(r10d))
	INSN2(sar,q	,R(cl), R(rdi))
	INSN2(mov,l	,R(esi), R(ecx))
	INSN2(mov,l	,NUM(64), R(esi))
	INSN2(sal,q	,R(cl), R(r10))
	INSN2(sub,l	,R(r8d), R(esi))
	INSN2(mov,q	,R(rdi), R(rax))
	INSN1(dec,q	,R(r10))
	INSN2(and,q	,X8 MEM_DISP(r11,8), R(r10))
	INSN2(mov,l	,R(esi), R(ecx))
	INSN2(sal,q	,R(cl), R(r10))
	INSN2(or,q	,R(r10), R(rax))
	INSN1(jmp,_	,L(41))
L(39):
	INSN2(lea,q	,X8 MEM_DISP_SHINDEX0(0,r8,8), R(rcx))
	INSN2(mov,q	,X8 MEM(r11), R(r12))
	INSN2(mov,q	,X8 MEM_DISP(r11,8), R(r8))
	INSN2(mov,l	,NUM(64), R(edi))
	INSN2(sub,l	,R(ecx), R(edi))
	INSN2(mov,l	,R(ecx), R(r9d))
	INSN2(sar,q	,R(cl), R(r12))
	INSN2(mov,q	,R(r8), R(rsi))
	INSN2(mov,l	,R(edi), R(ecx))
	INSN2(sal,q	,R(cl), R(rsi))
	INSN2(mov,q	,R(r12), R(rax))
	INSN2(mov,l	,R(r9d), R(ecx))
	INSN2(or,q	,R(rsi), R(rax))
	INSN2(lea,l	,X4 MEM_DISP_SHINDEX0(-129,r10,8), R(esi))
	INSN2(sar,q	,R(cl), R(r8))
	INSN2(mov,l	,NUM(2), R(r9d))
	INSN2(mov,q	,R(r8), R(rdx))
	INSN2(mov,l	,R(esi), R(ecx))
	INSN2(sal,q	,R(cl), R(r9))
	INSN2(mov,l	,R(edi), R(ecx))
	INSN2(lea,q	,X8 MEM_DISP(r9,-1), R(rsi))
	INSN2(and,q	,X8 MEM_DISP(r11,16), R(rsi))
	INSN2(sal,q	,R(cl), R(rsi))
	INSN2(or,q	,R(rsi), R(rdx))
	INSN1(jmp,_	,L(41))
L(FE2):
	FUNEND(vacall_receiver, .-vacall_receiver)
#if !(defined __sun || (defined __APPLE__ && defined __MACH__) || (defined _WIN32 || defined __WIN32__ || defined __CYGWIN__))
	.section	EH_FRAME_SECTION
L(frame1):
	.long	L(ECIE1)-.LSCIE1
L(SCIE1):
	.long	0x0
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
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
	.quad	L(FB2)
	.quad	L(FE2)-.LFB2
	.byte	0x4
	.long	L(CFI0)-.LFB2
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	L(CFI1)-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	L(CFI3)-.LCFI1
	.byte	0x8c
	.uleb128 0x3
	.align 8
L(EFDE1):
#endif
#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
