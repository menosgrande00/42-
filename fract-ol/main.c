#include "fractol.h"

void	print_usage(void)
{
	printf("Usage: ./fractol [fractal_type] [optional parameters]\n");
	printf("Fraktal types:\n");
	printf("  mandelbrot\n");
	printf("  julia [real] [imag]   (default: -0.7 0.27015)\n");
	printf("\nExample: ./fractol julia -0.8 0.156\n");
	exit(0);
}

void	init_fractol(t_fractol *fractol, int type, int argc ,char **argv)
{
	fractol->type = type;
	fractol->zoom = 1.0;
	fractol->move_x = 0.0;
	fractol->move_y = 0.0;
	fractol->aspect_ratio = (double)WIDTH / (double)HEIGHT;
    fractol->max_iter = MAX_ITER;

	if (type == JULIA)
	{
		if (argv[2] && argv[3] && is_valid_double(argv[2]) && is_valid_double(argv[3]))
			fractol->julia_k = init_complex(ft_atof(argv[2]), ft_atof(argv[3]));
		else
		{
			printf("Error: No valid parameters were entered for the Julia.\n");
			print_usage();
		}
	}
	else if (type == MANDELBROT && argc != 2)
	{
		printf("Error: No valid parameters were entered for the Mandelbrot.\n");
		print_usage();
	}
	init_complex_plane(fractol);
}

int	init_mlx(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		return (0);
	
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "Fract'ol");
	if (!fractol->win)
		return (0);
	
	fractol->img.img_ptr = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!fractol->img.img_ptr)
		return (0);
	
	fractol->img.addr = mlx_get_data_addr(fractol->img.img_ptr, 
		&fractol->img.bits_per_pixel, 
		&fractol->img.line_length, 
		&fractol->img.endian);
	return (1);
}

void	cleanup(t_fractol *fractol)
{
	if (fractol->img.img_ptr)
		mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2)
		print_usage();
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		init_fractol(&fractol, MANDELBROT, argc, argv);
	else if (ft_strcmp(argv[1], "julia") == 0)
		init_fractol(&fractol, JULIA, argc, argv);
	else
		print_usage();
	if (!init_mlx(&fractol))
		cleanup(&fractol);
	draw_fractol(&fractol);
	mlx_key_hook(fractol.win, key_hook, &fractol);
	mlx_mouse_hook(fractol.win, mouse_hook, &fractol);
	mlx_hook(fractol.win, 17, 0, close_window, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}
