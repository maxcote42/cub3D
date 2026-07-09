/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:54:21 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/06 15:46:02 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// jarriv pas a mettre le header mdr

#include "../cub3D.h"

bool	init_hand(t_game *game)
{
	char	*hand_paths[HAND_FRAMES];
	int		i;

	hand_paths[0] = "bonus/hand0.xpm";
	hand_paths[1] = "bonus/hand1.xpm";
	hand_paths[2] = "bonus/hand2.xpm";
	hand_paths[3] = "bonus/hand3.xpm";
	hand_paths[4] = "bonus/hand4.xpm";
	i = 0;
	while (i < HAND_FRAMES)
	{
		game->hand[i].img = mlx_xpm_file_to_image(game->mlx,
				hand_paths[i], &game->hand_w[i], &game->hand_h[i]);
		if (!game->hand[i].img)
			return (ft_puterr("Failed to load hand sprite"), false);
		game->hand[i].addr = mlx_get_data_addr(game->hand[i].img,
				&game->hand[i].bpp,
				&game->hand[i].line_len,
				&game->hand[i].endian);
		i++;
	}
	game->hand_frame = 0;
	game->hand_count = 0;
	return (true);
}

void	update_hand_anim(t_game *game)
{
	game->hand_count++;
	if (game->hand_count >= HAND_SPEED)
	{
		game->hand_count = 0;
		game->hand_frame = (game->hand_frame + 1) % HAND_FRAMES;
	}
}

static int	get_hand_pixel(t_image *sprite, int x, int y)
{
	char	*pixel;

	pixel = sprite->addr + (y * sprite->line_len + x * (sprite->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	draw_hand(t_game *game)
{
	t_image	*sprite;
	int		x_off;
	int		y_off;
	int		x;
	int		y;

	sprite = &game->hand[game->hand_frame];
	x_off = SCREEN_X / 8 - game->hand_w[game->hand_frame] / 8;
	y_off = SCREEN_Y - game->hand_h[game->hand_frame];
	y = -1;
	while (++y < game->hand_h[game->hand_frame])
	{
		x = -1;
		while (++x < game->hand_w[game->hand_frame])
		{
			if (get_hand_pixel(sprite, x, y) != HAND_BACK)
				add_pixel(&game->image, x_off + x, y_off + y,
					get_hand_pixel(sprite, x, y));
		}
	}
}
