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

#include "minishell.h"

// Concatenate two strings and free first one
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
