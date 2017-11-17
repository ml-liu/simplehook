#ifdef _MSC_VER
#include "vacall_r.h"
#endif
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
/* Implementation of callback_get_receiver */

/*
 * Copyright 2017 Bruno Haible <bruno@clisp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

__vacall_r_t
callback_get_receiver (void)
{
  return (__vacall_r_t)(void*)&callback_receiver;
}
