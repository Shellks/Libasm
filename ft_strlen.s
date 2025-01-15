bits 64

section .text
    global ft_strlen
    ft_strlen:
        xor rcx, rcx
        .count_loop:
            cmp byte [rdi + rcx], 0
            je .end
            inc rcx
            jmp .count_loop

        .end:
            mov rax, rcx
            ret
