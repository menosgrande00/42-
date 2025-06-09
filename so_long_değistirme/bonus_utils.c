#include "so_long.h"

int score_on_window(t_game *game)
{
	char    *str;
	char    *count;
	int     i;

	str = NULL;
	count = NULL;
	memory_for_score(str, game, count);
	str = ft_strdup("Score: ");
	i = 0;
	count = ft_itoa(game->moment_count);
	while (count[i] != '\0')
	{
		str[i + 7] = count[i];
		i++;
	}
	str[i + 7] = '\0';
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFF00, str);
	free(str);
	free(count);
	return (1);
}

int colectible_on_window(t_game *game)
{
	char    *str;
	char    *count;
	int     i;

	str = NULL;
	count = NULL;
	memory_for_score(str, game, count);
	str = ft_strdup("Collectible: ");
	i = 0;
	count = ft_itoa(game->collectible_count);
	while (count[i] != '\0')
	{
		str[i + 13] = count[i];
		i++;
	}
	str[i + 13] = '\0';
	mlx_string_put(game->mlx, game->win, 20, 30, 0xFFFF00, str);
	free(str);
	free(count);
	return (1);
}

int memory_for_score(char *str, t_game *game, char *count)
{
	str = malloc(sizeof(char) * 3);
	if (!str)
	{
		ft_printf("Error: Memory allocation failed\n");
		key_input(53, game);
	}
	count = ft_itoa(game->moment_count);
	if (!count)
	{
		free(str);
		ft_printf("Error: Memory allocation failed\n");
		key_input(53, game);
	}
	return (1);
}
