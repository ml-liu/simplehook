	.file	"avcall-i386.c"
	.text
	.align 2
	.p2align 2,,3
.globl avcall_call
	.type	avcall_call,@function
avcall_call:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	8(%ebp), %eax
	movl	20(%eax), %edx
	movl	24(%eax), %eax
	subl	%eax, %edx
	sarl	$2, %edx
	xorl	%esi, %esi
	subl	$1024, %esp
	cmpl	%edx, %esi
	movl	%esp, %edi
	jge	.L47
	movl	%eax, %ecx
	.p2align 2,,3
.L6:
	movl	(%ecx,%esi,4), %eax
	movl	%eax, (%edi,%esi,4)
	incl	%esi
	cmpl	%edx, %esi
	jl	.L6
.L47:
	movl	8(%ebp), %edx
	movl	12(%edx), %eax
	cmpl	$13, %eax
	je	.L55
	cmpl	$14, %eax
	je	.L56
	movl	8(%ebp), %ecx
	call	*4(%ecx)
	movl	%eax, %esi
	movl	8(%ebp), %eax
	movl	12(%eax), %ecx
	cmpl	$1, %ecx
	je	.L8
	testl	%ecx, %ecx
	jne	.L13
	movl	8(%eax), %eax
.L50:
	movl	%esi, (%eax)
.L8:
	leal	-8(%ebp), %esp
	popl	%esi
	xorl	%eax, %eax
	popl	%edi
	leave
	ret
.L13:
	cmpl	$2, %ecx
	je	.L53
	cmpl	$3, %ecx
	je	.L53
	cmpl	$4, %ecx
	je	.L53
	cmpl	$5, %ecx
	je	.L57
	cmpl	$6, %ecx
	je	.L51
	cmpl	$7, %ecx
	je	.L48
	cmpl	$8, %ecx
	je	.L54
	cmpl	$9, %ecx
	je	.L48
	cmpl	$10, %ecx
	je	.L54
	leal	-11(%ecx), %eax
	cmpl	$1, %eax
	jbe	.L49
	cmpl	$15, %ecx
	je	.L48
	cmpl	$16, %ecx
	jne	.L8
	movl	8(%ebp), %ecx
	testb	$2, 1(%ecx)
	je	.L8
	movl	16(%ecx), %eax
	cmpl	$1, %eax
	je	.L58
	cmpl	$2, %eax
	je	.L51
	cmpl	$4, %eax
	je	.L48
	cmpl	$8, %eax
	jne	.L8
.L49:
	movl	8(%ebp), %ecx
	movl	8(%ecx), %eax
	movl	%esi, (%eax)
	movl	%edx, 4(%eax)
	jmp	.L8
.L48:
	movl	8(%ebp), %edx
	movl	8(%edx), %eax
	jmp	.L50
.L51:
	movl	8(%ebp), %ecx
	movl	8(%ecx), %eax
.L52:
	movw	%si, (%eax)
	jmp	.L8
.L58:
	movl	8(%ecx), %eax
	movl	%esi, %edx
	movb	%dl, (%eax)
	jmp	.L8
	.p2align 2,,3
.L54:
	movl	8(%ebp), %ecx
	movl	8(%ecx), %eax
	jmp	.L50
.L57:
	movl	8(%ebp), %edx
	movl	8(%edx), %eax
	jmp	.L52
.L53:
	movl	8(%ebp), %edx
	movl	8(%edx), %eax
	movl	%esi, %ecx
	movb	%cl, (%eax)
	jmp	.L8
.L56:
	movl	8(%ebp), %eax
	call	*4(%eax)
	movl	8(%ebp), %edx
	movl	8(%edx), %eax
	fstpl	(%eax)
	jmp	.L8
.L55:
	call	*4(%edx)
	movl	8(%ebp), %ecx
	movl	8(%ecx), %eax
	fstps	(%eax)
	jmp	.L8
.Lfe1:
	.size	avcall_call,.Lfe1-avcall_call
	.ident	"GCC: (GNU) 3.1"
