/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:18:31 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:18:36 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	handle_mouse(int x, int y, t_game *game)
{
	if (y != -1)
		game->angle += (x - game->mouse_x) * 0.05;
	game->mouse_x = x;
	return (OK);
}

void	setup_bonus_hooks(t_game *game)
{
	mlx_hook(game->win, 6, 1L << 6, (int (*)())handle_mouse, game);
}
