#include "fractol.h"

int	key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
	{
		if (fractol->img.img_ptr)
			mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
		if (fractol->win)
			mlx_destroy_window(fractol->mlx, fractol->win);
		exit(0);
	}
    else if (keycode == 27)
    {
        fractol->max_iter += 10;
        draw_fractol(fractol);
    }
    else if (keycode == 24)
    {
        if (fractol->max_iter > 10)
            fractol->max_iter -= 10;
        draw_fractol(fractol);
    }
    return (0);
}

int mouse_hook(int button, int x, int y, t_fractol *fractol)
{
    t_complex mouse;
    double zoom_factor;

    if (button != MOUSE_SCROLL_UP && button != MOUSE_SCROLL_DOWN)
        return (0);

    mouse = get_complex_coord(x, y, fractol);

    zoom_factor = (button == MOUSE_SCROLL_UP) ? 1.0 / ZOOM_FACTOR : ZOOM_FACTOR;

    fractol->min_real = mouse.real - (mouse.real - fractol->min_real) * zoom_factor;
    fractol->max_real = mouse.real + (fractol->max_real - mouse.real) * zoom_factor;
    fractol->min_imag = mouse.imag - (mouse.imag - fractol->min_imag) * zoom_factor;
    fractol->max_imag = mouse.imag + (fractol->max_imag - mouse.imag) * zoom_factor;

    draw_fractol(fractol);
    return (0);
}

int	close_window(t_fractol *fractol)
{
	if (fractol->img.img_ptr)
		mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	exit(0);
	return (0);
}
