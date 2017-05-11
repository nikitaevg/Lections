	.text
	.globl _memcpy_
_memcpy_:
LFB1:
	pushq	%rbp
LCFI0:
	movq	%rsp, %rbp
LCFI1:
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	L2
L3:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-16(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -4(%rbp)
L2:
	movl	-4(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	L3
	nop
	popq	%rbp
LCFI2:
	ret
LFE1:
	.comm	_x,2000000000,5
	.comm	_y,2000000000,5
	.globl _DEBUG
	.zerofill __DATA,__pu_bss2,_DEBUG,4,2
	.cstring
lC0:
	.ascii "Need argument\0"
lC1:
	.ascii "%i \0"
lC2:
	.ascii "256\0"
lC3:
	.ascii "128\0"
lC4:
	.ascii "64\0"
lC5:
	.ascii "stupid\0"
lC6:
	.ascii "x[N - 1] == y[N - 1]\0"
lC7:
	.ascii "ex2.c\0"
	.text
	.globl _main
_main:
LFB2:
	pushq	%rbp
LCFI3:
	movq	%rsp, %rbp
LCFI4:
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$1, -20(%rbp)
	jne	L5
	leaq	lC0(%rip), %rdi
	call	_puts
	movl	$0, %eax
	jmp	L6
L5:
	movl	$0, -4(%rbp)
	jmp	L7
L9:
	movq	_x@GOTPCREL(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	-4(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
	movl	_DEBUG(%rip), %eax
	testl	%eax, %eax
	je	L8
	movq	_x@GOTPCREL(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, %esi
	leaq	lC1(%rip), %rdi
	movl	$0, %eax
	call	_printf
L8:
	addl	$1, -4(%rbp)
L7:
	cmpl	$499999999, -4(%rbp)
	jle	L9
	movl	_DEBUG(%rip), %eax
	testl	%eax, %eax
	je	L10
	movl	$10, %edi
	call	_putchar
L10:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$4, %edx
	leaq	lC2(%rip), %rsi
	movq	%rax, %rdi
	call	_strncmp
	testl	%eax, %eax
	je	L11
	movl	$2000000000, %edx
	movq	_y@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	_x@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_memcpy_256
	jmp	L12
L11:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$4, %edx
	leaq	lC3(%rip), %rsi
	movq	%rax, %rdi
	call	_strncmp
	testl	%eax, %eax
	je	L13
	movl	$2000000000, %edx
	movq	_y@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	_x@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_memcpy_128
	jmp	L12
L13:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$4, %edx
	leaq	lC4(%rip), %rsi
	movq	%rax, %rdi
	call	_strncmp
	testl	%eax, %eax
	je	L14
	movl	$2000000000, %edx
	movq	_y@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	_x@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_memcpy_64
	jmp	L12
L14:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$8, %edx
	leaq	lC5(%rip), %rsi
	movq	%rax, %rdi
	call	_strncmp
	testl	%eax, %eax
	je	L12
	movl	$2000000000, %edx
	movq	_y@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	_x@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	_memcpy_
L12:
	movl	_DEBUG(%rip), %eax
	testl	%eax, %eax
	je	L15
	movl	$0, -8(%rbp)
	jmp	L16
L17:
	movq	_y@GOTPCREL(%rip), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, %esi
	leaq	lC1(%rip), %rdi
	movl	$0, %eax
	call	_printf
	addl	$1, -8(%rbp)
L16:
	cmpl	$499999999, -8(%rbp)
	jle	L17
L15:
	movq	_x@GOTPCREL(%rip), %rax
	movl	1999999996(%rax), %edx
	movq	_y@GOTPCREL(%rip), %rax
	movl	1999999996(%rax), %eax
	cmpl	%eax, %edx
	setne	%al
	movzbl	%al, %eax
	testq	%rax, %rax
	je	L18
	leaq	lC6(%rip), %rcx
	movl	$46, %edx
	leaq	lC7(%rip), %rsi
	leaq	___func__.2294(%rip), %rdi
	call	___assert_rtn
L18:
	movl	$0, %eax
L6:
	leave
LCFI5:
	ret
LFE2:
	.const
___func__.2294:
	.ascii "main\0"
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.byte	0x1
	.byte	0x78
	.byte	0x10
	.byte	0x1
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.byte	0x90
	.byte	0x1
	.align 3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB1-.
	.set L$set$2,LFE1-LFB1
	.quad L$set$2
	.byte	0
	.byte	0x4
	.set L$set$3,LCFI0-LFB1
	.long L$set$3
	.byte	0xe
	.byte	0x10
	.byte	0x86
	.byte	0x2
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0xd
	.byte	0x6
	.byte	0x4
	.set L$set$5,LCFI2-LCFI1
	.long L$set$5
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$6,LEFDE3-LASFDE3
	.long L$set$6
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB2-.
	.set L$set$7,LFE2-LFB2
	.quad L$set$7
	.byte	0
	.byte	0x4
	.set L$set$8,LCFI3-LFB2
	.long L$set$8
	.byte	0xe
	.byte	0x10
	.byte	0x86
	.byte	0x2
	.byte	0x4
	.set L$set$9,LCFI4-LCFI3
	.long L$set$9
	.byte	0xd
	.byte	0x6
	.byte	0x4
	.set L$set$10,LCFI5-LCFI4
	.long L$set$10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.align 3
LEFDE3:
	.subsections_via_symbols
