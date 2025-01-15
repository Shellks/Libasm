NAME = libasm.a

CC = nasm
AR = ar rcs
OBJS_DIR = .objs/

SRCS =	ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.s=.o))

# Rule for compiling .s to .o files
$(OBJS_DIR)%.o: %.s | $(OBJS_DIR)
	$(CC) -f elf64 $< -o $@

all: $(NAME)

# Rule for creating the static library
$(NAME): $(OBJS)
	echo "\033[1;34m-> Creating.."
	$(AR) $(NAME) $(OBJS)
	echo "\033[1;32m-> Success !\033[1;33m libasm created"

run: all
	gcc main.c libasm.a -o main && ./main

clean:
	echo "\033[1;31m-> Cleaning All objects.."
	rm -rf $(OBJS_DIR)

fclean: clean
	echo "\033[1;31m-> Cleaning Executable.."
	rm -f $(NAME)
	rm -f main

re: fclean all

# Create object directory if necessary
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

.SILENT:

.PHONY: all clean fclean re