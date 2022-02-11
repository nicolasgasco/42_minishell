#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


struct s_node {
	int				quoted;
	int				length;
	char			q_type;
	char			*str;
	struct s_node	*next;
};

typedef struct QuotesData {
	int				start;
	int				end;
	int				d_open;
	int				s_open;
	char			*raw_input;
	struct s_node	*quotes_list;
} q_data;
typedef struct CommonData
{
	char			**envp;
	char			*username;
	char			*hostname;
	char			*prompt_text;
	char			*prompt_newline_text;
	char			**tokens;
	char			*cmd;
	char			**paths;
	q_data			*q_data;
} c_data;

// Main
void	ft_start_loop(c_data *c_data);

// Init
void	ft_init_common_data(c_data *c_data, char *envp[]);
void	ft_init_quotes_data(c_data *c_data);
void	ft_init_quotes_list(c_data *c_data);

// Prompt
char	*rl_gets(char *line_read, char *prompt_text);
int		ft_are_quotes_unclosed(char *line);
char	*ft_create_prompt_text(char *username, char *hostname);

// Quotes
void    ft_tokenize_quotes(c_data *c_data);
void 	ft_tokenization_logic(q_data *q_data, char *line, int i, char quote);
void 	ft_tokenization_logic_closed(q_data *q_data, int i, char quote);
void 	ft_tokenization_logic_open(q_data *q_data, int i, char quote);

// Quotes linked list
void	ft_add_node_quotes(q_data *q_data, int end, int quoted, char quote);

// Commands
char **ft_tokenize(c_data *c_data);
void	ft_check_cmd(char *cmd);

#endif