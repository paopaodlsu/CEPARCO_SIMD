section .text
bits 64
default rel
global square_ymm

square_ymm:
	xor r8, r8

L1:
	cmp r8, rdx
	jge L2

	vmovups ymm0, [rcx + r8*4]
	vmulps ymm0, ymm0, ymm0
	vmovups [rcx + r8*4], ymm0

	add r8, 8
	jmp L1
L2:
	vzeroupper
	ret