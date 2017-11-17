// Assembly language support for x86_64 CPU.
// Bruno Haible 2016-12-28

// Copyright (C) 1997-2017 Bruno Haible <bruno@clisp.org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// In order not to have to maintain several copies of the assembly language
// code, we use some macros which expand into the correct syntax.
// These macros are:
//   C(name)
//           This expands to the name of the C variable or function `name'.
//           On Unix BSD systems, this prepends an underscore.
//   L(label)
//           This expands to the name of a local label, having the name `label'.
//           On Unix ELF systems, where there is no underscore, names beginning
//           with an alphabetic character are automatically exported, so this
//           prepends a dot. Note that when defining a label, the `:' must
//           be inside the parentheses, not outside, because otherwise some
//           ANSI C preprocessor inserts a space between the label and the `:',
//           and some assemblers don't like this.
//   R(reg)
//           This expands to a reference to register `reg'. On Unix, this
//           prepends a % charater.
//   NUM(value)
//           This expands to an immediate value. On Unix, this prepends a $
//           character.
//   ADDR(variable)
//           This expands to an immediate value, the address of some variable
//           or function. On Unix, this prepends a $ character. With MSVC,
//           this prepends the keyword "OFFSET".
//   ADDR_PCRELATIVE(variable)
//           This expands to the address of symbol `variable', with program
//           counter (%rip) relative addressing.
//   About operand sizes: On Unix, a suffix to the instruction specifies the
//           size of the operands (for example "movb", "movw", "movl"). With
//           MSVC, there is no such suffix. Instead, the assembler infers the
//           operand size from the names of the registers ("al" vs. "ax" vs.
//           "eax"). This works well in most cases, but in instructions like
//           "mul [esi]" the assembler guesses the operand size: "byte" by
//           default. So it is better to explicitly specify the operand size
//           of memory operands (prefix X1, X2, X4, X8).
//           (Side note about Unix assemblers: Some Unix assemblers allow you
//           to write "testb %eax,%eax" but silently treat this as
//           "testb %al,%al".)
//   X1
//           This prefixes a memory reference of 1 byte.
//   X2
//           This prefixes a memory reference of 2 bytes.
//   X4
//           This prefixes a memory reference of 4 bytes.
//   X8
//           This prefixes a memory reference of 8 bytes.
//   MEM(base)
//           This expands to a memory reference at address `base'.
//   MEM_DISP(base,displacement)
//           This expands to a memory reference at address `base+displacement'.
//   MEM_INDEX(base,index)
//           This expands to a memory reference at address `base+index'.
//   MEM_SHINDEX(base,index,size)
//           This expands to a memory reference at address
//           `base+index*size', where `size' is 1, 2, 4, or 8.
//   MEM_DISP_SHINDEX0(displacement,index,size)
//           This expands to a memory reference at address
//           `displacement+index*size', where `size' is 1, 2, 4, or 8.
//   MEM_DISP_SHINDEX(base,displacement,index,size)
//           This expands to a memory reference at address
//           `base+displacement+index*size', where `size' is 1, 2, 4, or 8.
//   MEM_PCRELATIVE(variable)
//           This expands to a memory reference at symbol `variable', with
//           program counter (%rip) relative addressing.
//   INDIR(value)
//           This expands to an implicit indirection. On Unix, this prepends
//           a * character.
//   INSN1(mnemonic,size_suffix,dst)
//           This expands to an instruction with one operand.
//   INSN2(mnemonic,size_suffix,src,dst)
//           This expands to an instruction with two operands. In our notation,
//           `src' comes first and `dst' second, but they are reversed when
//           expanding to Intel syntax. In Intel syntax, size_suffix is omitted.
//   INSN2S(mnemonic,size_suffix,src,dst)
//           This expands to an instruction with two operands. In our notation,
//           `src' comes first and `dst' second, but they are reversed when
//           expanding to Intel syntax. In Intel syntax, size_suffix is
//           preserved.
//   INSN2MOVXL(mnemonic,size_suffix,src,dst)
//           This expands to an instruction with two operands, of type
//           movsbl/movzbl, which in some syntaxes requires a second suffix.
//   INSN2MOVXQ(mnemonic,size_suffix,src,dst)
//           This expands to an instruction with two operands, of type
//           movsbq/movzbq, which in some syntaxes requires a second suffix.
//   INSN2MOVXLQ(mnemonic,size_suffix,src,dst)
//           This expands to an instruction with two operands, of type
//           movslq/movzlq, which in some syntaxes requires a second suffix.
//   _
//           For instructions which don't have a size suffix, like jump
//           instructions. Expands to nothing. Needed for MSVC, which has
//           problems with empty macro arguments.
//   TEXT()
//           Switch to the code section.
//   P2ALIGN(log,max)
//           Align to 2^log bytes, but insert at most max bytes.
//   GLOBL(name)
//           Declare `name' to be a global symbol.
//   DECLARE_FUNCTION(name)
//           Declare `name' to be a global function. When assembly language
//           code is compiled into a shared library, ELF linkers need to know
//           which symbols are functions.
//   FUNBEGIN(name)
//           Start the assembly language code for the C function `name'.
//   FUNEND(name,size_expression)
//           End the assembly language code for the C function 'name'.
//   EH_FRAME_SECTION
//           The arguments to the .section statement that introduces the
//           exception handler section (on ELF platforms).

