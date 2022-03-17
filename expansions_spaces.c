#include "minishell.h"

/* Space between tweaks are removed */
void ft_expand_spaces(t_cdata *t_cdata)
{
	struct t_qnode	*curr;
    int             i;

    i = 0;
	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		// if (curr->q_type != '\'')
		// {
		// 	if (ft_find_dollar(curr->str))
		// 		curr->str = ft_add_variable_values(curr->str, t_cdata);
		// }
        printf(".%s.\n", curr->str);
        curr->str = ft_strtrim(curr->str, " \t\r\n\v\f");
        if (!curr->q_type)
        {
            printf("Spaces must be removed\n");
            ft_split_and_generate_node(curr);
        }
        printf(".%s.\n\n", curr->str);
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
        i++;
	}
}

void    ft_split_and_generate_node(struct t_qnode *curr)
{
    char            *token;
    char            *rest;
    int             t_len;
    // struct s_qnode  *new_node;
    printf("Splitting .%s.\n", curr->str);

    new_node = (struct s_qnode *)malloc(sizeof(struct s_qnode *));
    t_len = ft_calc_token_len(curr->str);
    printf("Token len is %d\n", t_len);
    token = (char *)malloc(sizeof(char) * t_len + 1);
    rest = ft_substr(curr->str, t_len, ft_strlen(curr->str) - t_len);
    rest = ft_strtrim(rest, " \t\r\n\v\f");
    ft_strlcpy(token, curr->str, t_len + 1);
    free(curr->str);
    curr->str = token;
    printf("Token: .%s., Rest: .%s.\n", token, rest);
}

// void    ft_splice_node_with_index(struct t_qnode *curr)
// {

// }

int ft_calc_token_len(char *str)
{
    int i;

    i = 0;
    while (!ft_isspace(str[i]))
        i++;
    return (i);
}

int ft_has_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (ft_isspace(str[i]))
            return (1);
        i++;
    }
    return (0);
}

int ft_isspace(char c)
{
    if (c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f' || c == ' ')
        return (1);
    return (0);
}
