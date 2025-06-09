#include "so_long.h"

void    load_enemy_down(t_game *game)
{
	int i;

	i = 0;
	game->img->enemy[0] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/down_1.xpm", &game->img->width, &game->img->height);
	game->img->enemy[1] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/down_2.xpm", &game->img->width, &game->img->height);
	game->img->enemy[2] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/down_3.xpm", &game->img->width, &game->img->height);
	game->img->enemy[3] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/down_4.xpm", &game->img->width, &game->img->height);
	game->img->enemy[4] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/down_5.xpm", &game->img->width, &game->img->height);
	game->img->enemy[5] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/down_6.xpm", &game->img->width, &game->img->height);
	game->img->enemy[6] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/down_7.xpm", &game->img->width, &game->img->height);
	game->img->enemy[7] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/down_8.xpm", &game->img->width, &game->img->height);
	while (i < 8)
		if (!game->img->enemy[i++])
			img_none(game);
	load_enemy_up(game);
}

void    load_enemy_up(t_game *game)
{
	int i;

	i = 8;
	game->img->enemy[8] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/up_1.xpm", &game->img->width, &game->img->height);
	game->img->enemy[9] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/up_2.xpm", &game->img->width, &game->img->height);
	game->img->enemy[10] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/up_3.xpm", &game->img->width, &game->img->height);
	game->img->enemy[11] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/up_4.xpm", &game->img->width, &game->img->height);
	game->img->enemy[12] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/up_5.xpm", &game->img->width, &game->img->height);
	game->img->enemy[13] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/up_6.xpm", &game->img->width, &game->img->height);
	game->img->enemy[14] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/up_7.xpm", &game->img->width, &game->img->height);
	game->img->enemy[15] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/up_8.xpm", &game->img->width, &game->img->height);
	while (i < 16)
		if (!game->img->enemy[i++])
			img_none(game);
	load_enemy_left(game);
}

void    load_enemy_left(t_game *game)
{
	int i;

	i = 16;
	game->img->enemy[16] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/left_1.xpm", &game->img->width, &game->img->height);
	game->img->enemy[17] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/left_2.xpm", &game->img->width, &game->img->height);
	game->img->enemy[18] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/left_3.xpm", &game->img->width, &game->img->height);
	game->img->enemy[19] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/left_4.xpm", &game->img->width, &game->img->height);
	game->img->enemy[20] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/left_5.xpm", &game->img->width, &game->img->height);
	game->img->enemy[21] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/left_6.xpm", &game->img->width, &game->img->height);
	game->img->enemy[22] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/left_7.xpm", &game->img->width, &game->img->height);
	game->img->enemy[23] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/left_8.xpm", &game->img->width, &game->img->height);
	while (i < 24)
		if (!game->img->enemy[i++])
			img_none(game);
	load_enemy_right(game);
}

void	load_enemy_right(t_game *game)
{
	int i;

	i = 24;
	game->img->enemy[24] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/right_1.xpm", &game->img->width, &game->img->height);
	game->img->enemy[25] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/right_2.xpm", &game->img->width, &game->img->height);
	game->img->enemy[26] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/right_3.xpm", &game->img->width, &game->img->height);
	game->img->enemy[27] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/right_4.xpm", &game->img->width, &game->img->height);
	game->img->enemy[28] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/right_5.xpm", &game->img->width, &game->img->height);
	game->img->enemy[29] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/right_6.xpm", &game->img->width, &game->img->height);
	game->img->enemy[30] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/right_7.xpm", &game->img->width, &game->img->height);
	game->img->enemy[31] = mlx_xpm_file_to_image(game->mlx,
		"XPM/enemy/right_8.xpm", &game->img->width, &game->img->height);
	while (i < 32)
		if (!game->img->enemy[i++])
			img_none(game);
	game->img->enemy[32] = NULL;
}
