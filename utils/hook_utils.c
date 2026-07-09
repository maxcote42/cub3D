/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:10:34 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:21:46 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	apply_rotation(t_game *game)
{
	if (game->keys.left)
		game->angle -= ROT_STEP;
	if (game->keys.right)
		game->angle += ROT_STEP;
	if (game->angle > 2 * M_PI)
		game->angle -= 2 * M_PI;
	if (game->angle < 0)
		game->angle += 2 * M_PI;
}

void	set_key_state(int keycode, t_game *game, bool state)
{
	if (keycode == XK_w)
		game->keys.w = state;
	else if (keycode == XK_a)
		game->keys.a = state;
	else if (keycode == XK_s)
		game->keys.s = state;
	else if (keycode == XK_d)
		game->keys.d = state;
	else if (keycode == XK_Left)
		game->keys.left = state;
	else if (keycode == XK_Right)
		game->keys.right = state;
}

static void	add_vector(double *dx, double *dy, double x, double y)
{
	*dx += x;
	*dy += y;
}

void	get_move_vector(t_game *game, double *dx, double *dy)
{
	double	norme;

	*dx = 0;
	*dy = 0;
	if (game->keys.w)
		add_vector(dx, dy, cos(game->angle), sin(game->angle));
	if (game->keys.s)
		add_vector(dx, dy, -cos(game->angle), -sin(game->angle));
	if (game->keys.d)
		add_vector(dx, dy, -sin(game->angle), cos(game->angle));
	if (game->keys.a)
		add_vector(dx, dy, sin(game->angle), -cos(game->angle));
	norme = sqrt((*dx) * (*dx) + (*dy) * (*dy));
	if (norme > 0)
	{
		*dx = *dx / norme * STEP;
		*dy = *dy / norme * STEP;
	}
}
