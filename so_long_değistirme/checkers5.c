#include "so_long.h"

int is_in_map(t_game *game, int x, int y)
{
	if (x > 0 && x < game->map_width - 1 && y > 0 && y < game->map_height - 1)
		return (1);
	return (0);
}

int walk_to_player(t_game *game, int j)
{
	game->view[0].x = game->enemy->x[j];
	game->view[0].y = game->enemy->y[j];
	if (game->enemy->x[j] < game->player_x)
		game->view[0].x++;
	else if (game->enemy->x[j] > game->player_x)
		game->view[0].x--;
	if (game->enemy->y[j] < game->player_y)
		game->view[0].y++;
	else if (game->enemy->y[j] > game->player_y)
		game->view[0].y--;
	return (1);
}

int	fill_for_init(t_game *game)
{
	game->enemy_count_tmp = 0;
	game->img->img_count_attack = 0;
	game->prev_loc->attack_count = 0;
	game->collectible_count = 0;
	game->player_count = 0;
	game->moment_count = 0;
	game->door_count = 0;
	game->img->wall = NULL;
	game->img->collectible = NULL;
	game->img->exit = NULL;
	game->img->floor = NULL;
	game->img->height = 0;
	game->img->width = 0;
	game->direction = 0;
	game->key_pressed = 0;
	return (1);
}

int	is_attack_in_map(t_game *game)
{
	if (game->direction == 0)
	{	
		if (game->player_y + 2 < game->map_height && game->map[game->player_y + 2][game->player_x] != '1'
			&& game->map[game->player_y + 1][game->player_x] != '1'
			&& game->map[game->player_y + 2][game->player_x] != 'E'
			&& game->map[game->player_y + 2][game->player_x] != 'C')
			{
				game->map[game->player_y + 2][game->player_x] = 'A';
				return (1);
			}
	}
	else if (game->direction == 1)
	{	
		if (game->player_y - 2 > 0 && game->map[game->player_y - 2][game->player_x] != '1'
			&& game->map[game->player_y - 1][game->player_x] != '1'
			&& game->map[game->player_y - 2][game->player_x] != 'E'
			&& game->map[game->player_y - 2][game->player_x] != 'C')
			{
				game->map[game->player_y - 2][game->player_x] = 'A';
				return (1);
			}
	}
	else if (game->direction == 2)
	{
		if (game->player_x - 2 > 0 && game->map[game->player_y][game->player_x - 2] != '1'
			&& game->map[game->player_y][game->player_x - 1] != '1'
			&& game->map[game->player_y][game->player_x - 2] != 'E'
			&& game->map[game->player_y][game->player_x - 2] != 'C')
			{
				game->map[game->player_y][game->player_x - 2] = 'A';
				return (1);
			}
	}
	else if (game->direction == 3)
	{
		if (game->player_x + 2 < game->map_width && game->map[game->player_y][game->player_x + 2] != '1'
			&& game->map[game->player_y][game->player_x + 1] != '1'
			&& game->map[game->player_y][game->player_x + 2] != 'E'
			&& game->map[game->player_y][game->player_x + 2] != 'C')
			{
				game->map[game->player_y][game->player_x + 2] = 'A';
				return (1);
			}
	}
	return (0);
}
void	count_map_elements_for_enemy(char **map, t_game *game, int col, int row)
{
	while (row < game->map_height)
	{
		col = 0;
		while (col < game->map_width)
		{
			if (map[row][col] == 'M')
			{
				game->enemy->y[game->enemy->enemy_count] = row;
				game->enemy->x[game->enemy->enemy_count] = col;
				game->enemy->enemy_count++;
			}
			col++;
		}
		row++;
	}
}
