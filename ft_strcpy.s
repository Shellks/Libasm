bits 64

section .text
    global ft_strcpy
    ft_strcpy:
        mov rax, rdi
        .cpy_loop:
            cmp byte [rsi], 0
            je .end
            mov r8b, [rsi]
            mov [rdi], r8b
            inc rdi
            inc rsi
            jmp .cpy_loop
        .end:
            mov byte [rdi], 0
            ret