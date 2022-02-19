#include "minishell.h"

void	ft_expand_pipes(struct s_node *quotes_list)
{
    struct s_node *curr;

    curr = quotes_list;
    while (1)
    {
        printf("String is .%s.\n", curr->str);
        if (ft_found_pipe(curr->str) && !curr->q_type)
            printf("Found a pipe\n");
        if (curr->next)
            curr = curr->next;
        else
            break;
    }
}

int ft_found_pipe(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\0')
        return (0);
    if (str[i] == '|' && str[i + 1] != '|')
        return (1);
    while (str[i + 1] != '\0')
    {
        printf("%c\n", str[i]);
        if (str[i] == '|' && str[i + 1] != '|')
            return (1);
        i++;
    }
    if (str[i] == '|')
        return (1);
    return (0);
}