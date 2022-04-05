/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:24:54 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/05 13:25:55 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_pwd(void)
{
	char	str[PATH_MAX];

	if (getcwd(str, sizeof(str)) == NULL)
		return (1);
	printf("%s\n", str);
	return (0);
}
