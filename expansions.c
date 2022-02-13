#include "minishell.h"

// First expand quotes, then variables
void    ft_expansions(q_data *q_data)
{
	ft_expand_variables(q_data);
	ft_expand_escaped(q_data);
}
