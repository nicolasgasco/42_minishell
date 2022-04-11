/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:21:09 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:21:11 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Init and reset data required at beginning of every loop */
void	ft_init_reset_loop_data(t_cdata *t_cdata)
{
	t_cdata->syntax_error = 0;
	t_cdata->tokens_list = NULL;
	ft_init_quotes_data(t_cdata);
}

// Structure with global data
void	ft_init_general_data(t_cdata *c_data, char **envp)
{
	memset(c_data, 0, sizeof(t_cdata));
	init_envp(envp, c_data);
	ft_init_prompt_data(c_data);
	init_export(c_data);
	ft_output_epic_welcome(c_data); // TBD
}

/* Structure containing information on quotes */
void	ft_init_quotes_data(t_cdata *t_cdata)
{
	t_cdata->t_qdata = (t_qdata *)malloc(sizeof(t_qdata));
	memset(t_cdata->t_qdata, 0, sizeof(t_qdata));
}

/* TODO has leaks */
void	init_envp(char **envp, t_cdata *t_cdata)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	t_cdata->envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		t_cdata->envp[i] = ft_strdup(envp[i]);
	t_cdata->envp[i] = NULL;
}

/* TODO has leaks */
void	init_export(t_cdata *t_cdata)
{
	int		i;
	char	*string;

	i = 0;
	while (t_cdata->envp[i])
		i++;
	t_cdata->envp_export = malloc(sizeof(char *) * (i));
	i = 0;
	if (t_cdata->envp[i])
	{
		while (t_cdata->envp[i + 1])
		{
			string = ms_make_string(t_cdata->envp[i]);
			t_cdata->envp_export[i] = ft_strdup(string);
			free(string);
			i++;
		}
	}
	t_cdata->envp_export[i] = NULL;
}
