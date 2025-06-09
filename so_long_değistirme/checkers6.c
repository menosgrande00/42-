#include "so_long.h"

int check_attack_area_for_two(t_game *game)
{
	int	x;
	int	y;

	x = game->player_x;
	y = game->player_y;
	if (game->direction == 0)
		y += 2;
	else if (game->direction == 1)
		y -= 2;
	else if (game->direction == 2)
		x -= 2;
	else if (game->direction == 3)
		x += 2;
	if (game->map[y][x] == 'M')
	{
		remove_enemy(game, x, y);
		game->map[y][x] = '0';
		return (1);
	}
	return (0);
}

void	check_attack_area(t_game *game)
{
	int	x;
	int	y;
	int enemy_found;

	enemy_found = 0;
	x = game->player_x;
	y = game->player_y;
	if (game->direction == 0)
		y++;
	else if (game->direction == 1)
		y--;
	else if (game->direction == 2)
		x--;
	else if (game->direction == 3)
		x++;
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height && game->map[y][x] == 'M')
	{
		remove_enemy(game, x, y);
		game->map[y][x] = '0';
		enemy_found = 1;
	}
	if (!enemy_found)
		check_attack_area_for_two(game);
}

int	check_attack_area_for_enemy_move(t_game *game)
{
	int	x;
	int	y;

	x = game->player_x;
	y = game->player_y;
	if (game->img->img_count_attack == 0)
		return (0);
	if (game->direction == 0)
		y++;
	else if (game->direction == 1)
		y--;
	else if (game->direction == 2)
		x--;
	else if (game->direction == 3)
		x++;
	check_attack_area_for_two(game);
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height && game->map[y][x] == 'M')
	{
		remove_enemy(game, x, y);
		game->map[y][x] = '0';
		return (1);
	}
	return (0);
}
