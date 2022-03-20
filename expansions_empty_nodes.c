#include "minishell.h"

void    ft_remove_empty_nodes(t_cdata *t_cdata)
{
    while (1)
    {
        if (!found_empty_node_to_remove(t_cdata))
            break;
    }
    ft_print_after_empty_removal(t_cdata);
}

/* Removing a single node contaning an empty string */
int    found_empty_node_to_remove(t_cdata *t_cdata)
{
    struct s_qnode  *curr;
    int i;

    i = 0;
    curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
        if (!*(curr->str))
        {
            ft_remove_node_with_index(i, &t_cdata->t_qdata->quotes_list);
            return (1);
        }
        if (curr->next == NULL)
            break ;
        curr = curr->next;
        i++;
	}
    return (0);
}

void    ft_remove_node_with_index(int index, struct s_qnode **root)
{
	struct s_qnode  *curr;
	struct s_qnode	*to_remove;
	int				i;

	i = 1;
	curr = *root;
	if (*root == NULL)
		return ;
	if (index == 0)
	{
		to_remove = *root;
		*root = (*root)->next;
        free(to_remove->str);
		free(to_remove);
		return ;
	}
	while (i < index)
	{
		curr = curr->next;
		i++;
	}
	to_remove = curr->next;
	curr->next = curr->next->next;
    free(to_remove->str);
	free(to_remove);
}
