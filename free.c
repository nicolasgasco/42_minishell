#include "minishell.h"

void	ft_free_loop_data(c_data *c_data)
{
	// FREE TOKENS
	ft_free_quotes_data(c_data);
	ft_free_prompt_data(c_data);
	ft_free_line_data(c_data);
	ft_deallocate_tokens_list(&c_data->tokens_list);
}

void	ft_free_common_data(c_data *c_data)
{
	if (c_data)
	{
		// It is not used at the moment
	}
}

void    ft_free_quotes_data(c_data *c_data)
{
	ft_deallocate_quotes_list(&c_data->q_data->quotes_list);
	free(c_data->q_data->raw_input);
	free(c_data->q_data);
}

void	ft_free_prompt_data(c_data *c_data)
{
	free(c_data->p_data->prompt_text);
	free(c_data->p_data);
}

// Linked list's nodes are deallocated one by one
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

// Linked list's nodes are deallocated one by one
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
		free(aux->str);
		free(aux);
	}
}