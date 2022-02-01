/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <ngasco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 17:44:27 by ngasco            #+#    #+#             */
/*   Updated: 2021/11/16 19:50:30 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char	c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	return (0);
}

static int	ft_calc_total_len(char const *s)
{
	int	i;
	int	tot_words;

	tot_words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isspace(s[i]) == 1 && s[i - 1] && ft_isspace(s[i - 1]) == 0)
			tot_words++;
		i++;
	}
	if (ft_isspace(s[i - 1]) == 0)
		tot_words += 1;
	return (tot_words);
}

static void	ft_write_strings_to_array(char const *s, char **result)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (s[i] != '\0')
	{
		if (ft_isspace(s[i]) == 1 && ft_isspace(s[i - 1]) == 0)
		{
			if (i - start != 0)
			{
				*result = ft_substr(s, start, i - start);
				result++;
			}
			start = i + 1;
		}
		else if (ft_isspace(s[i]) == 1 && ft_isspace(s[i - 1]) == 1)
			start++;
		i++;
	}
	if (ft_isspace(s[i - 1]) == 0)
	{
		*result = ft_substr(s, start, i - start);
		result++;
	}
	*result = NULL;
}

char	**ft_split(char const *s)
{
	char	**result;

	if (!s)
		return (NULL);
	if (s[0] == '\0' || ft_strlen(s) == 0)
	{
		result = (char **)malloc(sizeof(char *));
		result[0] = NULL;
		return (result);
	}
	result = (char **)malloc(ft_calc_total_len(s) * sizeof(char *) + 1);
	if (result == NULL)
	{
		free(result);
		return (NULL);
	}
	ft_write_strings_to_array(s, result);
	return (result);
}