#ifdef _MSC_VER
// MSVC
#define C(entrypoint) entrypoint
#define L(label) $L##label
#else
#ifdef ASM_UNDERSCORE
// Mac OS X
#define C(entrypoint) _##entrypoint
#define L(label) L##label
#else
// Linux/ELF, Solaris/ELF, Windows with GNU as
#define C(entrypoint) entrypoint
#define L(label) .L##label
#endif
#endif

// The two syntaxes:
// - ATT_SYNTAX for GNU assembler version 2.
// - INTEL_SYNTAX for MS assembler.
// Note: INTEL_SYNTAX is not the same syntax as produced by "gcc masm=intel"
// as there are syntactic differences between that syntax and the one accepted
// by the MS assembler (for MEM_DISP, INDIR, P2ALIGN, FUNBEGIN, FUNEND etc.).
#ifdef _MSC_VER
// MS assembler
#define R(r) r
#define NUM(n) n
#define ADDR(a) OFFSET a
#define ADDR_PCRELATIVE(a) OFFSET a
#define X1 BYTE PTR
#define X2 WORD PTR
#define X4 DWORD PTR
#define X8 QWORD PTR
#define MEM(base) [base]
#define MEM_DISP(base,displacement) [base+(displacement)]
#define MEM_INDEX(base,index) [base+index]
#define MEM_SHINDEX(base,index,size) [base+index*size]
#define MEM_DISP_SHINDEX0(displacement,index,size) [(displacement)+index*size]
#define MEM_DISP_SHINDEX(base,displacement,index,size) [base+(displacement)+index*size]
#define MEM_PCRELATIVE(variable) variable
#define INDIR(value)value
#define INSNCONC(mnemonic,suffix)mnemonic##suffix
#define INSN1(mnemonic,size_suffix,dst)mnemonic dst
#define INSN2(mnemonic,size_suffix,src,dst)mnemonic dst,src
#define INSN2S(mnemonic,size_suffix,src,dst)INSNCONC(mnemonic,size_suffix) dst,src
#define INSN2MOVXL(mnemonic,size_suffix,src,dst)INSNCONC(mnemonic,x) dst,src
#define INSN2MOVXQ(mnemonic,size_suffix,src,dst)INSNCONC(mnemonic,x) dst,src
#define INSN2MOVXLQ(mnemonic,size_suffix,src,dst)INSNCONC(mnemonic,xd) dst,src
#else
// GNU assembler version 2
#define R(r) %r
#define NUM(n) $ n
#define ADDR(a) $##a
#define ADDR_PCRELATIVE(a) a(%rip)
#define X1
#define X2
#define X4
#define X8
#define MEM(base)(R(base))
#define MEM_DISP(base,displacement)displacement(R(base))
#define MEM_INDEX(base,index)(R(base),R(index))
#define MEM_SHINDEX(base,index,size)(R(base),R(index),size)
#define MEM_DISP_SHINDEX0(displacement,index,size)displacement(,R(index),size)
#define MEM_DISP_SHINDEX(base,displacement,index,size)displacement(R(base),R(index),size)
#define MEM_PCRELATIVE(variable) variable(%rip)
#define INDIR(value)*value
#define INSNCONC(mnemonic,size_suffix)mnemonic##size_suffix
#define INSN1(mnemonic,size_suffix,dst)INSNCONC(mnemonic,size_suffix) dst
#define INSN2(mnemonic,size_suffix,src,dst)INSNCONC(mnemonic,size_suffix) src,dst
#define INSN2S(mnemonic,size_suffix,src,dst)INSNCONC(mnemonic,size_suffix) src,dst
#define INSN2MOVXL(mnemonic,size_suffix,src,dst)INSNCONC(mnemonic,size_suffix##l) src,dst
#define INSN2MOVXQ(mnemonic,size_suffix,src,dst)INSNCONC(mnemonic,size_suffix##q) src,dst
#define INSN2MOVXLQ(mnemonic,size_suffix,src,dst)INSNCONC(mnemonic,size_suffix##q) src,dst
#endif

