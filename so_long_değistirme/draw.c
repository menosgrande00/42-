/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:14:55 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 11:53:48 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	first_render(t_game *game, int i, int j)
{
	void	*rendered_img;

	rendered_img = game->img->floor;
	while (j < game->map_height)
	{
		i = 0;
		while (i < game->map_width)
		{
			if (rendered_img)
				mlx_put_image_to_window(game->mlx,
					game->win, rendered_img, i * 64, j * 64);
			i++;
		}
		j++;
	}
}
void	load_image(t_game *game)
{
	load_character_idle_down(game);
	load_enemy_down(game);
	load_character_attack_down(game);
	game->img->wall = mlx_xpm_file_to_image(game->mlx,
			"textures/walls.xpm", &game->img->width, &game->img->height);
	game->img->collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/chest.xpm", &game->img->width, &game->img->height);
	game->img->exit = mlx_xpm_file_to_image(game->mlx,
			"textures/wooden_door.xpm", &game->img->width, &game->img->height);
	game->img->floor = mlx_xpm_file_to_image(game->mlx,
			"textures/wooden_floor.xpm", &game->img->width, &game->img->height);
	if (!game->img->wall || !game->img->collectible || !game->img->attack[0]
		|| !game->img->attack[1] || !game->img->attack[2]
		|| !game->img->exit || !game->img->floor)
		img_none(game);
}

void	*render_for_img(t_game *game, int i, int j)
{
	void	*rendered_img;

	rendered_img = NULL;
	if (game->map[j][i] == '1')
		rendered_img = game->img->wall;
	else if (game->map[j][i] == 'A' && game->img->img_count_attack == 1)
	{
		game->map[j][i] = '0';
		game->img->img_count_attack = 0;
	}
	else if (game->map[j][i] == '0')
		rendered_img = game->img->floor;
	else if (game->map[j][i] == 'P')
	{
		if (game->map[game->player_y][game->player_x] == game->map[game->door_y][game->door_x])
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, i * 64, j * 64);
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->exit, i * 64, j * 64);
		}
		else
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, i * 64, j * 64);
		rendered_img = load_img_for_zone(game, time_after_time());
	}
	else if (game->map[j][i] == 'C')
		rendered_img = game->img->collectible;
	else if (game->map[j][i] == 'E')
		rendered_img = game->img->exit;
	else if (game->map[j][i] == 'A')
		rendered_img = render_for_attack(game);
	else if (game->map[j][i] == 'M')
	{
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, i * 64, j * 64);
		rendered_img = load_image_zone_enemy(game, time_for_enemy(), game->enemy->which_one);
		game->enemy->which_one++;
	}
	if (game->enemy->which_one >= game->enemy->enemy_count)
		game->enemy->which_one = 0;
	return (rendered_img);
}

int render_map_wrapper(void *param)
{
    static int is_rendering = 0;  // Static flag
    t_game *game;
    
    game = (t_game *)param;
    
    // Eğer zaten render işlemi devam ediyorsa, çık
    if (is_rendering)
        return (0);
        
    is_rendering = 1;  // Flag'i set et
    
    int result = render_map(game, 0, 0, 0);
    
    is_rendering = 0;  // Flag'i temizle
    
    return (result);
}

int	render_map(t_game *game, int i, int j, int force)
{
	static int	img_loaded;
	void		*rendered_img;

	rendered_img = NULL;
	if (img_loaded == 0)
	{
		load_image(game);
		img_loaded = 1;
		first_render(game, 0, 0);
	}
	if(time_map() == 1 && !force)
		return (0);
	while (j < game->map_height)
	{
		i = 0;
		while (i < game->map_width)
		{
			rendered_img = render_for_img(game, i, j);
			if (rendered_img)
			mlx_put_image_to_window(game->mlx,
				game->win, rendered_img, i * 64, j * 64);
			i++;
		}
		j++;
	}
	ft_check_enemies(game);
	score_on_window(game);
	colectible_on_window(game);
	return (1);
}
