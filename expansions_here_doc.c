#include "minishell.h"

/* Loof for a Here document structure in each string of the quotes linked list */
int ft_find_here_marker_list(t_cdata *t_cdata)
{
    struct s_qnode	*curr;

    curr = t_cdata->t_qdata->quotes_list;
    while (1)
    {
        if (curr->q_type != '\'')
        {
            if (ft_find_here_marker_str(curr->str))
                return (1);
        }
        if (curr->next == NULL)
            break;
        else
            curr = curr->next;
    }	
    return (0);
}

/* Look for Here document in a string not enclosed by single quotes */
int ft_find_here_marker_str(char *str)
{
    int i;

    i = 1;
    if (ft_strlen(str) < 4)
        return (-1);
    while (str[i + 2] != '\0')
    {
        if (str[i] == '<' && str[i + 1] == '<' && str[i - 1] != '<'
        && str[i + 2] != '|' && str[i + 2] != '<' && str[i + 2] != '>')
        {
            return (1);
        }
        i++;
    }
    if (str[i] == '<' && str[i + 1] == '<' && str[i - 1] != '<')
        return (1);
    return (0);
}

void    ft_here_doc_loop(t_cdata *t_cdata)
{
    int i;

    i = 0;
    ft_print_here_doc_detected();
    while (1)
    {
        printf("Raw input is %s\n", t_cdata->t_qdata->raw_input);
        ft_get_valid_input(t_cdata, t_cdata->t_pdata->prompt_nl_text);
        // Breaking when found marker
        if (i == 4)
            break;
        // line_read = rl_gets(line_read, t_cdata->prompt_newline_text);
        // if (!ft_are_quotes_unclosed(line_read))
        //     break;
        i++;
    }
}
