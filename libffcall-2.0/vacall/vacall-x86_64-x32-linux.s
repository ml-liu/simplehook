	.file	"vacall-x86_64.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	vacall_receiver
	.type	vacall_receiver, @function
vacall_receiver:
.LFB0:
	pushq	%rbp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	pushq	%r14
	subl	$184, %esp
.LCFI2:
	movq	%rsi, -64(%ebp)
	leal	16(%rbp), %esi
	movq	%rcx, -48(%ebp)
	movl	vacall_function(%rip), %ecx
	movsd	%xmm0, -144(%ebp)
	movq	%rdi, -72(%ebp)
	movq	%rdx, -56(%ebp)
	movsd	%xmm1, -136(%ebp)
	movq	%r8, -40(%ebp)
	movsd	%xmm2, -128(%ebp)
	leal	-192(%rbp), %edi
	movq	%r9, -32(%ebp)
	movsd	%xmm3, -120(%ebp)
	movsd	%xmm4, -112(%ebp)
	movl	$0, -192(%ebp)
	movsd	%xmm5, -104(%ebp)
	movl	%esi, -168(%ebp)
	movsd	%xmm6, -96(%ebp)
	movl	$0, -164(%ebp)
	movsd	%xmm7, -88(%ebp)
	movl	$0, -160(%ebp)
	movl	$0, -80(%ebp)
	movl	$0, -152(%ebp)
	call	*%rcx
	movl	-160(%ebp), %ecx
	testl	%ecx, %ecx
	je	.L1
	cmpl	$1, %ecx
	je	.L27
	cmpl	$2, %ecx
	je	.L27
	cmpl	$3, %ecx
	je	.L33
	cmpl	$4, %ecx
	je	.L34
	cmpl	$5, %ecx
	je	.L35
	cmpl	$6, %ecx
	je	.L30
	cmpl	$7, %ecx
	je	.L29
	cmpl	$8, %ecx
	je	.L30
	cmpl	$9, %ecx
	je	.L29
	cmpl	$10, %ecx
	je	.L31
	cmpl	$11, %ecx
	je	.L31
	cmpl	$12, %ecx
	je	.L36
	cmpl	$13, %ecx
	je	.L37
	cmpl	$14, %ecx
	je	.L30
	cmpl	$15, %ecx
	jne	.L1
	testb	$4, -191(%ebp)
	je	.L1
	movl	-156(%ebp), %ecx
	leal	-1(%rcx), %esi
	cmpl	$15, %esi
	ja	.L1
	movl	-164(%ebp), %esi
	movl	%esi, %edi
	andl	$7, %esi
	andl	$-8, %edi
	cmpl	$8, %ecx
	leal	(%rcx,%rsi), %r10d
	ja	.L17
	cmpl	$8, %r10d
	ja	.L18
	leal	-1(,%r10,8), %ecx
	movl	$2, %r8d
	salq	%cl, %r8
	movq	%r8, %rcx
	subq	$1, %rcx
	andq	(%edi), %rcx
	movq	%rcx, %rdi
	leal	0(,%rsi,8), %ecx
	sarq	%cl, %rdi
	movq	%rdi, %rax
.L1:
	addl	$184, %esp
	popq	%r14
	popq	%rbp
.LCFI3:
	ret
	.p2align 4,,10
	.p2align 3
.L27:
.LCFI4:
	movsbq	-184(%ebp), %rax
	addl	$184, %esp
	popq	%r14
	popq	%rbp
.LCFI5:
	ret
	.p2align 4,,10
	.p2align 3
.L30:
.LCFI6:
	movslq	-184(%ebp), %rax
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L33:
	movzbl	-184(%ebp), %eax
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L34:
	movswq	-184(%ebp), %rax
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L29:
	movl	-184(%ebp), %eax
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L35:
	movzwl	-184(%ebp), %eax
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L36:
	movss	-184(%ebp), %xmm0
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L31:
	movq	-184(%ebp), %rax
	jmp	.L1
.L37:
	movsd	-184(%ebp), %xmm0
	jmp	.L1
.L17:
	cmpl	$16, %r10d
	leal	0(,%rsi,8), %r9d
	jbe	.L38
	negl	%esi
	movq	8(%edi), %r8
	movl	%r9d, %ecx
	leal	64(,%rsi,8), %r11d
	movq	(%edi), %rsi
	movq	%r8, %r14
	sarq	%cl, %rsi
	movl	%r11d, %ecx
	salq	%cl, %r14
	leal	-129(,%r10,8), %ecx
	orq	%r14, %rsi
	movq	%rsi, %rax
	movl	$2, %esi
	salq	%cl, %rsi
	movl	%r11d, %ecx
	subq	$1, %rsi
	andq	16(%edi), %rsi
	salq	%cl, %rsi
	movl	%r9d, %ecx
	sarq	%cl, %r8
	orq	%r8, %rsi
	movq	%rsi, %rdx
	jmp	.L1
.L18:
	leal	-65(,%r10,8), %ecx
	movl	$2, %r8d
	salq	%cl, %r8
	movl	%esi, %ecx
	subq	$1, %r8
	andq	8(%edi), %r8
	negl	%ecx
	leal	64(,%rcx,8), %ecx
	movq	(%edi), %rdi
	salq	%cl, %r8
	leal	0(,%rsi,8), %ecx
	sarq	%cl, %rdi
	orq	%rdi, %r8
	movq	%r8, %rax
	jmp	.L1
.L38:
	leal	-65(,%r10,8), %ecx
	movl	$2, %r8d
	movq	(%edi), %r10
	imull	$-4, %esi, %esi
	salq	%cl, %r8
	movl	%r9d, %ecx
	subq	$1, %r8
	andq	8(%edi), %r8
	sarq	%cl, %r10
	addl	$32, %esi
	movl	%esi, %ecx
	movq	%r8, %rdi
	salq	%cl, %rdi
	salq	%cl, %rdi
	movl	%r9d, %ecx
	orq	%rdi, %r10
	sarq	%cl, %r8
	movq	%r10, %rax
	movq	%r8, %rdx
	jmp	.L1
.LFE0:
	.size	vacall_receiver, .-vacall_receiver
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
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
	.byte	0x3
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
	.long	.LFB0
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
	.byte	0x8e
	.uleb128 0x3
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
	.align 4
.LEFDE1:
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
