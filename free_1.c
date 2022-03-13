#include "minishell.h"

/* Linked list's nodes are deallocated one by one */
void	ft_deallocate_quotes_list(struct q_node **quotes_list)
{
	struct q_node	*curr;
	struct q_node	*aux;
	
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

/* Linked list's nodes are deallocated one by one */
void	ft_deallocate_tokens_list(struct t_node **token_list)
{
	struct t_node	*curr;
	struct t_node	*aux;
	
	curr = *token_list;
	if (curr == NULL)
		 *token_list = NULL;
	else
	{
		aux = curr;
		ft_deallocate_tokens_list(&curr->next);
		// free(aux->str);
		free(aux);
	}
}
