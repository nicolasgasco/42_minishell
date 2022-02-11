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
	int				q_open;
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


// TBD WILL BE DELETED
void	ft_print_array(char **str_array);

// Init
void	ft_init_common_data(c_data *c_data, char *envp[]);
void	ft_init_quotes_data(c_data *c_data);
char	*ft_create_prompt_text(char *username, char *hostname);

// Prompt
char	*rl_gets(char *line_read, char *prompt_text);
int		ft_are_quotes_unclosed(char *line);

// Quotes
void    ft_tokenize_quotes(c_data *c_data);
void	ft_add_node_quotes(q_data *q_data, int end, int quoted, char quote);
void	ft_tokenize_quotes_util_0(q_data *q_data, int *i, char quote);
void	ft_tokenize_quotes_util_1(q_data *q_data, int *i, char quote);

char	*ft_expand_line(char *line);
char    *ft_expand_line(char *line);
char    *ft_expand_simple_quotes(char *line);
char	*ft_expand_escaped_quotes(char *line, int length);
int		ft_str_len_unescaped(char *line, char c);
// Quotes utils
int		ft_isquote(char	c);
// int		ft_isspace(char	c);
int		ft_first_valid_quote(char *line);
int		ft_toggle_word_started(int word_started);
void    ft_expanded_escaped_quotes_init(int *i, int *y, int *w);

// Tokenization
char	**ft_tokenize(char *line, c_data *c_data);
void	ft_check_cmd(char *cmd);

// Strings
int		ft_count_char(char quote, char *line, int start);
char	*ft_remove_char(char c, char *line, int start);
char	*ft_remove_char_index(int index, char *line);

#endif