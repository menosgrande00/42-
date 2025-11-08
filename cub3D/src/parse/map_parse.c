#include "../inc/cub3d.h"

int set_map_parse(t_cub *cub, int fd)
{
	char	**lines;
	int		h;

	lines = NULL;
	h = 0;
	if (collect_map_lines(fd, &lines, &h))
		return (1);
	if (norm_to_grid(lines, h, &cub->map))
	{
		free_double(lines);
		return (1);
	}
	free_double(lines);
	if (validate_chars_and_player(&cub->map, &cub->player)
			|| check_closed_by_walls(&cub->map) || only_trailing_blank(fd))
	{
        free_map(&cub->map);
        return (1);
    }
}
