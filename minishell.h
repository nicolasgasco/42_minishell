#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct CommonData {
	char	*username;
}	c_data;

// Libft
int		ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

// Init
void	ft_init_common_data(c_data	*c_data);

// Prompt
char	*rl_gets(char *line_read);

#endif