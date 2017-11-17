	.file	"vacall-x86_64-windows.c"
	.text
	.p2align 4,,15
	.globl	vacall_receiver
	.type	vacall_receiver, @function
vacall_receiver:
.LFB0:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	subq	$144, %rsp
	movq	%rcx, 16(%rbp)
	leaq	16(%rbp), %rcx
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	%r9, 40(%rbp)
	movss	%xmm0, -52(%rbp)
	movq	%rcx, -88(%rbp)
	movss	%xmm1, -48(%rbp)
	movl	$0, -112(%rbp)
	movss	%xmm2, -44(%rbp)
	movq	$0, -80(%rbp)
	leaq	-112(%rbp), %rcx
	movss	%xmm3, -40(%rbp)
	movl	$0, -72(%rbp)
	movsd	%xmm0, -32(%rbp)
	movl	$0, -56(%rbp)
	movsd	%xmm1, -24(%rbp)
	movsd	%xmm2, -16(%rbp)
	movsd	%xmm3, -8(%rbp)
	call	*vacall_function(%rip)
	movl	-72(%rbp), %edx
	testl	%edx, %edx
	je	.L1
	cmpl	$1, %edx
	je	.L34
	cmpl	$2, %edx
	je	.L34
	cmpl	$3, %edx
	je	.L37
	cmpl	$4, %edx
	je	.L38
	cmpl	$5, %edx
	je	.L39
	cmpl	$6, %edx
	je	.L40
	cmpl	$7, %edx
	je	.L41
	cmpl	$8, %edx
	je	.L35
	cmpl	$9, %edx
	je	.L35
	cmpl	$10, %edx
	je	.L35
	cmpl	$11, %edx
	je	.L35
	cmpl	$12, %edx
	je	.L42
	cmpl	$13, %edx
	je	.L43
	cmpl	$14, %edx
	je	.L35
	cmpl	$15, %edx
	jne	.L1
	testb	$4, -111(%rbp)
	je	.L17
	movq	-64(%rbp), %rdx
	leaq	-4(%rdx), %rcx
	testq	$-5, %rcx
	je	.L20
	leaq	-1(%rdx), %rcx
	cmpq	$1, %rcx
	ja	.L1
.L20:
	movq	-80(%rbp), %r8
	movq	%r8, %r9
	andl	$7, %r8d
	addq	%r8, %rdx
	andq	$-8, %r9
	cmpq	$8, %rdx
	ja	.L19
	leal	-1(,%rdx,8), %ecx
	movl	$2, %edx
	salq	%cl, %rdx
	leal	0(,%r8,8), %ecx
	subq	$1, %rdx
	andq	(%r9), %rdx
	sarq	%cl, %rdx
	movq	%rdx, %rax
.L1:
	leave
.LCFI2:
	ret
	.p2align 4,,10
	.p2align 3
.L34:
.LCFI3:
	movsbq	-104(%rbp), %rax
	leave
.LCFI4:
	ret
	.p2align 4,,10
	.p2align 3
.L35:
.LCFI5:
	movq	-104(%rbp), %rax
	leave
.LCFI6:
	ret
	.p2align 4,,10
	.p2align 3
.L37:
.LCFI7:
	movzbl	-104(%rbp), %eax
	leave
.LCFI8:
	ret
	.p2align 4,,10
	.p2align 3
.L38:
.LCFI9:
	movswq	-104(%rbp), %rax
	leave
.LCFI10:
	ret
	.p2align 4,,10
	.p2align 3
.L39:
.LCFI11:
	movzwl	-104(%rbp), %eax
	leave
.LCFI12:
	ret
	.p2align 4,,10
	.p2align 3
.L40:
.LCFI13:
	movslq	-104(%rbp), %rax
	leave
.LCFI14:
	ret
	.p2align 4,,10
	.p2align 3
.L42:
.LCFI15:
	movss	-104(%rbp), %xmm0
	leave
.LCFI16:
	ret
	.p2align 4,,10
	.p2align 3
.L41:
.LCFI17:
	movl	-104(%rbp), %eax
	leave
.LCFI18:
	ret
.L43:
.LCFI19:
	movsd	-104(%rbp), %xmm0
	leave
.LCFI20:
	ret
.L17:
.LCFI21:
	movq	-80(%rbp), %rax
	leave
.LCFI22:
	ret
.L19:
.LCFI23:
	leal	-65(,%rdx,8), %ecx
	movl	$2, %edx
	salq	%cl, %rdx
	movl	%r8d, %ecx
	subq	$1, %rdx
	andq	8(%r9), %rdx
	negl	%ecx
	leal	64(,%rcx,8), %ecx
	salq	%cl, %rdx
	leal	0(,%r8,8), %ecx
	movq	(%r9), %r8
	leave
.LCFI24:
	sarq	%cl, %r8
	orq	%r8, %rdx
	movq	%rdx, %rax
	ret
.LFE0:
	.size	vacall_receiver, .-vacall_receiver
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
	.align 8
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
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xb
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xb
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xb
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xb
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xb
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI13-.LCFI12
	.byte	0xb
	.byte	0x4
	.long	.LCFI14-.LCFI13
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI15-.LCFI14
	.byte	0xb
	.byte	0x4
	.long	.LCFI16-.LCFI15
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI17-.LCFI16
	.byte	0xb
	.byte	0x4
	.long	.LCFI18-.LCFI17
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI19-.LCFI18
	.byte	0xb
	.byte	0x4
	.long	.LCFI20-.LCFI19
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI21-.LCFI20
	.byte	0xb
	.byte	0x4
	.long	.LCFI22-.LCFI21
	.byte	0xa
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI23-.LCFI22
	.byte	0xb
	.byte	0x4
	.long	.LCFI24-.LCFI23
	.byte	0xc6
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE1:
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
