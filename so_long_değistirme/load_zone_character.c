#include "so_long.h"

void	*load_character_zone_down(t_game *game, int time_zone, void *rendered_img)
{
	if (time_zone == 0)
		rendered_img = game->img->player[0];
	else if (time_zone == 1)
		rendered_img = game->img->player[1];
	else if (time_zone == 2)
		rendered_img = game->img->player[2];
	else if (time_zone == 3)
		rendered_img = game->img->player[3];
	else if (time_zone == 4)
		rendered_img = game->img->player[4];
	else if (time_zone == 5)
		rendered_img = game->img->player[5];
	return (rendered_img);
}

void	*load_character_zone_up(t_game *game, int time_zone, void *rendered_img)
{
	if (time_zone == 0)
		rendered_img = game->img->player[6];
	else if (time_zone == 1)
		rendered_img = game->img->player[7];
	else if (time_zone == 2)
		rendered_img = game->img->player[8];
	else if (time_zone == 3)
		rendered_img = game->img->player[9];
	else if (time_zone == 4)
		rendered_img = game->img->player[10];
	else if (time_zone == 5)
		rendered_img = game->img->player[11];
	return (rendered_img);
}
#include "so_long.h"

void	*load_character_zone_left(t_game *game, int time_zone, void *rendered_img)
{
	if (time_zone == 0)
		rendered_img = game->img->player[12];
	else if (time_zone == 1)
		rendered_img = game->img->player[13];
	else if (time_zone == 2)
		rendered_img = game->img->player[14];
	else if (time_zone == 3)
		rendered_img = game->img->player[15];
	else if (time_zone == 4)
		rendered_img = game->img->player[16];
	else if (time_zone == 5)
		rendered_img = game->img->player[17];
	return (rendered_img);
}

void	*load_character_zone_right(t_game *game, int time_zone, void *rendered_img)
{
	if (time_zone == 0)
		rendered_img = game->img->player[18];
	else if (time_zone == 1)
		rendered_img = game->img->player[19];
	else if (time_zone == 2)
		rendered_img = game->img->player[20];
	else if (time_zone == 3)
		rendered_img = game->img->player[21];
	else if (time_zone == 4)
		rendered_img = game->img->player[22];
	else if (time_zone == 5)
		rendered_img = game->img->player[23];
	return (rendered_img);
}

void	*load_img_for_zone(t_game *game, int time_zone)
{
	void	*rendered_img;

	rendered_img = NULL;
	if (game->direction == 0)
		rendered_img = load_character_zone_down(game, time_zone, rendered_img);
	else if (game->direction == 1)
		rendered_img = load_character_zone_up(game, time_zone, rendered_img);
	else if (game->direction == 2)
		rendered_img = load_character_zone_left(game, time_zone, rendered_img);
	else if (game->direction == 3)
		rendered_img = load_character_zone_right(game, time_zone, rendered_img);
	return (rendered_img);
}
