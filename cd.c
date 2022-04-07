/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:21:22 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/07 14:41:46 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_env(char **env, char *str)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_splitc(env[i], '=');
		if (ft_strcmp(split[0], str) == 0)
		{
			ft_free_tab(split);
			break ;
		}
		else
			i++;
		ft_free_tab(split);
	}
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
}

void	ms_set_env(char **env, char *value, t_cdata *t_cdata)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_splitc(value, '=');
	i = env_compare(env, arg, i);
	if (env[i] == NULL)
	{
		t_cdata->envp = ms_matrix_add_line(env, value);
		ft_free_tab(arg);
		return ;
	}
	free(env[i]);
	value = ft_strdup(value);
	env[i] = value;
	ft_free_tab(arg);
}

void	set_pwd(char *arg, char *c, t_cdata *t_cdata)
{
	char	*str;

	str = ft_strjoin(arg, c);
	ms_set_env(t_cdata->envp, str, t_cdata);
	free(str);
}

int	built_cd(char *arg, t_cdata *t_cdata)
{
	char	str[PATH_MAX];

	if (arg == NULL)
	{
		arg = ms_get_env(t_cdata->envp, "HOME") + 5;
		if ((arg -5) == NULL)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
	}
	getcwd(str, sizeof(str));
	if (chdir(arg) == -1)
	{
		if (arg[0] == '\0')
			return (1);
		printf("cd %s : No such file or directory\n", arg);
		return (1);
	}
	set_pwd("OLDPWD=", str, t_cdata);
	getcwd(str, sizeof(str));
	set_pwd("PWD=", str, t_cdata);
	return (0);
}
