#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
//# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>
# include <math.h>
# include <errno.h>
# include <string.h>

# define KEY_MAX	512
# define RD_CHUNK	4096

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
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		end;
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
	unsigned char	held[KEY_MAX];
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
	int		hit;
	t_side	side;
	double	perp_dist;
	double	wall_x;
	int		map_x;
	int		map_y;
}	t_rayhit;

typedef struct	s_cub
{
	void		*mlx;
	void		*win;
	int			screen_w;
	int			screen_h; 
	t_img		frame;
	t_tex		tex;
	t_map		map;
	t_player	player;
	t_keys		keys;
}	t_cub;

int		ft_strcmp(char *s1, char *s2);
int		in_range(int v);
int		set_tex_color_lines(t_cfg *cfg, const char *path);

#endif