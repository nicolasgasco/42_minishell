#include "minishell.h"

// First expand quotes, then variables
void    ft_expansions(c_data *c_data)
{
	ft_expand_variables(c_data);
	// ft_expand_escaped(q_data);
}
