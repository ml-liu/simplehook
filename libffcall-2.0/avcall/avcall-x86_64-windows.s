	.file	"avcall-x86_64-windows.c"
	.text
	.p2align 4,,15
	.globl	avcall_call
	.type	avcall_call, @function
avcall_call:
.LFB0:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	pushq	%rsi
	pushq	%rbx
.LCFI2:
	movq	%rcx, %rbx
	subq	$32, %rsp
	movq	48(%rcx), %rcx
	movq	40(%rbx), %rax
	subq	$2064, %rsp
	subq	%rcx, %rax
	sarq	$3, %rax
	cmpl	$4, %eax
	jle	.L6
	leal	-5(%rax), %r8d
	leaq	32(%rsp), %r9
	xorl	%eax, %eax
	addq	$1, %r8
	.p2align 4,,10
	.p2align 3
.L5:
	movq	32(%rcx,%rax,8), %rdx
	movq	%rdx, (%r9,%rax,8)
	addq	$1, %rax
	cmpq	%r8, %rax
	jne	.L5
.L6:
	movl	68(%rbx), %eax
	testl	%eax, %eax
	je	.L7
	testb	$1, %al
	je	.L8
	movss	76(%rbx), %xmm0
.L8:
	testb	$2, %al
	je	.L9
	movss	80(%rbx), %xmm1
.L9:
	testb	$4, %al
	je	.L10
	movss	84(%rbx), %xmm2
.L10:
	testb	$8, %al
	jne	.L78
.L7:
	movl	72(%rbx), %eax
	testl	%eax, %eax
	je	.L12
	testb	$1, %al
	je	.L13
	movsd	96(%rbx), %xmm0
.L13:
	testb	$2, %al
	je	.L14
	movsd	104(%rbx), %xmm1
.L14:
	testb	$4, %al
	je	.L15
	movsd	112(%rbx), %xmm2
.L15:
	testb	$8, %al
	jne	.L79
.L12:
	movl	24(%rbx), %eax
	cmpl	$13, %eax
	je	.L80
	cmpl	$14, %eax
	je	.L81
	movq	8(%rcx), %rdx
	movq	24(%rcx), %r9
	movq	16(%rcx), %r8
	movq	(%rcx), %rcx
	call	*8(%rbx)
	movl	24(%rbx), %edx
	cmpl	$1, %edx
	je	.L18
	testl	%edx, %edx
	je	.L76
	cmpl	$2, %edx
	je	.L73
	cmpl	$3, %edx
	je	.L73
	cmpl	$4, %edx
	je	.L73
	cmpl	$5, %edx
	je	.L74
	cmpl	$6, %edx
	je	.L74
	cmpl	$7, %edx
	je	.L75
	cmpl	$8, %edx
	je	.L75
	cmpl	$9, %edx
	je	.L76
	cmpl	$10, %edx
	je	.L76
	cmpl	$11, %edx
	je	.L76
	cmpl	$12, %edx
	je	.L76
	cmpl	$15, %edx
	je	.L76
	cmpl	$16, %edx
	jne	.L18
	testl	$512, (%rbx)
	je	.L18
	movq	32(%rbx), %r8
	leaq	-4(%r8), %rdx
	testq	$-5, %rdx
	je	.L35
	leaq	-1(%r8), %rdx
	cmpq	$1, %rdx
	ja	.L18
.L35:
	movq	16(%rbx), %rdx
	movq	%rdx, %r9
	andl	$7, %edx
	addq	%rdx, %r8
	andq	$-8, %r9
	cmpq	$8, %r8
	jbe	.L82
	leal	0(,%rdx,8), %ecx
	movq	(%r9), %r10
	movq	%rax, %rsi
	movq	$-1, %r11
	negl	%edx
	salq	%cl, %rsi
	salq	%cl, %r11
	movq	%rsi, %rcx
	xorq	%r10, %rcx
	andq	%r11, %rcx
	xorq	%r10, %rcx
	movq	8(%r9), %r10
	movq	%rcx, (%r9)
	leal	-65(,%r8,8), %ecx
	movl	$2, %r8d
	salq	%cl, %r8
	leal	64(,%rdx,8), %ecx
	subq	$1, %r8
	sarq	%cl, %rax
	xorq	%r10, %rax
	andq	%r8, %rax
	xorq	%r10, %rax
	movq	%rax, 8(%r9)
