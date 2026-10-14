section .text
bits 64
default rel
global square_asm

square_asm:
	xor r8, r8
L1:
	cmp r8, rdx
	jge L2

	movss xmm0, [rcx + r8*4]
	mulss xmm0, xmm0
	movss [rcx + r8*4], xmm0

	inc r8
	jmp L1
L2:
	ret