/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_spaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:32:24 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/29 11:32:26 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Keep removing spaces untill all are expanded */
void	ft_expand_spaces(t_cdata *t_cdata)
{
	while (1)
	{
		if (!ft_found_space_to_split(t_cdata))
			break ;
	}
	ft_print_after_spaces_expansion(t_cdata);
}

/* Iterate list looking for a space */
int	ft_found_space_to_split(t_cdata *t_cdata)
{
	struct s_qnode	*curr;
	int				found_space;

	found_space = 0;
	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		if (!curr->q_type)
		{
			curr->str = ft_strtrim_free(curr->str, " \t\r\n\v\f");
			curr->length = ft_strlen(curr->str);
			if (ft_has_spaces(curr->str))
			{
				found_space = 1;
				ft_split_and_generate_spaced_node(curr);
				break ;
			}
		}
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
	return (found_space);
}

/* Split string and generate a new node with expanded spaces */
void	ft_split_and_generate_spaced_node(struct s_qnode *curr)
{
	char			*token;
	char			*rest;
	int				t_len;
	struct s_qnode	*new_node;

	new_node = (struct s_qnode *)malloc(sizeof(struct s_qnode));
	memset(new_node, 0, sizeof(struct s_qnode));
	t_len = ft_calc_spaces_token_len(curr->str);
	token = (char *)malloc(sizeof(char) * t_len + 1);
	ft_strlcpy(token, curr->str, t_len + 1);
 	rest = ft_create_rest_str(curr->str, t_len);
	free(curr->str);
	curr->str = token;
	curr->length = ft_strlen(token);
	new_node->str = rest;
	new_node->length = ft_strlen(rest);
	new_node->next = curr->next;
	curr->next = new_node;
}

/* Utility function to create rest string without leaks */
char	*ft_create_rest_str(char *curr_str, int t_len)
{
	char	*result;
	char	*temp;

	temp = ft_substr(curr_str, t_len, ft_strlen(curr_str) - t_len);
	result = ft_strtrim(temp, " \t\r\n\v\f");
	free(temp);
	return (result);
}
