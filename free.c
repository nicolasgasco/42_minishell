#include "minishell.h"

void    ft_free_quotes_data(c_data *c_data)
{
    if (c_data)
    {
        //
    }
    // ft_deallocate_quotes_list(c_data->q_data->quotes_list);
}

// Linked list's nodes are deallocated one by one
void	ft_deallocate_quotes_list(struct s_node *quotes_list)
{
	struct s_node	*curr;
	struct s_node	*aux;

	curr = quotes_list;
	if (curr == NULL)
		 quotes_list = NULL;
	else
	{
		aux = curr;
		ft_deallocate_quotes_list(curr->next);
		free(curr->str);
		free(aux);
	}
}