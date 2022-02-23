
#include "libft.h"

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_tab(char **arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
				swap(&arr[i], &arr[j]);
			++j;
		}
		++i;
	}
}
