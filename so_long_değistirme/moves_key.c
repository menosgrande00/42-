/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:02:00 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 11:54:46 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_right(t_game *game)
{
	if (game->player_x + 1 < game->map_width
		&& game->map[game->player_y][game->player_x + 1] != '1'
		&& check_move_for_door(game, game->player_x + 1, game->player_y) == 1
		&& check_enemy(game, game->player_x + 1, game->player_y) == 1)
	{
		if (game->map[game->player_y][game->player_x]
			== game->map[game->door_y][game->door_x])
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, game->player_x * 64,
				game->player_y * 64);
			game->map[game->player_y][game->player_x] = 'E';
		}
		else
			game->map[game->player_y][game->player_x] = '0';
		game->prev_loc->player_x_prev_prev = game->prev_loc->player_x_prev;
		game->prev_loc->player_x_prev = game->player_x;	
		game->player_x++;
		if (game->player_x - 1 == game->prev_loc->player_x_prev
			&& game->prev_loc->player_x_prev - 1 == game->prev_loc->player_x_prev_prev)
				game->prev_loc->attack_count++;
		if (game->map[game->player_y][game->player_x] == 'C')
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, game->player_x * 64,
				game->player_y * 64);
		}
		game->map[game->player_y][game->player_x] = 'P';
		game->moment_count++;
		ft_printf("Score: %d\n", game->moment_count);
		game->direction = 3;
		return (1);
	}
	return (0);
}

int	move_left(t_game *game)
{
	if (game->player_x - 1 > 0
		&& game->map[game->player_y][game->player_x - 1] != '1'
		&& check_move_for_door(game, game->player_x - 1, game->player_y) == 1
		&& check_enemy(game, game->player_x - 1, game->player_y) == 1)
	{
		if (game->map[game->player_y][game->player_x]
			== game->map[game->door_y][game->door_x])
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, game->player_x * 64,
				game->player_y * 64);
			game->map[game->player_y][game->player_x] = 'E';
		}
		else
			game->map[game->player_y][game->player_x] = '0';
		game->prev_loc->player_x_prev_prev = game->prev_loc->player_x_prev;
		game->prev_loc->player_x_prev = game->player_x;
		game->player_x--;
		if (game->player_x + 1 == game->prev_loc->player_x_prev
			&& game->prev_loc->player_x_prev + 1 == game->prev_loc->player_x_prev_prev)
				game->prev_loc->attack_count++;
		if (game->map[game->player_y][game->player_x] == 'C')
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, game->player_x * 64,
				game->player_y * 64);
		}
		game->map[game->player_y][game->player_x] = 'P';
		game->moment_count++;
		ft_printf("Score: %d\n", game->moment_count);
		game->direction = 2;
		return (1);
	}
	return (0);
}

int	move_up(t_game *game)
{
	if (game->player_y - 1 > 0
		&& game->map[game->player_y - 1][game->player_x] != '1'
		&& check_move_for_door(game, game->player_x, game->player_y - 1) == 1
		&& check_enemy(game, game->player_x, game->player_y - 1) == 1)
	{
		if (game->map[game->player_y][game->player_x]
			== game->map[game->door_y][game->door_x])
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, game->player_x * 64,
				game->player_y * 64);
			game->map[game->player_y][game->player_x] = 'E';
		}
		else
			game->map[game->player_y][game->player_x] = '0';
		game->prev_loc->player_y_prev_prev = game->prev_loc->player_y_prev;
		game->prev_loc->player_y_prev = game->player_y;
		game->player_y--;
		if (game->player_y + 1 == game->prev_loc->player_y_prev
			&& game->prev_loc->player_y_prev + 1 == game->prev_loc->player_y_prev_prev)
				game->prev_loc->attack_count++;
		if (game->map[game->player_y][game->player_x] == 'C')
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, game->player_x * 64,
				game->player_y * 64);
		}
		game->map[game->player_y][game->player_x] = 'P';
		game->moment_count++;
		ft_printf("Score: %d\n", game->moment_count);
		game->direction = 1;
		return (1);
	}
	return (0);
}

int	move_down(t_game *game)
{
	if (game->player_y + 1 < game->map_height
		&& game->map[game->player_y + 1][game->player_x] != '1'
		&& check_move_for_door(game, game->player_x, game->player_y + 1) == 1
		&& check_enemy(game, game->player_x, game->player_y + 1) == 1)
	{
		if (game->map[game->player_y][game->player_x]
			== game->map[game->door_y][game->door_x])
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, game->player_x * 64,
				game->player_y * 64);
			game->map[game->player_y][game->player_x] = 'E';
		}
		else
			game->map[game->player_y][game->player_x] = '0';
		game->prev_loc->player_y_prev_prev = game->prev_loc->player_y_prev;
		game->prev_loc->player_y_prev = game->player_y;
		game->player_y++;
		if (game->player_y - 1 == game->prev_loc->player_y_prev
			&& game->prev_loc->player_y_prev - 1 == game->prev_loc->player_y_prev_prev)
				game->prev_loc->attack_count++;
		if (game->map[game->player_y][game->player_x] == 'C')
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img->floor, game->player_x * 64,
				game->player_y * 64);
		}
		game->map[game->player_y][game->player_x] = 'P';
		game->moment_count++;
		ft_printf("Score: %d\n", game->moment_count);
		game->direction = 0;
		return (1);
	}
	return (0);
}

int	key_input(int key_code, t_game *game)
{
	if (key_code == 53)
	{
		ft_free_for_img(game);
		ft_free_map(game);
		//mlx_destroy_display(game->mlx);
		free(game->mlx);
		free(game);
		exit(0);
	}
	if (game->key_pressed == 0)
	{
		key_pressed_check(key_code, game);
		if (key_code == 13 || key_code == 126)
			move_up(game);
		else if (key_code == 1 || key_code == 125)
			move_down(game);
		else if (key_code == 0 || key_code == 123)
			move_left(game);
		else if (key_code == 2 || key_code == 124)
			move_right(game);
		if (is_that_attack(game) == 1)
			is_attack_in_map(game);
		render_map(game, 0, 0, 1);
	}
	return (0);
}
