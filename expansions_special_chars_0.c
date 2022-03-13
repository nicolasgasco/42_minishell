#include "minishell.h"

int ft_special_chars_are_valid(c_data *c_data)
{
    if (ft_find_here_marker(c_data->line_expanded))
    {
        ft_print_here_doc_detected();
        // TODO nested loop for Here document
    }
    // TODO logic for << and >>
    if (ft_detect_special_characters(c_data))
        ft_print_special_char_detected(); // TBD
    else if (!ft_find_here_marker(c_data->line_expanded))
        ft_print_no_special_char_detected(); // TBD
    if (c_data->syntax_error)
    {
        ft_print_syntax_error(); // TBD
        return (0);
    }
    return (1);
}

/* Detect if pipes or redirections are present in the user input */
int ft_detect_special_characters(c_data *c_data)
{
	int     i;
    char    *str;

	i = 1;
    str = c_data->line_expanded;
    if (ft_found_special_character(str[0]))
    {
        if (!ft_found_invalid_character(str[1]))
            return (1);
        c_data->syntax_error = 1;
        return (0);
    }
    while (str[i + 1] != '\0')
	{
		if (ft_found_special_character(str[i]))
        {
            if (!ft_found_invalid_character(str[i + 1]) && !ft_found_invalid_character(str[i - 1]))
            return (1);
            c_data->syntax_error = 1;
            return (0);       
        }
        i++;
	}
    if (ft_found_special_character(str[i]))
    {
        if (!ft_found_invalid_character(str[i - 1]))
            return (1);
        c_data->syntax_error = 1;
        return (0);
    }
    return (0);
}
