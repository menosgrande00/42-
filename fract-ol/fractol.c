#include "fractol.h"

int main(int ac, char **av)
{
	t_fractal	fractal;
	if(ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10) 
		|| ac == 4 && !ft_strncmp(av[1], "julia", 5))
	{
		fractal.name = av[1];
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = atodbl(av[2]);
			fractal.julia_y = atodbl(av[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	return (0);
}