#include "minishell.h"

void    ft_output_epic_welcome(c_data *c_data)
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
    printf("%s", c_data->p_data->username);
    printf("\033[0m");
    printf(", you are now in charge. Good Luck.\n");
    printf("\n__________________________________________________________________________\n\n");
}