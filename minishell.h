#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct CommonData
{
	char *username;
	char *hostname;
	char *prompt_text;
} c_data;

// Init
void ft_init_common_data(c_data *c_data);
char *ft_create_prompt_text(char *username, char *hostname);

// Prompt
char *rl_gets(char *line_read, char *prompt_text);

#endif