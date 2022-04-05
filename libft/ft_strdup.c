/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <marvin@42.fr>                      +#+  +:+       +#       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:30:43 by adel-cor            #+#    #+#           */
/*   Updated: 2022/04/05 12:30:44 by adel-cor           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tab;
	int		i;

	i = 0;
	tab = (char *)malloc(sizeof(*tab) * (ft_strlen(s1) + 1));
	if (!tab)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
