command utils for compilation :
nasm -f elf64 main.s -o main.o && nasm -f elf64 ft_strlen.s -o ft_strlen.o
ld main.o ft_strlen.o -o main


Registres pour les arguments (dans l’ordre) :

rdi — 1er argument

rsi — 2e argument

rdx — 3e argument

rcx — 4e argument

r8 — 5e argument

r9 — 6e argument

Si plus de 6 arguments
Les arguments supplémentaires sont passés sur la pile (stack).

Retour de fonction
La valeur retournée est généralement dans rax.
____________________________________________________________________________________________________
XOR

Un XOR (pour "eXclusive OR", ou "OU exclusif" en français) est une opération logique binaire. Elle compare deux bits et donne :

1 si les deux bits sont différents

0 s’ils sont égaux

🔢 Table de vérité de XOR
Bit A	Bit B	A XOR B
0		0		0
0		1		1
1		0		1
1		1		0

_____________________________________________________________________________________

ft_strlen :

	xor rcx, rcx - permet de remettre a 0 le registre qui sert de compteur
	atout du xor :
	- plus rapide que mov rcx, 0 car n'utilise aucune valeur immediate encode
	- modifie les flags, ce qui permet d'utiliser des isntructions conditionnelles aux besoins (je, jne, ...)
	- utilise par les compilateurs

	cmp byte [rdi + rcx], 0 - precise que l'on veut comparer un seul octet avec "byte" a l'adresse [rdi + rcx] avec 0

ft_strcpy :

	mov rax, rdi - sauvegarde notre pointeur de debut de chaine dans le registre de retour avant d'avancer ce pointeur

	mov r8b, [rsi] - Copie l'octet present a [rsi] dans un registe temporaire qui fait la taille d'un char (defini avec le 'b' apres r8)
    mov [rdi], r8b - recupere l'octet precedement copier de rsi vers rdi(notre chaine de destination)
	- Cette operation est effectue en deux temps car l'architecture asm ne permet pas de faire deux acces memoires en une seule instruction

ft_strcmp:

	mov dl, byte [rdi]
    cmp dl, byte [rsi] - on utilise dl (sous partie du registre rdx) pour stocker notre char dans 8 bits et non 64

	mov dl, byte [rdi] - on utilise a nouveau dl et cl pour stocker nos char a soustraire
    mov cl, byte [rsi]
    sub edx, ecx - on soustrait nos deux char (dl et cl) converti en entier 32bits (edx et ecx), le resultat est stocker dans edx (edx = edx - ecx)

	sub edx, ecx
	Fait une soustraction sur 32 bits, donc elle traite les valeurs comme des entiers normaux (int)

	C’est ce que fait strcmp() en C : il retourne un int, donc c’est logique de faire la soustraction avec des registres 32 bits

ft_write :

	neg rax - transforme la valeur d’erreur négative en valeur positive (par convention, les numéros d’erreur sont positifs).

	call __errno_location wrt ..plt - appelles __errno_location pour obtenir l’adresse de la variable errno, cette adresse est retournée dans rax (c’est une convention).
	Puis:
	mov [rax], rsi - Donc : *errno = code_d_erreur

ft_read :

	pareil que ft_write

ft_strdup :
	push rdi - sauvegarde sur la pile la valeur orignal du 1er argument
	call ft_strlen
    mov rdi, rax
    inc rdi
    call malloc wrt ..plt - on recupere la longeur de la chaine source auquel on ajoute 1 pour le \0 puis on appelle malloc avec cette len + 1 en argument
	pop rsi - on recupere la chaine source en second argument pour strcpy
	test rax, rax  - verifie si rax et a zero en mettant les flag a jour
	jz .end - on ce sert du jz (jump if zero) dans le cas ou le flag zero a etait precedemment activer
	mov rdi, rax - on attribue en premier argument de strcpy notre chaine precedemment allouer
	
_____________________________________________________________________________________

Makefile :

ar : utilitaire GNU pour manipuler des fichiers .a (archives).

rcs :
	- r : remplace ou insère un fichier dans l’archive,
	- c : crée l’archive si elle n’existe pas,
	- s : ajoute un index (symbole) pour la rapidité d’accès.

$(CC) → nasm

-f elf64 → format de sortie pour du code 64 bits Linux.

$< → le fichier source (par exemple ft_strlen.s)

-o $@ → fichier cible (.objs/ft_strlen.o)