#include "minishell.h"

/* Space between tweaks are removed */
void ft_expand_spaces(t_cdata *t_cdata)
{
    while (1)
    {
        if (!ft_found_space_to_split(t_cdata))
            break;
    }
    ft_print_after_spaces_expansion(t_cdata);
}

int     ft_found_space_to_split(t_cdata *t_cdata)
{
	struct s_qnode	*curr;
    int             found_space;

    found_space = 0;
	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
        if (!curr->q_type && ft_has_spaces(curr->str))
        {
            found_space = 1;
            curr->str = ft_strtrim(curr->str, " \t\r\n\v\f");
            ft_split_and_generate_node(curr);
            break;
        }
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
    return (found_space);
}

void    ft_split_and_generate_node(struct s_qnode *curr)
{
    char            *token;
    char            *rest;
    int             t_len;
    struct s_qnode  *new_node;

    new_node = (struct s_qnode *)malloc(sizeof(struct s_qnode));
    memset(new_node, 0, sizeof(struct s_qnode));
    t_len = ft_calc_token_len(curr->str);
    token = (char *)malloc(sizeof(char) * t_len + 1);   
    ft_strlcpy(token, curr->str, t_len + 1);
    rest = ft_substr(curr->str, t_len, ft_strlen(curr->str) - t_len);
    rest = ft_strtrim(rest, " \t\r\n\v\f");
    free(curr->str);
    curr->str = token;
    new_node->str = rest;
    new_node->next = curr->next;
    curr->next = new_node;
}
