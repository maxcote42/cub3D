/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:55:37 by maxcote           #+#    #+#             */
/*   Updated: 2026/07/06 15:06:11 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	trace_frame(t_game *game)
{
	int	x;
	int	y;

	x = 20;
	while (x <= 199)
	{
		y = 20;
		while (y <= 199)
		{
			add_pixel(&game->image, x, y, 0x001c140a);
			y++;
		}
		x++;
	}
}

static void	trace_map(t_game *game)
{
	int		x;
	int		y;
	int		map_x;
	int		map_y;

	x = 25;
	while (x <= 194)
	{
		y = 25;
		while (y <= 194)
		{
			map_x = (int)(game->px + ((double)(x - 110) / 10.0));
			map_y = (int)(game->py + ((double)(y - 110) / 10.0));
			if (reach_wall(game, map_x, map_y))
				add_pixel(&game->image, x, y, 0x000f0b05);
			else if (!game->map->grid[map_y][map_x]
				|| game->map->grid[map_y][map_x] == ' ')
				add_pixel(&game->image, x, y, 0x000f0b05);
			else
				add_pixel(&game->image, x, y, 0x008f877c);
			y++;
		}
		x++;
	}
}

static void	draw_direction(t_game *game)
{
	double	x;
	double	y;
	double	step;

	x = 110;
	y = 110;
	step = 0;
	while (step < 20)
	{
		add_pixel(&game->image, (int)x, (int)y, 0x00b05757);
		x += cos(game->angle);
		y += sin(game->angle);
		step++;
	}
}

static void	trace_player(t_game *game)
{
	int	x;
	int	y;

	x = 109;
	while (x <= 111)
	{
		y = 109;
		while (y <= 111)
		{
			add_pixel(&game->image, x, y, 0x00ff5858);
			y++;
		}
		x++;
	}
}

void	trace_minimap(t_game *game)
{
	trace_frame(game);
	trace_map(game);
	trace_player(game);
	draw_direction(game);
}
