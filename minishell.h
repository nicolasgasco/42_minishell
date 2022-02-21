#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

typedef struct CommonData
{
	char	**envp;
	char	**envp_export;
	char	*username;
	char	*hostname;
	char	*prompt_text;
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

// Tokenization
char	**ft_tokenize(char *line, c_data *c_data);
void	ft_check_cmd(c_data *c_data);

//Builtins
void	built_envp(c_data *c_data);
void	built_pwd(void);
void	built_cd(char *arg, c_data *c_data);
int	built_echo(char **arg);
int	built_export(char **arg, c_data *c_data);
char	*ms_make_string(char *arg);
char	*ms_get_env(char **env, char *str);
void	ms_set_env(char **env, char *value, c_data *c_data);
char	**ms_matrix_add_line(char **matrix, char *new_line);
int	built_unset(char **arg, c_data *c_data);

#endif
