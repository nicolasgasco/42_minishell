#include "minishell.h"

/* Checking for >>, <, and > */
int ft_special_chars_are_valid(t_cdata *t_cdata)
{
    ft_expand_r_red_append(t_cdata);
    // ft_expand_reds(t_cdata);
    return (1);
}

/* Expansion of >> */
int ft_expand_r_red_append(t_cdata *t_cdata)
{
    while (1)
    {
        if (!ft_found_r_red_append(t_cdata))
            break;
    }
    return (1);
}

/* Iterating list untill all >> are expanded */
int ft_found_r_red_append(t_cdata *t_cdata)
{
    struct s_qnode	*curr;
    int             found_red;

    found_red = 0;
	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
        if (!curr->q_type)
        {
            if (ft_has_r_red_append(curr->str) && ft_strlen(curr->str) > 2)
            {
                found_red = 1;
                ft_split_and_generate_special_char_node(curr, 2);
                break;
            }

        }
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
    return (found_red);
}

/* Checking if >> is present */
int ft_has_r_red_append(char *str)
{
    int i;

    i = 0;
    while (str[i + 1] != '\0')
    {
        if (str[i] == '>' && str[i + 1] == '>')
            return (1);
        i++;
    }
    return (0);
}

/* Utility function calculating number of chars before >> */
int ft_calc_special_char_token_len(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '>' || str[i] == '<')
            return (i);
        i++;
    }
    return (i);
}

