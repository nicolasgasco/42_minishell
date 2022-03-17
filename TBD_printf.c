#include "minishell.h"

void    ft_print_expanded_output(t_cdata *t_cdata)
{
    printf("\033[0;34m");
    printf("Expanded input");
    printf("\033[0m");
    printf(":\n\t.%s.\n\n", t_cdata->line_expanded);
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

void    ft_print_here_doc_detected(void)
{
    printf("\033[0;33m");
    printf("Here document detected.\n\n");
    printf("\033[0m");
}

void    ft_print_unknown_command(void)
{
    printf("\033[0;31m");
    printf("Unknown command.\n");
    printf("\033[0m");
}

void    ft_print_after_spaces_expansion(t_cdata *t_cdata)
{
    printf("\033[0;34m");
	printf("List after space expansion");
	printf("\033[0m");
	printf(":\n");
    ft_print_quotes_list(t_cdata->t_qdata->quotes_list);
}

void    ft_print_after_quotes_expansion(t_cdata *t_cdata)
{
	printf("\033[0;34m");
	printf("List after quotes expansion");
	printf("\033[0m");
	printf(":\n");
	ft_print_quotes_list(t_cdata->t_qdata->quotes_list);
}

void    ft_print_after_variables_expansion(t_cdata *t_cdata)
{
	printf("\033[0;34m");
	printf("List after variables expansion");
	printf("\033[0m");
	printf(":\n");
	ft_print_quotes_list(t_cdata->t_qdata->quotes_list);
}