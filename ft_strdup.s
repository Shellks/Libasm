bits 64

extern ft_strlen
extern ft_strcpy
extern malloc


section .text
    global ft_strdup
    ft_strdup:
        push rdi
        call ft_strlen
        mov rdi, rax
        inc rdi
        call malloc wrt ..plt
        pop rsi
        test rax, rax
        jz .end
        mov rdi, rax
        call ft_strcpy

    .end:
        ret