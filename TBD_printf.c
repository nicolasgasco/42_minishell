#include "minishell.h"

// void    ft_print_expanded_output(t_cdata *t_cdata)
// {
//     printf("\033[0;34m");
//     printf("Expanded input");
//     printf("\033[0m");
//     printf(":\n\t.%s.\n\n", t_cdata->line_expanded);
// }

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
	printf("List after ");
	printf("\033[0m");
    printf("\033[0;33m");
    printf("spaces");
    printf("\033[0m");
    printf("\033[0;34m");
	printf(" expansion");
	printf("\033[0m");
	printf(":\n");
    ft_print_quotes_list(t_cdata->t_qdata->quotes_list);
}

void    ft_print_after_empty_removal(t_cdata *t_cdata)
{
    printf("\033[0;34m");
	printf("List after removal of ");
	printf("\033[0m");
    printf("\033[0;33m");
    printf("empty");
    printf("\033[0m");
    printf("\033[0;34m");
	printf(" nodes");
	printf("\033[0m");
    printf(":\n");
    ft_print_quotes_list(t_cdata->t_qdata->quotes_list);
}

void    ft_print_after_quotes_expansion(t_cdata *t_cdata)
{
	printf("\033[0;34m");
	printf("List after ");
	printf("\033[0m");
    printf("\033[0;33m");
    printf("quotes");
    printf("\033[0m");
    printf("\033[0;34m");
	printf(" expansion");
	printf("\033[0m");
	printf(":\n");
	ft_print_quotes_list(t_cdata->t_qdata->quotes_list);
}

void    ft_print_after_variables_expansion(t_cdata *t_cdata)
{
	printf("\033[0;34m");
	printf("List after ");
	printf("\033[0m");
    printf("\033[0;33m");
    printf("variables");
    printf("\033[0m");
    printf("\033[0;34m");
	printf(" expansion");
	printf("\033[0m");
	printf(":\n");
	ft_print_quotes_list(t_cdata->t_qdata->quotes_list);
}

void    ft_print_after_special_chars_expansion(t_cdata *t_cdata)
{
	printf("\033[0;34m");
	printf("List after ");
	printf("\033[0m");
    printf("\033[0;33m");
    printf("special chars");
    printf("\033[0m");
    printf("\033[0;34m");
	printf(" expansion");
	printf("\033[0m");
	printf(":\n");
	ft_print_quotes_list(t_cdata->t_qdata->quotes_list);
}

void    ft_print_new_input_header(char *line_read)
{
    if (*line_read)
    {
        printf("\n\n--------------------------------------------------------------------------\n");
        printf("                               New input");
        printf("\n--------------------------------------------------------------------------\n\n");
        printf("\033[0;34m");
        printf("Raw input");
        printf("\033[0m");
        printf(":\n\t.%s.\n\n", line_read);
    }
    else
    {
        printf("\033[0;34m");
        printf("\nEmpty input.\n\n");
        printf("\033[0m");   
    }
}

void    ft_print_quotes_list(struct s_qnode *list)
{
	struct s_qnode	*curr;
	int				i;
	
	i = 0;
	curr = list;
	while (1)
	{
        printf("\t%d) .%s. [%c] \t\t(%d chars)\n", i, curr->str, curr->q_type, curr->length);
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
		i++;
	}
    printf("\n");
}

void    ft_print_cmd(t_cdata *t_cdata)
{
    printf("\033[0;34m");
    printf("Command");
    printf("\033[0m");
    printf(":\n\t.%s.\n\n", t_cdata->cmd);
}

void    ft_output_epic_welcome(t_cdata *t_cdata)
{
    printf("\033[0;36m");
    printf("\n||WAR MACHINE IS READY||\n\n");
    printf("\033[0m");
    printf("Project Minishell.\n\n");
    printf("Made with love by ");
    printf("\033[0;33m");
    printf("NICO GASCO");
    printf("\033[0m");
    printf(" & ");
    printf("\033[0;33m");
    printf("TONI DEL CORRAL");
    printf("\033[0m");
    printf(".\n\n");
    printf("Welcome ");
    printf("\033[0;33m");
    printf("%s", t_cdata->t_pdata->username);
    printf("\033[0m");
    printf(", you are now in charge. Good Luck.\n");
    printf("\n__________________________________________________________________________\n\n");
}

void    ft_print_tokens_list(struct s_tnode *list)
{
	struct s_tnode	*curr;
	int				i;
	
	i = 0;
	curr = list;
	printf("\033[0;34m");
	printf("Tokens list");
	printf("\033[0m");
	printf(":\n");
	while (1)
	{
		if (curr->prev)
        	printf("\t%d) .%s. [%c] (%d chars) [Prev->str is .%s.]\n", i, curr->str, curr->q_type, curr->len, curr->prev->str);
		else
			printf("\t%d) .%s. [%c] (%d chars) [Prev is NULL]\n", i, curr->str, curr->q_type, curr->len);
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
		i++;
	}
    printf("\n");
}