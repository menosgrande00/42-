#include "so_long.h"

int ft_check_enemies(t_game *game)
{
	static struct timeval last_time;
	struct timeval current_time;
	double time_diff;
	static int i = 0;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0 && last_time.tv_usec == 0)
		last_time = current_time;
	time_diff = ((current_time.tv_sec - last_time.tv_sec)
		+ (current_time.tv_usec - last_time.tv_usec) / 1000000.0);
	i = find_and_move_enemy(game, time_diff, i);
	if(time_diff >= 0.5)
	{
		last_time = current_time;
		i++;
	}
	return (1);
}

int	find_and_move_enemy(t_game *game, double time_diff, int i)
{
	int		j;

	j = 0;
	if (time_diff >= 0.5)
	{
		while (j < game->enemy->enemy_count)
		{
			if (i % 4 == 0 || i % 4 == 3)
				ft_enemies_move(game, 1, j);
			else if (i % 4 == 1 || i % 4 == 2)
				ft_enemies_move(game, 2, j);
			j++;
		}
	}
	return (i);
}

int ft_enemies_move(t_game *game, int decision, int j)
{
	if (!check_attack_area_for_enemy_move(game) && radar(game, j) == 1)
		if(enemy_follow(game, j))
			return (1);

	if (decision == 1 && check_enemy_map_border(game, game->enemy->x[j] + 1, game->enemy->y[j], j) == 1)
	{
		game->map[game->enemy->y[j]][game->enemy->x[j]] = '0';
		game->enemy->x[j] += 1;
		game->map[game->enemy->y[j]][game->enemy->x[j]] = 'M';
		game->enemy->direction[j] = 2;
	}
	else if (decision == 2 && check_enemy_map_border(game, game->enemy->x[j] - 1, game->enemy->y[j], j) == 1)
	{
		game->map[game->enemy->y[j]][game->enemy->x[j]] = '0';
		game->enemy->x[j] -= 1;
		game->map[game->enemy->y[j]][game->enemy->x[j]] = 'M';
		game->enemy->direction[j] = 3;
	}
	else if (check_enemy_map_border(game, game->enemy->x[j], game->enemy->y[j] + 1, j) == 1)
		enemy_cant_move(game, 0, j);
	else if (check_enemy_map_border(game, game->enemy->x[j], game->enemy->y[j] - 1, j) == 1)
		enemy_cant_move(game, 1, j);

	check_attack_area_for_enemy_move(game);
	return (1);
}

int	enemy_follow(t_game *game, int j)
{
	if (game->map[game->view[0].y][game->view[0].x] == 'P')
	{
		ft_printf("You Dead\n");
		close_window(game);
	}
	else if (game->map[game->view[0].y][game->view[0].x] != '1'
		&& game->map[game->view[0].y][game->view[0].x] != 'C' 
		&& game->map[game->view[0].y][game->view[0].x] != 'E'
		&& game->map[game->view[0].y][game->view[0].x] != 'A')
	{
		game->map[game->enemy->y[j]][game->enemy->x[j]] = '0';
		if (game->enemy->x[j] < game->view[0].x)
			game->enemy->direction[j] = 2;
		else if (game->enemy->x[j] > game->view[0].x)
			game->enemy->direction[j] = 3;
		else if (game->enemy->y[j] < game->view[0].y)
			game->enemy->direction[j] = 0;
		else if (game->enemy->y[j] > game->view[0].y)
			game->enemy->direction[j] = 1;
		game->enemy->x[j] = game->view[0].x;
		game->enemy->y[j] = game->view[0].y;
		game->map[game->enemy->y[j]][game->enemy->x[j]] = 'M';
		free(game->view);

		return (1);
	}

	free(game->view);
	return (0);
}

int	enemy_cant_move(t_game *game, int z, int j)
{
	if (z == 0)
	{
		game->map[game->enemy->y[j]][game->enemy->x[j]] = '0';
		game->enemy->y[j] += 1;
		game->map[game->enemy->y[j]][game->enemy->x[j]] = 'M';
		game->enemy->direction[j] = 0;
	}
	else if (z == 1)
	{
		game->map[game->enemy->y[j]][game->enemy->x[j]] = '0';
		game->enemy->y[j] -= 1;
		game->map[game->enemy->y[j]][game->enemy->x[j]] = 'M';
		game->enemy->direction[j] = 1;
	}
	return (1);
}
