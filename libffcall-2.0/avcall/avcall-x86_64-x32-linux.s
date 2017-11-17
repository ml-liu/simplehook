	.file	"avcall-x86_64.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	avcall_call
	.type	avcall_call, @function
avcall_call:
.LFB0:
	pushq	%rbp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	pushq	%r12
	pushq	%rbx
.LCFI2:
	movq	%rdi, %rbx
	movl	24(%edi), %edi
	movl	20(%ebx), %ecx
	movl	88(%ebx), %r8d
	subl	$2064, %esp
	leal	96(%rbx), %eax
	leal	15(%rsp), %esi
	subl	%edi, %ecx
	subl	%eax, %r8d
	andl	$-16, %esi
	sarl	$3, %ecx
	sarl	$3, %r8d
	xorl	%eax, %eax
	testl	%ecx, %ecx
	jle	.L6
	.p2align 4,,10
	.p2align 3
.L77:
	movq	(%edi,%eax,8), %rdx
	movq	%rdx, (%esi,%eax,8)
	addl	$1, %eax
	cmpl	%eax, %ecx
	jne	.L77
.L6:
	movl	12(%ebx), %eax
	cmpl	$13, %eax
	je	.L95
	cmpl	$14, %eax
	je	.L96
	cmpl	$7, %r8d
	movl	4(%ebx), %r10d
	jle	.L39
	movsd	152(%ebx), %xmm14
.L40:
	movsd	144(%ebx), %xmm13
.L42:
	movsd	136(%ebx), %xmm12
.L44:
	movsd	128(%ebx), %xmm11
.L46:
	movsd	120(%ebx), %xmm10
.L48:
	movsd	112(%ebx), %xmm9
.L50:
	movsd	104(%ebx), %xmm8
.L52:
	movsd	96(%ebx), %xmm15
.L53:
	movq	64(%ebx), %rcx
	movq	56(%ebx), %rdx
	movl	$8, %eax
	movq	48(%ebx), %rsi
	movq	40(%ebx), %rdi
	movapd	%xmm14, %xmm7
	movapd	%xmm13, %xmm6
	movapd	%xmm12, %xmm5
	movq	80(%ebx), %r9
	movapd	%xmm11, %xmm4
	movq	72(%ebx), %r8
	movapd	%xmm10, %xmm3
	movapd	%xmm9, %xmm2
	movapd	%xmm8, %xmm1
	movapd	%xmm15, %xmm0
	call	*%r10
	movl	12(%ebx), %ecx
	cmpl	$1, %ecx
	je	.L22
	testl	%ecx, %ecx
	je	.L92
	cmpl	$2, %ecx
	je	.L86
	cmpl	$3, %ecx
	je	.L86
	cmpl	$4, %ecx
	je	.L86
	cmpl	$5, %ecx
	je	.L87
	cmpl	$6, %ecx
	je	.L87
	cmpl	$7, %ecx
	je	.L91
	cmpl	$8, %ecx
	je	.L91
	cmpl	$9, %ecx
	je	.L91
	cmpl	$10, %ecx
	je	.L91
	cmpl	$11, %ecx
	je	.L92
	cmpl	$12, %ecx
	je	.L92
	cmpl	$15, %ecx
	je	.L91
	cmpl	$16, %ecx
	jne	.L22
	testl	$512, (%ebx)
	je	.L22
	movl	16(%ebx), %ecx
	leal	-1(%rcx), %esi
	cmpl	$15, %esi
	ja	.L22
	movl	8(%ebx), %esi
	movl	%esi, %edi
	andl	$7, %esi
	andl	$-8, %edi
	cmpl	$8, %ecx
	leal	(%rcx,%rsi), %r8d
	ja	.L67
	cmpl	$8, %r8d
	ja	.L68
	leal	-1(,%r8,8), %ecx
	movq	(%edi), %r9
	sall	$3, %esi
	movl	$2, %edx
	movl	$1, %r8d
	salq	%cl, %rdx
	movl	%esi, %ecx
	salq	%cl, %r8
	salq	%cl, %rax
	subq	%r8, %rdx
	xorq	%r9, %rax
	andq	%rdx, %rax
	xorq	%r9, %rax
	movq	%rax, (%edi)
