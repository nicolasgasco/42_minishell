/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_vars_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:27:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:27:51 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 3a Isolate and create variable for variable name, e.g. PATH or USER */
char	*ft_get_var_name(char *str, int start, int end)
{
	char	*result;
	int		i;

	result = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!result)
		exit(1);
	i = 0;
	while (start < end)
	{
		result[i] = str[start];
		start++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

/* 3b Take variable value and splice it into original str */
char	*ft_splice_var_value(char *s, char *var, int start, int end)
{
	char	*result;
	int		i;
	int		x;

	i = 0;
	x = 0;
	result = (char *)malloc(ft_strlen(s) - (end - start) + ft_strlen(var) + 1);
	while (s[i] != '\0')
	{
		if (i == start)
		{
			ft_splice_var_value_utility(result, var, &x);
			i += (end - start);
		}
		result[x] = s[i];
		i++;
		x++;
	}
	result[x] = '\0';
	return (result);
}

/* Utility function for 3b in order to respect Norminette length restrictions */
void	ft_splice_var_value_utility(char *result, char *var, int *x)
{
	int	y;

	y = 0;
	while (var[y] != '\0')
	{
		result[*x] = var[y];
		y++;
		*x = *x + 1;
	}
}

/* 3c If variable value doesn't exist, just remove $VAR from string */
char	*ft_remove_var_name(char *str, int start, int end)
{
	int		i;
	int		y;
	char	*result;

	result = (char *)malloc(ft_strlen(str) - (end - start) + 1);
	i = 0;
	y = 0;
	while (str[i] != '\0')
	{
		if (i == (start - 1) || (i == 0 && start == 0))
		{
			while (i < end)
				i++;
		}
		result[y] = str[i];
		i++;
		y++;
	}
	result[y] = '\0';
	return (result);
}
