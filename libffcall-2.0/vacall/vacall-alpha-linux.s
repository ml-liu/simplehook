	.set noreorder
	.set volatile
	.set noat
	.set nomacro
	.text
	.align 2
	.align 4
	.globl vacall_receiver
	.ent vacall_receiver
vacall_receiver:
	.frame $15,192,$26,48
	.mask 0x4008000,-192
	ldah $29,0($27)		!gpdisp!1
	lda $29,0($29)		!gpdisp!1
$vacall_receiver..ng:
	lda $30,-192($30)
	stq $15,8($30)
	mov $30,$15
	lda $3,144($15)
	stq $26,0($30)
	.prologue 1
	lda $2,88($15)
	stq $16,144($15)
	subq $2,$3,$2
	ldq $3,vacall_function($29)		!literal
	stq $2,80($15)
	lda $2,192($15)
	lda $16,16($15)
	stq $2,72($15)
	ldq $27,0($3)
	lda $2,144($15)
	stq $17,152($15)
	stq $18,160($15)
	stq $19,168($15)
	stq $20,176($15)
	stq $21,184($15)
	stt $f16,88($15)
	stt $f17,96($15)
	stt $f18,104($15)
	stt $f19,112($15)
	stt $f20,120($15)
	stt $f21,128($15)
	stl $31,16($15)
	stq $2,40($15)
	stq $31,48($15)
	stl $31,56($15)
	jsr $26,($27),0
	ldah $29,0($26)		!gpdisp!2
	lda $29,0($29)		!gpdisp!2
	ldl $2,56($15)
	beq $2,$L43
	zapnot $2,15,$3
	cmpeq $3,1,$2
	bne $2,$L44
	cmpeq $3,2,$2
	bne $2,$L44
	cmpeq $3,3,$2
	bne $2,$L50
	cmpeq $3,4,$2
	bne $2,$L51
	cmpeq $3,5,$2
	bne $2,$L52
	cmpeq $3,6,$2
	bne $2,$L53
	cmpeq $3,7,$2
	bne $2,$L54
	cmpeq $3,8,$2
	bne $2,$L48
	cmpeq $3,9,$2
	bne $2,$L48
	cmpeq $3,10,$2
	bne $2,$L48
	cmpeq $3,11,$2
	bne $2,$L48
	cmpeq $3,12,$2
	bne $2,$L55
	cmpeq $3,13,$2
	bne $2,$L56
	cmpeq $3,14,$2
	bne $2,$L48
	cmpeq $3,15,$2
	beq $2,$L43
	lda $2,1024($31)
	ldl $3,16($15)
	and $2,$3,$2
	beq $2,$L43
	ldq $3,64($15)
	cmpeq $3,1,$2
	bne $2,$L57
	cmpeq $3,2,$2
	bne $2,$L58
	cmpeq $3,4,$2
	bne $2,$L59
	cmpeq $3,8,$2
	bne $2,$L60
	cmpeq $3,16,$2
	beq $2,$L43
	ldq $2,48($15)
	ldq $1,8($2)
	ldq $0,0($2)
	.align 4
$L43:
	mov $15,$30
	ldq $26,0($30)
	ldq $15,8($30)
	lda $30,192($30)
	ret $31,($26),1
	.align 4
$L44:
	mov $15,$30
	ldl $2,24($15)
	ldq $26,0($30)
	sll $2,56,$2
	sra $2,56,$0
	ldq $15,8($30)
	lda $30,192($30)
	ret $31,($26),1
$L51:
	ldl $2,24($15)
	sll $2,48,$2
	sra $2,48,$0
	br $31,$L43
$L50:
	ldl $2,24($15)
	bis $31,$31,$31
	and $2,0xff,$0
	br $31,$L43
$L48:
	ldq $0,24($15)
	br $31,$L43
$L52:
	ldl $2,24($15)
	bis $31,$31,$31
	zapnot $2,3,$0
	br $31,$L43
$L53:
	ldl $3,24($15)
	bis $31,$31,$31
	mov $3,$0
	br $31,$L43
$L54:
	ldl $2,24($15)
	bis $31,$31,$31
	zapnot $2,15,$0
	br $31,$L43
$L55:
	lds $f0,24($15)
	br $31,$L43
$L56:
	ldt $f0,24($15)
	br $31,$L43
$L57:
	ldq $3,48($15)
	ldq_u $2,0($3)
	extbl $2,$3,$0
	br $31,$L43
$L58:
	ldq $3,48($15)
	ldq_u $2,0($3)
	extwl $2,$3,$0
	br $31,$L43
$L60:
	ldq $2,48($15)
	bis $31,$31,$31
	ldq $0,0($2)
	br $31,$L43
$L59:
	ldq $2,48($15)
	ldl $3,0($2)
	zapnot $3,15,$0
	br $31,$L43
	.end vacall_receiver
	.ident	"GCC: (GNU) 4.0.2"
	.section	.note.GNU-stack,"",@progbits
