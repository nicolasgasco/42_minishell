/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:13:20 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/12 10:44:55 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_export_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		ft_put_error("export: '", arg, "': not a valid identifier\n", 2);
		return (1);
	}
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			ft_put_error("export: '", arg, "': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ms_make_string(char *arg)
{
	char	**strings;
	char	*string;
	int		i;

	i = 1;
	strings = ft_splitc(arg, '=');
	string = ft_strjoin(strings[0], "=\"");
	while (strings[i] && strings[i + 1])
	{
		string = ft_strjoin_free_s1(string, strings[i++]);
		string = ft_strjoin_free_s1(string, "=");
	}
	if (strings[i])
		string = ft_strjoin_free_s1(string, strings[i]);
	string = ft_strjoin_free_s1(string, "\"");
	ft_free_tab(strings);
	return (string);
}

void	ms_export_sort(t_cdata *t_cdata)
{
	int	i;

	i = 0;
	ft_sort_tab(t_cdata->envp_export);
	while (t_cdata->envp_export[i])
		printf("declare -x %s\n", t_cdata->envp_export[i++]);
}

void	ms_export_valid_arg(char *arg, char *strings, t_cdata *cdata)
{
	char	*string;

	if (ft_strchr(arg, '=') == NULL)
	{
		if (ms_get_env(cdata->envp_export, strings) == NULL)
			cdata->envp_export = ms_matrix_add_line(cdata->envp_export, arg);
	}
	else
	{
		string = ms_make_string(arg);
		if (ms_get_env(cdata->envp_export, strings) != NULL)
		{
			arg = ft_strdup(arg);
			ms_set_env(cdata->envp, arg, cdata);
			ms_set_env(cdata->envp_export, string, cdata);
			free(arg);
		}
		else
		{
			cdata->envp = ms_matrix_add_line(cdata->envp, arg);
			cdata->envp_export = ms_matrix_add_line(cdata->envp_export, string);
		}
		free(string);
	}
}

int	built_export(char **arg, t_cdata *t_cdata)
{
	char	**strings;
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (arg[i])
	{
		if (ms_check_export_arg(arg[i]) != 0)
		{
			i++;
			continue ;
			ret = 1;
		}
		strings = ft_splitc(arg[i], '=');
		ms_export_valid_arg(arg[i], strings[0], t_cdata);
		ft_free_tab(strings);
		i++;
	}
	if (arg[0] == NULL)
		ms_export_sort(t_cdata);
	return (ret);
}
