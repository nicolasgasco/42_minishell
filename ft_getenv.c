/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:38:04 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/12 10:40:12 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(char *var_name, char **env)
{
	int		i;
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(var_name, "=");
	temp2 = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], temp, ft_strlen(temp)))
		{
			temp2 = ft_substr(env[i], ft_strlen(temp),
					((ft_strlen(env[i]) - ft_strlen(temp))));
			free(temp);
			return (temp2);
		}
		i++;
	}
	free(temp);
	return (temp2);
}
