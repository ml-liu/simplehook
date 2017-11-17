#!/bin/sh
# Translate the assembler syntax of x86_64 assembler programs
# Usage: asm-x86_64.sh < linux-x86_64-asm-file > portable-asm-file
# The portable-asm-file has to be
#   1. preprocessed,
#   2. grep -v '^ *#line' | grep -v '^#'
#   3. sed -e 's,% ,%,g' -e 's,\. ,.,g' -e 's,@ ,@,g' -e 's,//.*$,,' -e 's/##//g'

# Copyright (C) 1997-2017 Bruno Haible <bruno@clisp.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

tmpscript1=sed$$tmp1
tmpscript2=sed$$tmp2
tmpscript3=sed$$tmp3
tmpscript4=sed$$tmp4
tmpscript5=sed$$tmp5
tmpscript6=sed$$tmp6
tmpscript7=sed$$tmp7
tmpscript8=sed$$tmp8
tmpscript9=sed$$tmp9
tmpremove='rm -f $tmpscript1 $tmpscript2 $tmpscript3 $tmpscript4 $tmpscript5 $tmpscript6 $tmpscript7 $tmpscript8 $tmpscript9'
trap "$tmpremove" 1 2 15

cat > $tmpscript1 << \EOF
# ----------- Remove #APP/#NO_APP lines and gcc self-identification
/^#APP$/d
/^#NO_APP$/d
/gcc2_compiled/d
/gnu_compiled_c/d
/\.ident/d
EOF

cat > $tmpscript2 << \EOF
# ----------- Global symbols depends on ASM_UNDERSCORE
s/^\([A-Za-z0-9_]\+\)/C(\1)/
s/\.L\([A-Za-z0-9_]\+\)/L(\1)/
s/\([A-Za-z0-9_]\+\)(%rip)/C(\1)(%rip)/
# ----------- Massage the beginning of functions
/\.type/{
s/\.type	\([A-Za-z0-9_]*\), *@function/DECLARE_FUNCTION(\1)/
}
# ----------- Massage the end of functions
s/\.size	\([A-Za-z0-9_]*\),\(.*\)/FUNEND(\1,\2)/
# ----------- Section of frame info for exception handlers
s/\.section	\.eh_frame,"a[w]*",@progbits/.section	EH_FRAME_SECTION/
# ----------- Disable the frame info for exception handlers on Solaris
# (as the Solaris linker expects a different format, see
# https://illumos.org/issues/3210)
# Likewise this section does not assemble on Mac OS X 10.5 and on Windows.
/EH_FRAME_SECTION/{
s/^/#if !(defined __sun || (defined __APPLE__ \&\& defined __MACH__) || (defined _WIN32 || defined __WIN32__ || defined __CYGWIN__))\
/
}
${
s/$/\
#endif/
}
EOF

cat > $tmpscript3 << \EOF
# ----------- Introduce macro syntax for operands
s/\([-+0-9A-Z_]\+\)[(]%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\)[)]/MEM_DISP(\2,\1)/g
s/\(C[(][A-Za-z0-9_]\+[)]\)[(]%rip[)]/MEM_PCRELATIVE(\1)/g
s/[(]%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\)[)]/MEM(\1)/g
s/\([-+0-9A-Z_]\+\)[(],%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\),\([0-9]*\)[)]/MEM_DISP_SHINDEX0(\1,\2,\3)/g
s/\([-+0-9A-Z_]\+\)[(]%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\),%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\),\([0-9]*\)[)]/MEM_DISP_SHINDEX(\2,\1,\3,\4)/g
s/[(]%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\),%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\),\([0-9]*\)[)]/MEM_SHINDEX(\1,\2,\3)/g
s/[(]%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\),%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\)[)]/MEM_INDEX(\1,\2)/g
EOF

