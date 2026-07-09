/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 03:25:32 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:33:32 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	perp_dist(t_game *game, t_ray *ray)
{
	if (ray->side == TEXT_WE || ray->side == TEXT_EA)
	{
		ray->perpwalldist = (ray->mapx - game->px
				+ (1 - ray->stepx) / 2.0) / ray->dirx;
		ray->wall_hit = game->py + ray->perpwalldist * ray->diry;
	}
	else
	{
		ray->perpwalldist = (ray->mapy - game->py
				+ (1 - ray->stepy) / 2.0) / ray->diry;
		ray->wall_hit = game->px + ray->perpwalldist * ray->dirx;
	}
	ray->wall_hit -= floor(ray->wall_hit);
}

double	run_dda(t_game *game, t_ray *ray)
{
	while (!reach_wall(game, ray->mapx, ray->mapy))
	{
		if (ray->nextx < ray->nexty)
		{
			ray->mapx += ray->stepx;
			ray->nextx += ray->deltax;
			if (ray->stepx == 1)
				ray->side = TEXT_EA;
			else
				ray->side = TEXT_WE;
		}
		else
		{
			ray->mapy += ray->stepy;
			ray->nexty += ray->deltay;
			if (ray->stepy == 1)
				ray->side = TEXT_SO;
			else
				ray->side = TEXT_NO;
		}
	}
	perp_dist(game, ray);
	return (ray->perpwalldist);
}
