bits 64

extern __errno_location
STDOUT equ 1

section .text
    global ft_write
    ft_write:
        mov rax, 1
        syscall
        cmp rax, 0
        jl .error
        ret
        
        .error:
            neg rax
            mov rsi, rax
            call __errno_location wrt ..plt
            mov [rax], rsi
            mov rax , -1
            ret