#include "so_long.h"

void	*load_enemy_zone_down(t_game *game, int time_zone, void *rendered_img)
{
	if (time_zone == 0)
		rendered_img = game->img->enemy[0];
	else if (time_zone == 1)
		rendered_img = game->img->enemy[1];
	else if (time_zone == 2)
		rendered_img = game->img->enemy[2];
	else if (time_zone == 3)
		rendered_img = game->img->enemy[3];
	else if (time_zone == 4)
		rendered_img = game->img->enemy[4];
	else if (time_zone == 5)
		rendered_img = game->img->enemy[5];
	else if (time_zone == 6)
		rendered_img = game->img->enemy[6];
	else if (time_zone == 7)
		rendered_img = game->img->enemy[7];
	return (rendered_img);
}

void	*load_enemy_zone_up(t_game *game, int time_zone, void *rendered_img)
{
	if (time_zone == 0)
		rendered_img = game->img->enemy[8];
	else if (time_zone == 1)
		rendered_img = game->img->enemy[9];
	else if (time_zone == 2)
		rendered_img = game->img->enemy[10];
	else if (time_zone == 3)
		rendered_img = game->img->enemy[11];
	else if (time_zone == 4)
		rendered_img = game->img->enemy[12];
	else if (time_zone == 5)
		rendered_img = game->img->enemy[13];
	else if (time_zone == 6)
		rendered_img = game->img->enemy[14];
	else if (time_zone == 7)
		rendered_img = game->img->enemy[15];
	return (rendered_img);
}

void	*load_enemy_zone_left(t_game *game, int time_zone, void *rendered_img)
{
	if (time_zone == 0)
		rendered_img = game->img->enemy[16];
	else if (time_zone == 1)
		rendered_img = game->img->enemy[17];
	else if (time_zone == 2)
		rendered_img = game->img->enemy[18];
	else if (time_zone == 3)
		rendered_img = game->img->enemy[19];
	else if (time_zone == 4)
		rendered_img = game->img->enemy[20];
	else if (time_zone == 5)
		rendered_img = game->img->enemy[21];
	else if (time_zone == 6)
		rendered_img = game->img->enemy[22];
	else if (time_zone == 7)
		rendered_img = game->img->enemy[23];
	return (rendered_img);
}

void	*load_enemy_zone_right(t_game *game, int time_zone, void *rendered_img)
{
	if (time_zone == 0)
		rendered_img = game->img->enemy[24];
	else if (time_zone == 1)
		rendered_img = game->img->enemy[25];
	else if (time_zone == 2)
		rendered_img = game->img->enemy[26];
	else if (time_zone == 3)
		rendered_img = game->img->enemy[27];
	else if (time_zone == 4)
		rendered_img = game->img->enemy[28];
	else if (time_zone == 5)
		rendered_img = game->img->enemy[29];
	else if (time_zone == 6)
		rendered_img = game->img->enemy[30];
	else if (time_zone == 7)
		rendered_img = game->img->enemy[31];
	return (rendered_img);
}

void	*load_image_zone_enemy(t_game *game, int time_zone, int x)
{
	void    *rendered_img;

	rendered_img = NULL;
	if (game->enemy->direction[x] == 0)
		rendered_img = load_enemy_zone_down(game, time_zone, rendered_img);
	else if (game->enemy->direction[x] == 1)
		rendered_img = load_enemy_zone_up(game, time_zone, rendered_img);
	else if (game->enemy->direction[x] == 2)
		rendered_img = load_enemy_zone_right(game, time_zone, rendered_img);
	else if (game->enemy->direction[x] == 3)
		rendered_img = load_enemy_zone_left(game, time_zone, rendered_img);
	return (rendered_img);
}
