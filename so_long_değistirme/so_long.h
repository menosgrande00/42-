/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 05:59:38 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 14:19:06 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <math.h>

# include "get_nextline/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "mlx_mac/mlx.h"
# include <sys/time.h>
# include <pthread.h>

typedef struct s_time
{
	long	tv_sec;
	long	tv_usec;
}		t_time;

typedef struct s_img
{
	void	**player;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*floor;
	int		width;
	int		height;
	void	**enemy;
	void	**attack;
	int 	img_count_attack;
}		t_img;

typedef struct s_enemy
{
	int		*x;
	int		*y;
	int		*direction;
	int		enemy_count;
	int		which_one;
}		t_enemy;

typedef struct s_view
{
	int		x;
	int		y;
}		t_view;

typedef struct s_prev
{
	int		player_x_prev;
	int		player_y_prev;
	int		player_x_prev_prev;
	int		player_y_prev_prev;
	int		attack_count;
}		t_prev;

typedef struct s_game
{
	pthread_mutex_t mutex;
	int		key_pressed;
	int		player_x;
	int		player_y;
	int		map_height;
	int		map_width;
	int		door_x;
	int		door_y;
	int		moment_count;
	int		player_count;
	int		collectible_count;
	int		door_count;
	char	**map;
	void	*win;
	void	*mlx;
	int 	direction;
	int		enemy_count_tmp;
	t_img	*img;
	t_enemy	*enemy;
	t_view	*view;
	t_prev	*prev_loc;
	int		*dx;
	int		*dy;
}		t_game;

int		key_input(int keycode, t_game *game);
int		move_down(t_game *game);
int		move_up(t_game *game);
int		move_left(t_game *game);
int		move_right(t_game *game);

int		close_window(t_game *game);
int		ft_map_reader(const char *filename, t_game *game);
int		line_counter(int fd);
int		ft_map_checker(char **map, t_game *game);
int		path_find(char **tmp_map, int x, int y, t_game *game);

int		render_map(t_game *game, int i, int j, int force);
void	*render_for_img(t_game *game, int i, int j);
void	load_image(t_game *game);
int		read_map_lines(int fd, char **map, char **tmp_map);
int		allocate_maps(char ***map, char ***tmp_map, int line_count, int fd);
int		open_map_file(const char *filename, int *fd, int *line_count);

int		check_move_for_door(t_game *game, int x, int y);
int		ft_strcspn(const char *s, const char *charset);
int		ft_strlen_for_int(char *str);
char	*ft_strdup(const char *s);
int		ft_free_map(t_game *game);
int		ft_free_for_img(t_game *game);
int		free_both_maps(char **map, char **tmp_map, int line_count);
int		free_tmp_map(char **tmp_map, int line_count);
int		check_map_borders(char **map, t_game *game);
void	*ft_memset(void *s, int c, size_t n);

void	mark_cell_and_update(char **tmp_map, int x, int y, int *counters);
int		ft_map_checker(char **map, t_game *game);
void	count_map_elements(char **map, t_game *game, int col, int row);
int		line_counter(int fd);
int		arg_check(int ac, char **arg);
int		img_none(t_game *game);
int		check_map_character(char **map, t_game *game);
//int		check_max_size(t_game *game);

//bonus
int 	score_on_window(t_game *game);
int 	memory_for_score(char *str, t_game *game, char *count);
int 	map_reader_false(t_game *game);
int 	render_map_wrapper(void *param);
int 	colectible_on_window(t_game *game);
int 	time_map(void);
int		check_enemy(t_game *game, int x, int y);
int 	ft_enemies_move(t_game *game, int decision, int j);
int 	ft_check_enemies(t_game *game);
int		render_map_enemy(void *param);
void	load_character_idle_down(t_game *game);
void	load_character_idle_up(t_game *game);
void	load_character_idle_left(t_game *game);
void	load_character_idle_right(t_game *game);
void	load_enemy_down(t_game *game);
void	load_enemy_up(t_game *game);
void	load_enemy_left(t_game *game);
void	load_enemy_right(t_game *game);
int		check_enemy_map_border(t_game *game, int x, int y, int j);
int		enemy_cant_move(t_game *game, int z, int f);
int 	memory_check_init(t_game *game);
int 	memory_for_enemy(t_game *game);
void	*load_img_for_zone(t_game *game, int time_zone);
int 	time_after_time(void);
int		key_pressed_check(int key_code, t_game *game);
int 	key_release(int key_code, t_game *game);
int		find_and_move_enemy(t_game *game, double time_diff, int i);
void	*load_image_zone_enemy(t_game *game, int time_zone, int x);
int		time_for_enemy(void);
int		memory_for_enemy_loc(t_game *game);
int		radar(t_game *game, int j);
int		memory_for_radar(t_game *game);
int 	free_visited(int **visited, int line_count);
int 	is_in_radar(t_game *game, int x, int y, int j);
void	ft_fill_dx_dy(t_game *game);
int		memory_for_visited(t_game *game, int ***visited, int j);
int		is_in_map(t_game *game, int x, int y);
int		enemy_follow(t_game *game, int j);
int 	walk_to_player(t_game *game, int j);
int		memory_for_attack(t_game *game);
int		time_for_attack(void);
int		load_character_attack_down(t_game *game);
int		is_that_attack(t_game *game);
void	*attack_for_time_img(t_game *game, void *rendered_img);
int		is_attack_in_map(t_game *game);
void	*render_for_attack(t_game *game);
void	*attack_direction_0(t_game *game, void *rendred_img);
void	*attack_direction_1(t_game *game, void *rendred_img);
void	*attack_direction_2(t_game *game, void *rendred_img);
void	*attack_direction_3(t_game *game, void *rendred_img);
int		fill_for_init(t_game *game);
void	remove_enemy(t_game *game, int x, int y);
void	count_map_elements_for_enemy(char **map, t_game *game, int col, int row);
int		this_is_attack(t_game *game);
void	check_attack_area(t_game *game);
int		check_attack_area_for_enemy_move(t_game *game);

#endif