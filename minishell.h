/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:14:58 by ngasco            #+#    #+#             */
/*   Updated: 2022/04/11 13:29:53 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int		g_ex_status;

typedef struct s_job
{
	struct s_job	*previous;
	char			**cmd;
	char			**file;
	int				fd[2];
	pid_t			pid;
	struct s_job	*next;
}	t_job;

typedef enum e_type
{
	VOID,
	PIPE,
	STRING,
	REDIR_L,
	REDIR_R,
	APPEND,
	HEREDOC_L,
}	t_type;

/* Single node of linked list contaning input tokenized as per quotes */
struct s_qnode {
	int				length;
	char			q_type;
	int				is_spaced;
	char			*str;
	struct s_qnode	*next;
};

/* Struct containig data related to input tokenized as per quotes */
typedef struct QuotesData {
	int				start;
	int				end;
	int				d_open;
	int				s_open;
	char			*raw_input;
	char			*delim;
	char			*after_delim;
	struct s_qnode	*quotes_list;
}	t_qdata;

/* Struct containig prompt related data */
typedef struct PromptData {
	char			*username;
	char			*hostname;
	char			*prompt_text;
	char			*prompt_nl_text;
}	t_pdata;

/* Struct for every node representing a word token in the linked list */
struct s_tnode {
	char			*str;
	int				len;
	char			q_type;
	t_type			type;
	int				is_spaced;
	struct s_tnode	*next;
	struct s_tnode	*prev;
};

/* Highest level struct with data shared by whole program */
typedef struct CommonData
{
	char			**envp;
	char			**envp_export;
	int				exit_status;
	char			*cmd;
	int				syntax_error;
	char			**paths;
	int				found_here_doc;
	struct s_tnode	*tokens_list;
	t_pdata			*t_pdata;
	t_qdata			*t_qdata;
}	t_cdata;

/* Necessary to fix 'implicit declaration' error on MacOs */
void			rl_replace_line(const char *text, int clear_undo);

/* Main */
void			ft_start_loop(t_cdata *t_cdata);
void			ft_check_cmd(t_cdata *t_cdata);

/* Init */
void			ft_init_general_data(t_cdata *t_cdata, char *envp[]);
void			ft_init_quotes_data(t_cdata *t_cdata);
void			ft_init_prompt_data(t_cdata *t_cdata);
char			*ft_create_prompt_text(char *username, char *hostname);
void			ft_init_reset_loop_data(t_cdata *t_cdata);
void			init_envp(char **envp, t_cdata *t_cdata);
void			init_export(t_cdata *t_cdata);

/* Free */
void			ft_free_general_data(t_cdata *t_cdata);
void			ft_free_quotes_data(t_cdata *t_cdata);
void			ft_free_prompt_data(t_cdata *t_cdata);
void			ft_deallocate_quotes_list(struct s_qnode **quotes_list);
void			ft_deallocate_tokens_list(struct s_tnode **token_list);
void			ft_free_loop_data(t_cdata *t_cdata);
void			ft_free_loop_data_quotes_error(t_cdata *t_cdata);
void			ft_free_export(t_cdata *t_cdata);
void			ft_free_envp(t_cdata *t_cdata);

/* Prompt */
int				ft_get_valid_input(t_cdata *t_cdata, char *prompt_text);
char			*ft_rl_gets(char *line_read, char *prompt_text);

/* Expansions - quotes (tokens) */
int				ft_expanded_quotes_are_valid(t_cdata *t_cdata);
void			ft_expand_quotes(t_cdata *t_cdata);
void			ft_tokenize_quotes(t_qdata *t_qdata);
void			ft_tokenization_logic(t_qdata *t_qdata, int i, char quote);
void			ft_tokenization_logic_unopened(t_qdata *t_qdata, int i,
					char quote);
void			ft_tokenization_logic_opened(t_qdata *t_qdata, int i,
					char quote);
char			*ft_strcat(char *src, char *dest);

