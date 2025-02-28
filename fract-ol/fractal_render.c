#include "fractol.h"
static void  my_pixel_put(int x, int y, t_image *img, int color)
{
	int	loc;

	loc = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + loc) = color;
}
static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_point	z;
	t_point	c;
	int 	i;
	int		color;

	i = 0;

	c.real = (map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x ;
	c.i = (map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;

	z.real = 0;
	z.i = 0;

	while (i < fractal->iterations_def)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.i * z.i) > fractal->escape_value)
		{
			color = map(i, BLACK, WHITE, 0, fractal->iterations_def);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	my_pixel_put(x, y, &fractal->img, BLACK);
}
void    fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			handle_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx_connection,
							fractal->mlx_window,
							fractal->img.img_ptr,
							0,0);
}