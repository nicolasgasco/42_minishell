#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct CommonData
{
	char	**envp;
	char	*username;
	char	*hostname;
	char	*prompt_text;
	char	*prompt_newline_text;
	char	**tokens;
	char	*cmd;
	char	**paths;
} c_data;

// TBD WILL BE DELETED
void	ft_print_array(char **str_array);

// Init
void	ft_init_common_data(c_data *c_data, char *envp[]);
char	*ft_create_prompt_text(char *username, char *hostname);

// Prompt
char	*rl_gets(char *line_read, char *prompt_text);

// Quotes
int		ft_are_quotes_even(char *line);
int		ft_isquote(char	c);
void	ft_expand_quotes(char *line, int start);
int 	ft_first_unescaped_quote(char *line);

// Tokenization
char	**ft_tokenize(char *line, c_data *c_data);
void	ft_check_cmd(char *cmd);

// Strings
int		ft_count_char(char quote, char *line, int start);
char	*ft_remove_char(char c, char *line, int start);

#endif