/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:20:38 by maxcote           #+#    #+#             */
/*   Updated: 2026/07/07 12:34:42 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	init_delta(t_ray *ray)
{
	if (ray->dirx == 0)
		ray->deltax = 1e30;
	else
		ray->deltax = fabs(1 / ray->dirx);
	if (ray->diry == 0)
		ray->deltay = 1e30;
	else
		ray->deltay = fabs(1 / ray->diry);
}

static void	init_ray(t_ray *ray, t_game *game)
{
	ray->mapx = (int)game->px;
	ray->mapy = (int)game->py;
	if ((ray->dirx) > 0)
		ray->stepx = 1;
	else
		ray->stepx = -1;
	if ((ray->diry) > 0)
		ray->stepy = 1;
	else
		ray->stepy = -1;
	init_delta(ray);
	if (ray->stepx == 1)
		ray->nextx = ((ray->mapx + 1) - game->px) * ray->deltax;
	else
		ray->nextx = (game->px - ray->mapx) * ray->deltax;
	if (ray->stepy == 1)
		ray->nexty = ((ray->mapy + 1) - game->py) * ray->deltay;
	else
		ray->nexty = (game->py - ray->mapy) * ray->deltay;
}

static void	cast_ray(t_camera *camera, t_ray *ray, int col, t_game *game)
{
	double	camerax;

	ray->side = 0;
	camerax = 2.0 * col / (SCREEN_X - 1.0) - 1.0;
	ray->dirx = camera->dirx + camera->planex * camerax;
	ray->diry = camera->diry + camera->planey * camerax;
	init_ray(ray, game);
}

static void	init_camera(t_camera *camera, t_game *game)
{
	game->tan_fov = tan(FOV / 2.0);
	camera->dirx = cos(game->angle);
	camera->diry = sin(game->angle);
	camera->planex = -camera->diry * game->tan_fov;
	camera->planey = camera->dirx * game->tan_fov;
}

void	trace_3d(t_game *game)
{
	t_camera	camera;
	t_ray		ray;
	int			col;
	double		distance;

	ft_memset(&ray, 0, sizeof(t_ray));
	ft_memset(&camera, 0, sizeof(t_camera));
	init_camera(&camera, game);
	col = 0;
	while (col < SCREEN_X)
	{
		cast_ray(&camera, &ray, col, game);
		distance = run_dda(game, &ray);
		draw_col(game, col, distance, ray);
		col++;
	}
}
