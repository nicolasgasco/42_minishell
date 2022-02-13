#include "minishell.h"

// 1/3 Linked list is iterated to expand variables
void	ft_expand_variables(q_data *q_data)
{
    struct s_node	*curr;
	
	curr = q_data->quotes_list;
	while (1)
	{
        if (curr->q_type != '\"' && curr->q_type != '\'')
			curr->str = ft_add_variable_values(curr->str);
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
	}	
}

// 2/3 Outside quotes, variables are expanded to their value
char	*ft_add_variable_values(char *str)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			start = i;
			i++;
			while (str[i] >= 'A' && str[i] <= 'Z')
				i++;
			break;
		}
		i++;
	}
	return (ft_expand_variable_value(str, start, i));
}

// 3/3 Splice variable value in the correct spot inside of string
char	*ft_expand_variable_value(char *str, int start, int end)
{
	char	*var_name;
    char    *var_value;
    char    *result;

	var_name = ft_get_var_name(str, start + 1, end);
	printf("Var_name is .%s.\n", var_name);
    var_value = getenv(var_name);
    printf("Var_value is .%s.\n", var_value);
    printf("Start is %d, end %d\n", start, end);
    if (!var_value)
        result = ft_remove_var_name(str, start, end);
    else
        result = ft_splice_var_value(str, var_value, start, end);
    free(str);
	return (result);
}