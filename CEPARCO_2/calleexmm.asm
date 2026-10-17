
section .text
bits 64
default rel
global vector_xmm

vector_xmm:
    push rbp
    mov rbp, rsp
    mov r10d, [rbp+48]
    mov r11d, r10d
    and r11d, -4 ; rounds down to nearest multiple of 4
    xor eax, eax

L1:
    cmp eax, r11d
    jge L2

    vmovups xmm0, [r8 + rax*4]
    vmovups xmm1, [r9 + rax*4]
    vmulps xmm0, xmm0, xmm1
    vmovups xmm2, [rdx + rax*4]
    vaddps xmm0, xmm0, xmm2
    vmovups [rcx + rax*4], xmm0

    add eax, 4
    jmp L1

L2:
    cmp eax, r10d
    jge L3

    movss xmm0, [r8 + rax*4]
    mulss xmm0, [r9 + rax*4]
    addss xmm0, [rdx + rax*4]
    movss [rcx + rax*4], xmm0

    inc eax
    jmp L2

L3:
    pop rbp
    ret