/* Expansions - quotes (list) */
void			ft_add_node_quotes(t_qdata *t_qdata, int end, char quote);
char			*ft_write_str_to_node(t_qdata *t_qdata, int end);
char			*ft_create_quoted_token(char *s, int start, int len);
char			*ft_create_quoted_token_empty(char *input, int start);
char			*ft_create_unquoted_token(char *input, int start, int len);
void			ft_deallocate_quotes_list(struct s_qnode **quotes_list);
char			*ft_convert_list_to_str(t_qdata *t_qdata);
void			ft_popoulate_new_node_quotes(struct s_qnode *new_node,
					t_qdata *t_qdata, int end, char quote);

/* Expansions - Spaces */
void			ft_expand_spaces(t_cdata *t_cdata);
int				ft_remove_empty_nodes(t_cdata *t_cdata);
int				ft_found_empty_node_to_remove(t_cdata *t_cdata);
int				ft_found_empty_node_to_remove_lonely_node(t_cdata *t_cdata,
					struct s_qnode *curr);
int				ft_remove_node_with_index(int index, struct s_qnode **root);
void			ft_split_and_generate_spaced_node(struct s_qnode *curr);
char			*ft_create_rest_str(char *curr_str, int t_len);
int				ft_has_spaces(char *str);
int				ft_isspace(char c);
int				ft_calc_spaces_token_len(char *str);
int				ft_found_space_to_split(t_cdata *t_cdata);
int				ft_isspace(char c);
void			ft_remove_node_with_index_free_util(struct s_qnode *to_remove);

/* Expansions - Variables */
void			ft_expand_variables(t_cdata *t_cdata);
int				ft_found_variable_to_expand(t_cdata *t_cdata);
int				ft_find_dollar(char *str);
char			*ft_add_variable_value(char *str, t_cdata *t_cdata);
char			*ft_expand_var_value(t_cdata *t_cdata, char *str,
					int start, int end);
char			*ft_get_var_name(char *str, int start, int end);
char			*ft_splice_var_value(char *str, char *var, int start, int end);
void			ft_splice_var_value_utility(char *result, char *var, int *x);
char			*ft_remove_var_name(char *str, int start, int end);
int				ft_find_quoted_vars(t_cdata *t_cdata);
void			ft_join_var_name_value(struct s_tnode *curr);

/* Expansion - Here document */
int				ft_here_doc_expansion(t_cdata *t_cdata);
int				ft_find_here_marker_str(char *str);
int				ft_found_lonely_here_marker(char *str);

/* Expansions - Special characters */
void			ft_expand_special_chars(t_cdata *t_cdata);
int				ft_special_chars_are_valid(t_cdata *t_cdata);
int				ft_expand_special_char(t_cdata *t_cdata, char *set);
int				ft_found_special_chars_set(t_cdata *t_cdata, char *set);
int				ft_has_special_char(char *str, char *set);
int				ft_find_special_char_set(char *str, char *set);
int				ft_find_special_char_single(char *str, char c);
void			ft_split_s_char_node(struct s_qnode *curr, int len,
					char *set, int i);
void			ft_add_special_char_nodes(struct s_qnode *curr, char *curr_str,
					char *next_str, char *rest);
void    		ft_populate_new_node_2(struct s_qnode *new_node1, struct s_qnode *curr,
					char *rest);
int				ft_found_adjacent_special_chars(t_cdata *t_cdata);
int				ft_is_special_str(char *str);
int				ft_found_adjecent_pipes(char *str);
int				ft_last_node_is_special_char(t_cdata *t_cdata);
void			ft_join_spaceless_nodes(t_cdata *t_cdata);
int				ft_found_spaceless_nodes(t_cdata *t_cdata);
void			ft_join_nodes(struct s_qnode *curr);
int				ft_found_one_special_char(char *str);
int				ft_first_node_is_pipe(t_cdata *t_cdata);

/* Tokens list */
void			ft_create_tokens_list(t_cdata *t_cdata);
void			ft_add_token_to_list(t_cdata *t_cdata, struct s_qnode *origin);

/* Errors */
int				ft_output_loop_err(t_cdata *t_cdata);

