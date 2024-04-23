bits 64

section .text
    global ft_strlen
    ft_strlen:
        mov rdi, rax
        xor rcx, rcx
        while1:
            cmp byte [rdi], 0
            je endwhile1
            inc rcx
            inc rdi
            jmp while1

        endwhile1:
            mov rax, rcx
            ret
