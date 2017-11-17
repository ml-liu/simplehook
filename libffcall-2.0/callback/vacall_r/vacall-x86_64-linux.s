	.file	"vacall-x86_64.c"
	.text
	.p2align 4,,15
	.type	callback_receiver, @function
callback_receiver:
.LFB2:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	pushq	%r13
.LCFI2:
	pushq	%r12
.LCFI3:
	subq	$192, %rsp
.LCFI4:
	movq	%rcx, -48(%rbp)
	leaq	16(%rbp), %rcx
	movq	%rdi, -72(%rbp)
	movq	%rsi, -64(%rbp)
	movsd	%xmm0, -144(%rbp)
	movq	%rcx, -184(%rbp)
	movq	$0, -176(%rbp)
	movsd	%xmm1, -136(%rbp)
	movq	%rdx, -56(%rbp)
	movsd	%xmm2, -128(%rbp)
	leaq	-208(%rbp), %rsi
	movq	%r8, -40(%rbp)
	movsd	%xmm3, -120(%rbp)
	movq	%r9, -32(%rbp)
	movsd	%xmm4, -112(%rbp)
	movsd	%xmm5, -104(%rbp)
	movl	$0, -208(%rbp)
	movsd	%xmm6, -96(%rbp)
	movl	$0, -168(%rbp)
	movsd	%xmm7, -88(%rbp)
	movl	$0, -80(%rbp)
	movl	$0, -152(%rbp)
	movq	8(%r10), %rdi
	call	*(%r10)
	movl	-168(%rbp), %ecx
	testl	%ecx, %ecx
	je	.L41
	cmpl	$1, %ecx
	je	.L42
	cmpl	$2, %ecx
	je	.L42
	cmpl	$3, %ecx
	.p2align 4,,5
	je	.L48
	cmpl	$4, %ecx
	.p2align 4,,5
	je	.L49
	cmpl	$5, %ecx
	.p2align 4,,5
	je	.L50
	cmpl	$6, %ecx
	.p2align 4,,5
	je	.L51
	cmpl	$7, %ecx
	.p2align 4,,5
	je	.L52
	cmpl	$8, %ecx
	.p2align 4,,5
	je	.L46
	cmpl	$9, %ecx
	.p2align 4,,5
	je	.L46
	cmpl	$10, %ecx
	.p2align 4,,5
	je	.L46
	cmpl	$11, %ecx
	.p2align 4,,5
	je	.L46
	cmpl	$12, %ecx
	.p2align 4,,5
	je	.L53
	cmpl	$13, %ecx
	.p2align 4,,5
	je	.L54
	cmpl	$14, %ecx
	.p2align 4,,5
	je	.L46
	cmpl	$15, %ecx
	.p2align 4,,5
	jne	.L41
	testb	$4, -207(%rbp)
	.p2align 4,,2
	je	.L41
	movq	-160(%rbp), %rsi
	leaq	-1(%rsi), %rcx
	cmpq	$15, %rcx
	ja	.L41
	movq	-176(%rbp), %rcx
	movq	%rcx, %r12
	movq	%rcx, %r8
	andl	$7, %r8d
	andq	$-8, %r12
	cmpq	$8, %rsi
	leaq	(%rsi,%r8), %r11
	ja	.L35
	cmpq	$8, %r11
	ja	.L37
	leal	-1(,%r11,8), %ecx
	movl	$2, %esi
	salq	%cl, %rsi
	leal	0(,%r8,8), %ecx
	decq	%rsi
	andq	(%r12), %rsi
	movq	%rsi, %rax
	sarq	%cl, %rax
	.p2align 4,,7
.L41:
	addq	$192, %rsp
	popq	%r12
	popq	%r13
	leave
	ret
	.p2align 4,,7
.L42:
	movsbq	-200(%rbp),%rax
	addq	$192, %rsp
	popq	%r12
	popq	%r13
	leave
	ret
.L49:
	movswq	-200(%rbp),%rax
	jmp	.L41
.L48:
	movzbq	-200(%rbp), %rax
	jmp	.L41
.L46:
	movq	-200(%rbp), %rax
	jmp	.L41
.L50:
	movzwq	-200(%rbp), %rax
	jmp	.L41
.L51:
	movslq	-200(%rbp),%rax
	jmp	.L41
.L52:
	mov	-200(%rbp), %eax
	jmp	.L41
.L53:
	movss	-200(%rbp), %xmm0
	jmp	.L41
.L54:
	movlpd	-200(%rbp), %xmm0
	jmp	.L41
.L35:
	cmpq	$16, %r11
	ja	.L39
	leal	-65(,%r11,8), %ecx
	movl	$2, %esi
	leal	0(,%r8,8), %r9d
	movl	$32, %edi
	salq	%cl, %rsi
	leaq	0(,%r8,4), %rcx
	movq	(%r12), %r8
	decq	%rsi
	andq	8(%r12), %rsi
	subl	%ecx, %edi
	movl	%r9d, %ecx
	sarq	%cl, %r8
	movl	%edi, %ecx
	movq	%r8, %rax
	movq	%rsi, %r11
	movq	%rsi, %rdx
	salq	%cl, %r11
	salq	%cl, %r11
	movl	%r9d, %ecx
	orq	%r11, %rax
	sarq	%cl, %rdx
	jmp	.L41
.L37:
	movq	(%r12), %rdi
	leal	-65(,%r11,8), %esi
	salq	$3, %r8
	movl	%r8d, %ecx
	movl	$2, %r11d
	sarq	%cl, %rdi
	movl	%esi, %ecx
	movl	$64, %esi
	salq	%cl, %r11
	subl	%r8d, %esi
	movq	%rdi, %rax
	decq	%r11
	andq	8(%r12), %r11
	movl	%esi, %ecx
	salq	%cl, %r11
	orq	%r11, %rax
	jmp	.L41
.L39:
	leaq	0(,%r8,8), %rcx
	movq	(%r12), %r13
	movq	8(%r12), %r8
	movl	$64, %edi
	subl	%ecx, %edi
	movl	%ecx, %r9d
	sarq	%cl, %r13
	movq	%r8, %rsi
	movl	%edi, %ecx
	salq	%cl, %rsi
	movq	%r13, %rax
	movl	%r9d, %ecx
	orq	%rsi, %rax
	leal	-129(,%r11,8), %esi
	sarq	%cl, %r8
	movl	$2, %r9d
	movq	%r8, %rdx
	movl	%esi, %ecx
	salq	%cl, %r9
	movl	%edi, %ecx
	leaq	-1(%r9), %rsi
	andq	16(%r12), %rsi
	salq	%cl, %rsi
	orq	%rsi, %rdx
	jmp	.L41
.LFE2:
	.size	callback_receiver, .-callback_receiver
	.p2align 4,,15
.globl callback_get_receiver
	.type	callback_get_receiver, @function
callback_get_receiver:
.LFB3:
	pushq	%rbp
.LCFI5:
	leaq	callback_receiver(%rip), %rax
	movq	%rsp, %rbp
.LCFI6:
	leave
	ret
.LFE3:
	.size	callback_get_receiver, .-callback_get_receiver
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zR"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x1
	.byte	0x1b
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB2-.
	.long	.LFE2-.LFB2
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB2
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI4-.LCFI1
	.byte	0x8c
	.uleb128 0x4
	.byte	0x8d
	.uleb128 0x3
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB3-.
	.long	.LFE3-.LFB3
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI5-.LFB3
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE3:
	.ident	"GCC: (GNU) 4.0.2"
	.section	.note.GNU-stack,"",@progbits
