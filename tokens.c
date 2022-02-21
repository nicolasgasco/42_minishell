#include "minishell.h"

char    **ft_tokenize(char *line, c_data *c_data)
{
    char    **result;

    result = ft_split(line);
    c_data->cmd = result[0];
    return result;
}

void    ft_check_cmd(c_data *c_data)
{
    if (ft_strncmp(c_data->cmd, "echo", 4) == 0)
	    built_echo(c_data->tokens);
    else if (ft_strncmp(c_data->cmd, "cd", 2) == 0)
	    built_cd(c_data->tokens[1], c_data);
    else if (ft_strncmp(c_data->cmd, "pwd", 3) == 0)
	    built_pwd();
    else if (ft_strncmp(c_data->cmd, "export", 6) == 0)
	    built_export(c_data->tokens + 1, c_data);
    else if (ft_strncmp(c_data->cmd, "unset", 5) == 0)
	    built_unset(c_data->tokens + 1, c_data);
    else if (ft_strncmp(c_data->cmd, "env", 3) == 0)
	    built_envp(c_data);
    else if (ft_strncmp(c_data->cmd, "exit", 4) == 0)
        exit(1);
    else
        printf("Unknown command\n");
}
