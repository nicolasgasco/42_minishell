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

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n)
	{
		*str = 0;
		str++;
		n--;
	}
}
