/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_vars_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:30:17 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:30:18 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 1/4 Iterate list and expand as long as there are variables to expand.
	Comes in handy in cases like $USER$PATH									*/
void	ft_expand_variables(t_cdata *t_cdata)
{
	while (1)
	{
		// ft_print_after_variables_expansion(t_cdata);
		if (!ft_found_variable_to_expand(t_cdata))
			break ;
	}
	ft_print_after_variables_expansion(t_cdata);
}

/* 2/4 Linked list is iterated to expand variables */
int	ft_found_variable_to_expand(t_cdata *t_cdata)
{
	struct s_qnode	*curr;
	int				found_var;

	found_var = 0;
	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		if (curr->q_type != '\'')
		{
			if (ft_find_dollar(curr->str))
			{
				curr->str = ft_add_variable_value(curr->str, t_cdata);
				curr->q_type = '\"';
				curr->length = ft_strlen(curr->str);
				found_var = 1;
			}
		}
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
	return (found_var);
}

/* 2a Check if there's at least one $ */
int	ft_find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

/* 3/4 Outside quotes, variables are expanded to their value */
char	*ft_add_variable_value(char *str, t_cdata *t_cdata)
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
				while ((str[i] >= 'A' && str[i] <= 'Z')
					|| (str[i] >= 'a' && str[i] <= 'z'))
					i++;
			}
			break ;
		}
		i++;
	}
	return (ft_expand_var_value(t_cdata, str, start, i));
}

/* 4/4 Splice variable value in the correct spot inside of string */
char	*ft_expand_var_value(t_cdata *t_cdata, char *str, int start, int end)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	if (str[start + 1] == '?')
	{
		var_value = ft_itoa(t_cdata->exit_status);
		result = ft_splice_var_value(str, var_value, start, end);
		free(var_value);
	}
	else
	{
		var_name = ft_get_var_name(str, start + 1, end);
		var_value = getenv(var_name);
		if (var_value == NULL)
			result = ft_remove_var_name(str, start + 1, end);
		else
			result = ft_splice_var_value(str, var_value, start, end);
		free(str);
		free(var_name);
	}
	return (result);
}
