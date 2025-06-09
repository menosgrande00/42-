#include "so_long.h"

int map_reader_false(t_game *game)
{
    ft_free_for_img(game);
	//mlx_destroy_display(game->mlx);
	free(game->mlx);
    free(game);
	write(2, "Error\n", 6);
	exit (0);
}

int	check_enemy(t_game *game, int x, int y)
{
	pthread_mutex_lock(&game->mutex);
	if (game->map[y][x] == 'M')
	{
		ft_printf("You Dead\n");
		ft_free_for_img(game);
		ft_free_map(game);
		//mlx_destroy_display(game->mlx);
		free(game->mlx);
		free(game);
		pthread_mutex_unlock(&game->mutex);
		exit (0);
	}
	pthread_mutex_unlock(&game->mutex);
	return (1);
}

int	check_enemy_map_border(t_game *game, int x, int y, int j)
{
	int attack_x;
	int attack_y;

	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
        return (0);
	if (game->map[y][x] == 'C' || game->map[y][x] == 'E'
		|| game->map[y][x] == 'M' || game->map[y][x] == '1')
		return (0);
	if (game->img->img_count_attack == 1)
	{
		attack_x = game->player_x;
		attack_y = game->player_y;
		if (game->direction == 0)
			attack_y++;
		else if (game->direction == 1)
			attack_y--;
		else if (game->direction == 2)
			attack_x++;
		else if (game->direction == 3)
			attack_x--;
		if (x == attack_x && y == attack_y)
			return (0);
	}
	if (game->map[game->enemy->y[j]][game->enemy->x[j]] == game->map[game->player_y][game->player_x])
	{
		write(2, "You DEAD\n", 9);
		close_window(game);
	}
	return (1);
}

int key_pressed_check(int key_code, t_game *game)
{

	if (key_code == 13 || key_code == 1 || key_code == 0 || key_code == 2
		|| key_code == 126 || key_code == 125 || key_code == 123 || key_code == 124)
        game->key_pressed = 1;
    return 0;
}

int key_release(int key_code, t_game *game)
{
    if (key_code == 13 || key_code == 1 || key_code == 0 || key_code == 2
        || key_code == 126 || key_code == 125 || key_code == 123 || key_code == 124)
        game->key_pressed = 0;
    return 0;
}