.L18:
	leaq	-16(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
.LCFI3:
	popq	%rsi
.LCFI4:
	popq	%rbp
.LCFI5:
	ret
	.p2align 4,,10
	.p2align 3
.L79:
.LCFI6:
	movsd	120(%rbx), %xmm3
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L78:
	movss	88(%rbx), %xmm3
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L76:
	movq	16(%rbx), %rdx
	movq	%rax, (%rdx)
	leaq	-16(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
.LCFI7:
	popq	%rsi
.LCFI8:
	popq	%rbp
.LCFI9:
	ret
	.p2align 4,,10
	.p2align 3
.L73:
.LCFI10:
	movq	16(%rbx), %rdx
	movb	%al, (%rdx)
	leaq	-16(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
.LCFI11:
	popq	%rsi
.LCFI12:
	popq	%rbp
.LCFI13:
	ret
	.p2align 4,,10
	.p2align 3
.L81:
.LCFI14:
	movq	16(%rbx), %rsi
	movq	8(%rcx), %rdx
	movq	24(%rcx), %r9
	movq	16(%rcx), %r8
	movq	(%rcx), %rcx
	call	*8(%rbx)
	movsd	%xmm0, (%rsi)
	leaq	-16(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
.LCFI15:
	popq	%rsi
.LCFI16:
	popq	%rbp
.LCFI17:
	ret
.L80:
.LCFI18:
	movq	16(%rbx), %rsi
	movq	8(%rcx), %rdx
	movq	24(%rcx), %r9
	movq	16(%rcx), %r8
	movq	(%rcx), %rcx
	call	*8(%rbx)
	movss	%xmm0, (%rsi)
	jmp	.L18
.L74:
	movq	16(%rbx), %rdx
	movw	%ax, (%rdx)
	jmp	.L18
.L75:
	movq	16(%rbx), %rdx
	movl	%eax, (%rdx)
	jmp	.L18
.L82:
	leal	-1(,%r8,8), %ecx
	movq	(%r9), %r10
	sall	$3, %edx
	movl	$2, %r8d
	movl	$1, %r11d
	salq	%cl, %r8
	movl	%edx, %ecx
	salq	%cl, %r11
	salq	%cl, %rax
	subq	%r11, %r8
	xorq	%r10, %rax
	andq	%r8, %rax
	xorq	%r10, %rax
	movq	%rax, (%r9)
	jmp	.L18
.LFE0:
	.size	avcall_call, .-avcall_call
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0
	.byte	0x3
	.string	"zR"
	.uleb128 0x1
	.sleb128 -8
	.uleb128 0x10
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
	.long	.LFB0-.
	.long	.LFE0-.LFB0
	.uleb128 0
	.byte	0x4
	.long	.LCFI0-.LFB0
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI2-.LCFI1
	.byte	0x84
	.uleb128 0x3
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xa
	.byte	0xc3
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xc4
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xb
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xa
	.byte	0xc3
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0xc4
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xb
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xa
	.byte	0xc3
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xc4
	.byte	0x4
	.long	.LCFI13-.LCFI12
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI14-.LCFI13
	.byte	0xb
	.byte	0x4
	.long	.LCFI15-.LCFI14
	.byte	0xa
	.byte	0xc3
	.byte	0x4
	.long	.LCFI16-.LCFI15
	.byte	0xc4
	.byte	0x4
	.long	.LCFI17-.LCFI16
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI18-.LCFI17
	.byte	0xb
	.align 8
.LEFDE1:
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
