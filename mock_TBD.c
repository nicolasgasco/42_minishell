#include "minishell.h"
#include <stdarg.h>

// Pass a variable number of arguments, last one must always be empty string
void ft_create_mock_list(c_data *c_data, char *str, ...)
{
    va_list args;
    char    *arg;

	va_start(args, str);
    ft_add_node_mock_list(c_data, str);
    printf("....%s....\n", str);
    while (1)
    {
        arg = va_arg(args, char *);
        if (arg[0] == '\0')
            break;
        ft_add_node_mock_list(c_data, arg);
    }
    va_end(args);
}

void    ft_add_node_mock_list(c_data *c_data, char *str)
{
    struct s_node *new_node;
	struct s_node *curr;

	curr = c_data->tokens_list;
	new_node = malloc(sizeof(struct s_node));
	new_node->str = ft_strdup(str);
	new_node->length = ft_strlen(str);
	new_node->q_type = 'm';
	new_node->next = NULL;
    while (curr && curr->next != NULL)
	{
		curr = curr->next;
	}
	if (curr)
		curr->next = new_node;
	else
		c_data->tokens_list = new_node;
}