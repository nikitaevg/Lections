	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.intel_syntax noprefix
	.globl	_memcpy_128
	.align	4, 0x90
_memcpy_128:   
	push	rbp
	mov	rbp, rsp
loop:
	prefetchnta [rdi]
	movdqa 	xmm1, [rdi]
	movntdq 	[rsi], xmm1
	add rsi, 16
	add rdi, 16
	sub rdx, 16
	jne loop
	pop	rbp
	ret


.globl	_memcpy_64
	.align	4, 0x90
_memcpy_64:                             
	push	rbp
	mov	rbp, rsp
loop1:
	mov 	r8, [rdi]
	movnti 	[rsi], r8
	inc	rdi
	inc rsi
	dec		rdx
	jnz loop1
	pop	rbp
	ret

.globl _memcpy_256
	.align 4, 0x90
_memcpy_256:
	push	rbp
	mov	rbp, rsp
loop2:
	prefetchnta [rdi]
	vmovdqa 	ymm0, [rdi]
	vmovntdq	[rsi], ymm0
	add rsi, 32
	add rdi, 32
	sub		rdx, 32
	jnz loop1
	pop	rbp
	ret

.subsections_via_symbols
