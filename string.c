#include "minishell.h"

int    ft_count_char(char c, char *line, int start)
{
    int i;
    int counter;

    i = start;
    counter = 0;
    while (line[i] != '\0')
    {
        if (line[i] == c)
            counter++;
        i++;
    }
    return (counter);
}

char    *ft_remove_char(char c, char *line, int start)
{
    int i;
    int y;
    int len;
    char *result;

    len = ft_strlen(line);
    result = malloc(sizeof(char) * (len - ft_count_char(c, line, start) + 1));
    i = 0;
    y = 0;
    while (line[i] != '\0')
    {
        if (line[i] != c || i < start || y < start)
        {
            result[y] = line[i];
            y++;
        }
        i++;
    }
    result[y] = '\0';
    free(line);
    return (result);
}

char *ft_remove_char_index(int index, char *line)
{
    int     i;
    int     y;
    int     len;
    char    *result;

    len = ft_strlen(line);
    result = malloc(sizeof(char) * (len - 1 + 1));
    i = 0;
    y = 0;
    while (line[i] != '\0')
    {
        if (i != index)
        {
            result[y] = line[i];
            y++;
        }
        i++;
    }
    result[y] = '\0';
    free(line);
    return (result);
}