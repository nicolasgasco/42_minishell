#include "minishell.h"

// Method to add a new node to the linked list containing the tokenized raw input
void ft_add_node_quotes(q_data *q_data, int end, int quoted, char quote)
{
	struct s_node *new_node;
	struct s_node *curr;
	int i;

	curr = q_data->quotes_list;
	new_node = malloc(sizeof(struct s_node));
	if (new_node == NULL)
		exit(1);
	new_node->str = ft_substr(q_data->raw_input, q_data->start, end - q_data->start);
	new_node->length = end - q_data->start;
	new_node->quoted = quoted;
	new_node->q_type = quote;
	new_node->next = NULL;
	i = 0;
	while (curr->next != NULL)
	{
		curr = curr->next;
		i++;
	}
	if (!new_node->q_type)
		printf("Quotes | | in node n. %d: |%s|\n", i, new_node->str);
	else
		printf("Quotes |%c| in node n. %d: |%s|\n", new_node->q_type, i, new_node->str);
	curr->next = new_node;
}

char	*ft_convert_list_to_str(q_data *q_data)
{
	struct s_node	*curr;
	char			*result;
	int				i;
	
	i = 0;
	curr = q_data->quotes_list;
	result = ft_strdup(curr->str);
	if (curr->next)
		curr = curr->next;
	while (curr->next != NULL)
	{
		printf("%d: |%s|\n", i, curr->str);
		curr = curr->next;
		if (curr == NULL)
			printf("%d: |%s|\n", i, curr->str);
		i++;
	}
	if (q_data)
		printf("Ciao\n");
	return (result);
}

// First block of list is always empty and must pruned
void	ft_prune_starting_node(struct s_node **root)
{
	struct s_node	*to_remove;

	if (root == NULL)
		return ;
	to_remove = *root;
	*root = (*root)->next;
	free(to_remove);
	return ;
}