/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:38:09 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/07 13:32:05 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if (str && str[i])
	{
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			i++;
			while (str[i] != '\0')
			{
				if (str[i] != 'n' && str[i] != '\0')
					return (1);
				i++;
			}
			return (0);
		}
	}
	return (1);
}

int	built_echo(char **arg)
{
	int	x;
	int	i;

	x = 1;
	i = 0;
	while (arg[x])
	{
		if (!check_new_line(arg[x]))
			i++;
		else
		{
			printf("%s", arg[x]);
			if (arg[x + 1] != NULL)
				printf(" ");
		}
		x++;
	}
	if (!i)
		printf("\n");
	return (0);
}
