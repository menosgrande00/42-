/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:20:12 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 15:17:03 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_elements(char **map, t_game *game, int col, int row)
{
	while (row < game->map_height)
	{
		col = 0;
		while (col < game->map_width)
		{
			if (map[row][col] == 'P')
			{
				game->player_count++;
				game->player_x = col;
				game->player_y = row;
			}
			else if (map[row][col] == 'E')
			{	
				game->door_y = row;
				game->door_x = col;
				game->door_count++;
			}
			else if (map[row][col] == 'C')
				game->collectible_count++;
			else if (map[row][col] == 'M')
			{
				game->enemy_count_tmp++;
			}
			col++;
		}
		row++;
	}
}

int	check_map_borders(char **map, t_game *game)
{
	int	col;
	int	row;

	col = 0;
	while (col < game->map_width)
	{
		if (map[0][col] != '1' || map[(game->map_height) - 1][col] != '1')
		{
			write(2, "Map must be surrounded by walls\n", 32);
			return (0);
		}
		col++;
	}
	row = 0;
	while (row < game->map_height)
	{
		if (map[row][0] != '1' || map[row][game->map_width - 1] != '1')
		{
			write(2, "Map must be surrounded by walls\n", 32);
			return (0);
		}
		row++;
	}
	return (1);
}

int	arg_check(int ac, char **arg)
{
	int	i;

	i = 0;
	if (ac != 2 || !arg[1] || arg[1][0] == '\0')
		return (0);
	while (arg[1][i] && arg[1][i] != '.')
		i++;
	if (arg[1][0] == '.')
		return (0);
	if (arg[1][i - 1] != '/' && arg[1][i] == '.' && arg[1][i + 1] == 'b'
		&& arg[1][i + 2] == 'e'
		&& arg[1][i + 3] == 'r' && arg[1][i + 4] == '\0')
		return (1);
	return (0);
}

int	img_none(t_game *game)
{
	write(2, "Error\n", 6);
	close_window(game);
	return (0);
}

int	check_map_character(char **map, t_game *game)
{
	int	col;
	int	row;

	col = 0;
	while (col < game->map_width)
	{
		row = 0;
		while (row < game->map_height)
		{
			if (map[row][col] != '1' && map[row][col] != '0'
				&& map[row][col] != 'P' && map[row][col] != 'C'
				&& map[row][col] != 'E' && map[row][col] != 'M')
			{
				write(2, "Invalid character in map\n", 25);
				return (0);
			}
			row++;
		}
		col++;
	}
	return (1);
}
