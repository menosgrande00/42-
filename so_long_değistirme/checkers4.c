#include "so_long.h"

int free_visited(int **visited, int line_count)
{
    int	i;

    i = 0;
    while (i < line_count)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
    return (1);
}

int	memory_for_radar(t_game *game)
{
	game->view = malloc(sizeof(t_view) * game->map_height * game->map_width);
	if (!game->view)
		close_window(game);
	ft_memset(game->view, 0, sizeof(t_view) * game->map_height * game->map_width);
	game->dx = malloc(sizeof(int) * 9);
	if (!game->dx)
	{
		free(game->view);
		close_window(game);
	}
	ft_memset(game->dx, 0, sizeof(int) * 9);
	game->dy = malloc(sizeof(int) * 9);
	if (!game->dy)
	{
		free(game->view);
		free(game->dx);
		close_window(game);
	}
	ft_memset(game->dy, 0, sizeof(int) * 9);
	ft_fill_dx_dy(game);
	return (1);
}

int is_in_radar(t_game *game, int x, int y, int j)
{
	int a;
	int b;

	a= game->enemy->x[j];
	b= game->enemy->y[j];
    if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height
		&& x >= a - 3 && x <= a + 3
		&& y >= b - 3 && y <= b + 3)
        return (1);
    return (0);
}

void	ft_fill_dx_dy(t_game *game)
{
	int	i;

	i = 0;
	game->dx[i] = 0;
	game->dy[i++] = -1;
	game->dx[i] = 0;
	game->dy[i++] = 1;
	game->dx[i] = -1;
	game->dy[i++] = 0;
	game->dx[i] = 1;
	game->dy[i++] = 0;
	game->dx[i] = -1;
	game->dy[i++] = -1;
	game->dx[i] = 1;
	game->dy[i++] = -1;
	game->dx[i] = -1;
	game->dy[i++] = 1;
	game->dx[i] = 1;
	game->dy[i++] = 1;
}

int	memory_for_visited(t_game *game, int ***visited, int j)
{
	int	i;

	i = 0;
	*visited = malloc(sizeof(int *) * game->map_height);
	if (!*visited)
		close_window(game);
	while (i < game->map_height)
	{
		(*visited)[i] = malloc(sizeof(int) * game->map_width);
		if (!(*visited)[i])
		{
			free_visited(*visited, i);
			close_window(game);
		}
		ft_memset((*visited)[i], 0, sizeof(int) * game->map_width);
		i++;
	}
	game->view[0].x = game->enemy->x[j];
	game->view[0].y = game->enemy->y[j];
	return (1);
}
