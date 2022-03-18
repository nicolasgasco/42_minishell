#include "minishell.h"

/* Splitting string containing >> and add linked list nodes */
void    ft_split_and_generate_special_char_node(struct s_qnode  *curr, int len)
{
    char            *token;
    char            *rest;
    int             t_len;
    char            *redirect;

    t_len = ft_calc_special_char_token_len(curr->str);
    token = (char *)malloc(sizeof(char) * (t_len + 1));   
    ft_strlcpy(token, curr->str, t_len + 1);
    rest = ft_substr(curr->str, t_len + len, ft_strlen(curr->str) - t_len - len);
    redirect = (char *)malloc(sizeof(char) * 3);
    redirect = ft_strdup(">>");
    ft_add_special_char_nodes(curr, token, redirect, rest);
}

/* Adding new nodes with the single parts of the split string containing >> */
void    ft_add_special_char_nodes(struct s_qnode  *curr, char *curr_str, char *next_str, char *rest)
{
    struct s_qnode  *new_node1;
    struct s_qnode  *new_node2;

    new_node1 = (struct s_qnode *)malloc(sizeof(struct s_qnode));
    memset(new_node1, 0, sizeof(struct s_qnode));
    new_node2 = (struct s_qnode *)malloc(sizeof(struct s_qnode));
    memset(new_node2, 0, sizeof(struct s_qnode));
    free(curr->str);
    curr->str = curr_str;
    new_node1->str = next_str;
    new_node1->next = curr->next;
    curr->next = new_node1;
    new_node2->str = rest;
    new_node1->next = new_node2;
}

