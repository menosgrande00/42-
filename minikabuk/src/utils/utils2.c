#include "minishell.h"

int	is_numeric(const char *str)
{
	int i;

    i = 0;
	if (!str || !str[0])
		return (1);
	while (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return(1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}