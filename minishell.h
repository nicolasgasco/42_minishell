#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


struct s_node {
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


typedef struct PromptData {
	char			*username;
	char			*hostname;
	char			*prompt_text;
	char			*prompt_nl_text;
} p_data;

typedef struct LineData {
	char			*line_expanded;
	char			**tokens;
	char			*cmd;
} l_data;

typedef struct CommonData
{
	char			**envp;
	int				exit_status;
	p_data			*p_data;
	q_data			*q_data;
	l_data			*l_data;
} c_data;

// Main
void	ft_start_loop(c_data *c_data);
void	ft_tokenize_expand_input(c_data *c_data, char *line_read);

// Init
void	ft_init_common_data(c_data *c_data, char *envp[]);
void	ft_init_quotes_data(c_data *c_data);
void	ft_init_prompt_data(c_data *c_data);
void	ft_init_line_data(c_data *c_data);
void	ft_init_structures(c_data *c_data);

// Free
void    ft_free_quotes_data(c_data *c_data);
void	ft_free_prompt_data(c_data *c_data);
void	ft_free_line_data(c_data *c_data);
void	ft_deallocate_quotes_list(struct s_node **quotes_list);

// Prompt
char	*rl_gets(char *line_read, char *prompt_text);
int		ft_are_quotes_unclosed(char *line);
char	*ft_create_prompt_text(char *username, char *hostname);

// Quotes token
void    ft_tokenize_quotes(q_data *q_data);
void 	ft_tokenization_logic(q_data *q_data, char *line, int i, char quote);
void 	ft_tokenization_logic_closed(q_data *q_data, int i, char quote);
void 	ft_tokenization_logic_open(q_data *q_data, int i, char quote);
// Quotes  - Linked list
void	ft_add_node_quotes(q_data *q_data, int end, char quote);
char	*ft_convert_list_to_str(q_data *q_data);
char    *ft_create_quoted_token(char *s, int start, int len);
char    *ft_create_quoted_token_empty(char *input, int start);
void	ft_deallocate_quotes_list(struct s_node **quotes_list);

// Expansions
void    ft_expansions(c_data *c_data);
// Expansions - escape character TBD
void	ft_expand_escaped(q_data *q_data);
char	*ft_remove_escaped_from_str(char *str);
// Expansions - Variables
void	ft_expand_variables(c_data *c_data);
int		ft_find_dollar(char *str);
char	*ft_add_variable_values(char *str, c_data *c_data);
char	*ft_expand_variable_value(c_data *c_data, char *str, int start, int end);
char	*ft_get_var_name(char *str, int start, int end);
char    *ft_splice_var_value(char *str, char *var, int start, int end);
char    *ft_remove_var_name(char *str, int start, int end);

// String manipulation
char    *ft_strcat(char *src, char *dest);
char    *ft_remove_char_index(char *line, int index);

// Commands
void    ft_extract_cmd(c_data *c_data);
void	ft_check_cmd(char *cmd);

// TBD
void    ft_print_linked_list(q_data *q_data);
void	ft_prune_starting_node(struct s_node **quotes_list);

#endif