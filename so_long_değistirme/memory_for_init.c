#include "so_long.h"

int memory_check_init(t_game *game)
{
	game->img = (t_img *)malloc(sizeof(t_img));
	if (!game->img)
	{
		free(game);
		return (0);
	}
	ft_memset(game->img, 0, sizeof(t_img));
	game->img->player = malloc(sizeof(void *) * 25);
	if (!game->img->player)
	{
		free(game->img);
		free(game);
		return (0);
	}
	ft_memset(game->img->player, 0, sizeof(void *) * 25);
	return (1);
}

int memory_for_enemy(t_game *game)
{
	game->img->enemy = malloc(sizeof(void *) * 33);
	if (!game->img->enemy)
	{
		free(game->img->player);
		free(game->img);
		free(game);
		return (0);
	}
	ft_memset(game->img->enemy, 0, sizeof(void *) * 33);
	game->enemy = (t_enemy *)malloc(sizeof(t_enemy));
	if (!game->enemy)
	{
		free(game->img->enemy);
		free(game->img->player);
		free(game->img);
		free(game);
		return (0);
	}
	if (!memory_for_enemy_loc(game))
	{
		free(game->enemy);
		free(game->img->enemy);
		free(game->img->player);
		free(game->img);
		free(game);
		return (0);
	}
	return (1);
}

int	memory_for_attack(t_game *game)
{
	game->img->attack = malloc(sizeof(void *) * 13);
	if (!game->img->attack)
	{
		free(game->enemy);
		free(game->img->enemy);
		free(game->img->player);
		free(game->img);
		free(game);
		return (0);
	}
	ft_memset(game->img->attack, 0, sizeof(void *) * 13);
	return (1);
}

int	memory_for_enemy_loc(t_game *game)
{
	game->enemy->x = malloc(sizeof(int) * game->enemy_count_tmp + 1);
	if (!game->enemy->x)
	{
		free(game->enemy);
		free(game->img->enemy);
		free(game->img->player);
		free(game->img);
		free(game);
		return (0);
	}
	ft_memset(game->enemy->x, 0, sizeof(int) * game->enemy_count_tmp + 1);
	game->enemy->y = malloc(sizeof(int) * game->enemy_count_tmp + 1);
	if (!game->enemy->y)
	{
		free(game->enemy->x);
		free(game->enemy);
		free(game->img->enemy);
		free(game->img->player);
		free(game->img);
		free(game);
		return (0);
	}
	ft_memset(game->enemy->y, 0, sizeof(int) * game->enemy_count_tmp + 1);
	game->enemy->direction = malloc(sizeof(int) * 5);
	if (!game->enemy->direction)
	{
		free(game->enemy->y);
		free(game->enemy->x);
		free(game->enemy);
		free(game->img->enemy);
		free(game->img->player);
		free(game->img);
		free(game);
		return (0);
	}
	ft_memset(game->enemy->direction, 0, sizeof(int) * 5);
	return (1);
}
