section .text
bits 64
default rel
global vector_asm

vector_asm:
	push rbp
	mov rbp, rsp
	add rbp, 16
	mov r10d, [rbp+48]
	xor rax, rax

L1:
	cmp eax, r10d
	jge L2

	movss xmm0, [r8 + rax*4]    
    mulss xmm0, [r9 + rax*4]    
    addss xmm0, [rdx + rax*4]   
    movss [rcx + rax*4], xmm0

	inc eax
	jmp L1
L2:
	pop rbp
	ret