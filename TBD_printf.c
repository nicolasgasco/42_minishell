#include "minishell.h"

void    ft_print_expanded_output(c_data *c_data)
{
    printf("\033[0;34m");
    printf("Expanded input");
    printf("\033[0m");
    printf(":\n\t|%s|\n\n", c_data->line_expanded);
}

void    ft_print_special_char_detected(void)
{
    printf("\033[0;33m");
    printf("Special character detected.\n\n");
    printf("\033[0m");
}

void    ft_print_syntax_error(void)
{
    printf("\033[0;31m");
    printf("Syntax error.\n");
    printf("\033[0m");
    printf("\n__________________________________________________________________________\n\n");
}

void    ft_print_no_special_char_detected(void)
{
    printf("\033[0;33m");
    printf("No special character detected.\n\n");
    printf("\033[0m");
}

void    ft_print_unclosed_quotes(void)
{
    printf("\033[0;33m");
    printf("Syntax error: Unclosed quotes\n");
    printf("\033[0m");
    printf("\n__________________________________________________________________________\n\n");
}