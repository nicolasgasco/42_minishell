#include "minishell.h"

// Linked list is iterated to expand escape characters and variables
void    ft_expansions(q_data *q_data)
{
    struct s_node	*curr;
	
	curr = q_data->quotes_list;
	while (1)
	{
        if (curr->q_type == '\"')
		{
			printf("Str is %s\n", curr->str);
			curr->str = ft_expand_escaped(curr->str);
			printf("Str is %s\n", curr->str);
		}
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
	}
}

// Inside double quotes, escape character works only with %, `, ", \, and \n; inside single quotes, it's ignored 
char	*ft_expand_escaped(char *str)
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
