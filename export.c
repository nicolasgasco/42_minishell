#include "minishell.h"

int	ms_check_export_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		printf("export: '%s': not a valid identifier\n", arg);
		return(1);
	}
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if(ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			printf("export: '%s': not a valid identifier\n". arg);
			return(1);
		}
		i++;
	}
	return(0);
}

char	*ms_make_string(char *arg)
{
	char	**strings;
	char	*string;
	int	i;

	i = 1;
	strings = ft_splitcc(arg, '=');
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
	return(string);
}

void	ms_export_sort(void)
{
	int	i;

	i = 0;
	ft_sort_tab(env_export);
	while (env_export[i])
		printf("%s\n", env_export[i++]);
}

void	ms_export_valid_arg(char *arg, char *strings)
{
	char	*string;

	if (ft_strchr(arg, '=') == NULL)
	{
		if (ms_get_env(env_export, strings) != NULL)
		{
			arg = ft_strdup(arg);
			ms_set_env(env, arg);
			ms_set_env(env_export, string);
			free(arg);
		}
		else
		{
			env = ms_matrix_add_line(env, arg);
			env_export = ms_matrix_add_line(env_export, string);
		}
		free(string);
	}
}

int built_export(char **arg)
{
	char	**strings;
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while(arg[i])
	{
		if (ms_check_export_arg(arg[i]) != 0)
		{
			i++;
			continue ;
			ret = 1;
		}
		strings = ft_splitcc(arg[i], '=');
		ms_export_valid_arg(arg[i], strings[0]);
		ft_free_tab(strings);
		i++;
	}
	if (arg[0] == NULL)
		ms_export_sort();
	return(ret);
}
