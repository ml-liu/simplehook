#include "asm-i386.h"
	TEXT()
	ALIGN(2)
	P2ALIGN(2,3)
	DECLARE_FUNCTION(callback_receiver)
FUNBEGIN(callback_receiver)
	INSN1(push,l	,R(ebp))
	INSN2(mov,l	,R(esp), R(ebp))
	INSN1(push,l	,R(edi))
	INSN1(push,l	,R(esi))
	INSN2(lea,l	,X4 MEM_DISP(ebp,8), R(edx))
	INSN2(sub,l	,NUM(56), R(esp))
	INSN2(mov,l	,R(edx),X4 MEM_DISP(ebp,-40))
	INSN2(lea,l	,X4 MEM_DISP(ebp,-56), R(edx))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(ebp,-56))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(ebp,-36))
	INSN2(mov,l	,NUM(0),X4 MEM_DISP(ebp,-32))
	INSN2(mov,l	,R(ebx),X4 MEM_DISP(ebp,-24))
	INSN1(push,l	,R(edx))
	INSN1(push,l	,X4 MEM_DISP(ecx,4))
	INSN1(call,_	,INDIR(X4 MEM(ecx)))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-32), R(esi))
	INSN2(add,l	,NUM(16), R(esp))
	INSN2(test,l	,R(esi), R(esi))
	INSN1(je,_	,L(43))
	INSN2(cmp,l	,NUM(1), R(esi))
	INSN1(je,_	,L(44))
	INSN2(cmp,l	,NUM(2), R(esi))
	INSN1(je,_	,L(44))
	INSN2(cmp,l	,NUM(3), R(esi))
	INSN1(je,_	,L(49))
	INSN2(cmp,l	,NUM(4), R(esi))
	INSN1(je,_	,L(50))
	INSN2(cmp,l	,NUM(5), R(esi))
	INSN1(je,_	,L(51))
	INSN2(cmp,l	,NUM(6), R(esi))
	INSN1(je,_	,L(48))
	INSN2(cmp,l	,NUM(7), R(esi))
	INSN1(je,_	,L(48))
	INSN2(cmp,l	,NUM(8), R(esi))
	INSN1(je,_	,L(48))
	INSN2(cmp,l	,NUM(9), R(esi))
	INSN1(je,_	,L(48))
	INSN2(lea,l	,X4 MEM_DISP(esi,-10), R(edx))
	INSN2(cmp,l	,NUM(1), R(edx))
	INSN1(ja,_	,L(22))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-48), R(eax))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-44),R(edx))
L(33):
	P2ALIGN(2,3)
L(43):
	INSN2(mov,l	,X4 MEM_DISP(ebp,-56), R(esi))
L(3):
	INSN2(and,l	,NUM(512), R(esi))
	INSN1(je,_	,L(1))
	INSN2(mov,l	,X4 MEM_DISP(ebp,0),R(ecx))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-40), R(esp))
	INSN1(jmp,_	,INDIR(R(ecx)))
L(1):
	INSN2(lea,l	,X4 MEM_DISP(ebp,-8), R(esp))
	INSN1(pop,l	,R(esi))
	INSN1(pop,l	,R(edi))
	leave
	ret
L(22):
	INSN2(cmp,l	,NUM(12), R(esi))
	INSN1(je,_	,L(52))
	INSN2(cmp,l	,NUM(13), R(esi))
	INSN1(je,_	,L(53))
	INSN2(cmp,l	,NUM(14), R(esi))
	INSN1(je,_	,L(48))
	INSN2(cmp,l	,NUM(15), R(esi))
	INSN1(jne,_	,L(43))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-56), R(esi))
	INSN2(test,l	,NUM(1024), R(esi))
	INSN2(mov,l	,R(esi), R(edi))
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
	INSN2(and,l	,NUM(16), R(edi))
	INSN2(mov,l	,X4 MEM_DISP(ebp,-36), R(eax))
	INSN1(jne,_	,L(3))
	INSN2(lea,l	,X4 MEM_DISP(ebp,-8), R(esp))
	INSN1(pop,l	,R(esi))
	INSN1(pop,l	,R(edi))
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
	FUNEND(callback_receiver,L(fe1)-callback_receiver)
	ALIGN(2)
	P2ALIGN(2,3)
GLOBL(C(callback_get_receiver))
	DECLARE_FUNCTION(callback_get_receiver)
FUNBEGIN(callback_get_receiver)
	INSN1(push,l	,R(ebp))
	INSN2(mov,l	,R(esp), R(ebp))
	INSN1(push,l	,R(ebx))
	INSN1(call,_	,L(59))
L(59):
	INSN1(pop,l	,R(ebx))
#ifdef __ELF__
	INSN2(add,l	,NUM()_GLOBAL_OFFSET_TABLE_+[.-L(59)],R(ebx))
#endif
#ifdef __ELF__
	INSN2(lea,l	,callback_receiver@MEM_DISP(ebx,GOTOFF), R(eax))
#else
	INSN2(lea,l	,C(callback_receiver)-L(59)MEM(ebx), R(eax))
#endif
	INSN2(mov,l	,X4 MEM(esp), R(ebx))
	leave
	ret
L(fe2):
	FUNEND(callback_get_receiver,L(fe2)-callback_get_receiver)

#if defined __linux__ || defined __FreeBSD__ || defined __FreeBSD_kernel__ || defined __DragonFly__
	.section .note.GNU-stack,"",@progbits
#endif
