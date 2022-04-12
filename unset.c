/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:34:50 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/12 10:48:19 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_matrix_remove_line(char **matrix, char *line)
{
	int		i;
	int		j;
	char	**new_matrix;

	i = 0;
	j = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (matrix[i])
	{
		if (ft_strcmp(matrix[i], line) == 0)
			i++;
		if (matrix[i])
		{
			new_matrix[j++] = ft_strdup(matrix[i]);
			i++;
		}
	}
	new_matrix[j] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}

int	check_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		ft_put_error("unset: '", arg, "': not a valid identifier\n", 2);
		return (1);
	}
	i++;
	while (arg[i])
	{
		if ((ft_isalnum(arg[i]) == 0 && arg[i] != '_') || arg[i] == '=')
		{
			ft_put_error("unset: '", arg,"': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**unset_remove(char **env, char *arg)
{
	char	*line;

	line = NULL;
	line = ms_get_env(env, arg);
	if (line != NULL)
		env = ms_matrix_remove_line(env, line);
	return (env);
}

int	built_unset(char **arg, t_cdata *t_cdata)
{
	int		i;
	char	**strings;
	int		ret;

	ret = 0;
	i = 0;
	while (arg[i])
	{
		if (check_unset_arg(arg[i]) != 0)
		{
			i++;
			ret = 1;
			continue ;
		}
		strings = ft_splitc(arg[i], '=');
		t_cdata->envp = unset_remove(t_cdata->envp, strings[0]);
		t_cdata->envp_export = unset_remove(t_cdata->envp_export, strings[0]);
		ft_free_tab(strings);
		i++;
	}
	return (ret);
}
