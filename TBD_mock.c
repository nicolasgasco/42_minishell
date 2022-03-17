#include "minishell.h"
#include <stdarg.h>

// Pass a variable number of arguments, last one must always be empty string
void ft_create_mock_list(t_cdata *t_cdata, char *str, ...)
{
    va_list args;
    char    *arg;

	va_start(args, str);
    ft_add_node_mock_list(t_cdata, ft_extract_cmd(t_cdata->line_expanded));
    while (1)
    {
        arg = va_arg(args, char *);
        if (arg[0] == '\0')
            break;
        ft_add_node_mock_list(t_cdata, arg);
    }
    va_end(args);
}

void    ft_add_node_mock_list(t_cdata *t_cdata, char *str)
{
    struct s_tnode *new_node;
	struct s_tnode *curr;

	curr = t_cdata->tokens_list;
	new_node = (struct s_tnode *)malloc(sizeof(struct s_tnode));
	new_node->str = ft_strdup(str);
	new_node->next = NULL;
    while (curr && curr->next != NULL)
	{
		curr = curr->next;
	}
	if (curr)
		curr->next = new_node;
	else
		t_cdata->tokens_list = new_node;
}


void    ft_print_tokens_list(struct s_tnode *list)
{
	struct s_tnode	*curr;
	int				i;
	
	i = 0;
	curr = list;
	printf("\033[0;34m");
	printf("Tokens list");
	printf("\033[0m");
	printf(":\n");
	while (1)
	{
        printf("\t%d) .%s.\n", i, curr->str);
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
		i++;
	}
    printf("\n");
}