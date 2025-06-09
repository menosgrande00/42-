#include "so_long.h"

void	*render_for_attack(t_game *game)
{
	void	*rendered_img;

	rendered_img = NULL;	
	check_attack_area(game);
	rendered_img = attack_for_time_img(game, rendered_img);
	return (rendered_img);
}

void	*attack_for_time_img(t_game *game, void *rendered_img)
{
	if (game->direction == 0)
		rendered_img = attack_direction_0(game, rendered_img);
	else if (game->direction == 1)
		rendered_img = attack_direction_1(game, rendered_img);
	else if (game->direction == 2)
		rendered_img = attack_direction_2(game, rendered_img);
	else if (game->direction == 3)
		rendered_img = attack_direction_3(game, rendered_img);
	return (rendered_img);
}

void	remove_enemy(t_game *game, int x, int y)
{
	int	i;
	int j;

	i = 0;
	while (i < game->enemy->enemy_count)
	{
		if (game->enemy->x[i] == x && game->enemy->y[i] == y)
		{
			game->map[y][x] = '0';
			j = i;
			while (j < game->enemy->enemy_count - 1)
			{
				game->enemy->x[j] = game->enemy->x[j + 1];
				game->enemy->y[j] = game->enemy->y[j + 1];
				game->enemy->direction[j] = game->enemy->direction[j + 1];
				j++;
			}
			game->enemy->enemy_count--;
			break;
		}
		i++;
	}
}

int	check_for_destroy(t_game *game, int y, int x, int desicion)
{
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
		return (0);
	if (desicion == 1 && game->map[y][x] == 'M' && game->map[y][x] != '1'
		&& game->map[y][x] != 'E' && game->map[y][x] != 'C')
	{
		remove_enemy(game, x, y);
		return (1);
	}
	if (desicion == 0 && game->map[y][x] == 'M' && game->map[y][x] != '1'
		&& game->map[y][x] != 'E' && game->map[y][x] != 'C')
	{
		remove_enemy(game, x, y);
		return (1);
	}
	return (0);
}

int	this_is_attack(t_game *game)
{
    if (game->direction == 0 && check_for_destroy(game, game->player_y + 1, game->player_x, 1) == 1)
    {
        game->map[game->player_y + 1][game->player_x] = '0';
        if (check_for_destroy(game, game->player_y + 1, game->player_x, 0) == 1)
            game->map[game->player_y + 2][game->player_x] = '0';
    }
    else if (game->direction == 1 && check_for_destroy(game, game->player_y - 1, game->player_x, 1) == 1)
    {
        game->map[game->player_y - 1][game->player_x] = '0';
        if (check_for_destroy(game, game->player_y - 1, game->player_x, 0) == 1)
            game->map[game->player_y - 2][game->player_x] = '0';
    }
    else if (game->direction == 2 && check_for_destroy(game, game->player_y, game->player_x - 1, 1) == 1)
    {
        game->map[game->player_y][game->player_x - 1] = '0';
        if (check_for_destroy(game, game->player_y, game->player_x - 1, 0) == 1)
            game->map[game->player_y][game->player_x - 2] = '0';
    }
    else if (game->direction == 3 && check_for_destroy(game, game->player_y, game->player_x + 1, 1) == 1)
    {
        game->map[game->player_y][game->player_x + 1] = '0';
        if (check_for_destroy(game, game->player_y, game->player_x + 1, 0) == 1)
            game->map[game->player_y][game->player_x + 2] = '0';
    }
    return (0);
}

int	is_that_attack(t_game *game)
{
	int	x;
	int	y;
	int x2;
	int y2;

	x = game->prev_loc->player_x_prev;
	y = game->prev_loc->player_y_prev;
	x2 = game->prev_loc->player_x_prev_prev;
	y2 = game->prev_loc->player_y_prev_prev;
	if (game->moment_count >= 2 && ((game->player_x - x == 1 && x - x2 == 1 && game->prev_loc->attack_count == 2)
	|| (game->player_x - x == -1 && x - x2 == -1 && game->prev_loc->attack_count == 2)
	|| (game->player_y - y == 1 && y - y2 == 1 && game->prev_loc->attack_count == 2)
	|| (game->player_y - y == -1 && y - y2 == -1 && game->prev_loc->attack_count == 2)))
		{
			this_is_attack(game);
			game->prev_loc->attack_count = 0;
			return (1);
		}
	else if(game->moment_count >= 2 && (game->player_x - x == 1
		|| game->player_x - x == -1
		|| game->player_y - y == 1 || game->player_y - y == -1))
		game->prev_loc->attack_count = 1;
	return (0);
}
