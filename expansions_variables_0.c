#include "minishell.h"

/* 1/3 Linked list is iterated to expand variables */
void	ft_expand_variables(c_data *c_data)
{
    struct q_node	*curr;
	
	curr = c_data->q_data->quotes_list;
	while (1)
	{
        if (curr->q_type != '\'')
		{
			if (ft_find_dollar(curr->str))
				curr->str = ft_add_variable_values(curr->str, c_data);
		}
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
	}	
}

/* 1a Check if there's at least one $ */
int	ft_find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

/* 2/3 Outside quotes, variables are expanded to their value */
char	*ft_add_variable_values(char *str, c_data *c_data)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (str[i] != '\0')
	{
		if ((i == 0 && str[i] == '$') || str[i] == '$')
		{
			start = i;
			i++;
			if (str[i] == '?')
				i++;
			else
			{
				while (str[i] >= 'A' && str[i] <= 'Z')
					i++;
			}
			break;
		}
		i++;
	}
	return (ft_expand_variable_value(c_data, str, start, i));
}

/* 3/3 Splice variable value in the correct spot inside of string */
char	*ft_expand_variable_value(c_data *c_data, char *str, int start, int end)
{
	char	*var_name;
    char    *var_value;
    char    *result;

	if (str[start + 1] == '?')
	{
		var_value = ft_itoa(c_data->exit_status);
		result = ft_splice_var_value(str, var_value, start, end);
		free(var_value);
	}
	else
	{
		var_name = ft_get_var_name(str, start + 1, end);
		var_value = getenv(var_name);
		if (var_value == NULL)
			result = ft_remove_var_name(str, start, end);
		else
			result = ft_splice_var_value(str, var_value, start, end);
		free(str);
		free(var_name);
	}
	return (result);
}