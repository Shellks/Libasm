bits 64

section .text
    global ft_strcmp
    ft_strcmp:
        xor rdx, rdx
        xor rcx, rcx

        .cmp_loop:
            cmp byte [rdi], 0
            je .end
            cmp byte [rsi], 0
            je .end
            mov dl, byte [rdi]
            cmp dl, byte [rsi]
            jne .end
            inc rdi
            inc rsi
            jmp .cmp_loop

        .end:
            mov dl, byte [rdi]
            mov cl, byte [rsi]
            sub edx, ecx
            mov eax, edx
            ret