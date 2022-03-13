#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>


/* Single node of linked list contaning input tokenized as per quotes */
struct q_node {
	int				length;
	char			q_type;
	char			*str;
	struct q_node	*next;
};

/* Struct containig data related to input tokenized as per quotes */
typedef struct QuotesData {
	int				start;
	int				end;
	int				d_open;
	int				s_open;
	char			*raw_input;
	struct q_node	*quotes_list;
} q_data;

/* Struct containig prompt related data */
typedef struct PromptData {
	char			*username;
	char			*hostname;
	char			*prompt_text;
	char			*prompt_nl_text;
} p_data;

/* Struct for every node representing a word token in the linked list */
struct t_node {
	char			*str;
	struct t_node	*next;
};

/* Highest level struct with data shared by whole program */
typedef struct CommonData
{
	char			**envp;
	char			**envp_export;
	int				exit_status;
	char			*cmd;
	char			**tokens;
	int				syntax_error;
	char			**paths;
	struct t_node	*tokens_list;
	char			*line_expanded;	
	p_data			*p_data;
	q_data			*q_data;
} c_data;


/* Main */
void	ft_start_loop(c_data *c_data);
void    ft_check_cmd(c_data *c_data);

/* Init */
void	ft_init_general_data(c_data *c_data, char *envp[]);
void	ft_init_quotes_data(c_data *c_data);
void	ft_init_prompt_data(c_data *c_data);
char	*ft_create_prompt_text(char *username, char *hostname);
void	ft_init_loop_data(c_data *c_data);
void	init_envp(char **envp, c_data *c_data);
void	init_export(c_data *c_data);

/* Free */
void	ft_free_general_data(c_data *c_data);
void    ft_free_quotes_data(c_data *c_data);
void	ft_free_prompt_data(c_data *c_data);
void	ft_deallocate_quotes_list(struct q_node **quotes_list);
void	ft_deallocate_tokens_list(struct t_node **token_list);
void	ft_free_loop_data(c_data *c_data);
void	ft_free_loop_data_quotes_error(c_data *c_data);

/* Prompt */
int		ft_get_valid_input(c_data *c_data, char *prompt_text);
char	*ft_rl_gets(char *line_read, char *prompt_text);

/* Quotes token */
int		ft_expanded_quotes_are_valid(c_data *c_data);
void	ft_expand_quotes(c_data *c_data);
void    ft_tokenize_quotes(q_data *q_data);
void 	ft_tokenization_logic(q_data *q_data, char *line, int i, char quote);
void 	ft_tokenization_logic_unopened(q_data *q_data, int i, char quote);
void 	ft_tokenization_logic_open(q_data *q_data, int i, char quote);
char    *ft_strcat(char *src, char *dest);

/* Quotes  - Linked list */
void	ft_add_node_quotes(q_data *q_data, int end, char quote);
char	*ft_write_str_to_node(q_data *q_data, int end);
char    *ft_create_quoted_token(char *s, int start, int len);
char    *ft_create_quoted_token_empty(char *input, int start);
char    *ft_create_unquoted_token(char *input, int start, int len);
void	ft_deallocate_quotes_list(struct q_node **quotes_list);
char	*ft_convert_list_to_str(q_data *q_data);

/* Expansions - Special chars */
int		ft_detect_special_chars(c_data *c_data);
int 	ft_first_char_special(char *str, c_data *c_data);
int 	ft_last_char_special(char *str, int i, c_data *c_data);

/* Expansions - Variables */
void	ft_expand_variables(c_data *c_data);
int		ft_find_dollar(char *str);
char	*ft_add_variable_values(char *str, c_data *c_data);
char	*ft_expand_variable_value(c_data *c_data, char *str, int start, int end);
char	*ft_get_var_name(char *str, int start, int end);
char    *ft_splice_var_value(char *str, char *var, int start, int end);
void    ft_splice_var_value_utility(char *result, char *var, int *x);
char    *ft_remove_var_name(char *str, int start, int end);

/* Expansion - Here document */
int		ft_find_here_marker_list(c_data *c_data);
int 	ft_find_here_marker_str(char *str);
void    ft_here_doc_loop(c_data *c_data);

/* Expansions - Special characters */
int		ft_special_chars_are_valid(c_data *c_data);
int 	ft_detect_special_chars(c_data *c_data);
int		ft_found_pipe(char *str);
int		ft_found_redirection(char *str);
int		ft_found_special_character(char c);
int		ft_found_invalid_character(char c);

/* String manipulation */

/* Commands */
char    *ft_extract_cmd(char *line);
int		ft_isspace(char	c);
int		ft_get_cmd_len(char *line);

/* Libft */
char	**ft_splitc(char const *s, char c);

/*Builtins */
int		built_envp(c_data *c_data);
int		built_pwd(void);
int		built_cd(char *arg, c_data *c_data);
int		built_echo(char **arg);
int		built_export(char **arg, c_data *c_data);
char	*ms_make_string(char *arg);
char	*ms_get_env(char **env, char *str);
void	ms_set_env(char **env, char *value, c_data *c_data);
char	**ms_matrix_add_line(char **matrix, char *new_line);
int		built_unset(char **arg, c_data *c_data);

/* TBD */
void    ft_print_quotes_list(struct q_node *list);
void	ft_prune_starting_node(struct q_node **quotes_list);
void	ft_expand_escaped(q_data *q_data);
char	*ft_remove_escaped_from_str(char *str);
void	ft_create_mock_list(c_data *c_data, char *str, ...);
void    ft_add_node_mock_list(c_data *c_data, char *str);
void    ft_print_tokens_list(struct t_node *list);
void	ft_init_line_data(c_data *c_data);
void	ft_free_line_data(c_data *c_data);
void    ft_output_epic_welcome(c_data *c_data);
void    ft_print_cmd(c_data *c_data);
void    ft_print_expanded_output(c_data *c_data);
void    ft_print_special_char_detected(void);
void    ft_print_syntax_error(void);
void    ft_print_no_special_char_detected(void);
void    ft_print_unclosed_quotes(void);
void    ft_print_here_doc_detected(void);
void    ft_print_unknown_command(void);
char    *ft_remove_char_index(char *line, int index);

#endif