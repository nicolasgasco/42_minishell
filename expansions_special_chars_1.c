/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_special_chars_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:36:09 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/29 11:36:11 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checking if the specified set or character are in the string */
int	ft_has_special_char(char *str, char *set)
{
	if (ft_strlen(set) == 2)
		return (ft_find_special_char_set(str, set));
	else
		return (ft_find_special_char_single(str, set[0]));
}

/* Checking if the specified set is in the string */
int	ft_find_special_char_set(char *str, char *set)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	len = ft_strlen(set);
	while (str[i + (len - 1)] != '\0')
	{
		k = i;
		j = 0;
		while (str[k] == set[j] && set[j] != '\0')
		{
			k++;
			j++;
		}
		if (str[k] != set[0] && set[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

/* Checking if the specified character is in the string */
int	ft_find_special_char_single(char *str, char c)
{
	int	i;

	i = 1;
	if (!ft_strlen(str))
		return (-1);
	if (str[0] == c && str[1] != c)
		return (0);
	while (str[i + 1] != '\0')
	{
		if (str[i] == c && str[i + 1] != c && str[i - 1] != c)
			return (i);
		i++;
	}
	if (str[i] == c && str[i - 1] != c)
		return (i);
	return (-1);
}

/* Splitting string containing >> and add linked list nodes */
void	ft_split_s_char_node(struct s_qnode *curr, int len, char *set, int i)
{
	char	*token;
	char	*rest;
	char	*symbol;

	token = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(token, curr->str, i + 1);
	rest = ft_substr(curr->str, i + len, (ft_strlen(curr->str) - i - len));
	symbol = ft_strdup(set);
	ft_add_special_char_nodes(curr, token, symbol, rest);
}
