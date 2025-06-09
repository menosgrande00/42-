#include "so_long.h"

void load_character_idle_down(t_game *game)
{
	int	i;

	i = 0;
	game->img->player[0] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/down_1.xpm", &game->img->width, &game->img->height);
	game->img->player[1] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/down_2.xpm", &game->img->width, &game->img->height);
	game->img->player[2] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/down_3.xpm", &game->img->width, &game->img->height);
	game->img->player[3] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/down_4.xpm", &game->img->width, &game->img->height);
	game->img->player[4] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/down_5.xpm", &game->img->width, &game->img->height);
	game->img->player[5] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/down_6.xpm", &game->img->width, &game->img->height);
	while (i < 6)
		if (!game->img->player[i++])
			img_none(game);
	load_character_idle_up(game);
}

void	load_character_idle_up(t_game *game)
{
	int i;

	i = 6;
	game->img->player[6] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/up_1.xpm", &game->img->width, &game->img->height);
	game->img->player[7] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/up_2.xpm", &game->img->width, &game->img->height);
	game->img->player[8] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/up_3.xpm", &game->img->width, &game->img->height);
	game->img->player[9] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/up_4.xpm", &game->img->width, &game->img->height);
	game->img->player[10] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/up_5.xpm", &game->img->width, &game->img->height);
	game->img->player[11] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/up_6.xpm", &game->img->width, &game->img->height);
	while (i < 12)
		if (!game->img->player[i++])
			img_none(game);
	load_character_idle_left(game);
}

void	load_character_idle_left(t_game *game)
{
	int i;

	i = 12;
	game->img->player[12] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/left_1.xpm", &game->img->width, &game->img->height);
	game->img->player[13] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/left_2.xpm", &game->img->width, &game->img->height);
	game->img->player[14] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/left_3.xpm", &game->img->width, &game->img->height);
	game->img->player[15] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/left_4.xpm", &game->img->width, &game->img->height);
	game->img->player[16] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/left_5.xpm", &game->img->width, &game->img->height);
	game->img->player[17] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/left_6.xpm", &game->img->width, &game->img->height);
	while (i < 18)
		if (!game->img->player[i++])
			img_none(game);
	load_character_idle_right(game);
}

void	load_character_idle_right(t_game *game)
{
	int i;

	i = 18;
	game->img->player[18] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/right_1.xpm", &game->img->width, &game->img->height);
	game->img->player[19] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/right_2.xpm", &game->img->width, &game->img->height);
	game->img->player[20] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/right_3.xpm", &game->img->width, &game->img->height);
	game->img->player[21] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/right_4.xpm", &game->img->width, &game->img->height);
	game->img->player[22] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/right_5.xpm", &game->img->width, &game->img->height);
	game->img->player[23] = mlx_xpm_file_to_image(game->mlx,
		"XPM/character/idle/right_6.xpm", &game->img->width, &game->img->height);
	while (i < 24)
		if (!game->img->player[i++])
			img_none(game);
	game->img->player[24] = NULL;
}
