/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:59:57 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 02:53:21 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return (false);
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	return (false);
}

bool	free_map(t_map *map)
{
	if (map->file)
		free_grid(map->file);
	if (map->grid)
		free_grid(map->grid);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map)
		free(map);
	return (false);
}

bool	is_wall_or_floor(char c)
{
	if (c == '0' || c == '1')
		return (true);
	return (false);
}

int	correct_char(char c, t_map *map, int y, int x)
{
	if (c == '2' && is_wall_or_floor(map->grid[y][x - 1])
		&& is_wall_or_floor(map->grid[y][x + 1])
		&& is_wall_or_floor(map->grid[y - 1][x])
		&& is_wall_or_floor(map->grid[y + 1][x]))
		return (0);
	if (c == '0' || c == '1' || c == ' ')
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (-1);
}
