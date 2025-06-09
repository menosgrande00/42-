#include "so_long.h"

void	*attack_direction_0(t_game *game, void *rendred_img)
{
	if (time_for_attack() == 0)
	{
		game->img->img_count_attack = 2;
		rendred_img = game->img->attack[0];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, game->player_x * 64,
			(game->player_y + 2) * 64);
	}
	else if (time_for_attack() == 1)
	{
		game->img->img_count_attack = 2;
		rendred_img = game->img->attack[1];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, game->player_x * 64,
			(game->player_y + 2) * 64);
	}	
	else if (time_for_attack() == 2)
	{
		game->img->img_count_attack = 1;
		rendred_img = game->img->attack[2];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, game->player_x * 64,
			(game->player_y + 2) * 64);
	}
	return (rendred_img);
}

void	*attack_direction_1(t_game *game, void *rendred_img)
{
	if (time_for_attack() == 0)
	{
		game->img->img_count_attack = 2;
		rendred_img = game->img->attack[3];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, (game->player_x) * 64,
			(game->player_y - 2) * 64);
	}
	else if (time_for_attack() == 1)
	{
		game->img->img_count_attack = 2;
		rendred_img = game->img->attack[4];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, (game->player_x) * 64,
			(game->player_y - 2) * 64);
	}
	else if (time_for_attack() == 2)
	{
		game->img->img_count_attack = 1;
		rendred_img = game->img->attack[5];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, (game->player_x) * 64,
			(game->player_y - 2) * 64);
	}
	return (rendred_img);
}

void	*attack_direction_2(t_game *game, void *rendred_img)
{
	if (time_for_attack() == 0)
	{
		game->img->img_count_attack = 2;
		rendred_img = game->img->attack[9];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, (game->player_x - 2)* 64,
			(game->player_y) * 64);
	}
	else if (time_for_attack() == 1)
	{
		game->img->img_count_attack = 2;
		rendred_img = game->img->attack[10];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, (game->player_x - 2) * 64,
			(game->player_y) * 64);
	}
	else if (time_for_attack() == 2)
	{
		game->img->img_count_attack = 1;
		rendred_img = game->img->attack[11];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, (game->player_x - 2) * 64,
			(game->player_y) * 64);
	}
	return (rendred_img);
}

void	*attack_direction_3(t_game *game, void *rendred_img)
{
	if (time_for_attack() == 0)
	{
		game->img->img_count_attack = 2;
		rendred_img = game->img->attack[6];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, (game->player_x + 2) * 64,
			(game->player_y) * 64);
	}
	else if (time_for_attack() == 1)
	{
		game->img->img_count_attack = 2;
		rendred_img = game->img->attack[7];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, (game->player_x + 2) * 64,
			(game->player_y) * 64);
	}
	else if (time_for_attack() == 2)
	{
		game->img->img_count_attack = 1;
		rendred_img = game->img->attack[8];
		mlx_put_image_to_window(game->mlx,
			game->win, game->img->floor, (game->player_x + 2) * 64,
			(game->player_y) * 64);
	}
	return (rendred_img);
}
