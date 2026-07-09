/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_char_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:19:47 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:19:50 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static bool	is_wall_or_floor(char c)
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
