#include "minishell.h"

// 1/2 Linked list is iterated to expand escaped characters
void	ft_expand_escaped(q_data *q_data)
{
    struct s_node	*curr;
	
	curr = q_data->quotes_list;
	while (1)
	{
        if (curr->q_type == '\"')
			curr->str = ft_remove_escaped_from_str(curr->str);
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
	}
}

// 2/2 Inside double quotes, escape character works only with %, `, ", \, and \n; inside single quotes, it's ignored 
char	*ft_remove_escaped_from_str(char *str)
{
	int	i;
	char	*result;

	i = 0;

	result = ft_strdup(str);
	while (str[i] != '\0')
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
