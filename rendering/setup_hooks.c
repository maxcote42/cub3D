/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:21:57 by maxcote           #+#    #+#             */
/*   Updated: 2026/07/07 12:23:11 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	handle_cross(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
		mlx_destroy_image(game->mlx, game->text[i++].img);
	mlx_destroy_image(game->mlx, game->image.img);
	free_bonus_resources(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(game->map);
	exit(0);
}

static int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		handle_cross(game);
	if (keycode == XK_space)
		toggle_door(game);
	set_key_state(keycode, game, true);
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	set_key_state(keycode, game, false);
	return (0);
}

static int	game_loop(t_game *game)
{
	double	dx;
	double	dy;

	update_hand_anim(game);
	if (game->keys.w || game->keys.a || game->keys.s || game->keys.d)
	{
		get_move_vector(game, &dx, &dy);
		safe_move(game, game->px + dx, game->py + dy);
	}
	apply_rotation(game);
	trace(game);
	return (OK);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, (int (*)())handle_cross, game);
	mlx_hook(game->win, 2, 1, (int (*)())key_press, game);
	mlx_hook(game->win, 3, 2, (int (*)())key_release, game);
	setup_bonus_hooks(game);
	mlx_loop_hook(game->mlx, (int (*)())game_loop, game);
}
