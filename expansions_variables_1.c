#include "minishell.h"

// 3a Isolate and create variable for variable name, e.g. PATH or USER
char *ft_get_var_name(char *str, int start, int end)
{
	char	*result;
	int		i;

	result = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!result)
		exit(1);
	i = 0;
	while (start < end)
	{
		result[i] = str[start];
		start++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

// 3b Take variable value and splice it into original str
char    *ft_splice_var_value(char *str, char *var, int start, int end)
{
    char    *result;
    int     i;
    int     y;
    int     x;

    i = 0;
    x = 0;
    result = (char *)malloc(sizeof(char) * (ft_strlen(str) - (end - start) + ft_strlen(var) + 1));
    while (str[i] != '\0')
    {
        result[x] = str[i];
        if (i == start)
        {
            y = 0;
            while (var[y] != '\0')
            {
                result[x] = var[y];
                y++;
                x++;
            }
        }
        i++;
        x++;
    }
    result[x] = '\0';
    return (result);
}

// 3c If variable value doesn't exist, just remove $VAR from string
char    *ft_remove_var_name(char *str, int start, int end)
{
    int     i;
    int     y;
    char    *result;

    result = (char *)malloc(sizeof(char) * (ft_strlen(str) - (end - start) + 1));
    i = 0;
    y = 0;
    while (str[i] != '\0')
    { 
        result[y] = str[i];
        if (i == (start - 1))
        {
            while (i < end)
                i++;
        }
        i++;
        y++;
    }
    result[y] = '\0';
    return (result);
}
