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
void ft_init_common_data(c_data *c_data, char *envp[]);
char *ft_create_prompt_text(char *username, char *hostname);

// Prompt
char *rl_gets(char *line_read, char *prompt_text);
int	ft_are_quotes_even(char *line);

// Tokenization
char	**ft_tokenize(char *line, c_data *c_data);
void	ft_check_cmd(char *cmd);

#endif