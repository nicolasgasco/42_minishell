#include "minishell.h"

void	ft_free_all(c_data *c_data)
{
	ft_deallocate_quotes_list(&c_data->q_data->quotes_list);
	free(c_data->q_data->raw_input);
	free(c_data->q_data);
	free(c_data->p_data->prompt_text);
	free(c_data->p_data);
	free(c_data->line_expanded);
}

void    ft_free_quotes_data(c_data *c_data)
{
    if (c_data)
    {
        //
    }

}

// Linked list's nodes are deallocated one by one
void	ft_deallocate_quotes_list(struct s_node **quotes_list)
{
	struct s_node	*curr;
	struct s_node	*aux;
	
	curr = *quotes_list;
	if (curr == NULL)
		 *quotes_list = NULL;
	else
	{
		aux = curr;
		ft_deallocate_quotes_list(&curr->next);
		free(aux->str);
		free(aux);
	}
}