.L22:
	leal	-16(%rbp), %esp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%rbp
.LCFI3:
	ret
	.p2align 4,,10
	.p2align 3
.L39:
.LCFI4:
	je	.L97
	cmpl	$6, %r8d
	je	.L98
	cmpl	$5, %r8d
	je	.L99
	cmpl	$4, %r8d
	je	.L100
	cmpl	$3, %r8d
	je	.L101
	cmpl	$2, %r8d
	je	.L102
	pxor	%xmm8, %xmm8
	cmpl	$1, %r8d
	movapd	%xmm8, %xmm9
	movapd	%xmm8, %xmm10
	movapd	%xmm8, %xmm11
	movapd	%xmm8, %xmm12
	movapd	%xmm8, %xmm13
	movapd	%xmm8, %xmm14
	je	.L52
	movapd	%xmm8, %xmm15
	jmp	.L53
	.p2align 4,,10
	.p2align 3
.L95:
	cmpl	$7, %r8d
	movl	8(%ebx), %r12d
	movl	4(%ebx), %r10d
	jle	.L7
	movsd	152(%ebx), %xmm14
.L8:
	movsd	144(%ebx), %xmm13
.L10:
	movsd	136(%ebx), %xmm12
.L12:
	movsd	128(%ebx), %xmm11
.L14:
	movsd	120(%ebx), %xmm10
.L16:
	movsd	112(%ebx), %xmm9
.L18:
	movsd	104(%ebx), %xmm8
.L20:
	movsd	96(%ebx), %xmm15
	jmp	.L21
	.p2align 4,,10
	.p2align 3
.L96:
	cmpl	$7, %r8d
	movl	8(%ebx), %r12d
	movl	4(%ebx), %r10d
	jle	.L24
	movsd	152(%ebx), %xmm14
.L25:
	movsd	144(%ebx), %xmm13
.L27:
	movsd	136(%ebx), %xmm12
.L29:
	movsd	128(%ebx), %xmm11
.L31:
	movsd	120(%ebx), %xmm10
.L33:
	movsd	112(%ebx), %xmm9
.L35:
	movsd	104(%ebx), %xmm8
.L37:
	movsd	96(%ebx), %xmm15
.L38:
	movq	64(%ebx), %rcx
	movq	56(%ebx), %rdx
	movl	$8, %eax
	movq	48(%ebx), %rsi
	movq	40(%ebx), %rdi
	movq	80(%ebx), %r9
	movq	72(%ebx), %r8
	movapd	%xmm14, %xmm7
	movapd	%xmm13, %xmm6
	movapd	%xmm12, %xmm5
	movapd	%xmm11, %xmm4
	movapd	%xmm10, %xmm3
	movapd	%xmm9, %xmm2
	movapd	%xmm8, %xmm1
	movapd	%xmm15, %xmm0
	call	*%r10
	movsd	%xmm0, (%r12d)
	leal	-16(%rbp), %esp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%rbp
.LCFI5:
	ret
	.p2align 4,,10
	.p2align 3
.L7:
.LCFI6:
	je	.L103
	cmpl	$6, %r8d
	je	.L104
	cmpl	$5, %r8d
	je	.L105
	cmpl	$4, %r8d
	je	.L106
	cmpl	$3, %r8d
	je	.L107
	cmpl	$2, %r8d
	je	.L108
	pxor	%xmm8, %xmm8
	cmpl	$1, %r8d
	movapd	%xmm8, %xmm9
	movapd	%xmm8, %xmm10
	movapd	%xmm8, %xmm11
	movapd	%xmm8, %xmm12
	movapd	%xmm8, %xmm13
	movapd	%xmm8, %xmm14
	movapd	%xmm8, %xmm15
	je	.L20
