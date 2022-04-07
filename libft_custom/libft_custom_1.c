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

#include "../minishell.h"

/* Function to free an array */
void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strjoin_free_s1(char *s1, char const *s2)
{
	char	*tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	tab = (char *)malloc(sizeof(*tab) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (tab == 0)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tab[i] = s2[j];
		j++;
		i++;
	}
	tab[i] = '\0';
	free(s1);
	return (tab);
}

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_tab(char **arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
				swap(&arr[i], &arr[j]);
			++j;
		}
		++i;
	}
}

int	ft_isllong(char *str)
{
	if (str[0] == '-' && ft_strlen(str) >= 20
		&& ft_strcmp(&str[1], "9223372036854775808") > 0)
		return (1);
	else if (ft_strlen(str) >= 19
		&& ft_strcmp(str, "9223372036854775807") > 0)
		return (1);
	return (0);
}
