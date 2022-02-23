#include "minishell.h"
void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
int	env_compare(char **env, char **arg, int i)
{
	char	**split;

	while(env[i])
	{
		split = ft_splitc(env[i], '=');
		if (ft_strcmp(split[0], arg[0]) == 0)
		{
			ft_free_tab(split);
			break;
		}
		i++;
		ft_free_tab(split);
	}
	return(i);
}

char	**ms_matrix_add_line(char **matrix, char *new_line)
{
	int	i;
	char	**new_matrix;

	i = 0;
	while(matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while(matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = ft_strdup(new_line);
	i++;
	new_matrix[i] = NULL;
	ft_free_tab(matrix);
	return(new_matrix);
}

char	*ms_get_env(char **env, char *str)
{
	int	i;
	char	**split;

	i = 0;
	while(env[i])
	{
		split = ft_splitc(env[i], '=');
		if (ft_strcmp(split[0], str) == 0)
		{
			ft_free_tab(split);
			break;
		}
		else
			i++;
		ft_free_tab(split);
	}
	if (env[i] == NULL)
		return(NULL);
	return(env[i]);
}

void	ms_set_env(char **env, char *value, c_data *c_data)
{
	int	i;
	char	**arg;

	i = 0;
	arg = ft_splitc(value, '=');
	i = env_compare(env, arg, i);
	if(env[i] == NULL)
	{
		c_data->envp = ms_matrix_add_line(env, value);
		ft_free_tab(arg);
		return ;
	}
	free(env[i]);
	value = ft_strdup(value);
	env[i] = value;
	ft_free_tab(arg);
}




void	 set_pwd(char *arg, char *c, c_data *c_data)
{
	char *str;
	printf("hi\n");
	str = ft_strjoin(arg, c);
	printf("HOLA\n");
	ms_set_env(c_data->envp, str, c_data);
	free(str);
}

int	built_cd(char *arg, c_data *c_data)
{
	char str[PATH_MAX];
	printf("arg es %s\n", arg);

	if (arg == NULL)
	{
		arg = ms_get_env(c_data->envp, "HOME") + 5;
		printf("arg es %s\n", arg);
		if ((arg -5) == NULL)
		{
			printf("cd: HOME not set\n");
			return(1);
		}
	}
	getcwd(str, sizeof(str));
	printf("current directory is %s\n", str);
	if (chdir(arg) == -1)
	{
		if (arg[0] == '\0')
			return (1);
		printf("cd %s : No such file or directory\n", arg);
		return(1);
	}
	set_pwd("OLDPWD=", str, c_data);
	getcwd(str, sizeof(str));
	set_pwd("PWD=", str, c_data);
	return(0);
}

