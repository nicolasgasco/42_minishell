/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_custom_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:22:04 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/11 10:41:17 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	printf("str es %s\n", str);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			return (0);
		}
		
		i++;
	}
	return (1);
}
