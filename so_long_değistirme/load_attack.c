#include "so_long.h"

int load_character_attack_left(t_game *game)
{
	game->img->attack[9] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/left_1.xpm", &game->img->width, &game->img->height);
	game->img->attack[10] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/left_2.xpm", &game->img->width, &game->img->height);
	game->img->attack[11] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/left_3.xpm", &game->img->width, &game->img->height);
	if (!game->img->attack[9] || !game->img->attack[10] || !game->img->attack[11])
	{
		free(game->img->attack[9]);
		free(game->img->attack[10]);
		free(game->img->attack[11]);
		return (0);
	}
	return (1);
}

int load_character_attack_right(t_game *game)
{
	game->img->attack[6] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/right_1.xpm", &game->img->width, &game->img->height);
	game->img->attack[7] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/right_2.xpm", &game->img->width, &game->img->height);
	game->img->attack[8] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/right_3.xpm", &game->img->width, &game->img->height);
	if (!game->img->attack[6] || !game->img->attack[7] || !game->img->attack[8])
	{
		free(game->img->attack[6]);
		free(game->img->attack[7]);
		free(game->img->attack[8]);
		return (0);
	}
	if (!load_character_attack_left(game))
		return (0);
	return (1);
}

int load_character_attack_up(t_game *game)
{
	game->img->attack[3] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/up_1.xpm", &game->img->width, &game->img->height);
	game->img->attack[4] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/up_2.xpm", &game->img->width, &game->img->height);
	game->img->attack[5] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/up_3.xpm", &game->img->width, &game->img->height);
	if (!game->img->attack[3] || !game->img->attack[4] || !game->img->attack[5])
	{
		free(game->img->attack[3]);
		free(game->img->attack[4]);
		free(game->img->attack[5]);
		return (0);
	}
	if (!load_character_attack_right(game))
		return (0);
	return (1);
}

int load_character_attack_down(t_game *game)
{
	game->img->attack[0] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/down_1.xpm", &game->img->width, &game->img->height);
	game->img->attack[1] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/down_2.xpm", &game->img->width, &game->img->height);
	game->img->attack[2] = mlx_xpm_file_to_image(game->mlx,
		"XPM/attack/down_3.xpm", &game->img->width, &game->img->height);
	if (!game->img->attack[0] || !game->img->attack[1] || !game->img->attack[2])
	{
		free(game->img->attack[0]);
		free(game->img->attack[1]);
		free(game->img->attack[2]);
		return (0);
	}
	if (!load_character_attack_up(game))
		return (0);
	return (1);
}
