#include "minishell.h"

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
    int     i;

    i = 0;
    t_cdata->t_qdata->delim = ft_extract_and_remove_delim(t_cdata);
    ft_print_here_doc_detected();
    while (1)
    {
        if (!ft_get_valid_input(t_cdata, t_cdata->t_pdata->prompt_nl_text))
            break ;
        i++;
    }
}

char    *ft_extract_and_remove_delim(t_cdata *t_cdata)
{
    int     i;
    char    *result;
    char    *raw_input_temp;

    i = 0;
    while (t_cdata->t_qdata->raw_input[i + 1] != '\0')
    {
        if (t_cdata->t_qdata->raw_input[i] == '<' && t_cdata->t_qdata->raw_input[i] == '<')
        {
            i += 2;
            break;
        }
        i++;
    }
    result = ft_substr(t_cdata->t_qdata->raw_input, i, ft_strlen(t_cdata->t_qdata->raw_input) - i);
    if (ft_has_spaces(result))
        result = ft_strtrim(result, " ");
        // result = ft_strtrim(result, " \t\r\n\v\f");
    raw_input_temp = ft_substr(t_cdata->t_qdata->raw_input, 0, i);
    free(t_cdata->t_qdata->raw_input);
    t_cdata->t_qdata->raw_input = raw_input_temp;
    return (result);
}
