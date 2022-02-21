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
			printf("export: '%s': not a valid identifier\n", arg);
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

void	ms_export_sort(c_data *c_data)
{
	int	i;

	i = 0;
	ft_sort_tab(c_data->envp_export);
	while (c_data->envp_export[i])
		printf("%s\n", c_data->envp_export[i++]);
}

void	ms_export_valid_arg(char *arg, char *strings, c_data *c_data)
{
	char	*string;

	if (ft_strchr(arg, '=') == NULL)
	{
		if (ms_get_env(c_data->envp_export, strings) == NULL)
			c_data->envp_export = ms_matrix_add_line(c_data->envp_export, arg);
	}
	else
	{
		string = ms_make_string(arg);
		if (ms_get_env(c_data->envp_export, strings) != NULL)
		{
			arg = ft_strdup(arg);
			ms_set_env(c_data->envp, arg, c_data);
			ms_set_env(c_data->envp_export, string, c_data);
			free(arg);
		}
		else
		{
			c_data->envp = ms_matrix_add_line(c_data->envp, arg);
			c_data->envp_export = ms_matrix_add_line(c_data->envp_export, string);
		}
		free(string);
	}
}

int built_export(char **arg, c_data *c_data)
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
		ms_export_valid_arg(arg[i], strings[0], c_data);
		ft_free_tab(strings);
		i++;
	}
if (arg[0] == NULL)
		ms_export_sort(c_data);
	return(ret);
}
