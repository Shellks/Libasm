command utils for compilation :
nasm -f elf64 main.s -o main.o && nasm -f elf64 ft_strlen.s -o ft_strlen.o
ld main.o ft_strlen.o -o main