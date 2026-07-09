/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:21:01 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:21:03 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	reach_wall(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (true);
	if (map_x >= game->map->width || map_y >= game->map->height)
		return (true);
	if (game->map->grid[map_y][map_x] == '1')
		return (true);
	return (false);
}

void	safe_move(t_game *game, double nx, double ny)
{
	double	secure;
	int		check_x;
	int		check_y;

	secure = 0.001;
	if (ny < game->py)
		check_y = (int)(ny - secure);
	else
		check_y = (int)ny;
	if (nx < game->px)
		check_x = (int)(nx - secure);
	else
		check_x = (int)nx;
	if (!reach_wall(game, check_x, check_y)
		&& !reach_wall(game, (int)game->px, check_y)
		&& !reach_wall(game, check_x, (int)game->py))
	{
		game->px = nx;
		game->py = ny;
	}
}