.L21:
	movq	64(%ebx), %rcx
	movq	56(%ebx), %rdx
	movl	$8, %eax
	movq	48(%ebx), %rsi
	movq	40(%ebx), %rdi
	movq	80(%ebx), %r9
	movq	72(%ebx), %r8
	movapd	%xmm14, %xmm7
	movapd	%xmm13, %xmm6
	movapd	%xmm12, %xmm5
	movapd	%xmm11, %xmm4
	movapd	%xmm10, %xmm3
	movapd	%xmm9, %xmm2
	movapd	%xmm8, %xmm1
	movapd	%xmm15, %xmm0
	call	*%r10
	movss	%xmm0, (%r12d)
	leal	-16(%rbp), %esp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%rbp
.LCFI7:
	ret
	.p2align 4,,10
	.p2align 3
.L102:
.LCFI8:
	pxor	%xmm9, %xmm9
	movapd	%xmm9, %xmm10
	movapd	%xmm9, %xmm11
	movapd	%xmm9, %xmm12
	movapd	%xmm9, %xmm13
	movapd	%xmm9, %xmm14
	jmp	.L50
.L24:
	je	.L109
	cmpl	$6, %r8d
	je	.L110
	cmpl	$5, %r8d
	je	.L111
	cmpl	$4, %r8d
	je	.L112
	cmpl	$3, %r8d
	je	.L113
	cmpl	$2, %r8d
	je	.L114
	pxor	%xmm8, %xmm8
	cmpl	$1, %r8d
	movapd	%xmm8, %xmm9
	movapd	%xmm8, %xmm10
	movapd	%xmm8, %xmm11
	movapd	%xmm8, %xmm12
	movapd	%xmm8, %xmm13
	movapd	%xmm8, %xmm14
	movapd	%xmm8, %xmm15
	jne	.L38
	jmp	.L37
	.p2align 4,,10
	.p2align 3
.L86:
	movl	8(%ebx), %edx
	movb	%al, (%edx)
	leal	-16(%rbp), %esp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%rbp
.LCFI9:
	ret
.L91:
.LCFI10:
	movl	8(%ebx), %edx
	movl	%eax, (%edx)
	jmp	.L22
	.p2align 4,,10
	.p2align 3
.L92:
	movl	8(%ebx), %edx
	movq	%rax, (%edx)
	leal	-16(%rbp), %esp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%rbp
.LCFI11:
	ret
.L108:
.LCFI12:
	pxor	%xmm9, %xmm9
	movapd	%xmm9, %xmm10
	movapd	%xmm9, %xmm11
	movapd	%xmm9, %xmm12
	movapd	%xmm9, %xmm13
	movapd	%xmm9, %xmm14
	jmp	.L18
.L87:
	movl	8(%ebx), %edx
	movw	%ax, (%edx)
	jmp	.L22
.L114:
	pxor	%xmm9, %xmm9
	movapd	%xmm9, %xmm10
	movapd	%xmm9, %xmm11
	movapd	%xmm9, %xmm12
	movapd	%xmm9, %xmm13
	movapd	%xmm9, %xmm14
	jmp	.L35
.L68:
	leal	0(,%rsi,8), %ecx
	movq	$-1, %rdx
	movq	(%edi), %r9
	negl	%esi
	salq	%cl, %rdx
	movq	%rdx, %r10
	movq	%rax, %rdx
	salq	%cl, %rdx
	leal	-65(,%r8,8), %ecx
	xorq	%r9, %rdx
	andq	%r10, %rdx
	xorq	%r9, %rdx
	movq	8(%edi), %r9
	movq	%rdx, (%edi)
	movl	$2, %edx
	salq	%cl, %rdx
	leal	64(,%rsi,8), %ecx
	subq	$1, %rdx
	sarq	%cl, %rax
	xorq	%r9, %rax
	andq	%rdx, %rax
	xorq	%r9, %rax
	movq	%rax, 8(%edi)
	jmp	.L22
