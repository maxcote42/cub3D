/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_texture_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:17:07 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:17:10 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	select_wall_texture(t_game *game, t_ray ray, t_image **tex,
		int *tex_h)
{
	if (game->map->grid[ray.mapy][ray.mapx] == '2')
	{
		*tex = &game->door_tex;
		*tex_h = game->door_h;
	}
	else
	{
		*tex = &game->text[ray.side];
		*tex_h = game->text_h[ray.side];
	}
}
