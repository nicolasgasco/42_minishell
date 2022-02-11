NAME = minishell

SRCS = $(wildcard *.c)

FLAGS = -Wall -Wextra -Werror

$(NAME): 
	@ cd libft && make libft.a && make clean
	@ echo "Compiling libft..."
	@ gcc $(FLAGS) $(SRCS) libft/libft.a -lreadline -o $(NAME)
	@ echo "Compiling Minishell..."

all : $(NAME) 

clean :
	@ rm -rf $(wildcard *.o)
	@ echo "Deleting .o..."

fclean : clean
	@ rm -rf $(NAME)
	@ echo "Deleting program..."

re : fclean all

.PHONY : all clean fclean re bonus