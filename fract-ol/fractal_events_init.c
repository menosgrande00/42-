#include "fractol.h"

int close_handler(t_fractal *fractal)
{
    mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
    mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
    //mlx_destroy_display
    free(fractal->mlx_connection);
    exit(EXIT_SUCCESS);
}

int key_handler(int keysym, t_fractal *fractal)
{
    if (keysym == 53)
        close_handler(fractal);
    printf("%d\n", keysym);
    if (keysym == 123)
        fractal->shift_x += (0.5 * fractal->zoom);
    else if (keysym == 124)
        fractal->shift_x -= (0.5 * fractal->zoom);
    else if (keysym == 126)
        fractal->shift_y -= (0.5 * fractal->zoom);
    else if (keysym == 125)
        fractal->shift_y += (0.5 * fractal->zoom);
    else if (keysym == 21)
        fractal->iterations_def += 10;
    else if (keysym == 24)
        fractal->iterations_def -= 10;
    else if (keysym == 15)
        fractal->zoom = 1;
    fractal_render(fractal);
    return (0);
}
int     mouse_handler(int button, int x, int y, t_fractal *fractal)
{
    if(button == 5)
    {
       fractal->zoom *= 0.95; 
    }
    else if(button == 4)
    {
       fractal->zoom *= 1.05;
    }

    printf("%d\n", button);
    fractal_render(fractal);
    return (0);
}