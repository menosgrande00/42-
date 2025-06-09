/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:08:14 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 14:11:09 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_map_checker(char **map, t_game *game)
{
	while (map[game->map_height] != NULL)
	{
		if (game->map_height == 0)
			game->map_width = ft_strlen(map[0]);
		else if (ft_strlen_for_int(map[game->map_height]) != game->map_width)
		{
			write(2, "Map must be rectangular\n", 24);
			return (0);
		}
		game->map_height++;
	}
	count_map_elements(map, game, 0, 0);
	if(!memory_for_enemy(game))
		return (0);
	count_map_elements_for_enemy(map, game, 0, 0);
	if (!check_map_borders(map, game))
		return (0);
	if (!check_map_character(map, game))
		return (0);
	//if (!check_max_size(game))
	//	return (0);
	if (game->player_count != 1
		|| game->door_count != 1 || game->collectible_count < 1)
	{
		write(2, "Map must have player, exit, collectible\n", 40);
		return (0);
	}
	return (1);
}

void	mark_cell_and_update(char **tmp_map, int x, int y, int *counters)
{
	if (tmp_map[y][x] == 'C')
		counters[0]++;
	if (tmp_map[y][x] == 'E')
		counters[1]++;
	tmp_map[y][x] = 'V';
}

int	path_find(char **tmp_map, int x, int y, t_game *game)
{
	static int	counters[2];
	int			i;

	if (tmp_map[y][x] == '1' || tmp_map[y][x] == 'V')
		return (0);
	mark_cell_and_update(tmp_map, x, y, counters);
	path_find(tmp_map, x + 1, y, game);
	path_find(tmp_map, x - 1, y, game);
	path_find(tmp_map, x, y + 1, game);
	path_find(tmp_map, x, y - 1, game);
	if (x == game->player_x && y == game->player_y)
	{
		if (counters[1] != 1 || counters[0] != game->collectible_count)
		{
			i = 0;
			ft_free_map(game);
			while (tmp_map[i] != NULL)
				free(tmp_map[i++]);
			free(tmp_map);
			write(2, "Path not found\n", 15);
			return (0);
		}
		return (1);
	}
	return (1);
}

int	ft_map_reader(const char *filename, t_game *game)
{
	int		fd;
	int		line_count;
	char	**map;
	char	**tmp_map;
	int		i;

	i = 0;
	map = NULL;
	if (!open_map_file(filename, &fd, &line_count))
		return (0);
	if (!allocate_maps(&map, &tmp_map, line_count, fd))
		return (0);
	line_count = read_map_lines(fd, map, tmp_map);
	if (line_count == 0)
		return (free_both_maps(map, tmp_map, line_count));
	close(fd);
	if (!ft_map_checker(map, game))
		return (free_both_maps(map, tmp_map, line_count));
	game->map = map;
	if (path_find(tmp_map, game->player_x, game->player_y, game) == 0)
		return (0);
	while (tmp_map[i] != NULL)
		free(tmp_map[i++]);
	free(tmp_map);
	return (1);
}
