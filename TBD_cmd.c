#include "minishell.h"

// Command is extracted from raw input
char    *ft_extract_cmd(char *line)
{
    int i;
    int y;
    char    *result;

    i = 0;
    y = 0;
    result = (char *)malloc(sizeof(char) * (ft_get_cmd_len(line) + 1));
    while (ft_isspace(line[i]) && line[i] != '\0')
            i++;
    while (!ft_isspace(line[i]) && line[i] != '\0')
    {
        result[y] = line[i]; 
        y++;
        i++;
    }
    result[y] = '\0';
    return (result);
}

// Calculate length of isolated command for malloc size
int ft_get_cmd_len(char *line)
{
    int i;
    int result;

    i = 0;
    result = 0;
    while (ft_isspace(line[i]) && line[i] != '\0')
        i++;
    while (!ft_isspace(line[i]) && line[i] != '\0')
    {
        i++;
        result++;
    }
    return (result);
}

void    ft_print_cmd(t_cdata *t_cdata)
{
    printf("\033[0;34m");
    printf("Command");
    printf("\033[0m");
    printf(":\n\t.%s.\n\n", t_cdata->cmd);
}