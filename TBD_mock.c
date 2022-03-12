#include "minishell.h"
#include <stdarg.h>

// Pass a variable number of arguments, last one must always be empty string
void ft_create_mock_list(c_data *c_data, char *str, ...)
{
    va_list args;
    char    *arg;

	va_start(args, str);
    ft_add_node_mock_list(c_data, ft_extract_cmd(c_data->line_expanded));
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
    struct t_node *new_node;
	struct t_node *curr;

	curr = c_data->tokens_list;
	new_node = malloc(sizeof(struct t_node));
	new_node->str = ft_strdup(str);
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


void    ft_print_tokens_list(struct t_node *list)
{
	struct t_node	*curr;
	int				i;
	
	i = 0;
	curr = list;
	printf("\033[0;34m");
	printf("Tokens list");
	printf("\033[0m");
	printf(":\n");
	while (1)
	{
        printf("\t%d) \"%s\"\n", i, curr->str);
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
		i++;
	}
    printf("\n");
}