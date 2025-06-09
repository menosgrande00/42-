#include "so_long.h"

int	path_for_follow(t_game *game, int j, int x, int y)
{
	int **visited;
	int front;
	int rear;
	int i;

	front = 0;
	rear = 1;
	memory_for_visited(game, &visited, j);
	while (front < rear)
	{
		if (game->view[front].x == game->player_x && game->view[front].y == game->player_y)
		{
			walk_to_player(game, j);
			free_visited(visited, game->map_height);
			return (1);
		}
		i = 0;
		while (i < 8)
		{
			x = game->view[front].x + game->dx[i];
			y = game->view[front].y + game->dy[i];
			if (is_in_map(game, x, y) && !visited[y][x] && game->map[y][x] != '1'
					&& game->map[y][x] != 'C' && game->map[y][x] != 'E')
			{
				game->view[rear].x = x;
				game->view[rear].y = y;
				rear++;
				visited[y][x] = 1;
			}
			i++;
		}
		front++;
	}
	return (0);
}

int	radar_activate(t_game *game, int j, int x, int y)
{
	int **visited;
	int front;
	int rear;
	int i;

	front = 0;
	rear = 1;
	memory_for_visited(game, &visited, j);
	while (front < rear && rear < 64)
	{
		if (game->view[front].x == game->player_x && game->view[front].y == game->player_y)
		{
			free_visited(visited, game->map_height);
			return (1);
		}
		i = 0;
		while (i < 8)
		{
			x = game->view[front].x + game->dx[i];
			y = game->view[front].y + game->dy[i];
			if (is_in_radar(game, x, y, j) && !visited[y][x] && game->map[y][x] != '1')
			{
				game->view[rear].x = x;
				game->view[rear].y = y;
				rear++;
				visited[y][x] = 1;
			}
			i++;
		}
		front++;
	}
	return (0);
}

int	radar(t_game *game, int j)
{
	memory_for_radar(game);
	if (radar_activate(game, j, 0, 0))
	{
		if (!path_for_follow(game, j, 0, 0))
		{
			free(game->view);
			return (0);
		}
	}
	else
	{
		free(game->view);
		return (0);
	}
	return (1);
}
