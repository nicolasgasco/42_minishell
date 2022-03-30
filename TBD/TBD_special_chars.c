#include "minishell.h"

// int	ft_special_chars_are_valid(t_cdata *t_cdata)
// {
// 	// if (ft_detect_special_chars(t_cdata))
// 	// 	ft_print_special_char_detected(); // TBD
// 	// else
// 	// 	ft_print_no_special_char_detected(); // TBD
// 	if (t_cdata->syntax_error)
// 	{
// 		ft_print_syntax_error(); // TBD
// 		return (0);
// 	}
// 	return (1);
// }


/* Loof for a Here document structure in each string of the quotes linked list */
int ft_find_here_marker_list(t_cdata *t_cdata)
{
    struct s_qnode	*curr;

    curr = t_cdata->t_qdata->quotes_list;
    while (1)
    {
        if (curr->q_type != '\'')
        {
            if (ft_find_here_marker_str(curr->str))
                return (1);
        }
        if (curr->next == NULL)
            break;
        else
            curr = curr->next;
    }	
    return (0);
}