/* Signals */
void			ft_shortcut_events(void);
void			ft_handle_signals(int sig);
void			ft_shortcut_events_interactive(void);
void			ft_handle_signals_interactive(int sig);
void			ft_handle_signals_here_docs(int sig);
void			ft_shortcut_events_here_docs(void);
void			ft_ignore_signal(struct sigaction sa, int sig);
void			ft_ignore_all_signals(void);

/* Execution */
void			ft_start_execution(t_cdata *t_cdata);
int				ft_isspace(char c);

/* Libft */
char			**ft_splitc(char const *s, char c);
void			ft_free_tab(char **tab);
char			*ft_strjoin_free_s1(char *s1, char const *s2);
void			ft_sort_tab(char **arr);
char			**ft_splitc(char const *s, char c);
long long		ft_atoll(const char *nptr);
int				ft_isllong(char *str);
int				ft_isalldigit(char *str);	

/*Builtins */
int				built_envp(t_cdata *t_cdata);
int				built_pwd(void);
int				built_cd(char *arg, t_cdata *t_cdata);
int				built_echo(char **arg);
int				built_export(char **arg, t_cdata *t_cdata);
char			*ms_make_string(char *arg);
char			*ms_get_env(char **env, char *str);
void			ms_set_env(char **env, char *value, t_cdata *t_cdata);
char			**ms_matrix_add_line(char **matrix, char *new_line);
int				built_unset(char **arg, t_cdata *t_cdata);
int				env_compare(char **env, char **arg, int i);

/* Execution */
void			test(struct s_tnode *test);
void			tester(struct s_tnode *test);
void			printest(struct s_tnode *tnode);
t_job			*ft_create_exec(t_job *job, struct s_tnode *token);
t_job			*ms_job_newlst(void);
void			ms_job_addback(t_job **job, t_job *new_job);
void			token_to_tab(struct s_tnode *token, t_job *job);
int				counter_string(struct s_tnode *tok);
bool			is_redirection(struct s_tnode *token);
t_job			*redirection_to_tab(struct s_tnode *token, t_job *job);
int				redir_counter(struct s_tnode *tok);
void			ms_exec(t_job *job, t_cdata *c_data);
void			child_process(t_job *job, t_job *first, t_cdata *c_data);
void			init_pipe(t_job *job);
int				ms_exec_builtins(t_job *job, t_cdata *c_data);
int				ms_builtins(char **arg, int i, t_job *job, t_cdata *c_data);
void			restore_fd(int saved_stdin, int saved_stdout);
int				check_builtins(char **arg);
int				check_redirection(t_job *job, int quit);
t_job			*ms_job_last(t_job *job);
struct	s_tnode	*ms_head_list(struct s_tnode *token);
t_job			*ms_head_list_job(t_job *job);
void			executor(t_job *job, t_cdata *c_data);
void			execute(char **cmd, t_job *job, t_cdata *c_data);
void			free_job_lst(t_job *job);
char			*find_path(char *cmd, t_job *job, t_cdata *c_data);
int				find_path_env(t_cdata *c_data);
void			error(char *arg, int i, t_job *job, t_cdata *c_data);
int				make_heredocs(t_job *job, t_cdata *c_data);
int				check_heredoc(char **redir, int stdin_fd,
					t_job *job, t_cdata *c_data);
int				redir_heredoc(char *limiter, int fd,
					t_job *job, t_cdata *c_data);
void			heredoc(char *limiter, int *fd, t_job *job, t_cdata *c_data);
int				ft_delim_is_quoted(t_cdata *c_data);
int				check_arg(char *arg, t_cdata *c_data);
void			built_exit(char **arg, t_job *job, t_cdata *c_data);
void			free_fd(t_job *first);
void			free_ex(t_job *job, t_cdata *c_data);
char			*ft_get_env(char *var_name, char **env);
void			mini_exec(t_job *job, t_job *first, t_cdata *c_data);
void			ex_stat(t_cdata *c_data, int status);
void			ft_put_error(char *str1, char *str2, char *str3, int fd);

#endif
