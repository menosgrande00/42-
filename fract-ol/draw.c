#include "fractol.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	init_complex_plane(t_fractol *fractol)
{
	if (fractol->type == MANDELBROT)
	{
		fractol->min_real = -2.0;
		fractol->max_real = 1.0;
		fractol->min_imag = -1.5;
		fractol->max_imag = 1.5;
	}
	else if (fractol->type == JULIA)
	{
		fractol->min_real = -2.0;
		fractol->max_real = 2.0;
		fractol->min_imag = -2.0;
		fractol->max_imag = 2.0;
	}
	double range_real = fractol->max_real - fractol->min_real;
	double range_imag = fractol->max_imag - fractol->min_imag;
	double target_ratio = fractol->aspect_ratio;
	double current_ratio = range_real / range_imag;
	if (current_ratio < target_ratio)
	{
		double new_range_real = range_imag * target_ratio;
		double center = (fractol->min_real + fractol->max_real) / 2.0;
		fractol->min_real = center - new_range_real / 2.0;
		fractol->max_real = center + new_range_real / 2.0;
	}
	else
	{
		double new_range_imag = range_real / target_ratio;
		double center = (fractol->min_imag + fractol->max_imag) / 2.0;
		fractol->min_imag = center - new_range_imag / 2.0;
		fractol->max_imag = center + new_range_imag / 2.0;
	}
}

t_complex get_complex_coord(int x, int y, t_fractol *fractol)
{
    t_complex c;
    
    c.real = fractol->min_real + (double)x / WIDTH * (fractol->max_real - fractol->min_real);
    c.imag = fractol->min_imag + (double)y / HEIGHT * (fractol->max_imag - fractol->min_imag);
    return (c);
}

void	draw_fractol(t_fractol *fractol)
{
	int			x;
	int			y;
	t_complex	c;
	int			iterations;

	y = 0;
	while (y++ < HEIGHT)
	{
		x = 0;
		while (x++ < WIDTH)
		{
			c = get_complex_coord(x, y, fractol);
			if (fractol->type == MANDELBROT)
				iterations = mandelbrot(c, fractol);
			else if (fractol->type == JULIA)
				iterations = julia(c, fractol->julia_k, fractol);
			else
				iterations = 0;
			my_mlx_pixel_put(&fractol->img, x, y, create_color(iterations, fractol->max_iter));
		}
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0, 0);
}
