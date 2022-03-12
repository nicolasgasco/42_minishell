#include "minishell.h"

void    ft_output_epic_welcome(c_data *c_data)
{
    printf("\n||WAR MACHINE IS READY||\n\n");
    printf("Project Minishell.\n\n");
    printf("Made with love by NICO GASCO & TONI DEL CORRAL.\n\n");
    printf("Welcome %s, you are now in charge. Good Luck.\n\n", c_data->p_data->username);
}