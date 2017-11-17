	.file	"avcall-x86_64.c"
	.text
	.p2align 4,,15
.globl avcall_call
	.type	avcall_call, @function
avcall_call:
.LFB2:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	pushq	%r13
.LCFI2:
	pushq	%r12
.LCFI3:
	pushq	%rbx
.LCFI4:
	movq	%rdi, %rbx
	leaq	128(%rbx), %rdx
	subq	$2072, %rsp
.LCFI5:
	movq	40(%rdi), %rax
	movq	48(%rdi), %r8
	leaq	15(%rsp), %rsi
	subq	%r8, %rax
	andq	$-16, %rsi
	movq	%rax, %rdi
	movq	120(%rbx), %rax
	shrq	$3, %rdi
	subq	%rdx, %rax
	movq	%rax, %r9
	shrq	$3, %r9
	testl	%edi, %edi
	jle	.L2
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	.p2align 4,,7
.L4:
	movq	(%rdx,%r8), %rax
	incl	%ecx
	movq	%rax, (%rsi,%rdx)
	addq	$8, %rdx
	cmpl	%ecx, %edi
	jne	.L4
.L2:
	movl	24(%rbx), %eax
	cmpl	$13, %eax
	je	.L127
	cmpl	$14, %eax
	je	.L128
	cmpl	$7, %r9d
	movq	8(%rbx), %r12
	jle	.L58
	movlpd	184(%rbx), %xmm10
.L60:
	movq	176(%rbx), %r9
.L63:
	movq	168(%rbx), %r11
.L66:
	movq	160(%rbx), %r10
.L69:
	movlpd	152(%rbx), %xmm8
.L72:
	movq	144(%rbx), %rax
.L75:
	movq	136(%rbx), %r8
.L78:
	movlpd	128(%rbx), %xmm9
.L81:
	movq	88(%rbx), %rdx
	movq	96(%rbx), %rcx
	movsd	%xmm10, %xmm7
	movq	80(%rbx), %rsi
	movq	72(%rbx), %rdi
	movsd	%xmm8, %xmm3
	movq	%r9, -32(%rbp)
	movsd	%xmm9, %xmm0
	movlpd	-32(%rbp), %xmm6
	movq	%r11, -32(%rbp)
	movlpd	-32(%rbp), %xmm5
	movq	%r10, -32(%rbp)
	movlpd	-32(%rbp), %xmm4
	movq	%rax, -32(%rbp)
	movl	$8, %eax
	movlpd	-32(%rbp), %xmm2
	movq	%r8, -32(%rbp)
	movlpd	-32(%rbp), %xmm1
	movq	112(%rbx), %r9
	movq	104(%rbx), %r8
	call	*%r12
	movq	%rax, %r8
	movl	24(%rbx), %eax
	movq	%rdx, %r9
	cmpl	$1, %eax
	je	.L31
	testl	%eax, %eax
	je	.L125
	cmpl	$2, %eax
	je	.L122
	cmpl	$3, %eax
	.p2align 4,,5
	je	.L122
	cmpl	$4, %eax
	.p2align 4,,5
	je	.L122
	cmpl	$5, %eax
	.p2align 4,,5
	je	.L123
	cmpl	$6, %eax
	.p2align 4,,5
	je	.L123
	cmpl	$7, %eax
	.p2align 4,,5
	je	.L124
	cmpl	$8, %eax
	.p2align 4,,5
	je	.L124
	cmpl	$9, %eax
	.p2align 4,,5
	je	.L125
	cmpl	$10, %eax
	.p2align 4,,5
	je	.L125
	cmpl	$11, %eax
	.p2align 4,,5
	je	.L125
	cmpl	$12, %eax
	.p2align 4,,5
	je	.L125
	cmpl	$15, %eax
	.p2align 4,,5
	je	.L125
	cmpl	$16, %eax
	.p2align 4,,5
	jne	.L31
	testb	$2, 1(%rbx)
	.p2align 4,,5
	je	.L31
	movq	32(%rbx), %rdx
	leaq	-1(%rdx), %rax
	cmpq	$15, %rax
	ja	.L31
	movq	16(%rbx), %rax
	movq	%rax, %r10
	movq	%rax, %rdi
	andl	$7, %edi
	andq	$-8, %r10
	cmpq	$8, %rdx
	leaq	(%rdx,%rdi), %r11
	ja	.L112
	cmpq	$8, %r11
	ja	.L114
	leal	-1(,%r11,8), %ecx
	movq	(%r10), %rsi
	sall	$3, %edi
	movl	$2, %edx
	movl	$1, %eax
	salq	%cl, %rdx
	movl	%edi, %ecx
	salq	%cl, %rax
	salq	%cl, %r8
	xorq	%rsi, %r8
	subq	%rax, %rdx
	andq	%r8, %rdx
	xorq	%rdx, %rsi
	movq	%rsi, (%r10)
