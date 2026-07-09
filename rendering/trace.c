/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevenfeijoeiro <stevenfeijoeiro@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 17:11:32 by maxcote           #+#    #+#             */
/*   Updated: 2026/07/03 14:20:04 by stevenfeijo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	add_pixel(t_image *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= SCREEN_X || y >= SCREEN_Y)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	trace(t_game *game)
{
	trace_3d(game);
	trace_minimap(game);
	draw_hand(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
}
