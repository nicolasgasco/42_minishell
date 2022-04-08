/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:11:11 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/05 13:12:16 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *arg, t_cdata *c_data)
{
	int			i;
	long long	exit_code;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
		i++;
	if (ft_isdigit(arg[i]) == 0 || ft_isllong(arg) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", arg);
		c_data->exit_status = 255;
		return (1);
	}
	exit_code = ft_atoll(arg);
	c_data->exit_status = exit_code % 256;
	if (c_data->exit_status < 0 || c_data->exit_status > 255)
		c_data->exit_status = 255;
	return (0);
}

void	built_exit(char **arg, t_job *job, t_cdata *c_data)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (arg[0])
	{
		i = check_arg(arg[0], c_data);
		if (arg[1] && i == 0)
		{
			printf("minishell: exit: too many arguments\n");
			c_data->exit_status = 1;
			return ;
		}
	}
	exit(c_data->exit_status);
}