.L67:
	leal	0(,%rsi,8), %r10d
	movq	(%edi), %r9
	movq	%rax, %rbx
	movq	$-1, %r11
	movl	%r10d, %ecx
	salq	%cl, %rbx
	salq	%cl, %r11
	movq	%rbx, %rcx
	xorq	%r9, %rcx
	andq	%r11, %rcx
	xorq	%r9, %rcx
	cmpl	$16, %r8d
	movq	%rcx, (%edi)
	jbe	.L115
	negl	%esi
	movq	16(%edi), %r9
	leal	64(,%rsi,8), %r11d
	movq	%rdx, %rsi
	movl	%r11d, %ecx
	sarq	%cl, %rax
	movl	%r10d, %ecx
	salq	%cl, %rsi
	leal	-129(,%r8,8), %ecx
	orq	%rsi, %rax
	movq	%rax, 8(%edi)
	movl	$2, %eax
	salq	%cl, %rax
	movl	%r11d, %ecx
	leaq	-1(%rax), %rsi
	movq	%rdx, %rax
	sarq	%cl, %rax
	xorq	%r9, %rax
	andq	%rsi, %rax
	xorq	%r9, %rax
	movq	%rax, 16(%edi)
	jmp	.L22
.L101:
	pxor	%xmm10, %xmm10
	movapd	%xmm10, %xmm11
	movapd	%xmm10, %xmm12
	movapd	%xmm10, %xmm13
	movapd	%xmm10, %xmm14
	jmp	.L48
.L115:
	negl	%esi
	leal	-65(,%r8,8), %ecx
	movq	8(%edi), %r9
	leal	32(,%rsi,4), %r11d
	movl	$2, %esi
	salq	%cl, %rsi
	movl	%r11d, %ecx
	subq	$1, %rsi
	sarq	%cl, %rax
	sarq	%cl, %rax
	movl	%r10d, %ecx
	salq	%cl, %rdx
	orq	%rdx, %rax
	xorq	%r9, %rax
	andq	%rsi, %rax
	xorq	%r9, %rax
	movq	%rax, 8(%edi)
	jmp	.L22
.L113:
	pxor	%xmm10, %xmm10
	movapd	%xmm10, %xmm11
	movapd	%xmm10, %xmm12
	movapd	%xmm10, %xmm13
	movapd	%xmm10, %xmm14
	jmp	.L33
.L112:
	pxor	%xmm11, %xmm11
	movapd	%xmm11, %xmm12
	movapd	%xmm11, %xmm13
	movapd	%xmm11, %xmm14
	jmp	.L31
.L97:
	pxor	%xmm14, %xmm14
	jmp	.L40
.L98:
	pxor	%xmm13, %xmm13
	movapd	%xmm13, %xmm14
	jmp	.L42
.L99:
	pxor	%xmm12, %xmm12
	movapd	%xmm12, %xmm13
	movapd	%xmm12, %xmm14
	jmp	.L44
.L100:
	pxor	%xmm11, %xmm11
	movapd	%xmm11, %xmm12
	movapd	%xmm11, %xmm13
	movapd	%xmm11, %xmm14
	jmp	.L46
.L111:
	pxor	%xmm12, %xmm12
	movapd	%xmm12, %xmm13
	movapd	%xmm12, %xmm14
	jmp	.L29
.L110:
	pxor	%xmm13, %xmm13
	movapd	%xmm13, %xmm14
	jmp	.L27
.L109:
	pxor	%xmm14, %xmm14
	jmp	.L25
.L107:
	pxor	%xmm10, %xmm10
	movapd	%xmm10, %xmm11
	movapd	%xmm10, %xmm12
	movapd	%xmm10, %xmm13
	movapd	%xmm10, %xmm14
	jmp	.L16
.L106:
	pxor	%xmm11, %xmm11
	movapd	%xmm11, %xmm12
	movapd	%xmm11, %xmm13
	movapd	%xmm11, %xmm14
	jmp	.L14
.L105:
	pxor	%xmm12, %xmm12
	movapd	%xmm12, %xmm13
	movapd	%xmm12, %xmm14
	jmp	.L12
.L104:
	pxor	%xmm13, %xmm13
	movapd	%xmm13, %xmm14
	jmp	.L10
.L103:
	pxor	%xmm14, %xmm14
	jmp	.L8
.LFE0:
	.size	avcall_call, .-avcall_call
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
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
	.align 4
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
	.byte	0x8c
	.uleb128 0x3
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xa
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xb
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xa
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xb
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xa
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0xb
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xa
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xb
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xa
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xb
	.align 4
.LEFDE1:
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
