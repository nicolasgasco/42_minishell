/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:11:11 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/12 11:55:26 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *arg)
{
	int			i;
	long long	exit_code;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
		i++;
	if (ft_isalldigit(arg + 1) == 0 || ft_isllong(arg) != 0)
	{
		ft_putendl_fd("minishell: exit : ", 2);
		ft_putendl_fd(arg, 2);
		ft_putendl_fd(": numeric argument required\n", 2);
		g_ex_status = 255;
		return (1);
	}
	exit_code = ft_atoll(arg);
	g_ex_status = exit_code % 256;
	if (g_ex_status < 0 || g_ex_status > 255)
		g_ex_status = 255;
	return (0);
}

void	built_exit(char **arg)
{
	int	i;

	i = 0;
	ft_putendl_fd("exit\n", 2);
	if (arg[0])
	{
		i = check_arg(arg[0]);
		if (arg[1] && i == 0)
		{
			ft_putendl_fd("minishell: exit: too many arguments\n", 2);
			g_ex_status = 1;
			return ;
		}
	}
	exit(g_ex_status);
}
