/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:11:35 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 14:49:39 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	free(game->img->attack[0]);
	free(game->img->attack[1]);
	free(game->img->attack[2]);
	ft_free_for_img(game);
	ft_free_map(game);
	//mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(0);
}

t_game	*init_game(t_game *game)
{
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_memset(game, 0, sizeof(t_game));
	if(!memory_check_init(game))
		return (NULL);
	if(!memory_for_attack(game))
		return (NULL);
	game->prev_loc = (t_prev *)malloc(sizeof(t_prev));
	if (!game->prev_loc)
		return (NULL);
	game->mlx = mlx_init();
	fill_for_init(game);
	return (game);
}

int	main(int ac, char **arg)
{
	t_game	*game;

	game = NULL;
	if (arg_check(ac, arg) == 0)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	game = init_game(game);
	pthread_mutex_init(&game->mutex, NULL);
	if (ft_map_reader(arg[1], game) == 0)
		map_reader_false(game);
	game->win = mlx_new_window(game->mlx, game->map_width * 64,
		game->map_height * 64, "so_long");
	game->prev_loc->player_x_prev = game->player_x;
	game->prev_loc->player_y_prev = game->player_y;
	game->prev_loc->player_x_prev_prev = game->player_x;
	game->prev_loc->player_y_prev_prev = game->player_y;
	mlx_loop_hook(game->mlx, render_map_wrapper, game);
	mlx_hook(game->win, 2, 1, key_input, game);
	mlx_hook(game->win, 3, 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
	return (0);
}
