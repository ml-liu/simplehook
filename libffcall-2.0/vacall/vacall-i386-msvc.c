#ifdef _MSC_VER
#include "vacall.h"
#endif
#include "asm-i386.h"
	TEXT()
	ALIGN(2)
	P2ALIGN(2,3)
GLOBL(C(vacall_receiver))
	DECLARE_FUNCTION(vacall_receiver)
FUNBEGIN(vacall_receiver)
	INSN1(push,l	,R(ebp))
	INSN2(mov,l	,R(esp), R(ebp))
	INSN2(lea,l	,X4 MEM_DISP(ebp,8), R(edx))
	INSN1(push,l	,R(esi))
	INSN2(sub,l	,NUM(64), R(esp))
	INSN2(mov,l	,R(edx),X4 MEM_DISP(ebp,-40))
	INSN2(lea,l	,X4 MEM_DISP(ebp,-56), R(edx))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(ebp,-56))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(ebp,-36))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(ebp,-32))
	INSN2(mov,l	,R(ebx),X4 MEM_DISP(ebp,-24))
	INSN1(push,l	,R(edx))
	INSN1(call,_	,INDIR(X4 C(vacall_function)))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-32), R(ecx))
	INSN2(add,l	,NUM(16), R(esp))
	INSN2(test,l	,R(ecx), R(ecx))
	INSN1(je,_	,L(43))
	INSN2(cmp,l	,NUM(1), R(ecx))
	INSN1(je,_	,L(44))
	INSN2(cmp,l	,NUM(2), R(ecx))
	INSN1(je,_	,L(44))
	INSN2(cmp,l	,NUM(3), R(ecx))
	INSN1(je,_	,L(49))
	INSN2(cmp,l	,NUM(4), R(ecx))
	INSN1(je,_	,L(50))
	INSN2(cmp,l	,NUM(5), R(ecx))
	INSN1(je,_	,L(51))
	INSN2(cmp,l	,NUM(6), R(ecx))
	INSN1(je,_	,L(48))
	INSN2(cmp,l	,NUM(7), R(ecx))
	INSN1(je,_	,L(48))
	INSN2(cmp,l	,NUM(8), R(ecx))
	INSN1(je,_	,L(48))
	INSN2(cmp,l	,NUM(9), R(ecx))
	INSN1(je,_	,L(48))
	INSN2(lea,l	,X4 MEM_DISP(ecx,-10), R(edx))
	INSN2(cmp,l	,NUM(1), R(edx))
	INSN1(ja,_	,L(22))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-48), R(eax))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-44),R(edx))
L(33):
	P2ALIGN(2,3)
L(43):
	INSN2(mov,l	,X4 MEM_DISP(ebp,-56), R(ecx))
L(3):
	INSN2(and,l	,NUM(512), R(ecx))
	INSN1(je,_	,L(1))
	INSN2(mov,l	,X4 MEM_DISP(ebp,0),R(ecx))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-40), R(esp))
	INSN1(jmp,_	,INDIR(R(ecx)))
L(1):
	INSN2(mov,l	,X4 MEM_DISP(ebp,-4), R(esi))
	leave
	ret
L(22):
	INSN2(cmp,l	,NUM(12), R(ecx))
	INSN1(je,_	,L(52))
	INSN2(cmp,l	,NUM(13), R(ecx))
	INSN1(je,_	,L(53))
	INSN2(cmp,l	,NUM(14), R(ecx))
	INSN1(je,_	,L(48))
	INSN2(cmp,l	,NUM(15), R(ecx))
	INSN1(jne,_	,L(43))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-56), R(ecx))
	INSN2(test,l	,NUM(1024), R(ecx))
	INSN2(mov,l	,R(ecx), R(esi))
	INSN1(je,_	,L(31))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-28), R(edx))
	INSN2(cmp,l	,NUM(1), R(edx))
	INSN1(je,_	,L(54))
	INSN2(cmp,l	,NUM(2), R(edx))
	INSN1(je,_	,L(55))
	INSN2(cmp,l	,NUM(4), R(edx))
	INSN1(je,_	,L(56))
	INSN2(cmp,l	,NUM(8), R(edx))
	INSN1(je,_	,L(57))
L(31):
	INSN2(and,l	,NUM(16), R(esi))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-36), R(eax))
	INSN1(jne,_	,L(3))
	INSN2(lea,l	,X4 MEM_DISP(ebp,-4), R(esp))
	INSN1(pop,l	,R(esi))
	leave
	ret NUM(4)
	INSN1(jmp,_	,L(3))
L(57):
	INSN2(mov,l	,X4 MEM_DISP(ebp,-36), R(edx))
	INSN2(mov,l	,X4 MEM(edx), R(eax))
	INSN2(mov,l	,X4 MEM_DISP(edx,4),R(edx))
	INSN1(jmp,_	,L(3))
L(56):
	INSN2(mov,l	,X4 MEM_DISP(ebp,-36), R(edx))
	INSN2(mov,l	,X4 MEM(edx), R(eax))
	INSN1(jmp,_	,L(3))
L(55):
	INSN2(mov,l	,X4 MEM_DISP(ebp,-36), R(edx))
	INSN2MOVXL(movz,w,X2 MEM(edx), R(eax))
	INSN1(jmp,_	,L(3))
L(54):
	INSN2(mov,l	,X4 MEM_DISP(ebp,-36), R(edx))
	INSN2MOVXL(movz,b,X1 MEM(edx), R(eax))
	INSN1(jmp,_	,L(3))
	P2ALIGN(2,3)
L(48):
	INSN2(mov,l	,X4 MEM_DISP(ebp,-48), R(eax))
	INSN1(jmp,_	,L(43))
L(53):
	INSN1(fld,l	,X8 MEM_DISP(ebp,-48))
	INSN1(jmp,_	,L(43))
L(52):
	INSN1(fld,s	,X4 MEM_DISP(ebp,-48))
	INSN1(jmp,_	,L(43))
	P2ALIGN(2,3)
L(51):
	INSN2MOVXL(movz,w,X2 MEM_DISP(ebp,-48), R(eax))
	INSN1(jmp,_	,L(43))
L(50):
	INSN2MOVXL(movs,w,X2 MEM_DISP(ebp,-48),R(eax))
	INSN1(jmp,_	,L(43))
L(49):
	INSN2MOVXL(movz,b,X1 MEM_DISP(ebp,-48), R(eax))
	INSN1(jmp,_	,L(43))
	P2ALIGN(2,3)
L(44):
	INSN2MOVXL(movs,b,X1 MEM_DISP(ebp,-48),R(eax))
	INSN1(jmp,_	,L(43))
L(fe1):
	FUNEND(vacall_receiver,L(fe1)-vacall_receiver)

#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
