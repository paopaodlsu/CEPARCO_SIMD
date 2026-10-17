section .text
bits 64
default rel
global vector_ymm

vector_ymm:
    push rbp
    mov rbp, rsp
    mov r10d, [rbp+48]
    mov r11d, r10d
    and r11d, -8 ; rounds down to nearest multiple of 8
    xor eax, eax 

L1:
    cmp eax, r11d
    jge L2

    vmovups ymm0, [r8 + rax*4]
    vmovups ymm1, [r9 + rax*4]
    vmulps ymm0, ymm1
    vaddps ymm0, [rdx + rax*4]
    vmovups [rcx + rax*4], ymm0

    add eax, 8
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