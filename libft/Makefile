NAME    = libft.a

SRCS    = ft_bzero.c\
          ft_strlen.c\
		  ft_strcpy.c\
          ft_strlcpy.c\
          ft_strlcat.c\
          ft_strchr.c\
          ft_strnstr.c\
		  ft_strcmp.c\
          ft_strncmp.c\
          ft_isalpha.c\
          ft_isalnum.c\
          ft_calloc.c\
          ft_strdup.c\
          ft_substr.c\
          ft_strjoin.c\
          ft_strtrim.c\
          ft_itoa.c\
          ft_putchar_fd.c\
          ft_putstr_fd.c\

LIBC    = ar -rcs
CC      = gcc
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror
INCS    = libft.h
OBJS    = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@ $(LIBC) $(NAME) $(OBJS)

all: $(NAME)

clean:
	@ $(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re .c .o
