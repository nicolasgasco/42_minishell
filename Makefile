NAME = minishell

SRCS = $(wildcard *.c)

LIBC    = ar -rcs
FLAGS 	= -Wall -Wextra -Werror -g
OBJS    = $(SRCS:.c=.o)
LIBFT 	=  -C ./libft

all:	
		@ $(MAKE) -s $(NAME)
		@ echo "Compiled..."

$(NAME) : $(OBJS)
			@ echo "Compiling..."
			@ ${MAKE} -s ${LIBFT}
			@ $(CC) ${FLAGS} $(OBJS) -I. ./libft/libft.a -lreadline -o $(NAME)
			
%.o: %.c
	$(CC) ${CFLAGS} -c $< -o $@
	
clean:
		@ echo "Cleaning objects..."
		@ rm -rf *.dSYM
		@ rm -rf $(OBJS)
		@ ${MAKE} clean ${LIBFT}
		@ echo "Cleaned"

fclean: 
		@ echo "Cleaning objects and program..."
		@ rm -rf *.dSYM
		@ rm -rf $(OBJS)
		@ rm -rf $(NAME)
		@ ${MAKE} fclean ${LIBFT}
		@ echo "Cleaned"

re:		fclean all

.PHONY: all s clean fclean re