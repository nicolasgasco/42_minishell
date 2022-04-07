/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_quotes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:35:18 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:35:19 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Concatenate two strings and free first one */
char	*ft_strcat(char *src, char *dest)
{
	int		i;
	int		y;
	char	*result;

	i = 0;
	y = 0;
	result = (char *)malloc(ft_strlen(src) + ft_strlen(dest) + 1);
	if (!result)
		exit (1);
	while (src[i] != '\0')
	{
		result[y] = src[i];
		y++;
		i++;
	}
	i = 0;
	while (dest[i] != '\0')
	{
		result[y] = dest[i];
		y++;
		i++;
	}
	result[y] = '\0';
	free(src);
	return (result);
}

/* 1/4 Ft_strtrim with free on the first string */
char	*ft_strtrim_free(char *s1, char const *set)
{
	int		start;
	int		end;
	char	*res;

	if (!set)
		return (NULL);
	if (!s1)
	{
		res = ft_create_empty_string();
		return (res);
	}
	end = ft_calc_end(s1, set);
	start = ft_calc_start(s1, set);
	if (start > end)
	{
		res = ft_create_empty_string();
		free(s1);
		return (res);
	}
	res = malloc((end - start + 1 + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, (char *)&s1[start], end - start + 1 + 1);
	free(s1);
	return (res);
}

/* 2/4 Utility function */
char	*ft_create_empty_string(void)
{
	char	*res;

	res = malloc(1 * sizeof(char));
	res[0] = '\0';
	return (res);
}

/* 2/4 Utility function */
static int	ft_calc_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (start < (int)ft_strlen((char *)s1))
	{
		if (!ft_strchr(set, s1[start]))
			break ;
		start++;
	}
	return (start);
}

/* 3/4 Utility function */
static int	ft_calc_end(char const *s1, char const *set)
{
	int	end;

	end = ft_strlen((char *)s1) - 1;
	while (end > 0)
	{
		if (!ft_strchr(set, s1[end]))
			break ;
		end--;
	}
	return (end);
}
