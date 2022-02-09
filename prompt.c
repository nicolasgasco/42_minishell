#include "minishell.h"

// Accepts user input
char	*rl_gets(char *line_read, char *prompt_text)
{
	char	*result;

	result = readline(prompt_text);
	if (line_read)
		result = ft_strjoin(line_read, result);
	if (result && *result)
		add_history(result);
	return (result);
}


// Check if the quotes (correctly expanded) are close or not. If not, new prompt line is shown
int ft_are_quotes_unclosed(char *line)
{
    int     i;
    int     word_open;

    i = 0;
    word_open = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '\'')
        {
            if (i > 0 && line[i - 1] == '\\')
            {
                if (word_open == 1)
                    word_open = 0;
            }
            else
            {
                if (word_open == 0)
                    word_open = 1;
                else if (word_open == 1)
                    word_open = 0;
            }
        }
        i++;
    }
    return (word_open);
}