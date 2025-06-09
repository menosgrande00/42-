/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:06:45 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 15:15:37 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_tmp_map(char **tmp_map, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(tmp_map[i]);
		i++;
	}
	free(tmp_map);
	return (0);
}

int	read_map_lines(int fd, char **map, char **tmp_map)
{
	char	*line;
	int		line_count;

	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line[ft_strcspn(line, "\n")] = 0;
		map[line_count] = line;
		tmp_map[line_count] = ft_strdup(line);
		if (!tmp_map[line_count])
		{
			free_tmp_map(tmp_map, line_count);
			return (0);
		}
		line_count++;
		line = get_next_line(fd);
	}
	map[line_count] = NULL;
	tmp_map[line_count] = NULL;
	return (line_count);
}

int	allocate_maps(char ***map, char ***tmp_map, int line_count, int fd)
{
	*map = malloc(sizeof(char *) * (line_count + 1));
	if (!*map)
	{
		close(fd);
		write(2, "Memory allocation failed\n", 25);
		return (0);
	}
	*tmp_map = malloc(sizeof(char *) * (line_count + 1));
	if (!*tmp_map)
	{
		free(*map);
		close(fd);
		write(2, "Memory allocation failed\n", 25);
		return (0);
	}
	return (1);
}

int	line_counter(int fd)
{
	int		line_count;
	char	*line;

	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	return (line_count);
}

int	open_map_file(const char *filename, int *fd, int *line_count)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		write(2, "Cannot open map file\n", 21);
		return (0);
	}
	*line_count = line_counter(*fd);
	close(*fd);
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		write(2, "Cannot open map file\n", 21);
		return (0);
	}
	return (1);
}
