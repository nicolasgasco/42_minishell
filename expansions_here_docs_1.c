#include "minishell.h"

/* Isolate delimiter from raw input */
char	*ft_extract_delim(t_cdata *t_cdata)
{
	int		i;
	char	*result;
	char	*raw_input;
	char	*raw_input_temp;

	raw_input = t_cdata->t_qdata->raw_input;
	i = 0;
	while (t_cdata->t_qdata->raw_input[i + 1] != '\0')
	{
		if (t_cdata->t_qdata->raw_input[i] == '<'
			&& t_cdata->t_qdata->raw_input[i] == '<')
		{
			i += 2;
			break ;
		}
		i++;
	}
	return (ft_remove_delim(t_cdata, i));
}

/* Remove delimiter from raw input */
char	*ft_remove_delim(t_cdata *t_cdata, int i)
{
	char	*result;
	char	*raw_input;
	char	*raw_input_temp;

	raw_input = t_cdata->t_qdata->raw_input;
	result = ft_substr(raw_input, i, ft_strlen(raw_input) - i);
	if (ft_has_spaces(result))
		result = ft_strtrim(result, " \t"); // Check
	raw_input_temp = ft_substr(raw_input, 0, i);
	free(t_cdata->t_qdata->raw_input);
	t_cdata->t_qdata->raw_input = raw_input_temp;
	return (result);
}
