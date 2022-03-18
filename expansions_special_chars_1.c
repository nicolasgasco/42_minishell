#include "minishell.h"


/* Utility function calculating number of chars before special symbol */
int ft_calc_special_char_token_len(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '>' || str[i] == '<' || str[i] == '|')
            return (i);
        i++;
    }
    return (i);
}

/* Splitting string containing >> and add linked list nodes */
void    ft_split_and_generate_special_char_node(struct s_qnode  *curr, int len, char *set)
{
    char            *token;
    char            *rest;
    int             t_len;
    char            *symbol;

    t_len = ft_calc_special_char_token_len(curr->str);
    token = (char *)malloc(sizeof(char) * (t_len + 1));   
    ft_strlcpy(token, curr->str, t_len + 1);
    rest = ft_substr(curr->str, t_len + len, ft_strlen(curr->str) - t_len - len);
    symbol = (char *)malloc(sizeof(char) * ft_strlen(set) + 1);
    symbol = ft_strdup(set);
    ft_add_special_char_nodes(curr, token, symbol, rest);
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
    curr->length = ft_strlen(curr_str);
    new_node1->str = next_str;
    new_node1->length = ft_strlen(new_node1->str);
    new_node1->next = curr->next;
    curr->next = new_node1;
    new_node2->str = rest;
    new_node2->length = ft_strlen(new_node2->str);
    new_node1->next = new_node2;
}

