NAME = minishell

SRCS =	minishell.c \
		cd.c \
		cd1.c \
		echo.c \
		env.c \
		errors.c \
		exec.c \
		exec2.c \
		exec3.c \
		exec4.c \
		exec5.c \
		exec6.c \
		exec7.c \
		exec8.c \
		exit.c \
		expansions_empty_nodes_0.c \
		expansions_empty_nodes_1.c \
		expansions_here_docs.c \
		expansions_quotes_0.c \
		expansions_quotes_1.c \
		expansions_quotes_2.c \
		expansions_spaces.c \
		expansions_spaces_utils.c \
		expansions_special_chars_0.c \
		expansions_special_chars_1.c \
		expansions_special_chars_2.c \
		expansions_special_chars_errors.c \
		expansions_tokens.c \
		expansions_vars_0.c \
		expansions_vars_1.c \
		expansions_vars_2.c \
		export.c \
		free_0.c \
		free_1.c \
		ft_getenv.c\
		init_0.c \
		init_1.c \
		loop_prompt.c \
		pwd.c \
		signals_0.c \
		signals_1.c \
		sniper.c \
		unset.c \
		./libft_custom/libft_custom_0.c \
		./libft_custom/libft_custom_1.c \
		./libft_custom/libft_custom_2.c \
		./libft_custom/libft_custom_3.c \


FLAGS 	= -Wall -Wextra -Werror
OBJS    = $(SRCS:.c=.o)
LIBFT 	=  -C ./libft

all:	
		@ $(MAKE) -s $(NAME)
		@ echo "Compiled... ✅"

$(NAME) : $(OBJS)
			@ echo "\nCompiling Minishell by \033[1;33mToni Del Corral\033[0m and \033[1;33mNicolas Gasco\033[0m... 🐚"
			@ ${MAKE} -s ${LIBFT}
			@ gcc ${FLAGS} $(OBJS) -I. ./libft/libft.a -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include -o $(NAME)

%.o: %.c
	gcc ${FLAGS} -c $< -o $@
	
clean:
		@ echo "Cleaning objects..."
		@ rm -rf *.dSYM
		@ rm -rf $(OBJS)
		@ ${MAKE} clean ${LIBFT}
		@ echo "Cleaned 🧹"

fclean: 
		@ echo "Cleaning objects and program..."
		@ rm -rf *.dSYM
		@ rm -rf $(OBJS)
		@ rm -rf $(NAME)
		@ ${MAKE} fclean ${LIBFT}
		@ echo "Cleaned 🧹"

re:		fclean all

.PHONY: all s clean fclean re
