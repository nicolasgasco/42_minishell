/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:41:35 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/11 13:05:03 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_envp(t_cdata *t_cdata)
{
	int	i;

	i = 0;
	while (t_cdata->envp[i])
		printf("%s\n", t_cdata->envp[i++]);
	return (0);
}
