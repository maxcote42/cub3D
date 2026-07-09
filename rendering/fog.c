/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 03:25:51 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:34:26 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double	get_fog(double distance)
{
	double	fog;

	fog = 1.0 - (distance / FOG_DIST_MAX);
	if (fog < FOG_MIN)
		fog = FOG_MIN;
	if (fog > 1.0)
		fog = 1.0;
	return (fog);
}

int	apply_fog(int color, double fog)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * fog);
	g = (int)(((color >> 8) & 0xFF) * fog);
	b = (int)((color & 0xFF) * fog);
	return ((r << 16) | (g << 8) | b);
}

double	get_fc_fog(int i)
{
	double	d;

	d = fabs(i - SCREEN_Y / 2.0);
	if (d < 1.0)
		d = 1.0;
	return (get_fog((SCREEN_Y / 2.0) / d));
}

void	init_fc_fog_table(t_game *game)
{
	int		i;
	double	fog;

	i = 0;
	while (i < SCREEN_Y)
	{
		fog = get_fc_fog(i);
		game->ceil_fog_table[i] = apply_fog(game->ceil_color, fog);
		game->floor_fog_table[i] = apply_fog(game->floor_color, fog);
		i++;
	}
}
