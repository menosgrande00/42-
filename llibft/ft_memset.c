#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
#include <stdio.h>
int main()
{
	char s[6];
	*s = 'h';
	*(s + 1) = 'e';
	*(s + 2) = 'l';
	*(s + 3) = 'l';
	*(s + 4) = 'o';
	*(s + 5) = '\0';
	
	printf("%s", (char *)ft_memset(s, 321 , 4));
}