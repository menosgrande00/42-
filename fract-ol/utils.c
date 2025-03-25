#include "fractol.h"

t_complex	init_complex(double real, double imag)
{
	t_complex	c;

	c.real = real;
	c.imag = imag;
	return (c);
}

int create_color(int iterations, int max_iter)
{
    double  t;
    int     r;
    int     g;
    int     b;

    if (iterations == max_iter)
        return (0x000000);

    t = (double)iterations / max_iter;

    r = (int)(9 * (1 - t) * t * t * t * 255);
    g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

    r = fmin(255, fmax(0, r));
    g = fmin(255, fmax(0, g));
    b = fmin(255, fmax(0, b));

    return ((r << 16) | (g << 8) | b);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	is_valid_double(char *str)
{
	int	i;
	int	decimal_point;

	i = 0;
	decimal_point = 0;
	
	if (str[i] == '-' || str[i] == '+')
		i++;
		
	if (!str[i])
		return (0);
		
	while (str[i])
	{
		if (str[i] == '.')
		{
			decimal_point++;
			if (decimal_point > 1)
				return (0);
		}
		else if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

double	ft_atof(char *str)
{
	double	result;
	double	decimal;
	int		sign;
	int		i;
	double	divisor;

	result = 0.0;
	decimal = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		divisor = 10.0;
		while (str[i] >= '0' && str[i] <= '9')
		{
			decimal += (str[i] - '0') / divisor;
			divisor *= 10.0;
			i++;
		}
	}
	return (sign * (result + decimal));
}
