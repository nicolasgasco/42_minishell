/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:22:29 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:22:30 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializing structure containing information on prompt */
void	ft_init_prompt_data(c_data *c_data)
{
	c_data->p_data = (p_data *)malloc(sizeof(p_data));
	memset(c_data->p_data, 0, sizeof(p_data));
	c_data->p_data->username = getenv("USER");
	if (!c_data->p_data->username)
		c_data->p_data->username = ft_strdup("username");
	c_data->p_data->hostname = getenv("HOSTNAME");
	if (!c_data->p_data->hostname)
		c_data->p_data->hostname = ft_strdup("os");
	c_data->p_data->prompt_text = ft_create_prompt_text(c_data->p_data->username, c_data->p_data->hostname);
	c_data->p_data->prompt_nl_text = ft_strdup("> ");
}

/* The text shown when prompting user for input, e.g. username@hostname */
char	*ft_create_prompt_text(char *username, char *hostname)
{
	int		i;
	int		len1;
	int		len2;
	char	*result;

	i = -1;
	len1 = ft_strlen(username);
	len2 = ft_strlen(hostname);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 4));
	while (++i < len1)
		result[i] = username[i];
	result[i] = '@';
	while (++i < (len1 + len2 + 1))
		result[i] = hostname[i - len1 - 1];
	result[i] = ':';
	result[i + 1] = ' ';
	result[i + 2] = '\0';
	return (result);
}
