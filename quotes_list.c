#include "minishell.h"

// struct s_node	*ft_create_quote_node(char *line, int start, int end);
// {
// 	struct s_node	*root;
	// int				i;

	// if (!num_arr)
	// 	return (NULL);
	// root = malloc(sizeof(struct s_node));
	// root->x = num_arr[0];
	// i = 1;
	// while (i < n)
	// {
	// 	ft_insert_end(&root, num_arr[i]);
	// 	i++;
	// }
	// return (root);
// }

// void	ft_insert_end(struct s_node **root, int value)
// {
// 	struct s_node	*new_node;
// 	struct s_node	*curr;

// 	new_node = malloc(sizeof(struct s_node));
// 	if (new_node == NULL)
// 		exit(1);
// 	new_node->next = NULL;
// 	new_node->x = value;
// 	if (*root == NULL)
// 		*root = new_node;
// 	curr = *root;
// 	while (curr->next != NULL)
// 		curr = curr->next;
// 	curr->next = new_node;
// }