cat > $tmpscript4 << \EOF
# ----------- Add size suffix to 'mov' instructions
s/mov\([ 	]\+.*, *%\(e[abcd]x\|e[sd]i\|e[bs]p\|r[89]d\|r1[012345]d\)\)$/movl\1/
# ----------- Introduce macro syntax for instructions
s/\(push\|pop\|mul\|div\|not\|neg\|inc\|dec\)\(.\)\([ 	]\+\)\(.*\)$/INSN1(\1,\2	,\4)/
s/\(call\|jmp\|jc\|jnc\|je\|jne\|jz\|jnz\|ja\|jae\|jb\|jbe\|jl\|jle\|jg\|jge\|js\|jns\)\([ 	]\+\)\(.*\)$/INSN1(\1,_	,\3)/
s/\(movs\|movz\)\(.\)l\([ 	]\+\)\(.*\)$/INSN2MOVXL(\1,\2,\4)/
s/\(movs\|movz\)\([bw]\)q\([ 	]\+\)\(.*\)$/INSN2MOVXQ(\1,\2,\4)/
s/\(movs\|movz\)\(l\)q\([ 	]\+\)\(.*\)$/INSN2MOVXLQ(\1,\2,\4)/
s/\(mov\|movlp\|add\|sub\|adc\|sbb\|xor\|xorp\|test\|cmp\|rcl\|rcr\|and\|or\|sar\|sal\|shr\|shl\|lea\)\(.\)\([ 	]\+\)\(.*\)$/INSN2(\1,\2	,\4)/
s/\(movs\)\([sd]\)\([ 	]\+\)\(.*\)$/INSN2S(\1,\2	,\4)/
EOF

cat > $tmpscript5 << \EOF
# ----------- Rewrite lea operand
s/INSN2[(]lea,\([^,]*\), *MEM_PCRELATIVE[(]/INSN2(lea,\1,ADDR_PCRELATIVE(/g
EOF

cat > $tmpscript6 << \EOF
# ----------- Add size prefixes to memory references
s/\([(][^(,]*,b.*\), *MEM/\1,X1 MEM/g
s/\([(][^(,]*,w.*\), *MEM/\1,X2 MEM/g
s/\([(][^(,]*,[ls].*\), *MEM/\1,X4 MEM/g
s/\([(][^(,]*,[qd].*\), *MEM/\1,X8 MEM/g
EOF

cat > $tmpscript7 << \EOF
# ----------- Introduce macro syntax for register names
# Cf. https://stackoverflow.com/questions/1753602/
s/%\([abcd]l\|[sd]il\|[bs]pl\|r[89]b\|r1[012345]b\)/R(\1)/g
s/%\([abcd]x\|[sd]i\|[bs]p\|r[89]w\|r1[012345]w\)/R(\1)/g
s/%\(e[abcd]x\|e[sd]i\|e[bs]p\|r[89]d\|r1[012345]d\)/R(\1)/g
s/%\(r[abcd]x\|r[sd]i\|r[bs]p\|r[89]\|r1[012345]\)/R(\1)/g
s/%\(xmm[0-9]\+\)/R(\1)/g
s/\$\([-0-9]*\)/NUM(\1)/g
EOF

cat > $tmpscript8 << \EOF
# ----------- Treat indirect calls
s/\(INSN1[(]\(call\|jmp\),_[^,]*,\)\*\(\(R\)[(][^)]*[)]\)[)]$/\1INDIR(\3))/
s/\(INSN1[(]\(call\|jmp\),_[^,]*,\)\*\(\(MEM\|MEM_DISP\|C\)[(][^)]*[)]\)[)]$/\1INDIR(X8 \3))/
s/\(INSN1[(]\(call\|jmp\),_[^,]*,\)\*\(MEM_PCRELATIVE[(].*[)]\)[)]$/\1INDIR(X8 \3))/
EOF

cat > $tmpscript9 << \EOF
# ----------- Introduce macro syntax for assembler pseudo-ops
/\.file\([ 	]\+\)/d
s/\.text/TEXT()/
s/\.p2align \([^,]*\),,\(.*\)/P2ALIGN(\1,\2)/
s/\.p2align 3$/P2ALIGN(3,7)/
s/\.globl\([ 	]\+\)\(.*\)$/GLOBL(C(\2))/
/\.section\([ 	]\+\).*GNU-stack/d
# ----------- Declare global symbols as functions (we have no variables)
s/^C(\([A-Za-z0-9_]*\)):/FUNBEGIN(\1)/
EOF

sed -f $tmpscript1 | \
sed -f $tmpscript2 | \
sed -f $tmpscript3 | \
sed -f $tmpscript4 | \
sed -f $tmpscript5 | \
sed -f $tmpscript6 | \
sed -f $tmpscript7 | \
sed -f $tmpscript8 | \
sed -f $tmpscript9

eval "$tmpremove"
