#include "fractol.h"

int	mandelbrot(t_complex c, t_fractol *fractol)
{
	t_complex	z;
	int			i;
	double		temp;

	z.real = 0;
	z.imag = 0;
	i = 0;
	
	while (i < fractol->max_iter)
	{
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		if (z.real * z.real + z.imag * z.imag > 4)
			return (i);
		i++;
	}
	return (fractol->max_iter);
}

int	julia(t_complex z, t_complex k, t_fractol *fractol)
{
	int			i;
	double		temp;

	i = 0;
	while (i < fractol->max_iter)
	{
		temp = z.real * z.real - z.imag * z.imag + k.real;
		z.imag = 2 * z.real * z.imag + k.imag;
		z.real = temp;
		if (z.real * z.real + z.imag * z.imag > 4)
			return (i);
		i++;
	}
	return (fractol->max_iter);
}
