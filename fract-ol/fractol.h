#ifndef FRACTOL_H
# define FRACTOL_H

#include "math.h"
#include "minilibx/mlx.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "X11/X.h"
#include "X11/keysym.h"

#define WIDTH	800
#define HEIGHT	800

#define BLACK         0x000000  
#define WHITE         0xFFFFFF  
#define RED           0xFF0000  
#define GREEN         0x00FF00  
#define BLUE          0x0000FF  
#define YELLOW        0xFFFF00  
#define CYAN          0x00FFFF  
#define PURPLE        0x800080  
#define GRAY          	0x808080  

#define MAGENTA_BURST	0xFF00FF  
#define NEON_PINK        0xFF10F0  
#define ELECTRIC_LIME    0xCCFF00  
#define PSYCHEDELIC_BLUE 0x1200FF  
#define HOT_ORANGE       0xFF4500  
#define RADIANT_YELLOW   0xFFDD44  
#define ACID_GREEN       0xB0FF1A  
#define LASER_LEMON      0xFFFF66  
#define ULTRA_VIOLET     0x6A0DAD  
#define HYPER_TEAL       0x00F5FF  
#define LAVA_RED         0xE42217  
#define COSMIC_PURPLE    0xA32CC4  
#define PSYCHEDELIC_SKY  0x7DF9FF  
#define FLUORESCENT_CYAN 0x08E8DE  
#define SHOCKING_PINK    0xFC0FC0 

typedef struct	s_point
{
	double real;
	double i;

}				t_point;

typedef struct	s_image
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endlan;
	int		line_len;
}				t_image;

typedef struct	s_fractal
{
	char	*name;
	void    *mlx_connection;
	void	*mlx_window;
	t_image	img;
	double	escape_value;
	int		iterations_def;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}				t_fractal;


int		ft_strncmp(const char *s1, const char *s2, size_t n);
void   	fractal_init(t_fractal *fractal);
double 	map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_point	square_complex(t_point x);
t_point	sum_complex(t_point z1, t_point z2);
void    fractal_render(t_fractal *fractal);
int key_handler(int keysym, t_fractal *fractal);
int close_handler(t_fractal *fractal);
int     mouse_handler(int button, int x, int y, t_fractal *fractal);
double	atodb(char *s);



#endif