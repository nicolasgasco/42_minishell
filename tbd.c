#include "minishell.h"

// All functions in this file will be deleted

void    ft_print_array(char **str_array)
{
    int i;

    i = 0;
    printf("Tokens: ");
    while (*(str_array + i))
    {
        printf("|%s| ", str_array[i]);
        i++;
    }
    printf("\n");
}


int    ft_count_char(char c, char *line, int start)
{
    int i;
    int counter;

    i = start;
    counter = 0;
    while (line[i] != '\0')
    {
        if (line[i] == c)
            counter++;
        i++;
    }
    return (counter);
}

char    *ft_remove_char(char c, char *line, int start)
{
    int i;
    int y;
    int len;
    char *result;

    len = ft_strlen(line);
    result = malloc(sizeof(char) * (len - ft_count_char(c, line, start) + 1));
    i = 0;
    y = 0;
    while (line[i] != '\0')
    {
        if (line[i] != c || i < start || y < start)
        {
            result[y] = line[i];
            y++;
        }
        i++;
    }
    result[y] = '\0';
    free(line);
    return (result);
}

void    ft_print_linked_list(q_data *q_data)
{
	struct s_node	*curr;
	int				i;
	
	i = 0;
	curr = q_data->quotes_list;
	while (1)
	{
        printf("|%s| ", curr->str);
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
		i++;
	}
    printf("\n");
}

// This is here only for series of ifs at the end, in case needed in the future
void ft_tokenize_quotes_TDB(q_data *q_data)
{
	int i;

	if (q_data->raw_input[0] == '\'')
		q_data->s_open = 1;
	else if (q_data->raw_input[0] == '\"')
		q_data->d_open = 1;
	i = 1;
	while (q_data->raw_input[i] != '\0')
	{
		if (q_data->raw_input[i] == '\'' && q_data->d_open == 0)
			ft_tokenization_logic(q_data, q_data->raw_input, i, '\'');
		else if (q_data->raw_input[i] == '\"' && q_data->s_open == 0)
			ft_tokenization_logic(q_data, q_data->raw_input, i, '\"');
		i++;
	}
	if (q_data->d_open)
		ft_add_node_quotes(q_data, i, '\0');
	else if (q_data->s_open)
		ft_add_node_quotes(q_data, i, '\0');
	else if (q_data->start == 0 || q_data->start != i)
		ft_add_node_quotes(q_data, i, '\0');
	ft_prune_starting_node(&q_data->quotes_list);
}

// First block of list is always empty and must pruned
void	ft_prune_starting_node(struct s_node **root)
{
	struct s_node	*to_remove;

	if (root == NULL)
		return ;
	to_remove = *root;
	*root = (*root)->next;
	free(to_remove->str);
	free(to_remove);
	return ;
}

// 2/2 Linked list containing single token information
void	ft_init_quotes_list(c_data *c_data)
{
	if (c_data)
	{
		//
	}
	// c_data->q_data->quotes_list = malloc(sizeof(struct s_node));
	// memset(c_data->q_data->quotes_list, 0, sizeof(struct s_node));
	// c_data->q_data->quotes_list->next = NULL;
	// c_data->q_data->quotes_list->length = 0;
	// c_data->q_data->quotes_list->str = "";
}

// 1/2 Linked list is iterated to expand escaped characters
void	ft_expand_escaped(q_data *q_data)
{
    struct s_node	*curr;
	
	curr = q_data->quotes_list;
	while (1)
	{
        if (curr->q_type == '\"')
			curr->str = ft_remove_escaped_from_str(curr->str);
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
	}
}

// 2/2 Inside double quotes, escape character works only with %, `, ", \, and \n; inside single quotes, it's ignored 
char	*ft_remove_escaped_from_str(char *str)
{
	int	i;
	char	*result;

	i = 0;

	result = ft_strdup(str);
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			if (str[i + 1] == '$' || str[i + 1] == '`' || str[i + 1] == '\"'
			|| str[i + 1] == '\\' || str[i + 1] == '\n')
			{
				result = ft_remove_char_index(str, i);
				break;
			}
		}
		if (str[i + 2] == '\0')
			break;
		i++;
	}
	free(str);
	return (result);
}
