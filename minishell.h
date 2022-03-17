#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>


/* Single node of linked list contaning input tokenized as per quotes */
struct t_qnode {
	int				length;
	char			q_type;
	char			*str;
	struct t_qnode	*next;
};

/* Struct containig data related to input tokenized as per quotes */
typedef struct QuotesData {
	int				start;
	int				end;
	int				d_open;
	int				s_open;
	char			*raw_input;
	struct t_qnode	*quotes_list;
} t_qdata;

/* Struct containig prompt related data */
typedef struct PromptData {
	char			*username;
	char			*hostname;
	char			*prompt_text;
	char			*prompt_nl_text;
} t_pdata;

/* Struct for every node representing a word token in the linked list */
struct s_tnode {
	char			*str;
	int				len;
	struct s_tnode	*next;
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
	struct s_tnode	*tokens_list; // Linked linked que pasa Nico a Tono
	char			*line_expanded;	
	t_pdata			*t_pdata;
	t_qdata			*t_qdata;
} t_cdata;


/* Main */
void	ft_start_loop(t_cdata *t_cdata);
void    ft_check_cmd(t_cdata *t_cdata);

/* Init */
void	ft_init_general_data(t_cdata *t_cdata, char *envp[]);
void	ft_init_quotes_data(t_cdata *t_cdata);
void	ft_init_prompt_data(t_cdata *t_cdata);
char	*ft_create_prompt_text(char *username, char *hostname);
void	ft_init_loot_pdata(t_cdata *t_cdata);
void	init_envp(char **envp, t_cdata *t_cdata);
void	init_export(t_cdata *t_cdata);

/* Free */
void	ft_free_general_data(t_cdata *t_cdata);
void    ft_free_quotes_data(t_cdata *t_cdata);
void	ft_free_prompt_data(t_cdata *t_cdata);
void	ft_deallocate_quotes_list(struct t_qnode **quotes_list);
void	ft_deallocate_tokens_list(struct s_tnode **token_list);
void	ft_free_loop_data(t_cdata *t_cdata);
void	ft_free_loop_data_quotes_error(t_cdata *t_cdata);

/* Prompt */
int		ft_get_valid_input(t_cdata *t_cdata, char *prompt_text);
char	*ft_rl_gets(char *line_read, char *prompt_text);

/* Expansions - quotes (tokens) */
int		ft_expanded_quotes_are_valid(t_cdata *t_cdata);
void	ft_expand_quotes(t_cdata *t_cdata);
void    ft_tokenize_quotes(t_qdata *t_qdata);
void 	ft_tokenization_logic(t_qdata *t_qdata, char *line, int i, char quote);
void 	ft_tokenization_logic_unopened(t_qdata *t_qdata, int i, char quote);
void 	ft_tokenization_logic_open(t_qdata *t_qdata, int i, char quote);
char    *ft_strcat(char *src, char *dest);

/* Expansions - quotes (list) */
void	ft_add_node_quotes(t_qdata *t_qdata, int end, char quote);
char	*ft_write_str_to_node(t_qdata *t_qdata, int end);
char    *ft_create_quoted_token(char *s, int start, int len);
char    *ft_create_quoted_token_empty(char *input, int start);
char    *ft_create_unquoted_token(char *input, int start, int len);
void	ft_deallocate_quotes_list(struct t_qnode **quotes_list);
char	*ft_convert_list_to_str(t_qdata *t_qdata);

/* Expansions - Spaces */
void	ft_expand_spaces(t_cdata *t_cdata);
int		ft_has_spaces(char *str);
int		ft_isspace(char c);
int		ft_calc_token_len(char *str);
void    ft_split_and_generate_node(struct t_qnode *curr);
// void    ft_splice_node_with_index(t_cdata *t_cdata, int i);

/* Expansions - Special chars */
int		ft_detect_special_chars(t_cdata *t_cdata);
int 	ft_first_char_special(char *str, t_cdata *t_cdata);
int 	ft_last_char_special(char *str, int i, t_cdata *t_cdata);

/* Expansions - Variables */
void	ft_expand_variables(t_cdata *t_cdata);
int		ft_find_dollar(char *str);
char	*ft_add_variable_values(char *str, t_cdata *t_cdata);
char	*ft_expand_variable_value(t_cdata *t_cdata, char *str, int start, int end);
char	*ft_get_var_name(char *str, int start, int end);
char    *ft_splice_var_value(char *str, char *var, int start, int end);
void    ft_splice_var_value_utility(char *result, char *var, int *x);
char    *ft_remove_var_name(char *str, int start, int end);

/* Expansion - Here document */
int		ft_find_here_marker_list(t_cdata *t_cdata);
int 	ft_find_here_marker_str(char *str);
void    ft_here_doc_loop(t_cdata *t_cdata);

/* Expansions - Special characters */
int		ft_special_chars_are_valid(t_cdata *t_cdata);
int 	ft_detect_special_chars(t_cdata *t_cdata);
int		ft_found_pipe(char *str);
int		ft_found_redirection(char *str);
int		ft_found_special_character(char c);
int		ft_found_inv_char(char c);

/* Tokens list */
int		ft_create_tokens_list(t_cdata *t_cdata);

/* Commands */
char    *ft_extract_cmd(char *line);
int		ft_isspace(char	c);
int		ft_get_cmd_len(char *line);

/* Libft */
char	**ft_splitc(char const *s, char c);

/*Builtins */
int		built_envp(t_cdata *t_cdata);
int		built_pwd(void);
int		built_cd(char *arg, t_cdata *t_cdata);
int		built_echo(char **arg);
int		built_export(char **arg, t_cdata *t_cdata);
char	*ms_make_string(char *arg);
char	*ms_get_env(char **env, char *str);
void	ms_set_env(char **env, char *value, t_cdata *t_cdata);
char	**ms_matrix_add_line(char **matrix, char *new_line);
int		built_unset(char **arg, t_cdata *t_cdata);

/* TBD */
void    ft_print_quotes_list(struct t_qnode *list);
void	ft_prune_starting_node(struct t_qnode **quotes_list);
void	ft_expand_escaped(t_qdata *t_qdata);
char	*ft_remove_escaped_from_str(char *str);
void	ft_create_mock_list(t_cdata *t_cdata, char *str, ...);
void    ft_add_node_mock_list(t_cdata *t_cdata, char *str);
void    ft_print_tokens_list(struct s_tnode *list);
void	ft_init_line_data(t_cdata *t_cdata);
void	ft_free_line_data(t_cdata *t_cdata);
void    ft_output_epic_welcome(t_cdata *t_cdata);
void    ft_print_cmd(t_cdata *t_cdata);
void    ft_print_expanded_output(t_cdata *t_cdata);
void    ft_print_special_char_detected(void);
void    ft_print_syntax_error(void);
void    ft_print_no_special_char_detected(void);
void    ft_print_unclosed_quotes(void);
void    ft_print_here_doc_detected(void);
void    ft_print_unknown_command(void);
char    *ft_remove_char_index(char *line, int index);

#endif