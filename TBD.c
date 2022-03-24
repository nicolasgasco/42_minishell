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

// This is here only for series of ifs at the end, in case needed in the future
void ft_tokenize_quotes_TDB(t_qdata *t_qdata)
{
	int i;

	if (t_qdata->raw_input[0] == '\'')
		t_qdata->s_open = 1;
	else if (t_qdata->raw_input[0] == '\"')
		t_qdata->d_open = 1;
	i = 1;
	while (t_qdata->raw_input[i] != '\0')
	{
		if (t_qdata->raw_input[i] == '\'' && t_qdata->d_open == 0)
			ft_tokenization_logic(t_qdata, t_qdata->raw_input, i, '\'');
		else if (t_qdata->raw_input[i] == '\"' && t_qdata->s_open == 0)
			ft_tokenization_logic(t_qdata, t_qdata->raw_input, i, '\"');
		i++;
	}
	if (t_qdata->d_open)
		ft_add_node_quotes(t_qdata, i, '\0');
	else if (t_qdata->s_open)
		ft_add_node_quotes(t_qdata, i, '\0');
	else if (t_qdata->start == 0 || t_qdata->start != i)
		ft_add_node_quotes(t_qdata, i, '\0');
	ft_prune_starting_node(&t_qdata->quotes_list);
}

// First block of list is always empty and must pruned
void	ft_prune_starting_node(struct s_qnode **root)
{
	struct s_qnode	*to_remove;

	if (root == NULL)
		return ;
	to_remove = *root;
	*root = (*root)->next;
	free(to_remove->str);
	free(to_remove);
	return ;
}

// 2/2 Linked list containing single token information
void	ft_init_quotes_list(t_cdata *t_cdata)
{
	if (t_cdata)
	{
		//
	}
	// t_cdata->t_qdata->quotes_list = malloc(sizeof(struct s_qnode));
	// memset(t_cdata->t_qdata->quotes_list, 0, sizeof(struct s_qnode));
	// t_cdata->t_qdata->quotes_list->next = NULL;
	// t_cdata->t_qdata->quotes_list->length = 0;
	// t_cdata->t_qdata->quotes_list->str = "";
}

// 1/2 Linked list is iterated to expand escaped characters
void	ft_expand_escaped(t_qdata *t_qdata)
{
    struct s_qnode	*curr;
	
	curr = t_qdata->quotes_list;
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

// void	ft_init_line_data(t_cdata *t_cdata)
// {
// 	t_cdata = malloc(sizeof(l_data));
// 	memset(t_cdata, 0, sizeof(l_data));
// }

void	ft_free_line_data(t_cdata *t_cdata)
{
	// free(t_cdata->line_expanded);
	free(t_cdata->tokens);
	free(t_cdata->cmd);
}

// Checks if all quotes are properly closed. If not, another prompt is shown
int ft_are_quotes_unclosed(char *line)
{
    int     i;
    int     word_open;

    i = 0;
    word_open = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '\'')
        {
            if (i > 0 && line[i - 1] == '\\')
            {
                if (word_open == 1)
                    word_open = 0;
            }
            else
            {
                if (word_open == 0)
                    word_open = 1;
                else if (word_open == 1)
                    word_open = 0;
            }
        }
        i++;
    }
    return (word_open);
}

// Remove character specified by index, NO FREE
char    *ft_remove_char_index(char *line, int index)
{
    int i;
    int y;
    char *result;

    result = (char *)malloc(sizeof(char) * (ft_strlen(line) - 1 + 1));
    i = 0;
    y = 0;
    while (line[i] != '\0')
    {
        if (i != index)
        {
            result[y] = line[i];
            y++;
        }
        i++;
    }
    result[y] = '\0';
    return (result);
}

void	ft_free_loop_data_quotes_error(t_cdata *t_cdata)
{
	ft_free_quotes_data(t_cdata);
	// free(t_cdata->line_expanded);
}