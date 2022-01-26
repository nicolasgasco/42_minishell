NAME = minishell

SRCS = $(wildcard *.c)

FLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS)
	@ gcc $(FLAGS) $(SRCS) -lreadline -o $(NAME)
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