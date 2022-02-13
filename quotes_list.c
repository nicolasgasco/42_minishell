#include "minishell.h"

// Method to add a new node to the linked list containing the tokenized raw input
void ft_add_node_quotes(q_data *q_data, int end, char quote)
{
	struct s_node *new_node;
	struct s_node *curr;
	int i;

	curr = q_data->quotes_list;
	new_node = malloc(sizeof(struct s_node));
	if (new_node == NULL)
		exit(1);
	if (end - q_data->start > 1)
		new_node->str = ft_create_quoted_token(q_data->raw_input, q_data->start, end - q_data->start);
	else
		new_node->str = ft_create_quoted_token_empty(q_data->raw_input, q_data->start);
	new_node->length = end - q_data->start;
	new_node->q_type = quote;
	new_node->next = NULL;
	i = 0;
	while (curr && curr->next != NULL)
	{
		curr = curr->next;
		i++;
	}
	if (!new_node->q_type)
		printf("Quotes | | in node n. %d: |%s|\n", i, new_node->str);
	else
		printf("Quotes |%c| in node n. %d: |%s|\n", new_node->q_type, i, new_node->str);
	if (curr)
		curr->next = new_node;
	else
		q_data->quotes_list = new_node;
}

// a) Actual token text is written into node ignoring quotes
char    *ft_create_quoted_token(char *input, int start, int len)
{
    char    *result;
    int     result_len;
    int     i;
    int     y;

    i = start;
    result_len = len;
    if (input[start + len - 1] == '\"' || input[start + len - 1] == '\'')
        result_len--;
    if (input[i] == '\"' || input[i] == '\'')
    {
        result_len--;
        i++;
    }
    y = 0;
    result = malloc(sizeof(char) * (result_len + 1));
    while (result_len != 0)
    {
        result[y] = input[i];
        i++;
        y++;
        result_len--;
    }
    result[y] = '\0';
    return (result);
}

// b) Actual token text is written into node ignoring quotes, case where empty set of quotes is given ""
char    *ft_create_quoted_token_empty(char *input, int start)
{
    char    *result;
    int     i;
    int     y;

    i = start;
    result = malloc(sizeof(char) * (ft_strlen(input) - 2 + 1));
    while (i < start)
    {
        result[y] = input[i];
        i++;
        y++;
    }
    result[y] = '\0';
    return (result);
}

// Iterate all nodes of linked lists and concatenate them in a string
char	*ft_convert_list_to_str(q_data *q_data)
{
	struct s_node	*curr;
	char			*result;
	int				i;
	
	i = 0;
	result = NULL;
	curr = q_data->quotes_list;
	while (1)
	{
		if (result == NULL)
			result = ft_strdup(curr->str);
		else
			result = ft_strcat(result, curr->str);
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
		i++;
	}
	return (result);
}
