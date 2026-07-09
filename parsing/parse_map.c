/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:42:28 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/06 17:21:47 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	correct_elements(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = -1;
	while (map->grid[++y])
	{
		x = -1;
		while (map->grid[y][++x])
		{
			if (correct_char(map->grid[y][x], map, y, x) == -1)
				return (ft_puterr("Invalid character in map"));
			else if (correct_char(map->grid[y][x], map, y, x) == 1)
			{
				player_count++;
				map->player_x = x;
				map->player_y = y;
				map->player_dir = map->grid[y][x];
			}
		}
	}
	if (player_count != 1)
		return (ft_puterr("Map must have exactly one player"));
	return (true);
}

bool	is_valid_neighbor(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return (false);
	if (x < 0 || x >= (int)ft_strlen(map->grid[y]))
		return (false);
	if (map->grid[y][x] == ' ')
		return (false);
	return (true);
}

bool	is_enclosed(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] != '1' && map->grid[y][x] != ' ')
			{
				if (is_valid_neighbor(map, x, y - 1) == false)
					return (ft_puterr("Map is not enclosed"));
				if (is_valid_neighbor(map, x, y + 1) == false)
					return (ft_puterr("Map is not enclosed"));
				if (is_valid_neighbor(map, x - 1, y) == false)
					return (ft_puterr("Map is not enclosed"));
				if (is_valid_neighbor(map, x + 1, y) == false)
					return (ft_puterr("Map is not enclosed"));
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	pad_line(t_map *map, int y)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char) * (map->width + 1));
	if (!new_line)
		return (false);
	i = 0;
	while (map->grid[y][i])
	{
		new_line[i] = map->grid[y][i];
		i++;
	}
	while (i < map->width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[map->width] = '\0';
	free(map->grid[y]);
	map->grid[y] = new_line;
	return (true);
}

bool	pad_grid(t_map *map)
{
	int	y;

	y = 0;
	while (map->grid[y])
	{
		if ((int)ft_strlen(map->grid[y]) < map->width)
		{
			if (pad_line(map, y) == false)
				return (false);
		}
		y++;
	}
	return (true);
}
