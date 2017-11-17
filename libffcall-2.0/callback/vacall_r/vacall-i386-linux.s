	.file	"vacall-i386.c"
	.text
	.align 2
	.p2align 2,,3
	.type	callback_receiver,@function
callback_receiver:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	leal	8(%ebp), %edx
	subl	$56, %esp
	movl	%edx, -40(%ebp)
	leal	-56(%ebp), %edx
	movl	$0, -56(%ebp)
	movl	$0, -36(%ebp)
	movl	$0, -32(%ebp)
	movl	%ebx, -24(%ebp)
	pushl	%edx
	pushl	4(%ecx)
	call	*(%ecx)
	movl	-32(%ebp), %esi
	addl	$16, %esp
	testl	%esi, %esi
	je	.L43
	cmpl	$1, %esi
	je	.L44
	cmpl	$2, %esi
	je	.L44
	cmpl	$3, %esi
	je	.L49
	cmpl	$4, %esi
	je	.L50
	cmpl	$5, %esi
	je	.L51
	cmpl	$6, %esi
	je	.L48
	cmpl	$7, %esi
	je	.L48
	cmpl	$8, %esi
	je	.L48
	cmpl	$9, %esi
	je	.L48
	leal	-10(%esi), %edx
	cmpl	$1, %edx
	ja	.L22
	movl	-48(%ebp), %eax
#APP
	movl -44(%ebp),%edx
.L33:
	.p2align 2,,3
#NO_APP
.L43:
	movl	-56(%ebp), %esi
.L3:
	andl	$512, %esi
	je	.L1
#APP
	movl 0(%ebp),%ecx
#NO_APP
	movl	-40(%ebp), %esp
#APP
	jmp *%ecx
#NO_APP
.L1:
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	leave
	ret
.L22:
	cmpl	$12, %esi
	je	.L52
	cmpl	$13, %esi
	je	.L53
	cmpl	$14, %esi
	je	.L48
	cmpl	$15, %esi
	jne	.L43
	movl	-56(%ebp), %esi
	testl	$1024, %esi
	movl	%esi, %edi
	je	.L31
	movl	-28(%ebp), %edx
	cmpl	$1, %edx
	je	.L54
	cmpl	$2, %edx
	je	.L55
	cmpl	$4, %edx
	je	.L56
	cmpl	$8, %edx
	je	.L57
.L31:
	andl	$16, %edi
	movl	-36(%ebp), %eax
	jne	.L3
#APP
	leal -8(%ebp), %esp
	popl %esi
	popl %edi
	leave
	ret $4
#NO_APP
	jmp	.L3
.L57:
	movl	-36(%ebp), %edx
	movl	(%edx), %eax
#APP
	movl 4(%edx),%edx
#NO_APP
	jmp	.L3
.L56:
	movl	-36(%ebp), %edx
	movl	(%edx), %eax
	jmp	.L3
.L55:
	movl	-36(%ebp), %edx
	movzwl	(%edx), %eax
	jmp	.L3
.L54:
	movl	-36(%ebp), %edx
	movzbl	(%edx), %eax
	jmp	.L3
	.p2align 2,,3
.L48:
	movl	-48(%ebp), %eax
	jmp	.L43
.L53:
#APP
	fldl -48(%ebp)
#NO_APP
	jmp	.L43
.L52:
#APP
	flds -48(%ebp)
#NO_APP
	jmp	.L43
	.p2align 2,,3
.L51:
	movzwl	-48(%ebp), %eax
	jmp	.L43
.L50:
	movswl	-48(%ebp),%eax
	jmp	.L43
.L49:
	movzbl	-48(%ebp), %eax
	jmp	.L43
	.p2align 2,,3
.L44:
	movsbl	-48(%ebp),%eax
	jmp	.L43
.Lfe1:
	.size	callback_receiver,.Lfe1-callback_receiver
	.align 2
	.p2align 2,,3
.globl callback_get_receiver
	.type	callback_get_receiver,@function
callback_get_receiver:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	call	.L59
.L59:
	popl	%ebx
	addl	$_GLOBAL_OFFSET_TABLE_+[.-.L59], %ebx
	leal	callback_receiver@GOTOFF(%ebx), %eax
	movl	(%esp), %ebx
	leave
	ret
.Lfe2:
	.size	callback_get_receiver,.Lfe2-callback_get_receiver
	.ident	"GCC: (GNU) 3.1"
