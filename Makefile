NAME = minishell

SRCS = $(wildcard *.c)

LIBC    = ar -rcs
CC      = gcc
FLAGS = -Wall -Wextra -Werror -g
OBJS    = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@ cd libft && make libft.a && make clean
	@ echo "Compiling libft..."
	@ $(LIBC) $(NAME) $(OBJS)
	@ gcc $(FLAGS) $(SRCS) libft/libft.a -lreadline -o $(NAME)
	@ echo "Compiling WAR MACHINE..."


all : $(NAME) 

clean :
	@ rm -rf $(wildcard *.o)
	@ echo "Deleting .o..."

fclean : clean
	@ rm -rf $(NAME)
	@ echo "Deleting program..."

re : fclean all

.PHONY : all clean fclean re bonus
