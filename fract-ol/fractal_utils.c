#include "fractol.h"

double  map(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
	return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min;
}
t_point	sum_complex(t_point z1, t_point z2)
{
	t_point	res;

	res.real = z1.real + z2.real;
	res.i = z1.i + z2.i;
	return (res);
}
t_point	square_complex(t_point x)
{
	t_point		result;

	result.real = pow(x.real, 2) - pow(x.i, 2);
	result.i = 2 * (x.real * x.i);
	return (result);
}
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int i = 0;
	while(s1[i] || s2[i] && i < n)
	{
		if(s1[i] - s2[i] != 0)
			return(s1[i] - s2[i]);
		i++;
	}
	return (0);
}
double	atodb(char *s)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	sign = +1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || 32 == *s)
		++s;
	while ('+' == *s || '-' == *s)
		if ('-' == *s++)
			sign = -sign;
	while (*s != '.' && *s)
		integer_part = (integer_part * 10) + (*s++ - 48);
	if ('.' == *s)
		++s;
	while (*s)
	{
		pow /= 10;
		fractional_part = fractional_part + (*s++ - 48) * pow;
	}
	return ((integer_part + fractional_part) * sign);
}
