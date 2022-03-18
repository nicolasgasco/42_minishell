#include "minishell.h"

void    ft_output_loop_error_message(t_cdata *t_cdata, char *message)
{
    ft_free_quotes_data(t_cdata);
    printf("Syntax error: %s\n", message);
}
