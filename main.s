bits 64

section .data
    message db "Hello World!"

section .bss

section .text
    extern ft_strlen
    global _start
    _start:
        mov rax, message
        call ft_strlen
        mov rsi, rax
        mov rax, 1
        mov rdi, 1
        mov rdx, 3
        syscall
        mov rax, 60
        xor rdi, rdi
        syscall