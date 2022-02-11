#include "minishell.h"

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