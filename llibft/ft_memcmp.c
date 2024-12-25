#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr1;

	if (n == 0)
		return (0);
	ptr = (unsigned char *)s1;
	ptr1 = (unsigned char *)s2;
	while ((*ptr == *ptr1) && n - 1 > 0)
	{
		ptr++;
		ptr1++;
		n--;
	}
	return ((int)(*ptr - *ptr1));
}
int main()
{
	int a[4] = {1 , 256 , 3, 4};
	int b[3];
	
	*b = 1;
	*(b + 1) = 0;
	*(b + 2) = 4;


	printf("%d", ft_memcmp(&a, &b, 6));
}