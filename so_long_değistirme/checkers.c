/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:21:39 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 15:16:26 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_move_for_door(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
	{
		game->collectible_count--;
		ft_printf("Received! Remaining: %d\n", game->collectible_count);
	}
	if (game->map[y][x] == 'E')
	{
		if (game->collectible_count <= 0)
		{
			game->moment_count++;
			ft_printf("Score: %d\n", game->moment_count);
			ft_printf("All collectibles are collected, WP!\n");
			ft_free_for_img(game);
			ft_free_map(game);
			//mlx_destroy_display(game->mlx);
			free(game->mlx);
			free(game);
			exit(0);
		}
		else
			ft_printf("Remaining collectible: %d\n", game->collectible_count);
	}
	return (1);
}

int	ft_free_for_img(t_game *game)
{
	int	i;

	i = 0;
	if (game->mlx)
	{
		while (i < 32)
			if (game->img->player[i++])
				mlx_destroy_image(game->mlx, game->img->player[i - 1]);
		i = 0;
		while (i < 32)
			if (game->img->enemy[i++])
				mlx_destroy_image(game->mlx, game->img->enemy[i - 1]);
		if (game->img->wall)
			mlx_destroy_image(game->mlx, game->img->wall);
		if (game->img->collectible)
			mlx_destroy_image(game->mlx, game->img->collectible);
		if (game->img->exit)
			mlx_destroy_image(game->mlx, game->img->exit);
		if (game->img->floor)
			mlx_destroy_image(game->mlx, game->img->floor);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
	}
	free(game->img);
	return (1);
}

int	ft_free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i] != NULL)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	return (0);
}

int	free_both_maps(char **map, char **tmp_map, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(map[i]);
		i++;
	}
	free(map);
	i = 0;
	while (i < line_count)
	{
		free(tmp_map[i]);
		i++;
	}
	free(tmp_map);
	return (0);
}

int	check_max_size(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	//mlx_get_screen_size(game->mlx, &x, &y);
	if (!(game->map_height * 64 <= y && game->map_width * 64 <= x))
		return (0);
	return (1);
}
