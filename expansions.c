#include "minishell.h"

void    ft_expand_quotes(q_data *q_data)
{
    struct s_node	*curr;
	int				i;
	
	i = 0;
	curr = q_data->quotes_list;
	while (1)
	{
        if (curr->q_type == '\"')
		{
            curr->str = ft_strtrim(curr->str, "\"");
			curr->str = ft_expand_escaped(curr->str);
		}
		else if (curr->q_type == '\'')
            curr->str = ft_strtrim(curr->str, "\'");
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
		i++;
	}
}

char	*ft_expand_escaped(char *str)
{
	int	i;
	char	*result;

	i = 0;

	while (1)
	{
		if (str[i] == '\\')
		{
			printf("Found a backslash\n");
			if (str[i + 1] == '$' || str[i + 1] == '`' || str[i + 1] == '\"'
			|| str[i + 1] == '\\' || str[i + 1] == '\n')
			{
				result = ft_remove_char_index(str, i);
				break;
			}
		}
		if (str[i + 2] == '\0')
			break;
		i++;
	}
	free(str);
	return (result);
}

// dollar, backtick, double quote, backslash or newline, double quotes