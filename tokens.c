#include "minishell.h"

// Command is extracted
char **ft_tokenize(c_data *c_data)
{
    char **result;

    result = ft_split(c_data->q_data->raw_input);
    c_data->cmd = result[0];
    return result;
}

// Depending on command, input is further processed
void ft_check_cmd(char *cmd)
{
    if (ft_strncmp(cmd, "echo", 4) == 0)
        printf("%s\n", cmd);
    else if (ft_strncmp(cmd, "cd", 2) == 0)
        printf("%s\n", cmd);
    else if (ft_strncmp(cmd, "pwd", 3) == 0)
        printf("%s\n", cmd);
    else if (ft_strncmp(cmd, "export", 6) == 0)
        printf("%s\n", cmd);
    else if (ft_strncmp(cmd, "unset", 5) == 0)
        printf("%s\n", cmd);
    else if (ft_strncmp(cmd, "env", 3) == 0)
        printf("%s\n", cmd);
    else if (ft_strncmp(cmd, "exit", 4) == 0)
        exit(1);
    else
        printf("Unknown command\n");
}