section .text
bits 64
default rel
global square_xmm

square_xmm:
	xor r8, r8

L1:
	cmp r8, rdx
	jge L2

	movups xmm0, [rcx + r8*4]
	mulps xmm0, xmm0
	movups [rcx + r8*4], xmm0

	add r8, 4
	jmp L1

L2:
	ret