#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
//# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>
# include <math.h>
# include <errno.h>

# define KEY_MAX 512

typedef struct	s_v2
{
	double	x;
	double	y;
}	t_v2;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct	s_img
{
	void	*img; // mlx image ptr
	char	*addr; // pixel data
	int		bpp; // bits per pixel
	int		line_len; // stride (bytes)
	int		end; // 0 = little
	int		w;
	int		h;
}	t_img;

typedef struct	s_tex
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}	t_tex;

typedef struct	s_map
{
	char	**grid;
	int		w;
	int		h;
}	t_map;

typedef struct	s_player
{
	t_v2	pos;
	t_v2	dir;
	t_v2	plane;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct	s_keys
{
	unsigned char	held[KEY_MAX]; //when hold press the button
}	t_keys;

typedef struct	s_cfg
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	ceil;
	t_color	floor;
	char	**map_lines;
	int		map_w;
	int		map_h;
}	t_cfg;

typedef enum	e_side
{
	SIDE_X = 0,
	SIDE_Y = 1
}	t_side;

typedef struct	s_rayhit
{
	int		hit; // 0/1
	t_side	side; // X or Y surface
	double	perp_dist; // fixed distance(fisheye)
	double	wall_x; //  x coord.
	int		map_x;
	int		map_y; // hit point
}	t_rayhit;

typedef struct	s_cub
{
	void		*mlx; // mlx_init
	void		*win; // mlx_new_window
	int			screen_w;
	int			screen_h; 
	t_img		frame; // (single image)
	t_tex		tex; // four side tex
	t_map		map; // world grid
	t_player	player; // placement and dir
	t_keys		keys;
}	t_cub;

#endif