.L31:
	leaq	-24(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	leave
	ret
.L58:
	je	.L129
	cmpl	$5, %r9d
	jle	.L64
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movlpd	-32(%rbp), %xmm10
	.p2align 4,,3
	jmp	.L63
.L127:
	cmpl	$7, %r9d
	movq	16(%rbx), %r13
	movq	8(%rbx), %r12
	jle	.L7
	movlpd	184(%rbx), %xmm10
.L9:
	movq	176(%rbx), %r9
.L12:
	movq	168(%rbx), %r11
.L15:
	movq	160(%rbx), %r10
.L18:
	movlpd	152(%rbx), %xmm8
.L21:
	movq	144(%rbx), %rax
.L24:
	movq	136(%rbx), %r8
.L27:
	movlpd	128(%rbx), %xmm9
.L30:
	movq	96(%rbx), %rcx
	movq	88(%rbx), %rdx
	movsd	%xmm10, %xmm7
	movq	80(%rbx), %rsi
	movq	72(%rbx), %rdi
	movsd	%xmm8, %xmm3
	movq	%r9, -32(%rbp)
	movsd	%xmm9, %xmm0
	movlpd	-32(%rbp), %xmm6
	movq	%r11, -32(%rbp)
	movlpd	-32(%rbp), %xmm5
	movq	%r10, -32(%rbp)
	movlpd	-32(%rbp), %xmm4
	movq	%rax, -32(%rbp)
	movl	$8, %eax
	movlpd	-32(%rbp), %xmm2
	movq	%r8, -32(%rbp)
	movlpd	-32(%rbp), %xmm1
	movq	112(%rbx), %r9
	movq	104(%rbx), %r8
	call	*%r12
	movss	%xmm0, (%r13)
	leaq	-24(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	leave
	ret
.L125:
	movq	16(%rbx), %rax
	movq	%r8, (%rax)
	leaq	-24(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	leave
	ret
.L128:
	cmpl	$7, %r9d
	movq	16(%rbx), %r13
	movq	8(%rbx), %r12
	jle	.L34
	movlpd	184(%rbx), %xmm10
.L36:
	movq	176(%rbx), %r10
.L39:
	movq	168(%rbx), %r11
.L42:
	movq	160(%rbx), %r9
.L45:
	movlpd	152(%rbx), %xmm8
.L48:
	movq	144(%rbx), %rax
.L51:
	movq	136(%rbx), %r8
.L54:
	movlpd	128(%rbx), %xmm9
.L57:
	movq	96(%rbx), %rcx
	movq	88(%rbx), %rdx
	movsd	%xmm10, %xmm7
	movq	80(%rbx), %rsi
	movq	72(%rbx), %rdi
	movsd	%xmm8, %xmm3
	movq	%r10, -32(%rbp)
	movsd	%xmm9, %xmm0
	movlpd	-32(%rbp), %xmm6
	movq	%r11, -32(%rbp)
	movlpd	-32(%rbp), %xmm5
	movq	%r9, -32(%rbp)
	movlpd	-32(%rbp), %xmm4
	movq	%rax, -32(%rbp)
	movl	$8, %eax
	movlpd	-32(%rbp), %xmm2
	movq	%r8, -32(%rbp)
	movlpd	-32(%rbp), %xmm1
	movq	112(%rbx), %r9
	movq	104(%rbx), %r8
	call	*%r12
	movsd	%xmm0, (%r13)
	leaq	-24(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	leave
	ret
.L7:
	jne	.L10
	xorpd	%xmm10, %xmm10
	jmp	.L9
.L129:
	xorpd	%xmm10, %xmm10
	.p2align 4,,7
	jmp	.L60
.L34:
	.p2align 4,,7
	jne	.L37
	xorpd	%xmm10, %xmm10
	.p2align 4,,7
	jmp	.L36
.L122:
	movq	16(%rbx), %rax
	movb	%r8b, (%rax)
	leaq	-24(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	leave
	ret
.L10:
	cmpl	$5, %r9d
	jg	.L130
	jne	.L16
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	jmp	.L15
.L64:
	.p2align 4,,3
	je	.L131
	cmpl	$3, %r9d
	jle	.L70
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r10
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	jmp	.L69
.L37:
	cmpl	$5, %r9d
	jg	.L132
	jne	.L43
	xorl	%r10d, %r10d
	movq	%r10, -32(%rbp)
	movq	%r10, %r11
	movlpd	-32(%rbp), %xmm10
	jmp	.L42
.L130:
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movlpd	-32(%rbp), %xmm10
	jmp	.L12
.L131:
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	jmp	.L66
.L132:
	xorl	%r10d, %r10d
	movq	%r10, -32(%rbp)
	movlpd	-32(%rbp), %xmm10
	jmp	.L39
.L123:
	movq	16(%rbx), %rax
	movw	%r8w, (%rax)
	jmp	.L31
.L124:
	movq	16(%rbx), %rax
	movl	%r8d, (%rax)
	jmp	.L31
.L16:
	cmpl	$3, %r9d
	jle	.L19
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r10
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	jmp	.L18
.L70:
	jne	.L73
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r10
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	movsd	%xmm10, %xmm8
	jmp	.L72
.L43:
	cmpl	$3, %r9d
	jle	.L46
	xorl	%r10d, %r10d
	movq	%r10, -32(%rbp)
	movq	%r10, %r9
	movq	%r10, %r11
	movlpd	-32(%rbp), %xmm10
	jmp	.L45
.L19:
	jne	.L22
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r10
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	movsd	%xmm10, %xmm8
	jmp	.L21
.L73:
	cmpl	$1, %r9d
	jle	.L76
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r10
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	movq	%r9, %rax
	movsd	%xmm10, %xmm8
	jmp	.L75
.L46:
	jne	.L49
	xorl	%r10d, %r10d
	movq	%r10, -32(%rbp)
	movq	%r10, %r9
	movq	%r10, %r11
	movlpd	-32(%rbp), %xmm10
	movsd	%xmm10, %xmm8
	jmp	.L48
.L22:
	cmpl	$1, %r9d
	jle	.L25
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r10
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	movq	%r9, %rax
	movsd	%xmm10, %xmm8
	jmp	.L24
.L49:
	cmpl	$1, %r9d
	jle	.L52
	xorl	%r10d, %r10d
	movq	%r10, -32(%rbp)
	movq	%r10, %r9
	movq	%r10, %r11
	movlpd	-32(%rbp), %xmm10
	movq	%r10, %rax
	movsd	%xmm10, %xmm8
	jmp	.L51
.L76:
	jne	.L133
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r10
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	movq	%r9, %rax
	movq	%r9, %r8
	movsd	%xmm10, %xmm8
	jmp	.L78
.L25:
	jne	.L134
	xorl	%r9d, %r9d
	movq	%r9, -32(%rbp)
	movq	%r9, %r10
	movq	%r9, %r11
	movlpd	-32(%rbp), %xmm10
	movq	%r9, %rax
	movq	%r9, %r8
	movsd	%xmm10, %xmm8
	jmp	.L27
.L112:
	leaq	0(,%rdi,8), %r12
	movq	(%r10), %rsi
	movq	%r8, %rax
	movq	$-1, %rdx
	movl	%r12d, %ecx
	salq	%cl, %rax
	salq	%cl, %rdx
	xorq	%rsi, %rax
	andq	%rax, %rdx
	xorq	%rdx, %rsi
	cmpq	$16, %r11
	movq	%rsi, (%r10)
	ja	.L116
	leaq	0(,%rdi,4), %rax
	leal	-65(,%r11,8), %edx
	movl	$32, %edi
	movq	8(%r10), %rsi
	subl	%eax, %edi
	movl	%edx, %ecx
	movl	$2, %eax
	salq	%cl, %rax
	movl	%edi, %ecx
	sarq	%cl, %r8
	decq	%rax
	sarq	%cl, %r8
	movl	%r12d, %ecx
	salq	%cl, %r9
	orq	%r9, %r8
	xorq	%rsi, %r8
	andq	%r8, %rax
	xorq	%rax, %rsi
	movq	%rsi, 8(%r10)
	jmp	.L31
	.p2align 4,,7
.L133:
	xorpd	%xmm9, %xmm9
	movsd	%xmm9, -32(%rbp)
	movq	-32(%rbp), %r9
	movsd	%xmm9, %xmm10
	movsd	%xmm9, %xmm8
	movq	%r9, %r11
	movq	%r9, %r10
	movq	%r9, %rax
	movq	%r9, %r8
	jmp	.L81
.L52:
	jne	.L135
	xorl	%r10d, %r10d
	movq	%r10, -32(%rbp)
	movq	%r10, %r9
	movq	%r10, %r11
	movlpd	-32(%rbp), %xmm10
	movq	%r10, %rax
	movq	%r10, %r8
	movsd	%xmm10, %xmm8
	jmp	.L54
.L134:
	xorpd	%xmm9, %xmm9
	movsd	%xmm9, -32(%rbp)
	movq	-32(%rbp), %r9
	movsd	%xmm9, %xmm10
	movsd	%xmm9, %xmm8
	movq	%r9, %r11
	movq	%r9, %r10
	movq	%r9, %rax
	movq	%r9, %r8
	jmp	.L30
.L135:
	xorpd	%xmm9, %xmm9
	movsd	%xmm9, -32(%rbp)
	movq	-32(%rbp), %r10
	movsd	%xmm9, %xmm10
	movsd	%xmm9, %xmm8
	movq	%r10, %r11
	movq	%r10, %r9
	movq	%r10, %rax
	movq	%r10, %r8
	jmp	.L57
.L114:
	leaq	0(,%rdi,8), %rsi
	movq	(%r10), %rdx
	movq	%r8, %rbx
	movq	$-1, %rax
	movl	%esi, %ecx
	salq	%cl, %rbx
	salq	%cl, %rax
	movq	%rbx, %rcx
	xorq	%rdx, %rcx
	andq	%rcx, %rax
	leal	-65(,%r11,8), %ecx
	xorq	%rax, %rdx
	movl	$2, %eax
	salq	%cl, %rax
	movq	%rdx, (%r10)
	movl	$64, %ecx
	movq	8(%r10), %rdx
	subl	%esi, %ecx
	decq	%rax
	sarq	%cl, %r8
	xorq	%rdx, %r8
	andq	%r8, %rax
	xorq	%rax, %rdx
	movq	%rdx, 8(%r10)
	jmp	.L31
.L116:
	movl	$64, %esi
	movq	%r9, %rax
	movq	16(%r10), %rdx
	subl	%r12d, %esi
	movl	%esi, %ecx
	sarq	%cl, %r8
	movl	%r12d, %ecx
	salq	%cl, %rax
	leal	-129(,%r11,8), %ecx
	orq	%r8, %rax
	movq	%rax, 8(%r10)
	movl	$2, %eax
	salq	%cl, %rax
	movl	%esi, %ecx
	sarq	%cl, %r9
	decq	%rax
	xorq	%rdx, %r9
	andq	%r9, %rax
	xorq	%rax, %rdx
	movq	%rdx, 16(%r10)
	jmp	.L31
.LFE2:
	.size	avcall_call, .-avcall_call
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
	.byte	0x83
	.uleb128 0x5
	.byte	0x8c
	.uleb128 0x4
	.byte	0x8d
	.uleb128 0x3
	.align 8
.LEFDE1:
	.ident	"GCC: (GNU) 4.0.2"
	.section	.note.GNU-stack,"",@progbits
