#include "cub3d.h"

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		i++;
	}
	return s1[i] - s2[i];
}

void	free_double(char **str)
{
	
}

void	ft_error(char *str)
{

}

int	in_range(int v)
{
	int i;

	if (v >= 0 && v <= 255)
		return (1);
	else
		return (0);
}