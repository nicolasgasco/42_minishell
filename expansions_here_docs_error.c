/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_here_docs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:44:07 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/21 16:44:09 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks for case when input is just << with no content */
int	ft_found_lonely_here_marker(char *str)
{
	char	*temp;

	temp = ft_strtrim(str, "\n\t ");
	if (ft_strcmp(temp, "<<") == 0)
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

int	ft_found_here_marker_without_cmd(char *str)
{
	char	*temp;

	temp = ft_strtrim(str, "\n\t ");
	if (temp[0] == '<' && temp[1] == '<')
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}
