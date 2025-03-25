#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"

# define WIDTH 800
# define HEIGHT 800

# define KEY_ESC 53

# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define MANDELBROT 1
# define JULIA 2

# define MAX_ITER 42

# define ZOOM_FACTOR 1.2

# define COLOR_R 9
# define COLOR_G 15
# define COLOR_B 8.5

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

/* Görüntü verilerini tutacak yapı */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

/* Fraktal verilerini tutacak ana yapı */
typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			type;
    int         max_iter;
	double		zoom;
	double		move_x;
	double		move_y;
	t_complex	julia_k;
	double		min_real;
	double		max_real;
	double		min_imag;
	double		max_imag;
	double		aspect_ratio;
}	t_fractol;

/* main.c */
int			main(int argc, char **argv);
void		print_usage(void);
int			init_mlx(t_fractol *fractol);
void		init_fractol(t_fractol *fractol, int type, int argc, char **argv);
void		cleanup(t_fractol *fractol);

/* draw.c */
void		draw_fractol(t_fractol *fractol);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_complex	get_complex_coord(int x, int y, t_fractol *fractol);
void		init_complex_plane(t_fractol *fractol);

/* fractals.c */
int	        mandelbrot(t_complex c, t_fractol *fractol);
int			julia(t_complex z, t_complex k, t_fractol *fractol);

/* utils.c */
t_complex	init_complex(double real, double imag);
int         create_color(int iterations, int max_iter);
int			ft_strcmp(const char *s1, const char *s2);
int			is_valid_double(char *str);
double		ft_atof(char *str);

/* hooks.c */
int			key_hook(int keycode, t_fractol *fractol);
int			mouse_hook(int button, int x, int y, t_fractol *fractol);
int			close_window(t_fractol *fractol);

#endif