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