#define _

#ifdef _MSC_VER
// MS assembler
#define TEXT() _TEXT SEGMENT
#else
#define TEXT() .text
#endif

#ifdef _MSC_VER
// MS assembler
// There is no equivalent for "p2align 4,,7". This comes closest:
#define P2ALIGN(log,max) ALIGN 8
#else
#if defined __sun
// Solaris
#define P2ALIGN(log,max) .align 1<<log
#else
// Mac OS X, Linux, Windows with GNU as
#define P2ALIGN(log,max) .p2align log,,max
#endif
#endif

#ifdef _MSC_VER
// MS assembler
#define GLOBL(name)
#else
#define GLOBL(name) .globl name
#endif

// Define the DECLARE_FUNCTION(name) macro.
#ifdef _MSC_VER
// MS assembler
#define DECLARE_FUNCTION(name) PUBLIC name
#else
#if (defined _WIN32 || defined __WIN32__ || defined __CYGWIN__)
// Windows with GNU as
#define DECLARE_FUNCTION(name) .def C(name); .scl 2; .type 32; .endef
#else
#ifdef ASM_UNDERSCORE
// Mac OS X
#define DECLARE_FUNCTION(name)
#else
// ELF
#define DECLARE_FUNCTION(name) .type C(name),@function
#endif
#endif
#endif

// Define the FUNBEGIN(name) and FUNEND() macros.
#ifdef _MSC_VER
// MS assembler
#define FUNBEGIN(name) name PROC
#define FUNEND(name,size_expression) name ENDP
#else
#define FUNBEGIN(name) C(name):
#if (defined _WIN32 || defined __WIN32__ || defined __CYGWIN__) || defined(ASM_UNDERSCORE)
// Windows with GNU as, Mac OS X
#define FUNEND(name,size_expression)
#else
// ELF
#if defined __sun
// Solaris/ELF
#define FUNEND(name,size_expression) .size C(name), . - C(name)
#else
// Linux/ELF
#define FUNEND(name,size_expression) .size C(name),size_expression
#endif
#endif
#endif

// Section of frame info for exception handlers
#if defined __APPLE__ && defined __MACH__
// Mac OS X
#define EH_FRAME_SECTION __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
#else
#if defined __sun
// Solaris/ELF
#define EH_FRAME_SECTION .eh_frame,"aL",link=.text,@unwind
#else
// Linux/ELF
#define EH_FRAME_SECTION .eh_frame,"aw",@progbits
#endif
#endif
