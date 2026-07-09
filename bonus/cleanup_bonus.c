/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:19:07 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:19:10 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_bonus_resources(t_game *game)
{
	int	i;

	i = 0;
	while (i < HAND_FRAMES)
		mlx_destroy_image(game->mlx, game->hand[i++].img);
	mlx_destroy_image(game->mlx, game->door_tex.img);
}
