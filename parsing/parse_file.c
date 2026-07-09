/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 01:45:24 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 18:35:51 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	count_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

bool	read_file(t_map *map, char *path)
{
	int		count;
	int		i;
	char	*line;

	count = count_lines(path);
	if (count <= 0)
		return (false);
	map->file = ft_calloc(count + 1, sizeof(char *));
	if (!map->file)
		return (false);
	map->fd = open(path, O_RDONLY);
	if (map->fd == -1)
		return (false);
	i = 0;
	line = get_next_line(map->fd);
	while (line)
	{
		if (line[(int)ft_strlen(line) - 1] == '\n')
			line[(int)ft_strlen(line) - 1] = '\0';
		map->file[i++] = line;
		line = get_next_line(map->fd);
	}
	map->file[i] = NULL;
	close(map->fd);
	return (true);
}

static bool	fill_map_grid(t_map *map)
{
	int	i;
	int	j;

	i = map->map_start - 1;
	j = 0;
	while (map->file[++i])
	{
		if (map->file[i][0] == '\0')
			return (ft_puterr("Empty line in map"));
		map->grid[j] = ft_strdup(map->file[i]);
		if (!map->grid[j])
			return (false);
		if ((int)ft_strlen(map->grid[j]) > map->width)
			map->width = (int)ft_strlen(map->grid[j]);
		if (map->width > MAX_MAP_SIZE)
			return (ft_puterr("Map is too large (max 500x500)"));
		j++;
	}
	map->grid[j] = NULL;
	return (true);
}

bool	read_map(t_map *map)
{
	int	i;

	i = map->map_start;
	while (map->file[i] && map->file[i][0] != '\0')
		i++;
	map->height = i - map->map_start;
	if (map->height > MAX_MAP_SIZE)
		return (ft_puterr("Map is too large (max 500x500)"));
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (false);
	return (fill_map_grid(map));
}
